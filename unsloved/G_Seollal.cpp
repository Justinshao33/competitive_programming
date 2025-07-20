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
    
    /*
    M1 = xx matroid, M2 = xx matroid
    y<-s if I+y   satisfies M1
    y->t if I+y   satisfies M2
    x<-y if I-x+y satisfies M2
    x->y if I-x+y satisfies M1
    交換圖點權：
    -w[e] if e \in I
    w[e] otherwise
    */
    vector<int> I(, 0);
    while (true) {
        vector<vector<int>> adj();
        int s = , t = s + 1;
        auto M1 = [&]() -> void { // xx matroid
            {   // y<-s
    
            }
            {   // x->y
    
            }
        };
        auto M2 = [&]() -> void { // xx matroid
            {   // y->t
    
            }
            {   // x<-y
    
            }
        };
        auto augment = [&]() -> bool { // 註解掉的是帶權版
            vector<int> vis( + 2, 0), dis( + 2, IINF), from( + 2, -1);
            queue<int> q;
            // vis[s] = 1;
            dis[s] = 0;
            q.push(s);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                // vis[u] = 0;
                for (int v : adj[u]) {
                    int w = ; // no weight -> 1
                    if (chmin(dis[v], dis[u] + w)) {
                        from[v] = u;
                        // if (!vis[v]) {
                            // vis[v] = 1;
                            q.push(v);
                        // }
                    }
                }
            }
            if (from[t] == -1) return false;
            for (int cur = from[t];; cur = from[cur]) {
                if (cur == -1 || cur == s) break;
                I[cur] ^= 1;
            }
            return true;
        };
        M1(), M2();
        if (!augment()) break;
    }
}

vector<int> BuildDomTree(vector<vector<int>> adj, int rt) {
    int n = adj.size();

    // buckets: list of vertices y with sdom(y) = x
    vector<vector<int>> buckets(n), radj(n);

    // rev[dfn[x]] = x
    vector<int> dfn(n, -1), rev(n, -1), pa(n, -1);
    vector<int> sdom(n, -1), dom(n, -1);
    vector<int> fa(n, -1), val(n, -1);

    int stamp = 0;

    // re-number in DFS order
    auto dfs = [&](auto self, int u) -> void {
        rev[dfn[u] = stamp] = u;
        fa[stamp] = sdom[stamp] = val[stamp] = stamp;
        stamp++;
        for (int v : adj[u]) {
            if (dfn[v] == -1) {
                self(self, v);
                pa[dfn[v]] = dfn[u];
            }
            radj[dfn[v]].pb(dfn[u]);
        }
    };

    function<int(int, bool)> Eval = [&](int x, bool fir) {
        if (x == fa[x]) return fir ? x : -1;
        int p = Eval(fa[x], false);
        // x is one step away from the root
        if (p == -1) return x;
        if (sdom[val[x]] > sdom[val[fa[x]]]) val[x] = val[fa[x]];
        fa[x] = p;
        return fir ? val[x] : p;
    };

    auto Link = [&](int x, int y) -> void { fa[x] = y; };

    dfs(dfs, rt);

    // compute sdom in reversed DFS order
    for (int x = stamp - 1; x >= 0; --x) {
        for (int y : radj[x]) {
            // sdom[x] = min({y | (y, x) in E(G), y < x}, {sdom[z] | (y, x) in E(G), z > x && z is y's ancestor})
            chmin(sdom[x], sdom[Eval(y, true)]);
        }
        if (x > 0) buckets[sdom[x]].pb(x);
        for (int u : buckets[x]) {
            int p = Eval(u, true);
            if (sdom[p] == x) dom[u] = x;
            else dom[u] = p;
        }
        if (x > 0) Link(x, pa[x]);
    }
    // idom[x] = -1 if x is unreachable from rt
    vector<int> idom(n, -1);
    idom[rt] = rt;
    rep (x, 1, stamp) {
        if (sdom[x] != dom[x]) dom[x] = dom[dom[x]];
    }
    rep (i, 1, stamp) idom[rev[i]] = rev[dom[i]];
    return idom;
}

int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}