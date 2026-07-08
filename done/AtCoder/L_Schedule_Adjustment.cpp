#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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

struct TwoSat {
    int n;
    vector<vector<int>> G;
    vector<bool> ans;
    vector<int> id, dfn, low, stk;
    TwoSat(int n) : n(n), G(2 * n) {}
    void addClause(int u, bool f, int v, bool g) { // (u = f) or (v = g)
        G[2 * u + !f].push_back(2 * v + g);
        G[2 * v + !g].push_back(2 * u + f);
    }
    void addImply(int u, bool f, int v, bool g) { // (u = f) -> (v = g)
        G[2 * u + f].push_back(2 * v + g);
        G[2 * v + !g].push_back(2 * u + !f);
    }
    int addVar() {
        G.emplace_back();
        G.emplace_back();
        return n++;
    }
    void addAtMostOne(const vector<pair<int, bool>> &li) {
        if (ssize(li) <= 1) return;
        int pu; bool pf; tie(pu, pf) = li[0];
        for (int i = 2; i < ssize(li); i++) {
            const auto &[u, f] = li[i];
            int nxt = addVar();
            addClause(pu, !pf, u, !f);
            addClause(pu, !pf, nxt, true);
            addClause(u, !f, nxt, true);
            tie(pu, pf) = make_pair(nxt, true);
        }
        addClause(pu, !pf, li[1].first, !li[1].second);
    } // {b42333}
    int cur = 0, scc = 0;
    void dfs(int u) {
        stk.push_back(u);
        dfn[u] = low[u] = cur++;
        for (int v : G[u]) {
            if (dfn[v] == -1) {
                dfs(v);
                chmin(low[u], low[v]);
            } else if (id[v] == -1) {
                chmin(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            int x;
            do {
                x = stk.back();
                stk.pop_back();
                id[x] = scc;
            } while (x != u);
            scc++;
        }
    }
    bool satisfiable() {
        ans.assign(n, 0);
        id.assign(2 * n, -1);
        dfn.assign(2 * n, -1);
        low.assign(2 * n, -1);
        for (int i = 0; i < n * 2; i++)
            if (dfn[i] == -1) {
                dfs(i);
            }
        for (int i = 0; i < n; ++i) {
            if (id[2 * i] == id[2 * i + 1]) {
                return false;
            }
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }
}; // [9fb62b] \ addVar, addAtMostOne

void solve() {
    int n, m; cin >> n >> m;
    vector a(n, vector<int>(2));
    rep (i, 0, n) {
        int b; cin >> b;
        a[i][0] = b;
        int d; cin >> d;
        a[i][1] = b + d;
    }
    vector<pii> edge;
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        edge.push_back({a, b});
    }
    auto check = [&](int x) -> bool {
        TwoSat ts(n);
        for (const auto &[u, v] : edge) {
            rep (i, 0, 2) rep (j, 0, 2) {
                if (abs(a[u][i] - a[v][j]) < x) {
                    ts.addImply(u, i, v, j ^ 1);
                    ts.addImply(v, j, u, i ^ 1);
                }
            }
        }
        return ts.satisfiable();
    };
    int l = 0, r = IINF * 2;
    while (r - l > 1) {
        int mid = l + r >> 1;
        if (check(mid)) l = mid;
        else r = mid;
    }
    cout << l << '\n';
    vector<int> ans(n);
    rep (i, 0, n) {
        TwoSat ts(n);
        rep (j, 0, i + 1) ts.addClause(j, ans[j], j, ans[j]);
        for (const auto &[u, v] : edge) {
            rep (i, 0, 2) rep (j, 0, 2) {
                if (abs(a[u][i] - a[v][j]) < l) {
                    ts.addImply(u, i, v, j ^ 1);
                    ts.addImply(v, j, u, i ^ 1);
                }
            }
        }
        ans[i] = ts.satisfiable() ^ 1;
        cout << ans[i];
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}