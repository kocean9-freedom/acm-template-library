// 单调队列：输出每个长度为 k 的滑动窗口最小值和最大值。
// 复杂度 O(n)，每个元素至多进出队各一次。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;
int n, k, a[MAXN];

vector<int> work(bool get_max) {
    deque<int> q;
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && q.front() <= i - k) q.pop_front();
        while (!q.empty() && (get_max ? a[q.back()] <= a[i] : a[q.back()] >= a[i])) {
            q.pop_back();
        }
        q.push_back(i);
        if (i >= k) ans.push_back(a[q.front()]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int x : work(false)) cout << x << ' ';
    cout << '\n';
    for (int x : work(true)) cout << x << ' ';
    cout << '\n';
    return 0;
}
