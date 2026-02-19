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

void solve() {
    int n, m; cin >> n >> m;
    vector a(n, vector<int>(m));
    vector<array<int, 3>> seg;
    rep (i, 0, n) {
        seg.push_back({IINF, 0, i});
        rep (j, 0, m) {
            cin >> a[i][j];
            if (a[i][j]) {
                chmin(seg[i][0], a[i][j]);
                chmax(seg[i][1], a[i][j]);
            }
        }
    }
    sort(all(seg));
    rep (i, 1, n) {
        if (seg[i][0] == IINF) continue;
        if (seg[i][0] < seg[i - 1][1]) {
            cout << "No\n";
            return;
        }
    }
    vector<vector<int>> adj(m);
    vector<int> ind(m);
    int id = m;
    rep (x, 0, n) {
        int i = seg[x][2];
        vector<pii> col;
        rep (j, 0, m) col.push_back({a[i][j], j});
        sort(all(col));
        auto dic = a[i];
        dic.push_back(0);
        sort(all(dic));
        dic.erase(unique(all(dic)), dic.end());
        rep (j, 0, ssize(dic) - 1) {
            adj.push_back(vector<int>());
            ind.push_back(0);
        }
        // debug(ssize(dic));
        for (const auto &[v, j] : col) {
            if (v == 0) continue;
            int p = lower_bound(all(dic), v) - dic.begin() - 1;
            // debug(j, "->", id + p);
            // debug(id + p - 1, "->", j);
            adj[j].push_back(id + p);
            ind[id + p]++;
            if (p > 0) {
                adj[id + p - 1].push_back(j);
                ind[j]++;
            }
        }
        id += ssize(dic) - 1;
    }
    queue<int> q;
    rep (i, 0, id) if (ind[i] == 0) {
        debug(i);
        q.push(i);
    }
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cnt++;
        for (int v : adj[u]) {
            ind[v]--;
            if (!ind[v]) q.push(v);
        }
    }
    debug(id, cnt);
    cout << (cnt == id ? "Yes\n" : "No\n");
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}