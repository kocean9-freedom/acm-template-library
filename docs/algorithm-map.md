# 算法地图：从题面信号到模板

先判断模型，再找模板。等级含义：A 必须背，B 熟练改，C 知道去哪找。层级是训练建议，不是官方题目标签。

## 基础与解题模式

| 等级 | 题面信号 | 方法 | 核心检查 |
|---|---|---|---|
| A | 任何题、多测或大输入 | [竞赛基础骨架](../00-basic/base.cpp) | I/O、类型、数组清空范围、多测状态重置 |
| A | 数据小、排列/子集很少、要求构造所有方案 | [枚举与模拟](../01-signin/simulation_enumeration.cpp) | 先算状态数；明确更新顺序和去重 |
| A | 排序后局部选择看似最优 | [排序贪心](../01-signin/greedy_sort.cpp) | 必须能说交换论证或首个分歧 |
| A | 多次静态区间和；区间修改后统一输出 | [前缀和/差分](../01-signin/prefix_difference.cpp) | 边界 `r+1`、二维符号 |
| A | 连续区间且可行性随端点单调 | [双指针](../01-signin/two_pointers.cpp) | 有负数时窗口单调性可能失效 |
| A | 最大化最小值、最小化最大值 | [二分](../01-signin/binary_search.cpp) | `check` 单调方向和无解返回值 |
| A | 大值域但只关心顺序 | [离散化](../01-signin/discretization.cpp) | 排名相邻不代表原值差 1 |
| A | 无权最短步数 | [网格 BFS](../01-signin/bfs_grid.cpp) | 入队即标记，避免重复入队 |
| A | 线性状态、选或不选、最长序列 | [基础 DP](../01-signin/basic_dp.cpp)、[背包/LIS](../01-signin/knapsack_lis.cpp) | 状态语义、初值、循环方向 |

## 数据结构

| 等级 | 题面信号 | 模板 | 复杂度与边界 |
|---|---|---|---|
| A | 动态连通、合并集合 | [并查集](../02-bronze/dsu.cpp) | 近似 `O(1)`；不支持直接删边 |
| A | 单点修改、前缀/区间和 | [树状数组](../02-bronze/fenwick.cpp) | `O(log n)`；下标不能为 0 |
| A/B | 区间合并、区间修改 | [懒线段树](../02-bronze/segment_tree_lazy.cpp) | `O(log n)`；先写标记复合 |
| B | 静态 RMQ | [ST 表](../02-bronze/sparse_table.cpp) | 预处理 `O(nlog n)`，查询 `O(1)`；运算需幂等 |
| A | 滑动窗口最值 | [单调队列](../02-bronze/monotonic_queue.cpp) | `O(n)`；保存下标 |
| A | 每个元素找最近更大/更小 | [单调栈](../02-bronze/monotonic_stack.cpp) | `O(n)`；明确是否弹相等元素 |
| B | 区间赋值/翻转并问最长同值段 | [01 复杂线段树](../03-silver/binary_sequence_segment_tree.cpp) | `O(log n)`；赋值覆盖翻转 |
| B | 树上路径修改/查询 | [树链剖分](../03-silver/heavy_light_decomposition.cpp) | `O(log²n)`；点权与边权映射不同 |
| B | 静态区间第 k 小 | [主席树](../03-silver/persistent_segment_tree.cpp) | `O(log n)`；节点池 `O(nlog n)` |
| C | 离线区间询问且端点可 O(1) 增删 | [莫队](../03-silver/mo_algorithm.cpp) | 约 `O((n+q)sqrt n)` |
| B | 相对距离/势能约束并合并 | [带权并查集](../03-silver/weighted_dsu.cpp) | 近似 `O(1)`；路径压缩时更新势能 |
| C | 离线动态连通、分治时间 | [可撤销并查集](../03-silver/rollback_dsu.cpp) | 不做路径压缩；按栈回滚 |
| C | 动态加入直线、查询最值 | [Li Chao 树](../03-silver/li_chao_tree.cpp) | `O(log X)`；值域和溢出 |

## 图论与树

| 等级 | 题面信号 | 模板 | 复杂度与边界 |
|---|---|---|---|
| A | 非负边单源最短路 | [Dijkstra](../02-bronze/dijkstra.cpp) | `O((n+m)log n)`；不能有负边 |
| A | 只有 0/1 边权 | [0-1 BFS](../02-bronze/zero_one_bfs.cpp) | `O(n+m)` |
| B | 负边、负环或差分约束 | [Bellman-Ford](../02-bronze/bellman_ford.cpp)、[差分约束](../03-silver/difference_constraints.cpp) | `O(nm)`；先判断可达再相加 |
| B | 点数很小的全源最短路 | [Floyd](../02-bronze/floyd.cpp) | `O(n³)`；`k` 必须最外层 |
| A | 最小代价连通全部点 | [Kruskal](../02-bronze/mst_kruskal.cpp) | `O(mlog m)`；断图需判定 |
| A | 依赖顺序、DAG | [拓扑排序](../02-bronze/toposort.cpp) | `O(n+m)`；处理不足 n 个即有环 |
| B | 每条边恰走一次 | [欧拉路](../02-bronze/euler_trail.cpp) | `O(n+m)`；度数与连通性 |
| B | 删除点/边破坏连通 | [桥与割点](../02-bronze/bridge_articulation.cpp) | `O(n+m)`；根节点单独判断 |
| A/B | 二分图规模中等、求最大匹配 | [匈牙利算法](../02-bronze/bipartite_matching.cpp) | `O(nm)`；每轮重新清空右侧访问标记 |
| A | 树上祖先、距离 | [LCA](../02-bronze/lca.cpp) | 预处理 `O(nlog n)`，查询 `O(log n)` |
| A | 树上最远点 | [树的直径](../02-bronze/tree_diameter.cpp) | `O(n)`；负权树不能直接两遍 DFS |
| A/B | 子树合并、树上选或不选 | [树形 DP](../02-bronze/tree_dp.cpp) | `O(n)`；写清父子状态 |
| B | 每个点作为根都要求答案 | [换根 DP](../03-silver/rerooting_dp.cpp) | `O(n)`；父方向贡献不能漏 |
| C | 子树颜色/频次离线统计 | [DSU on tree](../03-silver/dsu_on_tree.cpp) | `O(nlog n)` 常见；重儿子保留 |
| B | 有向图互相可达后做 DAG DP | [SCC](../03-silver/scc.cpp) | `O(n+m)` |
| B | 每变量二选一、析取约束 | [2-SAT](../03-silver/two_sat.cpp) | `O(n+m)`；否定编号和边方向 |
| B | 容量、分配、最小割 | [Dinic](../03-silver/dinic.cpp) | 常见 `O(n²m)`；反向边和当前弧 |
| C | 流还带单位代价 | [最小费用流](../03-silver/min_cost_flow.cpp) | 依增广次数；反向边费用取负 |
| B | 二分图大规模匹配 | [Hopcroft-Karp](../03-silver/hopcroft_karp.cpp) | `O(m√n)`；左右点编号域 |

## DP、字符串、数学与几何

| 等级 | 题面信号 | 模板 | 核心检查 |
|---|---|---|---|
| A/B | 连续区间合并、最后一次操作 | [区间 DP](../02-bronze/interval_dp.cpp) | 先枚举长度，再枚举左端点和断点 |
| B | `n≤20`、状态是已选集合 | [状压 DP](../02-bronze/bitmask_dp.cpp) | `O(2^n n)`；转移方向 |
| B | 固定维状态重复极多次 | [矩阵快速幂](../02-bronze/matrix_fast_power.cpp) | `O(k³log n)`；单位矩阵和乘法溢出 |
| B | mask 的子集/超集聚合 | [SOS DP](../03-silver/sos_dp.cpp) | 位在外层；明确子集和还是超集和 |
| A | 单模式匹配或 border | [KMP/Z](../02-bronze/kmp_z.cpp) | 匹配后继续跳 failure |
| A/B | 多次子串相等、路径串比较 | [滚动哈希](../02-bronze/rolling_hash.cpp) | 双哈希/随机基数；下标与幂方向 |
| A | 前缀字典 | [Trie](../02-bronze/trie.cpp) | 字符集和多测清空 |
| B | 多模式匹配 | [AC 自动机](../03-silver/ac_automaton.cpp) | fail 贡献、重复模式 |
| B | 最长回文/回文半径 | [Manacher](../03-silver/manacher.cpp) | 奇偶统一与半径换算 |
| C | 后缀排序、LCP、不同子串 | [后缀数组](../03-silver/suffix_array.cpp) | 倍增排名、LCP 下标 |
| B | 数位条件统计 `[0,n]` | [数位 DP](../03-silver/digit_dp.cpp) | `tight/started` 和前导零 |
| B | 最大子集异或 | [线性基](../03-silver/linear_basis.cpp) | 位数、有符号数、第 k 小需化简 |
| A | gcd、逆元、幂、正模 | [数学工具](../00-basic/math_utils.cpp) | 逆元存在条件与 `__int128` |
| A | 质数、组合数 | [筛与组合数](../02-bronze/sieve_comb.cpp) | 模数为质数、预处理范围 |
| C | 多个同余方程合并 | [广义 CRT](../03-silver/chinese_remainder.cpp) | 不互质也可合并；检查无解和 lcm 溢出 |
| C | 实数线性方程组 | [高斯消元](../03-silver/gaussian_elimination.cpp) | 主元、无解/多解、EPS |
| B | 点、叉积、线段关系 | [几何基础](../03-silver/geometry_base.cpp) | 整数叉积用 `__int128`，共线边界按题意 |
| B | 最外层边界、多边形 | [凸包](../03-silver/convex_hull.cpp) | 是否保留共线点 |

## C 级扩展索引

稳定银牌后再按队伍专长扩展：NTT/FFT、后缀自动机/PAM、点分治、虚树、线段树分治、线段树 beats、Miller-Rabin/Pollard-Rho、最小圆覆盖、半平面交、LCT、一般图匹配。判断是否升级为 B 级的标准是：近三个月训练至少遇到三次，并且全队有人能解释不变量与验证方式。
