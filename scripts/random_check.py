#!/usr/bin/env python3
"""对高风险模板做小数据随机对拍。参数为已编译二进制目录。"""

from itertools import product
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


if __name__ == "__main__":
    check_binary_segment_tree()
    check_persistent_segment_tree()
    check_two_sat()
    print("random checks passed: binary segment tree, persistent segment tree, 2-SAT")
