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

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
#define PU(x) vi[p3++] = x

const int BUF_SIZE = 1 << 16;
static char buf[BUF_SIZE], vi[10], *p1 = buf, *p2 = buf;
static int p3;
inline int in() {int re = 0, f = 1; char c = GU; while (c == ' ' || c == '\n') {c = GU;} if (c == '-') {f = -1, c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return f * re;}
inline void out(int x) {char str[10]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];} write(1, vi, p3);}

void solve() {
    int n = in();
    vector<int> d(n);
    vector<vector<pii>> edge(n);
    rep (i, 0, n) {
        d[i] = in();
        rep (j, 0, d[i]) {
            int t = in(), w = in();
            t--;
            edge[i].pb({t, w});
        }
    }
    vector<int> a(n), x(n), b(n), y(n), c(n);
    rep (i, 0, n) a[i] = in();
    rep (i, 0, n) x[i] = in();
    rep (i, 0, n) b[i] = in();
    rep (i, 0, n) y[i] = in();
    rep (i, 0, n) c[i] = in();
    vector<vector<pii>> adj(n);
    auto dij = [&](int s) -> void {
        vector<ll> dis(d[s], LINF);
        dis[0] = 0;
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push({dis[0], 0});
        while (!pq.empty()) {
            auto [dd, u] = pq.top();
            pq.pop();
            if (dd != dis[u]) continue;
            int l = (u + x[s]) % d[s], r = (u + y[s]) % d[s];
            if (chmin(dis[l], dis[u] + a[s]) && dis[l] <= c[s]) {
                pq.push({dis[l], l});
            }
            if (chmin(dis[r], dis[u] + b[s]) && dis[r] <= c[s]) {
                pq.push({dis[r], r});
            }
        }
        rep (i, 0, d[s]) if (dis[i] <= c[s]) {
            auto [v, w] = edge[s][i];
            adj[v].pb({s, w});
        }
    };
    rep (i, 0, n) dij(i);
    vector<int> dis(n, IINF);
    queue<int> q;
    dis[n - 1] = 0;
    q.push(n - 1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : adj[u]) {
            if (chmin(dis[v], dis[u] + 1)) q.push(v);
        }
    }
    vector<ll> ans(n, -1);
    vector<int> p(n);
    iota(all(p), 0);
    sort(all(p), [&](int i, int j) {
        return dis[i] < dis[j];
    });
    ans[n - 1] = 0;
    rep (i, 0, n) if (dis[p[i]] != -1) {
        int u = p[i];
        for (auto [v, w] : adj[u]) if (dis[v] == dis[u] + 1) {
            chmax(ans[v], ans[u] + w);
        }
    }
    rep (i, 0, n) cout << ans[i] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}