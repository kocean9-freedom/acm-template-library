# 小技巧与快捷函数

## 最值得放进个人骨架的函数

```cpp
using ll = long long;
using i128 = __int128_t;

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

// b > 0；C++ 的整数除法向 0 取整，这两个函数是数学取整。
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

ll isqrt(ll x) {
    ll r = sqrtl((long double)x);
    while ((i128)(r + 1) * (r + 1) <= x) ++r;
    while ((i128)r * r > x) --r;
    return r;
}

ll norm(ll x, ll mod) { return (x % mod + mod) % mod; }
```

`chmin/chmax` 的返回值能直接表示是否发生松弛。整数开方必须在浮点答案附近校正。

## `__int128` 输入输出

```cpp
using i128 = __int128_t;

i128 read_i128() {
    string s;
    cin >> s;
    int i = 0, sign = 1;
    if (s[0] == '-') sign = -1, i = 1;
    i128 x = 0;
    for (; i < (int)s.size(); ++i) x = x * 10 + s[i] - '0';
    return x * sign;
}

void print_i128(i128 x) {
    if (x < 0) cout << '-', x = -x;
    if (x >= 10) print_i128(x / 10);
    cout << char('0' + x % 10);
}
```

触发条件：两个 `long long` 相乘、坐标叉积、模乘或答案可能超过 `9e18`。

## STL 速查

```cpp
sort(a.begin(), a.end());
a.erase(unique(a.begin(), a.end()), a.end());

int ge = lower_bound(a.begin(), a.end(), x) - a.begin(); // 第一个 >= x
int gt = upper_bound(a.begin(), a.end(), x) - a.begin(); // 第一个 > x
int count_x = gt - ge;

priority_queue<int> big;
priority_queue<int, vector<int>, greater<int>> small;
```

`lower_bound` 依赖区间有序。离散值若交给树状数组，排名必须从 1 开始。

## 位运算速查

```cpp
int lowbit(int x) { return x & -x; }

__builtin_popcount(x);
__builtin_popcountll(x);
__builtin_ctz(x); // x 必须非 0
__builtin_clz(x); // x 必须非 0

bool has = mask >> k & 1;
mask |= 1LL << k;
mask &= ~(1LL << k);
mask ^= 1LL << k;

for (int sub = mask; sub; sub = (sub - 1) & mask) {
    // 枚举 mask 的所有非空子集
}
```

`1 << k` 的 1 是 `int`，当 `k >= 31` 时必须写 `1LL << k`。

## 背包循环方向

```cpp
// 0/1 背包：倒序，同一件物品只能使用一次。
for (int j = V; j >= w; --j) chmax(f[j], f[j - w] + val);

// 完全背包：正序，允许重复使用。
for (int j = w; j <= V; ++j) chmax(f[j], f[j - w] + val);
```

## 图论建图习惯

- 无向边要加两次；网络流反向边的初始容量通常是 0。
- Floyd 读重边必须取最小；邻接表最短路可以自然松弛重边。
- 距离数组用 `long long`，判断不是 `INF` 后再相加。
- 需要输出路径时，在松弛成功的分支同步记录 `pre[y]=x`。
- 深度可能达到 `2e5` 时，递归 DFS 有爆栈风险，可改成显式栈。

## 懒标记先写复合表

复杂线段树动手前，先写新操作如何作用于旧标记。01 序列的规则是：

| 旧标记 | 新 `set(v)` | 新 `reverse` |
|---|---|---|
| 无 | `set(v)` | `reverse` |
| `set(old)` | `set(v)` | `set(old xor 1)` |
| `reverse` | `set(v)` | 两次翻转抵消 |

始终区分：`apply` 修改当前节点信息与标记，`down` 把标记传给孩子，`up` 只从孩子合并。

## 调试宏

```cpp
#ifdef LOCAL
#define debug(x) cerr << #x << " = " << (x) << '\n'
#else
#define debug(x) ((void)0)
#endif
```

本地使用 `-DLOCAL` 编译。调试信息写 `cerr`，不要污染标准输出。

## 随机对拍最小流程

1. 写一个只支持小数据的暴力解法。
2. 固定随机种子，生成几百组边界和随机数据。
3. 同一输入分别运行暴力与正解，比较输出。
4. 出错时打印完整输入，先固定为回归样例，再改正解。

仓库的 `scripts/random_check.py` 已对复杂 01 线段树、主席树和 2-SAT 做固定种子随机对拍。

## 交题前 30 秒检查表

- 数组是否开到 `n+5`、`4n` 或 `n log n`？多测是否清空？
- 输入是 0 下标还是 1 下标？区间是闭区间还是半开区间？
- 答案、距离、区间和与乘法中间量会不会溢出？
- 取模减法是否变成负数？逆元前提是否成立？
- 图是有向还是无向？是否有负边、重边、自环、断图？
- 二分无解时返回什么？`check` 的真假方向是否一致？
- 输出格式、精度、换行是否符合题意？

## 赛场建议

- 签到题优先使用 STL 和短函数，不要为了套模板写更重的数据结构。
- 铜牌模板要练到不看代码也能说出状态含义与复杂度。
- 银牌题先写不变量、懒标记复合或 DP 状态，再开始敲代码。
- 模板通过样例不代表建模正确：先检查题目是否满足模板前提。
