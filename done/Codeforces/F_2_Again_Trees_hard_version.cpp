#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops,no-stack-protector")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)

#ifdef LOCAL
#define ZTMYACANESOCUTE // freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

template<class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

#define int long long

const int MOD = 1e9 + 7;

inline void fwt(vector<int> &f, bool inv = false) {
    const int N = 31 - __builtin_clz(ssize(f)),
              inv2 = (MOD + 1) / 2;
    rep (i, 0, N) rep (j, 0, 1 << N) {
        if (j >> i & 1 ^ 1) {
            int a = f[j], b = f[j | (1 << i)];
            if (inv) {
                f[j] = (a + b) * inv2 % MOD;
                f[j | (1 << i)] = (a - b + MOD) * inv2 % MOD;
            } else {
                f[j] = (a + b) % MOD;
                f[j | (1 << i)] = (a - b + MOD) % MOD;
            }
        }
    }
}

const int MAXN = 1e5 + 5;

int32_t dp2[MAXN][1 << 10];
int pc[1 << 10];

inline char readchar() {
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p == q && (q = (p=buf)+fread(buf,1,S,stdin)) == buf) return EOF;
	return *p++;
}

inline int in() {
	int x = 0, c = readchar();
	while(('0' > c || c > '9') && c!='-' && c!=EOF) c = readchar();
	while('0' <= c && c <= '9') x = x*10 + (c^'0'), c = readchar();
	return x; // returns 0 if EOF
}

int fpow(int x, int e) {
    int res = 1;
    while (e > 0) {
        if (e & 1) res = res * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return res;
}

inline void solve() {
    int n = in(), k = in();
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a = in(), b = in();
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    } 
    vector<int> val(n), b(k);
    rep (i, 0, n) val[i] = in();
    rep (i, 0, k) b[i] = in();
    vector<int> com(1 << k);
    unordered_map<int, int> id;
    vector<int> basis(1 << k);
    rep (bit, 0, 1 << k) {
        rep (i, 0, k) if (bit >> i & 1) {
            com[bit] ^= b[i];
        }
        if (!id.contains(com[bit])) {
            id[com[bit]] = bit;
            bool f = 0;
            rep (i, 0, k) if (com[bit] == b[i]) {
                f = 1;
                break;
            }
            if (f) basis[bit] = 1;
        }
    }
    fwt(basis);
    vector<int> dp(n);
    int inv = fpow(1 << k, MOD - 2);
    // \sum f_{a xor g_i} = [x^a] (f*g)
    rep (i, 0, n) rep (j, 0, 1 << k) dp2[i][j] = 1;
    auto dfs = [&](auto &&self, int u, int pa) -> void {
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u);
            val[u] ^= val[v];
            rep (i, 0, 1 << k) dp2[u][i] = 1LL * dp2[u][i] * dp2[v][i] % MOD;
        }
        if (id.contains(val[u])) {
            int pos = id[val[u]];
            __int128_t sum = 0;
            rep (i, 0, 1 << k) sum += 1LL * (pc[pos & i] ? -1 : 1) * dp2[u][i] * basis[i];
            sum = (sum % MOD + MOD) * inv % MOD;
            dp[u] = sum;
            rep (i, 0, 1 << k) {
                if (pc[pos & i]) {
                    dp2[u][i] += MOD - dp[u];
                } else {
                    dp2[u][i] += dp[u];
                }
                if (dp2[u][i] >= MOD) dp2[u][i] -= MOD;
            }
        }
    };
    dfs(dfs, 0, -1);
    cout << dp[0] << '\n';
}
 
signed main() {
    // ZTMYACANESOCUTE;
    int T = in();
    rep (i, 1, 1 << 10) pc[i] = pc[i >> 1] ^ (i & 1);
    while (T--) {
        solve();
    }
}