# 分层例题索引

建议顺序：模板题独立 AC → 口述核心转化 → 不看板重写 → 做一题包装不同的变式。链接只作为训练入口，题目难度会随平台和年份变化。

## 签到层

| 模板 | 模板/台阶题 | 训练重点 |
|---|---|---|
| 枚举 | [CSES Apple Division](https://cses.fi/problemset/task/1623) | 先估算 `2^n`，再写无遗漏枚举 |
| 排序贪心 | [CSES Movie Festival](https://cses.fi/problemset/task/1629) | 最早结束与交换论证 |
| 前缀和 / 差分 | [洛谷 P8218](https://www.luogu.com.cn/problem/P8218) · [P2367](https://www.luogu.com.cn/problem/P2367) | 静态查询与区间修改的区别 |
| 双指针 | [CSES Subarray Sums I](https://cses.fi/problemset/task/1660) · [洛谷 P1638](https://www.luogu.com.cn/problem/P1638) | 窗口单调性的前提 |
| 二分答案 | [洛谷 P2440](https://www.luogu.com.cn/problem/P2440) · [P2678](https://www.luogu.com.cn/problem/P2678) | `check` 的真假方向 |
| 离散化 | [洛谷 P1496](https://www.luogu.com.cn/problem/P1496) | 排名与真实距离不能混用 |
| BFS | [洛谷 P1746](https://www.luogu.com.cn/problem/P1746) · [CSES Labyrinth](https://cses.fi/problemset/task/1193) | 入队标记与路径恢复 |
| 基础 DP | [CSES Grid Paths](https://cses.fi/problemset/task/1638) | 状态只保留未来需要的信息 |
| 背包 / LIS | [洛谷 P1048](https://www.luogu.com.cn/problem/P1048) · [P1020](https://www.luogu.com.cn/problem/P1020) | 循环方向与 `lower_bound/upper_bound` |

## 铜牌层：数据结构

| 模板 | 模板题 | 变式或验收 |
|---|---|---|
| DSU | [洛谷 P3367](https://www.luogu.com.cn/problem/P3367) | [CSES Road Construction](https://cses.fi/problemset/task/1676) |
| Fenwick | [洛谷 P3374](https://www.luogu.com.cn/problem/P3374) | [CSES Range Update Queries](https://cses.fi/problemset/task/1651) |
| 懒线段树 | [洛谷 P3372](https://www.luogu.com.cn/problem/P3372) | [CSES Range Updates and Sums](https://cses.fi/problemset/task/1735) |
| ST 表 | [洛谷 P3865](https://www.luogu.com.cn/problem/P3865) | 自己说明为什么 sum 不能用两个重叠块 |
| 单调队列 | [洛谷 P1886](https://www.luogu.com.cn/problem/P1886) | [CSES Sliding Window Minimum](https://cses.fi/problemset/task/3221) |
| 单调栈 | [洛谷 P5788](https://www.luogu.com.cn/problem/P5788) | [CSES Nearest Smaller Values](https://cses.fi/problemset/task/1645) |

## 铜牌层：图与树

| 模板 | 模板题 | 训练重点 |
|---|---|---|
| Dijkstra | [洛谷 P4779](https://www.luogu.com.cn/problem/P4779) | 旧堆元素、负边、`long long` |
| 0-1 BFS | [洛谷 P4554](https://www.luogu.com.cn/problem/P4554) | 权 0 放队首、权 1 放队尾 |
| Bellman-Ford | [CSES Cycle Finding](https://cses.fi/problemset/task/1197) | 可达负环与全图负环的区别 |
| Floyd | [洛谷 P1119](https://www.luogu.com.cn/problem/P1119) | `k` 最外层、重边和 INF |
| Kruskal | [洛谷 P3366](https://www.luogu.com.cn/problem/P3366) | 断图判断与总权溢出 |
| 拓扑排序 | [CSES Course Schedule](https://cses.fi/problemset/task/1679) | 有环时处理数量不足 |
| 欧拉路 | [洛谷 P2731](https://www.luogu.com.cn/problem/P2731) | 奇度数、连通性、重边编号 |
| 桥 / 割点 | [洛谷 P3388](https://www.luogu.com.cn/problem/P3388) · [CSES Necessary Roads](https://cses.fi/problemset/task/2076) | DFS 根与重边 |
| 二分图匹配 | [洛谷 P3386](https://www.luogu.com.cn/problem/P3386) | 左右编号域和访问标记 |
| LCA | [洛谷 P3379](https://www.luogu.com.cn/problem/P3379) | `LOG`、深度拉齐、路径距离 |
| 树的直径 | [CSES Tree Diameter](https://cses.fi/problemset/task/1131) | 负权时两遍 DFS 失效 |
| 树形 DP | [洛谷 P1352](https://www.luogu.com.cn/problem/P1352) | 选/不选状态与父子约束 |

## 铜牌层：DP、字符串和数学

| 模板 | 模板题 | 训练重点 |
|---|---|---|
| 状压 DP | [CSES Hamiltonian Flights](https://cses.fi/problemset/task/1690) | `mask` 是否包含终点、转移方向 |
| 区间 DP | [洛谷 P1880](https://www.luogu.com.cn/problem/P1880) | 长度 → 左端点 → 断点 |
| 矩阵快速幂 | [洛谷 P1962](https://www.luogu.com.cn/problem/P1962) | 从递推写出状态向量和单位矩阵 |
| KMP / Z | [洛谷 P3375](https://www.luogu.com.cn/problem/P3375) · [P5410](https://www.luogu.com.cn/problem/P5410) | border 语义和匹配后跳转 |
| 滚动哈希 | [洛谷 P3370](https://www.luogu.com.cn/problem/P3370) | 双模、随机基数和碰撞边界 |
| Trie | [洛谷 P8306](https://www.luogu.com.cn/problem/P8306) | 前缀与完整单词计数 |
| 线性筛 / 组合数 | [洛谷 P3383](https://www.luogu.com.cn/problem/P3383) · [P3807](https://www.luogu.com.cn/problem/P3807) | 最小质因子与模数前提 |

## 银牌层：数据结构、树与位运算

| 模板 | 模板题 | 变式或验收 |
|---|---|---|
| 01 复合线段树 | [洛谷 P2572](https://www.luogu.com.cn/problem/P2572) | 先手写赋值/翻转复合表，再编码 |
| HLD | [洛谷 P3384](https://www.luogu.com.cn/problem/P3384) | 点权/边权映射与子树区间 |
| 主席树 | [洛谷 P3834](https://www.luogu.com.cn/problem/P3834) | 前缀版本相减与节点池 |
| 莫队 | [洛谷 P1494](https://www.luogu.com.cn/problem/P1494) | 端点增删必须足够快 |
| 带权 DSU | [洛谷 P2024](https://www.luogu.com.cn/problem/P2024) | 势能方向和路径压缩 |
| 可撤销 DSU | [Library Checker Persistent Unionfind](https://judge.yosupo.jp/problem/persistent_unionfind) | 用离线版本树 + 回滚实现；不做路径压缩，历史栈对称恢复 |
| Li Chao | [洛谷 P4097](https://www.luogu.com.cn/problem/P4097) | 比较端点/中点、直线相等和溢出 |
| DSU on tree | [Codeforces 600E](https://codeforces.com/problemset/problem/600/E) | 重儿子保留、轻儿子清空 |
| 换根 DP | [CSES Tree Distances II](https://cses.fi/problemset/task/1133) | 父根移到儿根时贡献增减 |
| SOS DP | [Codeforces 449D](https://codeforces.com/problemset/problem/449/D) | 子集/超集方向和位循环顺序 |
| 线性基 | [洛谷 P3812](https://www.luogu.com.cn/problem/P3812) | 最高位消元、最大 xor |

## 银牌层：约束、流与字符串

| 模板 | 模板题 | 训练重点 |
|---|---|---|
| 差分约束 | [洛谷 P5960](https://www.luogu.com.cn/problem/P5960) | 不等式方向与超级源 |
| SCC | [洛谷 P3387](https://www.luogu.com.cn/problem/P3387) | 栈内返祖边、缩点 DAG DP |
| 2-SAT | [洛谷 P4782](https://www.luogu.com.cn/problem/P4782) | 析取转蕴含与真假编号 |
| Dinic | [洛谷 P3376](https://www.luogu.com.cn/problem/P3376) | 反向边、当前弧、容量类型 |
| 最小费用流 | [洛谷 P3381](https://www.luogu.com.cn/problem/P3381) | 负费用反边与最短增广路 |
| Hopcroft-Karp | [Library Checker Bipartite Matching](https://judge.yosupo.jp/problem/bipartitematching) | BFS 分层后批量增广 |
| AC 自动机 | [洛谷 P3808](https://www.luogu.com.cn/problem/P3808) | fail 链贡献与重复模式 |
| Manacher | [洛谷 P3805](https://www.luogu.com.cn/problem/P3805) | 半径与原串长度换算 |
| 后缀数组 | [洛谷 P3809](https://www.luogu.com.cn/problem/P3809) | 排名倍增与 Kasai LCP |

## 银牌层：数学、DP 与几何

| 模板 | 模板题 | 训练重点 |
|---|---|---|
| 数位 DP | [洛谷 P2602](https://www.luogu.com.cn/problem/P2602) | 前导零、`tight` 和记忆化条件 |
| 广义 CRT | [洛谷 P4777](https://www.luogu.com.cn/problem/P4777) | 不互质合并、无解与乘法溢出 |
| 高斯消元 | [洛谷 P3389](https://www.luogu.com.cn/problem/P3389) | 选主元、无解和多解 |
| 线段相交 | [AOJ CGL_2_B](https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_B) | 端点接触、共线重叠、整数叉积 |
| 凸包 | [洛谷 P2742](https://www.luogu.com.cn/problem/P2742) | 共线边界点是否保留 |

## 用两年区域赛报告做实战迁移

| 能力 | 2024 代表 | 2025 代表 | 对应板子 |
|---|---|---|---|
| 结构刻画后贪心 | 杭州 E/M、昆明 L、上海 G | 武汉 F、成都 C、香港 J、南京 G | 排序贪心、二分、堆、凸壳思想 |
| 等价类与连通性 | 杭州 A/F、沈阳 M | 南京 F、成都 L | DSU、带权 DSU、SCC、DSU on tree |
| 小状态压缩 | 沈阳 E、济南 B、重庆 A | 成都 B、上海 D、重庆 B | 状压 DP、SOS DP、矩阵快速幂 |
| 树上贡献 | 南京 G、济南 I、哈尔滨 L | 西安 J、重庆 F、香港 B | LCA、树形 DP、换根、HLD |
| 字符串结构 | 以前后缀与匹配为主 | 南京 H、哈尔滨 J、重庆 K、香港 K | KMP/Z、Manacher、滚动哈希、后缀结构 |

报告中的“铜/银”由奖牌区正式队通过率与题解门槛综合得到，只用于制定训练顺序。完整题名、链接、通过率和同构题见 [两年报告](../contest-reviews/README.md)。
