#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define int long long

using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
using pld = pair<ld, ld>;
#define fi first
#define se second

#ifdef LOCAL
#define ZTMYACANESOCUTE // freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

void dbg() { cerr << '\n'; }
template<typename T, typename ...U>
void dbg(T t, U ...u) { cerr << t << ' '; dbg(u...); }

pii operator + (const pii &p1, const pii &p2) { return make_pair(p1.fi + p2.fi, p1.se + p2.se); }
pii operator - (const pii &p1, const pii &p2) { return make_pair(p1.fi - p2.fi, p1.se - p2.se); }

template<class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

#define lpos pos << 1
#define rpos pos << 1 | 1
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename A> ostream& operator << (ostream &os, const vector<A> &p) { for(const auto &a : p) os << a << " "; os << '\n'; return os; }
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n; cin >> n;
    vector<int> a(n), c(n);
    rep (i, 0, n) cin >> a[i];
    rep (i, 0, n) cin >> c[i];
    vector<int> st;
    vector<int> L(n, -1), R(n, -1);
    rep (i, 0, n) {
        while (!st.empty() && (a[st.back()] < a[i] || (a[st.back()] == a[i] && c[st.back()] > c[i]))) {
            L[i] = st.back();
            st.pop_back();
        }
        if (!st.empty()) R[st.back()] = i;
        st.push_back(i);
    }
    vector<int> F(n, -1);
    auto dp = c;
    auto dfs = [&](auto self, int u) -> void {
        if (L[u] != -1) {
            F[L[u]] = u;
            chmin(dp[L[u]], dp[u]);
            self(self, L[u]);
        }
        if (R[u] != -1) {
            F[R[u]] = u;
            chmin(dp[R[u]], dp[u]);
            self(self, R[u]);
        }
    };
    dfs(dfs, st[0]);
    dp[st[0]] = 0;
    int ans = accumulate(all(dp), 0LL);
    cout << ans << ' ';
    vector<bool> vis(n, 0);
    auto dfs2 = [&](auto self, int u) -> void {
        vis[u] = 1;
        ans -= dp[u];
        if (L[u] != -1 && !vis[L[u]]) self(self, L[u]);
        if (R[u] != -1 && !vis[R[u]]) self(self, R[u]);
    };
    rep (i, 0, n) {
        int p; cin >> p;
        p--;
        if (!vis[p]) {
            while (F[p] != -1 && a[F[p]] == a[p]) p = F[p];
            dfs2(dfs2, p);
        }
        cout << ans << " \n" [i == n - 1];
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}