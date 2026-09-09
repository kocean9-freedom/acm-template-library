// 字典树：插入小写字符串，查询某字符串完整出现次数。
// 复杂度 O(字符串总长度)，空间 O(字符总数*26)。
#include <bits/stdc++.h>
using namespace std;

const int MAXS = 1e6 + 5;
int tr[MAXS][26], cnt[MAXS], tot;

void insert(const string &s) {
    int p = 0;
    for (char c : s) {
        int x = c - 'a';
        if (!tr[p][x]) tr[p][x] = ++tot;
        p = tr[p][x];
    }
    cnt[p]++;
}

int query(const string &s) {
    int p = 0;
    for (char c : s) {
        int x = c - 'a';
        if (!tr[p][x]) return 0;
        p = tr[p][x];
    }
    return cnt[p];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    while (n--) {
        string s;
        cin >> s;
        insert(s);
    }
    while (q--) {
        string s;
        cin >> s;
        cout << query(s) << '\n';
    }
    return 0;
}
