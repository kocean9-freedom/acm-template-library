// 单调栈：对每个位置求左侧最近的严格更大元素下标，不存在输出 0。
// 栈内值严格递减；每个下标至多进出一次。复杂度 O(n)。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n + 1);
    vector<int> st;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
        cout << (st.empty() ? 0 : st.back()) << " \n"[i == n];
        st.push_back(i);
    }
    return 0;
}
