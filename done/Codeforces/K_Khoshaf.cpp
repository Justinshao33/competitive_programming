#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define int i64
#define all(a) begin(a), end(a)
#define rep(a, b, c) for (int a = b; a < c; a++) 

const int MOD = 1e9 + 7;

void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int C2(int x) {
    return x * (x - 1) / 2;
}

void solve() {
    int n, K, L, R; cin >> n >> K >> L >> R;
    if (n >= 500) {
        cout << 0 << '\n';
        return;
    }
    vector<int> cnt(3, 0);
    rep (i, 0, 3) cnt[i] = ((R - i) < 0 ? -1 : (R - i) / 3) - (L - 1 - i < 0 ? -1 : (L - 1 - i) / 3);
    // rep (i, 0, 3) {
    //     cout << cnt[i] << " \n" [i == 2];
    // }
    int sz = 0;
    while (sz * (sz - 1) / 2 <= K) sz++;
    sz += 5;
    vector dp(sz + 1, vector (sz + 1, vector<int> (3, 0))); // 0, 1
    dp[1][0][0] = 1;
    rep (i, 0, n) {
        vector g(sz + 1, vector (sz + 1, vector<int>(3, 0)));
        rep (j, 0, sz + 1) rep (k, 0, sz + 1) rep (d, 0, 3) rep (nd, 0, 3) {
            int cur = (d + nd) % 3;
            if (cur == 0 && j + 1 <= sz) add(g[j + 1][k][cur], dp[j][k][d] * cnt[nd] % MOD);
            if (cur == 1 && k + 1 <= sz) add(g[j][k + 1][cur], dp[j][k][d] * cnt[nd] % MOD);
            if (cur == 2) add(g[j][k][cur], dp[j][k][d] * cnt[nd] % MOD);
        }
        swap(dp, g);
    }
    int ans = 0;
    rep (i, 0, sz + 1) rep (j, 0, sz + 1) if (i + j <= n + 1) rep (d, 0, 3) {
        if (C2(i) + C2(j) + C2(n + 1 - i - j) == K) add(ans, dp[i][j][d]);
    }
    cout << ans << '\n';
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("khoshaf.in", "r", stdin);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}