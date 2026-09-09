# 题面信号、思路与使用场景

这份指南回答四个问题：**什么时候想到它、它维护什么、复杂度是多少、最容易错在哪里**。例题主要选模板题，先独立写一遍，再对照源码复盘。

## 一眼选算法

| 题面信号 | 第一反应 |
|---|---|
| 多次问静态区间和 | 前缀和 |
| 多次区间加，最后统一输出 | 差分 |
| 连续区间 + 元素非负/性质随端点单调 | 双指针 / 滑动窗口 |
| “最大化最小值”“最小化最大值”且可行性单调 | 二分答案 |
| 值域到 `1e9/1e18`，只关心顺序 | 离散化 |
| 无权最少步数 | BFS |
| 单点修改 + 区间和 | 树状数组 |
| 区间修改 + 区间查询 | 懒标记线段树 |
| 静态区间 max/min/gcd | ST 表 |
| 非负权最短路 | Dijkstra |
| 只有 0/1 边权 | 0-1 BFS |
| 选边连通所有点且总权最小 | MST / Kruskal |
| 依赖关系、先后顺序 | 拓扑排序 |
| 树上两点公共祖先/距离 | LCA |
| 单模式串匹配 | KMP / Z |
| 多模式串匹配 | AC 自动机 |
| 有向图环互相可达、缩点后做 DP | SCC |
| 每个变量二选一，条件是“至少一个成立” | 2-SAT |
| 容量、分配、最少删边、二分图匹配 | 最大流 / 最小割 |
| 每单位流还有代价 | 最小费用最大流 |
| 树上路径反复修改/查询 | 树链剖分 |
| 静态区间第 k 小 | 主席树 |
| 静态区间询问，答案可 O(1) 增删端点 | 莫队 |
| 最大子集异或 | 线性基 |
| 统计 `[0,n]` 且条件与数位有关 | 数位 DP |

## 00 · 基础骨架

### [单题骨架](../00-basic/base.cpp)

- **思路**：把 I/O、多测循环和常用类型固定下来，现场只改 `solve()`。
- **场景**：所有题。多测题先确认每组数据是否需要清空全局状态。
- **坑**：`4e18` 只能安全放进 `long long`；加法前仍要防止 `INF + w` 溢出。
- **例题**：[Codeforces 4A - Watermelon](https://codeforces.com/problemset/problem/4/A)。

### [整数与模运算工具](../00-basic/math_utils.cpp)

- **思路**：快速幂用二进制拆指数；exgcd 求 `ax+by=gcd(a,b)`；逆元只有 `gcd(a,mod)=1` 时存在。
- **复杂度**：快速幂和 exgcd 都是 `O(log n)`。
- **坑**：费马逆元要求模数为质数且底数不被模数整除；lcm 先除后乘；乘法中间量可能需要 `__int128`。
- **例题**：[P1226 快速幂](https://www.luogu.com.cn/problem/P1226)、[P1082 同余方程](https://www.luogu.com.cn/problem/P1082)。

## 01 · 签到稳定

参考：[OI Wiki 算法基础](https://oi-wiki.org/basic/)。

| 模板 | 核心思路与运用 | 复杂度 | 最常见坑 | 例题 |
|---|---|---:|---|---|
| [前缀和 / 差分](../01-signin/prefix_difference.cpp) | 前缀和把区间和变成两个前缀之差；差分只改区间两端，最后前缀还原 | `O(n+m)` | `d[r+1]` 要留空间；二维差分符号 | [P8218](https://www.luogu.com.cn/problem/P8218) / [P2367](https://www.luogu.com.cn/problem/P2367) |
| [双指针](../01-signin/two_pointers.cpp) | 两个端点都只向前移动，把暴力枚举区间降为线性 | `O(n)` | 有负数时“超限后左移”通常不再正确 | [P1638](https://www.luogu.com.cn/problem/P1638) |
| [二分](../01-signin/binary_search.cpp) | 保持“答案一定在当前闭区间”不变量；答案二分要写单调 `check` | `O(log n)` | `mid` 取整方向、无解返回值、边界死循环 | [P2440](https://www.luogu.com.cn/problem/P2440) |
| [离散化](../01-signin/discretization.cpp) | 排序去重后用排名代替原值，保留大小和相等关系 | `O(n log n)` | 离散后相邻排名不代表原值相差 1 | [P1496](https://www.luogu.com.cn/problem/P1496) |
| [网格 BFS](../01-signin/bfs_grid.cpp) | 队列按距离分层，第一次到达即最短 | `O(nm)` | 起点要先标记；边界和障碍判断顺序 | [P1746](https://www.luogu.com.cn/problem/P1746) |
| [0/1 背包与 LIS](../01-signin/knapsack_lis.cpp) | 0/1 背包容量倒序；LIS 维护每个长度的最小结尾 | `O(nV)` / `O(n log n)` | 完全背包是正序；非严格 LIS 用 `upper_bound` | [P1048](https://www.luogu.com.cn/problem/P1048) / [P1020](https://www.luogu.com.cn/problem/P1020) |

## 02 · 铜牌必会

铜牌层的目标不是“听说过”，而是看到标准模型后能在 15–25 分钟内写完并过边界。

### 数据结构

参考：[OI Wiki 数据结构](https://oi-wiki.org/ds/)。

| 模板 | 核心思路与运用 | 复杂度 | 最常见坑 | 例题 |
|---|---|---:|---|---|
| [并查集](../02-bronze/dsu.cpp) | 每个集合是一棵树；路径压缩 + 按大小合并 | 近似 `O(1)` 均摊 | 只能方便地合并，不能直接删边；先找根再合并 | [P3367](https://www.luogu.com.cn/problem/P3367) |
| [树状数组](../02-bronze/fenwick.cpp) | `lowbit` 管理前缀分块，适合可逆前缀信息 | `O(log n)` | 下标不能为 0；max 一般不能用两个前缀相减 | [P3374](https://www.luogu.com.cn/problem/P3374) |
| [懒标记线段树](../02-bronze/segment_tree_lazy.cpp) | 整段修改先记标记，需要进入子树时再下传 | `O(log n)` | 区间长度、标记清空、先 `down` 再递归 | [P3372](https://www.luogu.com.cn/problem/P3372) |
| [ST 表](../02-bronze/sparse_table.cpp) | 用两个可能重叠的 `2^k` 块回答静态 RMQ | 预处理 `O(n log n)`，查询 `O(1)` | 只适合 max/min/gcd 等重复不影响结果的运算 | [P3865](https://www.luogu.com.cn/problem/P3865) |
| [单调队列](../02-bronze/monotonic_queue.cpp) | 队列保存仍可能成为答案的下标，队头过期、队尾失去竞争力就弹出 | `O(n)` | 存下标而不是只存值；先判断窗口过期 | [P1886](https://www.luogu.com.cn/problem/P1886) |

### 图论与树

参考：[OI Wiki 最短路](https://oi-wiki.org/graph/shortest-path/) 与 [图论部分](https://oi-wiki.org/graph/)。

| 模板 | 核心思路与运用 | 复杂度 | 最常见坑 | 例题 |
|---|---|---:|---|---|
| [Dijkstra](../02-bronze/dijkstra.cpp) | 每次确定当前距离最小的未确定点，用它松弛出边 | `O((n+m)log n)` | 不能有负边；`dis` 用 `long long`；旧堆元素要跳过 | [P4779](https://www.luogu.com.cn/problem/P4779) |
| [0-1 BFS](../02-bronze/zero_one_bfs.cpp) | 权 0 的新状态放队首，权 1 放队尾 | `O(n+m)` | 只适用于 0/1 权；仍需做距离松弛 | [P4554](https://www.luogu.com.cn/problem/P4554) |
| [Floyd](../02-bronze/floyd.cpp) | 枚举中转点 `k`，允许路径内部点逐步扩展 | `O(n^3)` | `k` 必须最外层；INF 相加前判断；重边取最小 | [P1119](https://www.luogu.com.cn/problem/P1119) |
| [Kruskal](../02-bronze/mst_kruskal.cpp) | 边从小到大，若连接不同连通块就选 | `O(m log m)` | 图不连通时不存在生成树；总权用 `long long` | [P3366](https://www.luogu.com.cn/problem/P3366) |
| [拓扑排序](../02-bronze/toposort.cpp) | 不断删除入度为 0 的点；处理数不足说明有环 | `O(n+m)`，小根堆版多 `log n` | 只有 DAG 才有完整拓扑序；重边会重复贡献入度 | [P1347](https://www.luogu.com.cn/problem/P1347) |
| [二分图匹配](../02-bronze/bipartite_matching.cpp) | 为每个左点寻找增广路，必要时让已匹配点换对象 | `O(n_1m)` | 左右编号域、每轮访问标记、图必须二分 | [P3386](https://www.luogu.com.cn/problem/P3386) |
| [倍增 LCA](../02-bronze/lca.cpp) | `up[x][k]` 表示 `2^k` 级祖先，先拉齐深度再同时上跳 | 预处理 `O(nlog n)`，查询 `O(log n)` | `LOG` 要覆盖最大 n；深树递归可能爆栈 | [P3379](https://www.luogu.com.cn/problem/P3379) |
| [树的直径](../02-bronze/tree_diameter.cpp) | 非负权树从任一点找最远点，再从该点找最远点 | `O(n)` | 有负边不能直接两次 DFS；只有树才能这样做 | [P1099](https://www.luogu.com.cn/problem/P1099) |

### 字符串与数学

| 模板 | 核心思路与运用 | 复杂度 | 最常见坑 | 例题 |
|---|---|---:|---|---|
| [KMP / Z](../02-bronze/kmp_z.cpp) | KMP 用最长 border 失配跳转；Z 维护与整串前缀相同的最远盒子 | `O(n+m)` | KMP 匹配成功后继续跳 `pi[j-1]`；下标转换 | [P3375](https://www.luogu.com.cn/problem/P3375) / [P5410](https://www.luogu.com.cn/problem/P5410) |
| [Trie](../02-bronze/trie.cpp) | 公共前缀共用路径，结尾节点记录完整单词信息 | `O(总字符数)` | 字符集决定内存；清空多测；前缀与完整单词不同 | [P8306](https://www.luogu.com.cn/problem/P8306) |
| [线性筛 / 组合数](../02-bronze/sieve_comb.cpp) | 每个合数由最小质因子筛一次；阶乘与逆阶乘回答组合数 | `O(n)` | 组合数板要求质数模且预处理范围通常小于模数 | [P3383](https://www.luogu.com.cn/problem/P3383) / [P3807](https://www.luogu.com.cn/problem/P3807) |

## 03 · 银牌突破

银牌层更重要的是“建模和不变量”。复制代码前，必须先说清节点/状态的含义以及合并为什么正确。

### 复杂数据结构

| 模板 | 核心思路与运用 | 复杂度 | 最常见坑 | 例题 |
|---|---|---:|---|---|
| [01 序列线段树](../03-silver/binary_sequence_segment_tree.cpp) | 同时维护 0/1 的前缀、后缀和最长段；翻转时交换两套信息 | `O(log n)` | 赋值会覆盖旧翻转；翻转遇到赋值标记应直接改赋值值；查询合并要用真实子段长度 | [P2572](https://www.luogu.com.cn/problem/P2572) |
| [树链剖分](../03-silver/heavy_light_decomposition.cpp) | 重儿子优先 DFS，让一条树路径拆成 `O(log n)` 个连续 DFS 序区间 | `O(log^2 n)` | 子树区间是 `[dfn,dfn+siz-1]`；点权/边权映射不同；全程取模 | [P3384](https://www.luogu.com.cn/problem/P3384) |
| [主席树](../03-silver/persistent_segment_tree.cpp) | 每个前缀建立一个共享旧节点的新版本，两个版本相减得到区间频次 | `O(log n)`/询问 | 节点池开到 `n log n`；先离散化；第 k 小的 k 从 1 开始 | [P3834](https://www.luogu.com.cn/problem/P3834) |
| [莫队](../03-silver/mo_algorithm.cpp) | 离线重排区间，使相邻询问端点移动总量较小 | 约 `O((n+q)sqrt n)` | 只有答案能快速增删端点才适合；必须恢复原询问顺序 | [P1494](https://www.luogu.com.cn/problem/P1494) |
| [线性基](../03-silver/linear_basis.cpp) | 按最高位消元，保留线性无关的异或向量 | `O(64n)` | 有符号右移与第 63 位；求第 k 小还需把基化为简化形 | [P3812](https://www.luogu.com.cn/problem/P3812) |

### 连通性、约束与网络流

| 模板 | 核心思路与运用 | 复杂度 | 最常见坑 | 例题 |
|---|---|---:|---|---|
| [SCC 缩点](../03-silver/scc.cpp) | `low[x]` 表示 DFS 栈内能追溯到的最早时间；每个 SCC 缩成 DAG 节点再 DP | `O(n+m)` | 返祖边只用栈内点；缩点后可能有重边，但拓扑入度也要一致计数 | [P3387](https://www.luogu.com.cn/problem/P3387) |
| [2-SAT](../03-silver/two_sat.cpp) | `(A or B)` 等价于 `not A -> B` 与 `not B -> A`；变量真假在同一 SCC 则无解 | `O(n+m)` | 否定编号、蕴含边方向、Tarjan 编号决定取值比较方向 | [P4782](https://www.luogu.com.cn/problem/P4782) |
| [Dinic](../03-silver/dinic.cpp) | BFS 建分层图，DFS 只沿层数递增边推流 | 常见上界 `O(n^2m)` | 反向边下标、容量用 `long long`、当前弧优化 | [P3376](https://www.luogu.com.cn/problem/P3376) |
| [最小费用最大流](../03-silver/min_cost_flow.cpp) | 每次沿费用最短的可增广路送尽可能多的流 | 依增广次数而定 | 反向边费用取负；负费用边需能正确求最短路；乘法溢出 | [P3381](https://www.luogu.com.cn/problem/P3381) |

### 字符串、DP 与几何

| 模板 | 核心思路与运用 | 复杂度 | 最常见坑 | 例题 |
|---|---|---:|---|---|
| [AC 自动机](../03-silver/ac_automaton.cpp) | Trie 上加 fail 指针，多模式串失配时跳到最长可用后缀 | `O(模式总长+文本长+答案)` | 重复模式串计数、fail 链贡献、字符集内存 | [P3808](https://www.luogu.com.cn/problem/P3808) |
| [Manacher](../03-silver/manacher.cpp) | 插入分隔符统一奇偶回文，利用镜像和最右回文边界 | `O(n)` | 哨兵不能出现在原串；半径与原串长度的换算 | [P3805](https://www.luogu.com.cn/problem/P3805) |
| [数位 DP](../03-silver/digit_dp.cpp) | 从高位到低位填数，状态记录历史约束、是否开始、是否贴上界 | `O(位数×状态×10)` | 前导零是否属于数字；只有 `tight=false` 的状态适合记忆化 | [P2602](https://www.luogu.com.cn/problem/P2602) |
| [Andrew 凸包](../03-silver/convex_hull.cpp) | 排序后用叉积维护上下凸壳 | `O(n log n)` | 是否保留共线边界点要按题意改 `<0/<=0`；叉积可能溢出 | [P2742](https://www.luogu.com.cn/problem/P2742) |

## 你的线段树代码怎么理解

你原来的写法维护了：区间 `1` 的数量，0/1 各自的最长前缀、最长后缀、最长连续段；这套信息是正确方向。关键合并式是：

```text
best = max(left.best, right.best, left.suf + right.pre)
pre  = left 全部同值 ? left.len + right.pre : left.pre
suf  = right 全部同值 ? right.len + left.suf : right.suf
```

它适合“最长连续同类段”类题：最长连续空房、最长可用座位、区间颜色段、括号/字符段信息合并等。真正的难点不在递归，而在两个不变量：

1. 节点信息必须只描述该节点的完整区间；查询返回的临时节点则必须保存自己的真实长度。
2. 懒标记要看作函数复合。`set` 会抹掉此前一切修改；`reverse` 接在 `set(v)` 后等价于 `set(v xor 1)`。

[重构后的版本](../03-silver/binary_sequence_segment_tree.cpp) 把长度直接放在 `Node` 中，避免原代码查询时通过 `mid-max(jobl,l)+1` 手算交集长度；这会让复用到其他“区间合并”题时更稳。

## 暂不进入首版的内容

- **稳定银牌后再补**：差分约束、欧拉路、点分治、DSU on tree、矩阵快速幂、高斯消元、状态压缩 DP、字符串哈希。
- **按赛区与队伍专长选修**：NTT/FFT、后缀数组/SAM/PAM、Miller-Rabin/Pollard-Rho、二维/三维完整几何。
- **更高阶或低频**：Min25、生成函数、一般图匹配、半平面交、LCT、全局最小割。

筛选原则不是“这些算法不重要”，而是先让模板库保持可复习、可检索、能稳定转化为现场得分。
