// 线性基：维护一组数异或能得到的最大值。
// 插入/查询 O(B)，这里 B=63，支持非负 long long。
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

struct Basis {
    ull p[64]{};

    bool insert(ull x) {
        for (int i = 63; i >= 0; i--) {
            if (!(x >> i & 1)) continue;
            if (!p[i]) {
                p[i] = x;
                return true;
            }
            x ^= p[i];
        }
        return false;
    }

    ull get_max() const {
        ull ans = 0;
        for (int i = 63; i >= 0; i--) ans = max(ans, ans ^ p[i]);
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    Basis b;
    while (n--) {
        ull x;
        cin >> x;
        b.insert(x);
    }
    cout << b.get_max() << '\n';
    return 0;
}
