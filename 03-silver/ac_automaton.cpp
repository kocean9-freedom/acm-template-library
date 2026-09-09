// AC 自动机：统计有多少个模式串在文本中至少出现一次（重复模式串分别计数）。
// 构建与匹配近似 O(模式串总长+文本长+命中 fail 链)。
#include <bits/stdc++.h>
using namespace std;

const int MAXS = 1e6 + 5;
int tr[MAXS][26], fail_link[MAXS], cnt[MAXS], tot;

void insert(const string &s) {
    int p = 0;
    for (char c : s) {
        int x = c - 'a';
        if (!tr[p][x]) tr[p][x] = ++tot;
        p = tr[p][x];
    }
    cnt[p]++;
}

void build() {
    queue<int> q;
    for (int c = 0; c < 26; c++) if (tr[0][c]) q.push(tr[0][c]);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int c = 0; c < 26; c++) {
            int y = tr[x][c];
            if (y) {
                fail_link[y] = tr[fail_link[x]][c];
                q.push(y);
            } else {
                tr[x][c] = tr[fail_link[x]][c];
            }
        }
    }
}

int query(const string &s) {
    int p = 0, ans = 0;
    for (char c : s) {
        p = tr[p][c - 'a'];
        for (int x = p; x && cnt[x] != -1; x = fail_link[x]) {
            ans += cnt[x];
            cnt[x] = -1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        insert(s);
    }
    build();
    string text;
    cin >> text;
    cout << query(text) << '\n';
    return 0;
}
