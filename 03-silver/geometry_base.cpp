// 二维整数几何基础：向量、叉积、点在线段上、两闭线段是否相交。
// 叉积用 __int128 防止 long long 坐标相乘溢出。单次判断 O(1)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
using i128 = __int128_t;

struct Point {
    ll x, y;
    Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }
};

i128 cross(Point a, Point b) {
    return (i128)a.x * b.y - (i128)a.y * b.x;
}

i128 cross(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

int sign(i128 x) {
    return (x > 0) - (x < 0);
}

bool on_segment(Point p, Point a, Point b) {
    return cross(a, b, p) == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x)
           && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool intersect(Point a, Point b, Point c, Point d) {
    i128 c1 = cross(a, b, c), c2 = cross(a, b, d);
    i128 c3 = cross(c, d, a), c4 = cross(c, d, b);
    if (!c1 && on_segment(c, a, b)) return true;
    if (!c2 && on_segment(d, a, b)) return true;
    if (!c3 && on_segment(a, c, d)) return true;
    if (!c4 && on_segment(b, c, d)) return true;
    return sign(c1) * sign(c2) < 0 && sign(c3) * sign(c4) < 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        Point a, b, c, d;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
        cout << (intersect(a, b, c, d) ? "YES" : "NO") << '\n';
    }
    return 0;
}
