// Andrew 凸包：整数点，去除共线边上的中间点，逆时针输出凸包。
// 复杂度 O(n log n)。叉积使用 __int128 防止 long long 乘法溢出。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
    bool operator<(const Point &o) const { return x != o.x ? x < o.x : y < o.y; }
    bool operator==(const Point &o) const { return x == o.x && y == o.y; }
};

__int128 cross(Point a, Point b, Point c) {
    return (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
}

vector<Point> convex_hull(vector<Point> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    if (p.size() <= 1) return p;
    vector<Point> h;
    for (Point x : p) {
        while (h.size() >= 2 && cross(h[h.size() - 2], h.back(), x) <= 0) h.pop_back();
        h.push_back(x);
    }
    size_t lower = h.size();
    for (int i = (int)p.size() - 2; i >= 0; i--) {
        Point x = p[i];
        while (h.size() > lower && cross(h[h.size() - 2], h.back(), x) <= 0) h.pop_back();
        h.push_back(x);
    }
    h.pop_back();
    return h;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto &[x, y] : p) cin >> x >> y;
    vector<Point> h = convex_hull(p);
    cout << h.size() << '\n';
    for (auto [x, y] : h) cout << x << ' ' << y << '\n';
    return 0;
}
