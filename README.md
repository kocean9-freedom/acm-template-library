# ACM Template Library

按 **签到稳定 → 铜牌必会 → 银牌突破** 分层的 GNU C++17 模板库。代码采用全局数组、1 下标、短函数名的 ACM 现场风格；每个 `.cpp` 都能独立编译。

> 分层是训练口径，不是任何比赛的官方题目标签。题目的包装、数据范围和算法组合会改变实际难度。

## 怎么用

1. 先看 [题面信号与使用指南](docs/guide.md)，判断该用哪个算法。
2. 打开对应源码，先读文件顶部的前提与复杂度，再复制到题目中改输入输出。
3. 复杂数据结构不要背整份代码，重点记住“维护什么信息、如何合并、懒标记如何复合”。
4. 赛前运行 `bash scripts/check.sh`；GNU 编译器可通过 `CXX=g++-15 bash scripts/check.sh` 指定。

常用函数、整数边界、STL 速查和交题检查表见 [小技巧与快捷函数](docs/tricks.md)。

## 00 · 基础骨架

| 模板 | 用途 |
|---|---|
| [base.cpp](00-basic/base.cpp) | 单/多测骨架、常用类型和无穷大 |
| [math_utils.cpp](00-basic/math_utils.cpp) | 快速幂、gcd/lcm、exgcd、逆元、正模 |

## 01 · 签到稳定

| 模板 | 看到这些信号就考虑 |
|---|---|
| [prefix_difference.cpp](01-signin/prefix_difference.cpp) | 静态区间和；多次区间修改、最后统一输出 |
| [two_pointers.cpp](01-signin/two_pointers.cpp) | 连续区间、非负/单调、最长或最短 |
| [binary_search.cpp](01-signin/binary_search.cpp) | 有序数组边界；答案具有单调可行性 |
| [discretization.cpp](01-signin/discretization.cpp) | 值域大，但只关心相对大小/相等关系 |
| [bfs_grid.cpp](01-signin/bfs_grid.cpp) | 无权图或网格最少步数 |
| [knapsack_lis.cpp](01-signin/knapsack_lis.cpp) | 0/1 选择；最长递增子序列 |

## 02 · 铜牌必会

| 方向 | 模板 |
|---|---|
| 数据结构 | [并查集](02-bronze/dsu.cpp) · [树状数组](02-bronze/fenwick.cpp) · [懒标记线段树](02-bronze/segment_tree_lazy.cpp) · [ST 表](02-bronze/sparse_table.cpp) · [单调队列](02-bronze/monotonic_queue.cpp) |
| 图论 | [Dijkstra](02-bronze/dijkstra.cpp) · [0-1 BFS](02-bronze/zero_one_bfs.cpp) · [Floyd](02-bronze/floyd.cpp) · [Kruskal](02-bronze/mst_kruskal.cpp) · [拓扑排序](02-bronze/toposort.cpp) · [二分图匹配](02-bronze/bipartite_matching.cpp) |
| 树 | [倍增 LCA](02-bronze/lca.cpp) · [树的直径](02-bronze/tree_diameter.cpp) |
| 字符串 | [KMP 与 Z 函数](02-bronze/kmp_z.cpp) · [Trie](02-bronze/trie.cpp) |
| 数学 | [线性筛与组合数](02-bronze/sieve_comb.cpp) |

## 03 · 银牌突破

| 方向 | 模板 |
|---|---|
| 数据结构 | [01 序列复杂线段树](03-silver/binary_sequence_segment_tree.cpp) · [树链剖分](03-silver/heavy_light_decomposition.cpp) · [主席树](03-silver/persistent_segment_tree.cpp) · [莫队](03-silver/mo_algorithm.cpp) · [线性基](03-silver/linear_basis.cpp) |
| 图论 | [SCC 缩点](03-silver/scc.cpp) · [2-SAT](03-silver/two_sat.cpp) · [Dinic 最大流](03-silver/dinic.cpp) · [最小费用最大流](03-silver/min_cost_flow.cpp) |
| 字符串 | [AC 自动机](03-silver/ac_automaton.cpp) · [Manacher](03-silver/manacher.cpp) |
| DP / 几何 | [数位 DP](03-silver/digit_dp.cpp) · [Andrew 凸包](03-silver/convex_hull.cpp) |

## 推荐学习顺序

- **先稳签到**：前缀和/差分 → 二分 → 双指针 → BFS → 基础 DP。
- **再稳铜牌**：并查集 → 树状数组 → 线段树 → 最短路/MST → LCA → KMP。
- **冲银主线**：复杂线段树 → SCC/2-SAT → 网络流 → 树链剖分/主席树 → AC 自动机。
- **按需补充**：莫队、线性基、数位 DP、凸包。这四类很有用，但更依赖题型识别。

## 为什么没有把 WIDA / OI Wiki 全搬进来

WIDA 打印版和 [OI Wiki](https://oi-wiki.org/) 都是很好的完整知识库，但完整目录包含 Min25、Pollard-Rho、多项式全家桶、一般图匹配、LCT、后缀自动机、三维几何等内容。对“区域赛签到到银牌尾部”而言，过大的板子会提高记忆和检索成本。

首版的筛选标准是：区域赛出现频率、能否跨题迁移、现场实现风险、板子长度和是否有清晰的识别信号。更高阶算法列在指南末尾，达到稳定银牌后再按队伍短板扩展。

## 验证

- 所有源码使用 `-std=c++17 -O2 -Wall -Wextra` 严格编译。
- 复杂 01 线段树、主席树、2-SAT 使用固定随机种子做小数据对拍。
- 关键模板运行确定性样例，全部 Markdown 相对链接检查存在性。
- 一键执行：`bash scripts/check.sh`。

## 资料来源与取舍

清单参考用户提供的 WIDA 算法模板打印版与 [OI Wiki](https://oi-wiki.org/)，但代码和说明均重新整理。筛选优先级是：区域赛出现频率、跨题迁移性、现场实现风险和板子长度；完整筛选理由见 [使用指南](docs/guide.md#暂不进入首版的内容)。
- 关键模板运行确定性样例。
- 01 序列线段树、主席树和 2-SAT 运行固定随机种子的暴力对拍。
- Markdown 内部链接由脚本检查。

```bash
bash scripts/check.sh
python3 scripts/random_check.py build
```

## License

[MIT](LICENSE)。示例题目与外部教程版权归各自平台和作者所有；本仓库仅提供原创整理与实现。
