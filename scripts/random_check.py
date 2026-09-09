#!/usr/bin/env python3
"""对高风险模板做小数据随机对拍。参数为已编译二进制目录。"""

from itertools import product
from math import lcm
from pathlib import Path
import random
import subprocess
import sys


BIN = Path(sys.argv[1]) if len(sys.argv) > 1 else Path("build")
RNG = random.Random(20260909)


def run(name: str, data: str) -> str:
    result = subprocess.run(
        [str(BIN / name)], input=data, text=True, capture_output=True, check=True
    )
    return result.stdout.strip()


def check_binary_segment_tree() -> None:
    for _ in range(200):
        n = RNG.randint(1, 18)
        arr = [RNG.randrange(2) for _ in range(n)]
        cur = arr[:]
        ops = []
        expected = []
        for _ in range(80):
            op = RNG.randrange(5)
            l = RNG.randrange(n)
            r = RNG.randrange(l, n)
            ops.append((op, l, r))
            if op == 0:
                cur[l : r + 1] = [0] * (r - l + 1)
            elif op == 1:
                cur[l : r + 1] = [1] * (r - l + 1)
            elif op == 2:
                cur[l : r + 1] = [x ^ 1 for x in cur[l : r + 1]]
            elif op == 3:
                expected.append(str(sum(cur[l : r + 1])))
            else:
                best = now = 0
                for x in cur[l : r + 1]:
                    now = now + 1 if x else 0
                    best = max(best, now)
                expected.append(str(best))
        data = f"{n} {len(ops)}\n" + " ".join(map(str, arr)) + "\n"
        data += "\n".join("%d %d %d" % x for x in ops) + "\n"
        assert run("binary_sequence_segment_tree", data).splitlines() == expected


def check_persistent_segment_tree() -> None:
    for _ in range(120):
        n = RNG.randint(1, 40)
        arr = [RNG.randint(-20, 20) for _ in range(n)]
        queries = []
        expected = []
        for _ in range(60):
            l = RNG.randint(1, n)
            r = RNG.randint(l, n)
            k = RNG.randint(1, r - l + 1)
            queries.append((l, r, k))
            expected.append(str(sorted(arr[l - 1 : r])[k - 1]))
        data = f"{n} {len(queries)}\n" + " ".join(map(str, arr)) + "\n"
        data += "\n".join("%d %d %d" % x for x in queries) + "\n"
        assert run("persistent_segment_tree", data).splitlines() == expected


def check_two_sat() -> None:
    for _ in range(160):
        n = RNG.randint(1, 7)
        clauses = []
        for _ in range(RNG.randint(1, 18)):
            clauses.append((RNG.randint(1, n), RNG.randrange(2), RNG.randint(1, n), RNG.randrange(2)))
        good = []
        for values in product(range(2), repeat=n):
            if all(values[x - 1] == a or values[y - 1] == b for x, a, y, b in clauses):
                good.append(values)
        data = f"{n} {len(clauses)}\n" + "\n".join("%d %d %d %d" % x for x in clauses) + "\n"
        out = run("two_sat", data).splitlines()
        if not good:
            assert out == ["IMPOSSIBLE"]
        else:
            assert out[0] == "POSSIBLE"
            values = tuple(map(int, out[1].split()))
            assert len(values) == n
            assert all(values[x - 1] == a or values[y - 1] == b for x, a, y, b in clauses)


def check_sos_dp() -> None:
    for _ in range(120):
        k = RNG.randint(0, 8)
        n = 1 << k
        values = [RNG.randint(-20, 20) for _ in range(n)]
        expected = [
            sum(values[sub] for sub in range(n) if sub & mask == sub)
            for mask in range(n)
        ]
        data = f"{k}\n" + " ".join(map(str, values)) + "\n"
        actual = list(map(int, run("sos_dp", data).split()))
        assert actual == expected


def check_weighted_dsu() -> None:
    for _ in range(100):
        n = RNG.randint(1, 20)
        potential = [0] + [RNG.randint(-100, 100) for _ in range(n)]
        parent = list(range(n + 1))

        def find(x: int) -> int:
            while parent[x] != x:
                x = parent[x]
            return x

        ops = []
        expected = []
        for _ in range(100):
            x, y = RNG.randint(1, n), RNG.randint(1, n)
            if RNG.randrange(3):
                ops.append((1, x, y, potential[y] - potential[x]))
                fx, fy = find(x), find(y)
                if fx != fy:
                    parent[fx] = fy
            else:
                ops.append((2, x, y))
                if find(x) == find(y):
                    expected.append(str(potential[y] - potential[x]))
                else:
                    expected.append("UNKNOWN")
        data = f"{n} {len(ops)}\n"
        data += "\n".join(" ".join(map(str, op)) for op in ops) + "\n"
        assert run("weighted_dsu", data).splitlines() == expected


def check_suffix_array() -> None:
    alphabet = "abcd"
    for _ in range(160):
        n = RNG.randint(1, 35)
        s = "".join(RNG.choice(alphabet) for _ in range(n))
        sa = sorted(range(n), key=lambda i: s[i:])
        lcp = [0]
        for i in range(1, n):
            x, y, same = sa[i - 1], sa[i], 0
            while x + same < n and y + same < n and s[x + same] == s[y + same]:
                same += 1
            lcp.append(same)
        lines = run("suffix_array", s + "\n").splitlines()
        assert list(map(int, lines[0].split())) == sa
        assert list(map(int, lines[1].split())) == lcp


def check_hopcroft_karp() -> None:
    for _ in range(120):
        nl, nr = RNG.randint(1, 7), RNG.randint(1, 7)
        edges = [(x, y) for x in range(1, nl + 1) for y in range(1, nr + 1)
                 if RNG.randrange(3) == 0]
        possible = {x: [] for x in range(1, nl + 1)}
        for x, y in edges:
            possible[x].append(y)
        dp = {0: 0}
        for x in range(1, nl + 1):
            nxt = dict(dp)
            for mask, value in dp.items():
                for y in possible[x]:
                    if not (mask >> (y - 1) & 1):
                        new_mask = mask | 1 << (y - 1)
                        nxt[new_mask] = max(nxt.get(new_mask, 0), value + 1)
            dp = nxt
        data = f"{nl} {nr} {len(edges)}\n"
        data += "\n".join(f"{x} {y}" for x, y in edges) + "\n"
        assert int(run("hopcroft_karp", data)) == max(dp.values())


def check_li_chao_tree() -> None:
    for _ in range(100):
        lines = []
        ops = []
        expected = []
        for _ in range(60):
            if not lines or RNG.randrange(3):
                k, b = RNG.randint(-30, 30), RNG.randint(-100, 100)
                lines.append((k, b))
                ops.append((1, k, b))
            else:
                x = RNG.randint(-40, 40)
                ops.append((2, x))
                expected.append(str(max(k * x + b for k, b in lines)))
        data = f"{len(ops)}\n" + "\n".join(" ".join(map(str, op)) for op in ops) + "\n"
        assert run("li_chao_tree", data).splitlines() == expected


def check_rollback_dsu() -> None:
    for _ in range(100):
        n = RNG.randint(1, 15)
        history = []
        ops = []
        expected = []

        def connected(x: int, y: int) -> bool:
            parent = list(range(n + 1))

            def find(z: int) -> int:
                while parent[z] != z:
                    z = parent[z]
                return z

            for a, b in history:
                a, b = find(a), find(b)
                if a != b:
                    parent[a] = b
            return find(x) == find(y)

        for _ in range(80):
            kind = RNG.randrange(4)
            if kind == 0:
                x, y = RNG.randint(1, n), RNG.randint(1, n)
                history.append((x, y))
                ops.append((1, x, y))
            elif kind == 1:
                ops.append((2,))
                expected.append(str(len(history)))
            elif kind == 2:
                version = RNG.randint(0, len(history))
                history = history[:version]
                ops.append((3, version))
            else:
                x, y = RNG.randint(1, n), RNG.randint(1, n)
                ops.append((4, x, y))
                expected.append("Y" if connected(x, y) else "N")
        data = f"{n} {len(ops)}\n" + "\n".join(" ".join(map(str, op)) for op in ops) + "\n"
        assert run("rollback_dsu", data).splitlines() == expected


def check_chinese_remainder() -> None:
    for _ in range(160):
        congruences = [(RNG.randint(-20, 20), RNG.randint(1, 10))
                       for _ in range(RNG.randint(1, 5))]
        merged_mod = 1
        for _, mod in congruences:
            merged_mod = lcm(merged_mod, mod)
        solutions = [x for x in range(merged_mod)
                     if all(x % mod == residue % mod for residue, mod in congruences)]
        data = f"{len(congruences)}\n"
        data += "\n".join(f"{residue} {mod}" for residue, mod in congruences) + "\n"
        output = run("chinese_remainder", data)
        if not solutions:
            assert output == "-1"
        else:
            assert output == f"{solutions[0]} {merged_mod}"


def check_rerooting_dp() -> None:
    for _ in range(120):
        n = RNG.randint(1, 25)
        edges = [(x, RNG.randint(1, x - 1)) for x in range(2, n + 1)]
        graph = [[] for _ in range(n + 1)]
        for x, y in edges:
            graph[x].append(y)
            graph[y].append(x)
        expected = []
        for source in range(1, n + 1):
            dis = [-1] * (n + 1)
            dis[source] = 0
            queue = [source]
            for x in queue:
                for y in graph[x]:
                    if dis[y] == -1:
                        dis[y] = dis[x] + 1
                        queue.append(y)
            expected.append(sum(dis[1:]))
        data = f"{n}\n" + "\n".join(f"{x} {y}" for x, y in edges) + "\n"
        actual = list(map(int, run("rerooting_dp", data).split()))
        assert actual == expected


if __name__ == "__main__":
    check_binary_segment_tree()
    check_persistent_segment_tree()
    check_two_sat()
    check_sos_dp()
    check_weighted_dsu()
    check_suffix_array()
    check_hopcroft_karp()
    check_li_chao_tree()
    check_rollback_dsu()
    check_chinese_remainder()
    check_rerooting_dp()
    print("random checks passed: binary segment tree, persistent segment tree, "
          "2-SAT, SOS DP, weighted DSU, suffix array, Hopcroft-Karp, Li Chao, "
          "rollback DSU, generalized CRT, rerooting DP")
