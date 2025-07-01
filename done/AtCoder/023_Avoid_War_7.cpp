#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include <iostream>
#include <string>
#include <numeric>
#define rep(X, a, b) for(int X = a; X < b; ++X)

const int MOD = 1e9 + 7;

inline void add(int &a, int &b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int n, m;
int dp[1 << 24], g[1 << 24];

void solve() {
    std::cin >> n >> m;
    dp[0] = 1;
    while (n--) {
        std::string s; std::cin >> s;
        rep (bit, 0, 1 << m) if (dp[bit]) {
            int tmp = dp[bit];
            auto dfs = [&](auto self, int i, int bit2) {
                if (i == m) {
                    add(g[bit2], tmp);
                    return;
                }
                self(self, i + 1, bit2);
                if (s[i] == '.' && (i == 0 || ((bit2 >> (i - 1) & 1) == 0 && (bit >> (i - 1) & 1) == 0)) && (bit >> i & 1) == 0 && (i == m - 1 || (bit >> (i + 1) & 1) == 0)) {
                    self(self, i + 1, bit2 | (1 << i));
                }
            };
            dfs(dfs, 0, 0);
        }
        rep (bit, 0, 1 << m) {
            dp[bit] = g[bit];
            g[bit] = 0;
        }
    }
    std::cout << std::accumulate(dp, dp + (1 << m), 0LL) % MOD << '\n';
}
 
int main() {
    std::ios_base::sync_with_stdio(0), std::cin.tie(0);
    solve();
}