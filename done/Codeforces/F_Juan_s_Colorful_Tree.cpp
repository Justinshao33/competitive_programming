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
const ll LINF = 1e18L + 5;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, k, s, q; cin >> n >> k >> s >> q;
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<vector<int>> VtoC(n), CtoV(k), coid(n), veid(k);
    rep (i, 0, s) {
        int v, x; cin >> v >> x;
        x--, v--;
        VtoC[v].push_back(x);
        CtoV[x].push_back(v);
    }
    rep (i, 0, n) {
        sort(all(VtoC[i]));
        rep (j, 0, ssize(VtoC[i])) veid[VtoC[i][j]].push_back(j);
    }
    rep (i, 0, k) {
        sort(all(CtoV[i]));
        rep (j, 0, ssize(CtoV[i])) coid[CtoV[i][j]].push_back(j);
    }
    vector<vector<vector<int>>> CG(k);
    rep (i, 0, k) {
        CG[i].resize(ssize(CtoV[i]));
    }
    const int B = sqrt(s);
    vector<int> bid(n);
    vector<vector<int>> exi;
    rep (i, 0, n) if (ssize(VtoC[i]) >= B) {
        bid[i] = ssize(exi);
        exi.push_back(vector<int>(k, -1));
        rep (j, 0, ssize(VtoC[i])) exi[bid[i]][VtoC[i][j]] = j;
    }
    rep (i, 0, n) for (int v : adj[i]) {
        if (ssize(VtoC[v]) < ssize(VtoC[i]) || (ssize(VtoC[v]) == ssize(VtoC[i]) && v < i)) continue;
        if (ssize(VtoC[v]) < B) {
            for (int ptr = 0, j = 0; int x : VtoC[i]) {
                while (ptr < ssize(VtoC[v]) && VtoC[v][ptr] < x) ptr++;
                if (ptr < ssize(VtoC[v]) && VtoC[v][ptr] == x) {
                    CG[x][coid[i][j]].push_back(coid[v][ptr]);
                    CG[x][coid[v][ptr]].push_back(coid[i][j]);
                }
                j++;
            }
        } else {
            for (int j = 0; int x : VtoC[i]) {
                if (exi[bid[v]][x] != -1) {
                    CG[x][coid[i][j]].push_back(coid[v][exi[bid[v]][x]]);
                    CG[x][coid[v][exi[bid[v]][x]]].push_back(coid[i][j]);
                }
                j++;
            }
        }
    }
    vector<vector<int>> cc(n);
    rep (i, 0, n) cc[i].resize(ssize(VtoC[i]), 0);
    rep (i, 0, k) {
        int id = 0;
        auto dfs = [&](auto self, int u) -> void {
            cc[CtoV[i][u]][veid[i][u]] = id;
            for (int v : CG[i][u]) {
                if (!cc[CtoV[i][v]][veid[i][v]]) {
                    self(self, v);
                }
            }
        };
        rep (j, 0, ssize(CtoV[i])) {
            if (!cc[CtoV[i][j]][veid[i][j]]) {
                id++;
                dfs(dfs, j);
            }
        }
    } 
    map<pair<int, int>, int> mp;
    while (q--) {
        int u, v; cin >> u >> v;
        u--, v--;
        if (ssize(VtoC[u]) > ssize(VtoC[v]) || (ssize(VtoC[u]) == ssize(VtoC[v]) && u > v)) swap(u, v);
        if (!mp.count({u, v})) {
            int cnt = 0;
            if (ssize(VtoC[v]) < B) {
                for (int ptr = 0, i = 0; int x : VtoC[u]) {
                    while (ptr < ssize(VtoC[v]) && VtoC[v][ptr] < x) ptr++;
                    if (ptr < ssize(VtoC[v]) && VtoC[v][ptr] == x && cc[u][i] == cc[v][ptr]) {
                        cnt++;
                    }
                    i++;
                }
            } else {
                rep (i, 0, ssize(VtoC[u])) {
                    int col = VtoC[u][i];
                    if (exi[bid[v]][col] != -1 && cc[u][i] == cc[v][exi[bid[v]][col]]) cnt++;
                }
            }
            mp[{u, v}] = cnt;
        }
        cout << mp[{u, v}] << ' ';
    }
    cout << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}