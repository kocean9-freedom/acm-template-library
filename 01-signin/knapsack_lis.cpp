// 入门 DP 快捷函数：0/1 背包与严格递增 LIS。
// knapsack: O(nV)，lis: O(n log n)。本文件作为函数板，main 留空。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll knapsack01(const vector<int> &w, const vector<ll> &v, int V) {
    vector<ll> f(V + 1);
    for (int i = 0; i < (int)w.size(); i++) {
        for (int j = V; j >= w[i]; j--) {
            f[j] = max(f[j], f[j - w[i]] + v[i]);
        }
    }
    return *max_element(f.begin(), f.end());
}

int lis(const vector<int> &a) {
    vector<int> d;
    for (int x : a) {
        auto it = lower_bound(d.begin(), d.end(), x);
        if (it == d.end()) d.push_back(x);
        else *it = x;
    }
    return (int)d.size();
}

int main() {
    return 0;
}
