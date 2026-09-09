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

if [[ "$count" -ne 61 ]]; then
    echo "template count mismatch: expected 61, got $count"
    exit 1
fi

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
check_case simulation_enumeration $'4 5\n1 2 3 4\n' '2'
check_case greedy_sort $'5\n1 3\n2 5\n4 6\n6 7\n5 9\n' '3'
check_case basic_dp $'3 3\n1 3 1\n1 5 1\n4 2 1\n' '7'
check_case monotonic_stack $'5\n2 1 4 3 5\n' '0 1 0 3 0'
check_case rolling_hash $'abacaba\n3\n1 3 5 7\n1 2 2 3\n3 4 4 5\n' $'Yes\nNo\nNo'
check_case bellman_ford $'4 4 1\n1 2 3\n2 3 -2\n1 3 5\n3 4 1\n' '0 3 1 2'
check_case euler_trail $'3 3\n1 2\n2 3\n3 1\n' '1 2 3 1'
check_case bridge_articulation $'5 5\n1 2\n2 3\n3 1\n3 4\n4 5\n' $'2\n3 4\n4 5\n2\n3 4'
check_case matrix_fast_power $'2 10 1000000007\n0 1\n1 1\n' '55'
check_case matrix_fast_power $'2 4 7\n0 1\n1 -1\n' '6'
check_case bitmask_dp $'4\n0 1 15 6\n2 0 7 3\n9 6 0 12\n10 4 8 0\n' '20'
check_case interval_dp $'3\n10 30 5 60\n' '4500'
check_case tree_dp $'5\n1 2 3 4 5\n1 2\n1 3\n3 4\n3 5\n' '11'
check_case dsu_on_tree $'5\n1 2 1 3 2\n1 2\n1 3\n3 4\n3 5\n' '3 1 3 1 1'
check_case rerooting_dp $'5\n1 2\n1 3\n3 4\n3 5\n' '6 9 5 8 8'
check_case sos_dp $'2\n1 2 3 4\n' '1 3 4 10'
check_case difference_constraints $'3 3\n1 2 -1\n2 3 -2\n1 3 0\n' $'YES\n0 -1 -3'
check_case weighted_dsu $'4 5\n1 1 2 3\n1 2 3 4\n2 1 3\n2 3 1\n2 1 4\n' $'7\n-7\nUNKNOWN'
check_case rollback_dsu $'4 7\n1 1 2\n2\n1 2 3\n4 1 3\n3 1\n4 1 3\n4 1 2\n' $'1\nY\nN\nY'
check_case hopcroft_karp $'3 3 5\n1 1\n1 2\n2 2\n3 2\n3 3\n' '3'
check_case gaussian_elimination $'2\n1 1 3\n2 -1 0\n' $'1.0000000000\n2.0000000000'
check_case chinese_remainder $'2\n2 3\n3 5\n' '8 15'
check_case suffix_array $'banana\n' $'5 3 1 0 4 2\n0 1 3 0 0 2'
check_case li_chao_tree $'5\n1 2 1\n2 3\n1 -1 10\n2 3\n2 -2\n' $'7\n7\n12'
check_case geometry_base $'3\n0 0 4 4 0 4 4 0\n0 0 2 0 2 0 3 0\n0 0 1 0 2 0 3 0\n' $'YES\nYES\nNO'

PYTHON_BIN="${PYTHON:-python3}"
"$PYTHON_BIN" "$ROOT/scripts/random_check.py" "$BUILD"
"$PYTHON_BIN" "$ROOT/scripts/test_check_links.py"
"$PYTHON_BIN" "$ROOT/scripts/check_links.py"

for report in \
    "$ROOT/contest-reviews/2024_ICPC_CCPC_铜银题冲银训练图谱.pdf" \
    "$ROOT/contest-reviews/2025_ICPC_CCPC_铜银题冲银训练图谱.pdf"; do
    if [[ ! -s "$report" ]]; then
        echo "missing report: ${report#"$ROOT/"}"
        exit 1
    fi
done
echo "contest report artifacts passed"
echo "all checks passed"
