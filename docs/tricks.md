# 小技巧与快捷函数

这些内容比“再背一个大算法”更常直接减少罚时。只把真正会反复使用的函数放进个人骨架。

## 1. 推荐基础定义

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int INF = 0x3f3f3f3f;
const ll LINF = 4e18;
```

不要无条件 `#define int long long`：它会改变容器内存、函数重载和 `main` 类型。真正可能溢出的量单独用 `long long`。

## 2. `chmin` / `chmax`

```cpp
template<class T>
bool chmin(T &a, const T &b) {
    if (b < a) return a = b, true;
    return false;
}

template<class T>
bool chmax(T &a, const T &b) {
    if (a < b) return a = b, true;
    return false;
}
```

返回值表示是否真的发生松弛，可直接用于队列入队、记录前驱或提前停止。

## 3. 数学意义的整除取整

C++ 整数除法向 0 取整，不等于负数上的 floor：

```cpp
ll floor_div(ll a, ll b) {
    assert(b > 0);
    ll q = a / b, r = a % b;
    return q - (r < 0);
}

ll ceil_div(ll a, ll b) {
    assert(b > 0);
    ll q = a / b, r = a % b;
    return q + (r > 0);
}
```

只处理非负整数时，`ceil(a / b)` 可写成 `a / b + (a % b != 0)`，比 `(a+b-1)/b` 更不容易加法溢出。

## 4. 安全整数开方

```cpp
ll isqrt(ll x) {
    ll r = sqrtl((long double)x);
    while ((i128)(r + 1) * (r + 1) <= x) ++r;
    while ((i128)r * r > x) --r;
    return r;
}
```

浮点只负责给近似值，最后必须在整数域校正。

## 5. `__int128` 输出

```cpp
void print_i128(i128 x) {
    if (x < 0) cout << '-', x = -x;
    if (x >= 10) print_i128(x / 10);
    cout << char('0' + x % 10);
}
```

触发场景：两个 `long long` 相乘、坐标叉积、CRT 合并模数、直线代入和可能超过 `9e18` 的答案。

## 6. 二分只保留两种写法

找第一个满足 `check(x)` 的整数：

```cpp
ll l = low, r = high;
while (l < r) {
    ll mid = l + (r - l) / 2;
    if (check(mid)) r = mid;
    else l = mid + 1;
}
```

找最后一个满足 `check(x)` 的整数：

```cpp
ll l = low, r = high;
while (l < r) {
    ll mid = l + (r - l + 1) / 2;
    if (check(mid)) l = mid;
    else r = mid - 1;
}
```

不要临场混用开区间/闭区间版本。先写清 `check` 的真假分界和无解时返回什么。

## 7. STL 边界速查

```cpp
sort(a.begin(), a.end());
a.erase(unique(a.begin(), a.end()), a.end());

int ge = lower_bound(a.begin(), a.end(), x) - a.begin(); // 第一个 >= x
int gt = upper_bound(a.begin(), a.end(), x) - a.begin(); // 第一个 > x
int count_x = gt - ge;

priority_queue<int> big;
priority_queue<int, vector<int>, greater<int>> small;
```

`lower_bound` 依赖有序区间。离散化后交给 Fenwick 时通常再 `+1`，因为树状数组下标不能为 0。

## 8. 自定义排序别写减法

```cpp
sort(a.begin(), a.end(), [](const Node &x, const Node &y) {
    if (x.key != y.key) return x.key < y.key;
    return x.id < y.id;
});
```

不要写 `return x.key - y.key < 0`，差值本身可能溢出。比较器必须满足严格弱序，不能写 `<=`。

## 9. 位运算

```cpp
int lowbit(int x) { return x & -x; }

__builtin_popcount(x);
__builtin_popcountll(x);
__builtin_ctzll(x); // x 必须非 0
__builtin_clzll(x); // x 必须非 0

bool has = mask >> k & 1;
mask |= 1LL << k;
mask &= ~(1LL << k);
mask ^= 1LL << k;

for (int sub = mask; sub; sub = (sub - 1) & mask) {
    // mask 的所有非空子集
}
```

`1 << k` 的 1 是 32 位 `int`；`k >= 31` 时必须写 `1LL << k`。空子集要单独处理。

## 10. 背包循环方向

```cpp
// 0/1 背包：同一件物品只能用一次，容量倒序。
for (int j = V; j >= w; --j) chmax(f[j], f[j - w] + val);

// 完全背包：允许重复使用，容量正序。
for (int j = w; j <= V; ++j) chmax(f[j], f[j - w] + val);
```

如果状态是“恰好装满”，除 `f[0]=0` 外应初始化为负无穷；如果是“不超过容量”，通常初始化为 0。

## 11. 递归 Lambda

```cpp
auto dfs = [&](auto &&self, int x, int fa) -> void {
    for (int y : e[x]) {
        if (y == fa) continue;
        self(self, y, x);
    }
};
dfs(dfs, 1, 0);
```

适合只在 `solve()` 内使用的小 DFS。需要互相递归或函数很长时，普通函数更清晰。

## 12. 随机数与防卡哈希

```cpp
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t seed =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + seed);
    }
};
```

本地随机对拍要固定 seed，方便复现；比赛中防恶意哈希才使用时间 seed。

## 13. 图论建图纪律

- 无向边加两次；网络流反向边初始容量通常为 0。
- Floyd 读重边取最小，`k` 放最外层。
- Dijkstra 不能有负边；0-1 BFS 只允许 0/1 权。
- 需要输出路径时，每次松弛成功同步记录 `pre[y]=x`。
- Tarjan 处理无向重边时使用边编号，不只判断 `y != parent`。
- 多测题要清空邻接表、时间戳、访问数组和节点池指针。

## 14. 懒标记先写复合表

01 序列的赋值与翻转：

| 旧标记 | 新 `set(v)` | 新 `reverse` |
|---|---|---|
| 无 | `set(v)` | `reverse` |
| `set(old)` | `set(v)` | `set(old xor 1)` |
| `reverse` | `set(v)` | 两次翻转抵消 |

始终区分：`apply` 改当前节点和标记，`down` 传给孩子，`up` 只从孩子合并。

## 15. 调试宏

```cpp
#ifdef LOCAL
#define debug(x) cerr << #x << " = " << (x) << '\n'
#else
#define debug(x) ((void)0)
#endif
```

本地用 `-DLOCAL` 编译，调试信息写 `cerr`。提交前不要靠手删调试输出，交给宏控制。

## 16. 推荐本地编译参数

```bash
g++ -std=c++17 -O2 -Wall -Wextra -Wshadow -DLOCAL main.cpp
```

出现运行时错误时再用：

```bash
g++ -std=c++17 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer main.cpp
```

Sanitizer 版只用于本地调试，不要提交到评测机。

## 17. 随机对拍最小闭环

1. 写只能跑小数据的暴力解。
2. 固定随机种子生成边界与随机数据。
3. 同一输入分别运行暴力和正解。
4. 发现不同就完整保存输入并停止。
5. 先把失败数据加入回归，再修改正解。

本仓库的 [random_check.py](../scripts/random_check.py) 已覆盖复杂 01 线段树、主席树、2-SAT、SOS DP、带权并查集和后缀数组。

## 18. 提交前 30 秒

- 数组是 `n+5`、`4n` 还是 `n log n`？多测清空了吗？
- 输入是 0 下标还是 1 下标？闭区间还是半开区间？
- 答案、距离、区间和、乘法中间量会溢出吗？
- 取模减法是否为负？逆元前提成立吗？
- 图是有向还是无向？有负边、重边、自环、断图吗？
- 二分无解返回什么？`check` 的方向一致吗？
- 构造题是否逐条验证了输出限制？
- 输出格式、精度、空格和换行符合题意吗？
