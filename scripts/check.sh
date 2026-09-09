#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD="$ROOT/build"

if [[ -n "${CXX:-}" ]]; then
    COMPILER="$CXX"
elif command -v g++-15 >/dev/null 2>&1; then
    COMPILER="g++-15"
else
    COMPILER="g++"
fi

mkdir -p "$BUILD"
count=0
while IFS= read -r file; do
    name="$(basename "${file%.cpp}")"
    "$COMPILER" -std=c++17 -O2 -Wall -Wextra "$file" -o "$BUILD/$name"
    count=$((count + 1))
done < <(find "$ROOT/00-basic" "$ROOT/01-signin" "$ROOT/02-bronze" "$ROOT/03-silver" -name '*.cpp' | sort)
echo "compiled $count C++17 templates with $COMPILER"

check_case() {
    local name="$1" input="$2" expected="$3" actual
    actual="$(printf '%s' "$input" | "$BUILD/$name")"
    if [[ "$actual" != "$expected" ]]; then
        echo "sample failed: $name"
        echo "expected:"
        printf '%s\n' "$expected"
        echo "actual:"
        printf '%s\n' "$actual"
        return 1
    fi
}

check_case prefix_difference $'5 2\n1 2 3 4 5\n1 3 2\n2 5 -1\n' '3 3 4 3 4'
check_case dsu $'5 5\n1 1 2\n2 1 2\n2 1 3\n1 2 3\n2 1 3\n' $'Y\nN\nY'
check_case fenwick $'5 3\n1 2 3 4 5\n2 2 4\n1 3 5\n2 2 4\n' $'9\n14'
check_case segment_tree_lazy $'5 3\n1 2 3 4 5\n2 1 5\n1 2 4 1\n2 2 4\n' $'15\n12'
check_case dijkstra $'4 4 1\n1 2 2\n1 3 5\n2 3 1\n3 4 2\n' '0 2 3 5'
check_case kmp_z $'ababa aba\n' $'1\n3\n0 0 1'
check_case binary_sequence_segment_tree $'5 7\n1 0 1 1 0\n3 0 4\n4 0 4\n2 1 3\n3 0 4\n4 0 4\n0 2 4\n4 0 4\n' $'3\n2\n2\n2\n2'
check_case scc $'4 4\n1 2 3 4\n1 2\n2 1\n2 3\n3 4\n' '10'
check_case two_sat $'2 2\n1 1 1 1\n2 0 1 1\n' $'POSSIBLE\n1 0'
check_case dinic $'4 5 1 4\n1 2 3\n1 3 2\n2 3 1\n2 4 2\n3 4 3\n' '5'
check_case min_cost_flow $'3 3 1 3\n1 2 2 1\n2 3 2 1\n1 3 1 5\n' '3 9'
check_case persistent_segment_tree $'5 3\n1 5 2 4 3\n1 5 3\n2 4 2\n3 3 1\n' $'3\n4\n2'
check_case ac_automaton $'4\nhe\nshe\nhers\nhis\nahishers\n' '4'
check_case manacher $'abacaba\n' '7'
check_case digit_dp $'1 20\n' '19'
check_case linear_basis $'3\n1 2 4\n' '7'

PYTHON_BIN="${PYTHON:-python3}"
"$PYTHON_BIN" "$ROOT/scripts/random_check.py" "$BUILD"
"$PYTHON_BIN" "$ROOT/scripts/check_links.py"
echo "all checks passed"
