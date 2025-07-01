#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
using pll = pair<ll, ll>;
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
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.fi + p2.fi, p1.se + p2.se); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.fi - p2.fi, p1.se - p2.se); }

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
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n; cin >> n;
    vector<int> v(n), p(n), dic;
    rep (i, 0, n) cin >> v[i] >> p[i], v[i] = -v[i], dic.pb(v[i]), dic.pb(p[i]);
    sort(all(dic));
    dic.erase(unique(all(dic)), dic.end());
    rep (i, 0, n) v[i] = lower_bound(all(dic), v[i]) - dic.begin();
    rep (i, 0, n) p[i] = lower_bound(all(dic), p[i]) - dic.begin();
    vector<vector<int>> adj(n + n);
    rep (i, 0, n) {
        adj[v[i]].pb(i);
        adj[p[i]].pb(i);
    }
    // debug(v, p);
    // rep (i, 0, 2 * n) cout << adj[i];
    vector<int> ans, it(n + n, 0);
    vector<bool> vis(n, 0);
    int odd = 0, st = 0;
    rep (i, 0, n + n) if (adj[i].size() % 2) {
        odd++;
        st = i;
    } 
    if (odd != 0 && odd != 2) {
        cout << "NO\n";
        return;
    }
    auto dfs = [&](auto self, int u, int eid) -> void {
        for (; it[u] < ssize(adj[u]); it[u]++) {
            int id = adj[u][it[u]];
            if (vis[id]) continue;
            vis[id] = 1;
            int nv = (u ^ p[id] ^ v[id]);
            self(self, nv, id);
        }
        if (eid != -1) ans.pb(eid);
    };
    dfs(dfs, st, -1);
    reverse(all(ans));
    // cout << ans;
    if (ssize(ans) != n) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int x : ans) cout << x + 1 << ' ';
        cout << '\n';
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}