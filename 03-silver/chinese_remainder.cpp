// 广义 CRT：合并 x ≡ r[i] (mod m[i])，模数不要求互质。
// 每次用 exgcd 解线性同余；无解输出 -1，否则输出最小非负解及合并模数。O(n log M)。
#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;

i128 exgcd(i128 a, i128 b, i128 &x, i128 &y) {
    if (!b) return x = 1, y = 0, a;
    i128 x1, y1;
    i128 g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}

i128 norm(i128 x, i128 mod) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

void print_i128(i128 x) {
    if (x < 0) cout << '-', x = -x;
    if (x >= 10) print_i128(x / 10);
    cout << char('0' + x % 10);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    i128 r = 0, mod = 1;
    for (int i = 0; i < n; i++) {
        long long ri0, mi0;
        cin >> ri0 >> mi0;
        i128 ri = ri0, mi = mi0, x, y;
        i128 g = exgcd(mod, mi, x, y);
        i128 diff = ri - r;
        if (diff % g) {
            cout << -1 << '\n';
            return 0;
        }
        i128 step_mod = mi / g;
        i128 k = norm(diff / g * x, step_mod);
        r += mod * k;
        mod = mod / g * mi;
        r = norm(r, mod);
    }
    print_i128(r);
    cout << ' ';
    print_i128(mod);
    cout << '\n';
    return 0;
}
