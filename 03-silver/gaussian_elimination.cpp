// 高斯消元解 n 元实数线性方程组。输出唯一解，或 No solution / Infinite solutions。
// 每列选绝对值最大主元以减小误差。复杂度 O(n^3)，浮点比较使用 EPS。
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<double>> a(n, vector<double>(n + 1));
    for (auto &row : a) for (double &x : row) cin >> x;
    vector<int> where(n, -1);
    int row = 0;
    for (int col = 0; col < n && row < n; col++) {
        int sel = row;
        for (int i = row; i < n; i++) {
            if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
        }
        if (abs(a[sel][col]) < EPS) continue;
        swap(a[sel], a[row]);
        where[col] = row;
        double div = a[row][col];
        for (int j = col; j <= n; j++) a[row][j] /= div;
        for (int i = 0; i < n; i++) {
            if (i == row) continue;
            double c = a[i][col];
            for (int j = col; j <= n; j++) a[i][j] -= c * a[row][j];
        }
        row++;
    }
    for (int i = 0; i < n; i++) {
        bool all_zero = true;
        for (int j = 0; j < n; j++) all_zero &= abs(a[i][j]) < EPS;
        if (all_zero && abs(a[i][n]) >= EPS) {
            cout << "No solution\n";
            return 0;
        }
    }
    if (row < n) {
        cout << "Infinite solutions\n";
        return 0;
    }
    vector<double> ans(n);
    for (int i = 0; i < n; i++) ans[i] = a[where[i]][n];
    cout << fixed << setprecision(10);
    for (double x : ans) cout << (abs(x) < EPS ? 0.0 : x) << '\n';
    return 0;
}
