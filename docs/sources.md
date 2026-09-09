# 资料来源、融合方法与取舍

这不是某一份模板的搬运版。仓库用不同资料解决不同问题：现场手册决定“多短才可用”，算法百科负责“为什么正确”，官方库与验证仓库负责“怎样测”，2024–2025 区域赛复盘负责“先学什么”。所有源码均按本仓库风格重新实现；外部代码没有直接复制。

## 参考体系

| 资料 | 我从中吸收什么 | 不直接照搬什么 |
|---|---|---|
| [KACTL](https://github.com/kth-competitive-programming/kactl) | 短、快、可修改；文件头写用途、复杂度和测试状态；压力测试 | 极限压行和依赖统一宏的写法 |
| [AtCoder Library](https://github.com/atcoder/ac-library) | 明确接口与约束；DSU、Fenwick、Segtree、SCC、流、卷积的可靠基线 | 泛型程度较高、依赖整库 include 的接口 |
| [Library Checker](https://github.com/yosupo06/library-checker-problems) | 标准化任务、强数据生成器和验证问题 | 银牌目标之外的大量多项式与动态数据结构 |
| [ecnerwala/cp-book](https://github.com/ecnerwala/cp-book) | 独立 header、自动 bundle、competitive-verifier 与 CI | C++23 依赖和高抽象接口 |
| [Stanford ACM notebook](https://github.com/jaehyunp/stanfordacm) | 经典 ICPC 手册的专题组织与 PDF 生成 | 年代较久的接口和未统一测试状态的实现 |
| [bqi343/cp-notebook](https://github.com/bqi343/cp-notebook) | 题单、难度与实现交叉组织，数据结构覆盖广 | 与个人宏体系紧耦合的代码 |
| [hitonanode/cplib-cpp](https://github.com/hitonanode/cplib-cpp) | 小组件、验证文件和复用边界 | 超出区域赛银尾的长尾组件 |
| [maspypy/library](https://github.com/maspypy/library) | 现代算法覆盖、OJ 验证与高阶扩展视野 | 为追求全覆盖而引入的复杂模板 |
| [NyaanNyaan/library](https://github.com/NyaanNyaan/library) | 图、数据结构、数论、多项式的现代目录 | 高阶多项式和低频动态结构 |
| [OI Wiki](https://oi-wiki.org/) | 中文定义、前提、证明、复杂度和完整知识树 | 将百科全目录塞进个人现场板 |
| [cp-algorithms](https://cp-algorithms.com/) | 标准算法推导、证明、边界和练习入口 | 与本项目目标无关的完整专题 |
| [CSES Handbook / Problem Set](https://cses.fi/book/index.php) | 从基础到图、DP、树、字符串的渐进训练顺序 | 将中学生赛制难度直接等同于 ICPC 奖牌线 |
| [USACO Guide](https://usaco.guide/general/using-this-guide) | 前置知识、模块化课程和题单验收 | USACO Bronze/Silver 名称与本仓库铜银层级混用 |
| [AC Library 文档](https://atcoder.github.io/ac-library/master/document_en/) | 输入约束、行为边界和测试过的公共组件清单 | 假设比赛环境预装 ACL |
| 用户提供的 WIDA 打印版 | 中文现场板的候选全集与常用函数速查 | 原 PDF、原代码和 116 页全量目录均不上传 |

## 为什么分成 A / B / C

- **A · 必须背**：高频、短、跨题迁移强。离开模板也应在 10–20 分钟写出。
- **B · 熟练改**：理解不变量与接口，现场从个人板复制后能可靠改题。
- **C · 知道去哪找**：低频、长或实现风险高。赛前按队伍专长准备，不占用全员记忆。

KACTL 的取舍很有启发：它会因为篇幅排除“太简单”和“太少见”的算法。ICPC World Finals 的团队参考文档也长期以 25 页为典型限制，因此本仓库把“完整学习库”和“最终打印板”视为两件东西。代码仓库可以完整，真正带上场的 PDF 应由队伍按短板二次裁剪。

## 本版为何新增这些模板

2024–2025 ICPC/CCPC 铜银题复盘反复出现以下能力，而首版覆盖不足：

- 模拟、观察、构造和贪心证明：往往决定铜牌包罚时。
- 树形 DP、换根与 DSU on tree：多站银牌第 k+1 题的公共骨架。
- 矩阵快速幂、状压与 SOS：把小状态推广到巨大步数或位掩码偏序。
- 字符串哈希、KMP/Manacher 的组合：不只做裸匹配，还承担树路径和计数结构。
- 欧拉路、桥/割点、差分约束：标准图模型的明显缺口。

因此本版优先补这些内容，而不是先加入 Min25、LCT、一般图带权匹配和形式幂级数。

## 许可与引用边界

- 本仓库 MIT 许可只覆盖本仓库原创的代码与文字。
- 外部题面、教程和报告链接的版权归各平台或作者。
- 资料链接用于说明研究来源，不代表外部项目为本仓库正确性背书。
- 若未来直接引入外部实现，必须逐文件核对许可证并保留作者与来源；当前版本没有这样做。
