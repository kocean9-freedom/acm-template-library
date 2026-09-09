// 二分答案工具：查找有序数组中第一个 >= x 的位置。
// 若不存在输出 n+1；下标从 1 开始。复杂度 O(log n)。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
int n, q, a[MAXN];

int first_ge(int x) {
    int l = 1, r = n, ans = n + 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] >= x) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    while (q--) {
        int x;
        cin >> x;
        cout << first_ge(x) << '\n';
    }
    return 0;
}
