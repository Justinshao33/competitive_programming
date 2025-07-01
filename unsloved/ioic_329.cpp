#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0)
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define debug(x) cerr << #x << " = " << x << '\n';
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

pii operator + (const pii &p1, const pii &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pii operator - (const pii &p1, const pii &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }

template<class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

#define lpos pos << 1
#define rpos pos << 1 | 1
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename A> ostream& operator << (ostream &os, const vector<A> &p) { for(const auto &a : p) os << a << " "; os << '\n'; return os; }
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n, m; cin >> n >> m;
    vector<int> v(n);
    vector<vector<int>> adj(n);
    rep (i, 0, n) cin >> v[i];
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int cnt = 0, cnt2 = 0;
    vector<int> dfn(n, 0), st, cid(n, 0);
    vector<bool> is_pt(n, 0), last(n, 0);
    auto getid = [&](auto self, int u, int pa) -> void {
        dfn[u] = ++cnt;
        st.pb(u);
        for (int v : adj[u]) {
            if (v == pa || dfn[v] > dfn[u]) continue;
            if (dfn[v]) {
                last[u] = 1;
                cnt2++;
                while (st.back() != v) {
                    cid[st.back()] = cnt2;
                    st.pop_back();
                }
                cid[st.back()] = cnt2;
                st.pop_back();
            } else {
                self(self, v, u);
            }
        }
        if (!st.empty() && st.back() == u) {
            is_pt[u] = 1;
            cid[u] = ++cnt2;
            st.pop_back();
        }
    };
    getid(getid, 0, -1);
    vector<bool> vis(n, 0);
    vector dp(n, vector<vector<int>>(2, vector<int>(2, 0)));
    auto dfs = [&](auto self, int u, int pa) -> void {
        vis[u] = 1;
        if (last[u]) {
            dp[u][0][0] = 0;
            dp[u][1][1] = v[u];
            dp[u][0][1] = dp[u][1][0] = -IINF;
        } else {
            rep (i, 0, 2) dp[u][1][i] = v[u];
        }
        for (int v : adj[u]) {
            if (v == pa || vis[v]) continue;
            self(self, v, u);
            if (is_pt[v]) {
                rep (i, 0, 2) rep (j, 0, 2) {
                    int val = 0;
                    rep (k, 0, 2) {
                        chmax(val, dp[u][i ^ 1][k]);
                    }
                    dp[u][i][j] += val;
                }
            } else if (cid[u] == cid[v]) {
                dp[u][0][0] += dp[v][1][0];
                dp[u][1][0] += dp[v][0][0];
                dp[u][0][1] += dp[v][1][1];
                dp[u][1][1] += dp[v][0][1];
            } else {
                int val = max(dp[v][0][0], dp[v][0][1]);
                dp[u][0][0] += dp[v][1][0];
                dp[u][1][0] += val;
                dp[u][0][1] += dp[v][1][0];
                dp[u][1][1] += val;
            }
        }
    };
    dfs(dfs, 0, -1);
    int ans = 0;
    ans = max({dp[0][0][0], dp[0][0][1], dp[0][1][0]});
    if (is_pt[0]) cout << max(ans, dp[0][1][1]) << '\n';
    else cout << ans << '\n';;
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}