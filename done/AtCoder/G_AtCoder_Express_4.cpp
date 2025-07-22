#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
#define PU(x) vi[p3++] = x

const int BUF_SIZE = 1 << 16;
static char buf[BUF_SIZE], vi[10], *p1 = buf, *p2 = buf;
static int p3;
inline ll in() {ll re = 0, f = 1; char c = GU; while (c == ' ' || c == '\n') {c = GU;} if (c == '-') {f = -1, c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return f * re;}
inline void out(int x) {char str[10]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];} write(1, vi, p3);}

void solve() {
    int n = in(), m = in();
    vector<ll> x(n);
    rep (i, 0, n) x[i] = in();
    int cnt = 0;
    vector<int> id(n);
    vector tid(4, vector<int>(n << 2)); // Rin / Rout / Lin / Lout
    int N = n * 8 + m * 2;
    vector<vector<pll>> adj(N);
    auto build = [&](auto self, int pos, int l, int r) -> void {
        if (l == r) {
            rep (i, 0, 4) tid[i][pos] = cnt;
            id[l] = cnt++;
            return;
        }
        int mid = l + r >> 1;
        rep (i, 0, 4) tid[i][pos] = cnt++;
        self(self, lpos, l, mid);
        self(self, rpos, mid + 1, r);
        // Rin
        adj[tid[0][pos]].pb({tid[0][lpos], 0});
        adj[tid[0][pos]].pb({tid[0][rpos], x[mid + 1] - x[l]});
        // Lin
        adj[tid[2][pos]].pb({tid[2][lpos], x[r] - x[mid]});
        adj[tid[2][pos]].pb({tid[2][rpos], 0});
        // Rout
        adj[tid[1][lpos]].pb({tid[1][pos], x[r] - x[mid]});
        adj[tid[1][rpos]].pb({tid[1][pos], 0});
        // Lout
        adj[tid[3][lpos]].pb({tid[3][pos], 0});
        adj[tid[3][rpos]].pb({tid[3][pos], x[mid + 1] - x[l]});
    };
    build(build, 1, 0, n - 1);
    auto mod = [&](auto self, int pos, int l, int r, int ml, int mr, int con, int bd, int t) -> void {
        // Rout: x[bd] - x[r] -> 1
        // Rin: x[l] - x[bd] -> 0
        // Lout: x[l] - x[bd] -> 3
        // Lin: x[bd] - x[r] -> 2
        if (ml <= l && mr >= r) {
            ll w = __builtin_popcount(t) == 1 ? x[bd] - x[r] : x[l] - x[bd];
            if (t & 1) {
                // debug(t, r, bd);
                adj[tid[t][pos]].pb({con, w});
            } else {
                // debug(t, bd, l);
                adj[con].pb({tid[t][pos], w});
            }
            return;
        }
        int mid = l + r >> 1;
        if (ml <= mid) self(self, lpos, l, mid, ml, mr, con, bd, t);
        if (mr > mid) self(self, rpos, mid + 1, r, ml, mr, con, bd, t);
    };
    rep (i, 0, m) {
        int l = in(), r = in(), L = in(), R = in(); ll c = in();
        l--, r--, L--, R--;
        if (r < L) {
            mod(mod, 1, 0, n - 1, l, r, cnt++, r, 1);
            adj[cnt - 1].pb({cnt, c + x[L] - x[r]});
            mod(mod, 1, 0, n - 1, L, R, cnt++, L, 0);
        } else {
            mod(mod, 1, 0, n - 1, l, r, cnt++, l, 3);
            adj[cnt - 1].pb({cnt, c + x[l] - x[R]});
            mod(mod, 1, 0, n - 1, L, R, cnt++, R, 2);
        }
    }
    // rep (i, 0, cnt) for (auto [v, w] : adj[i]) assert(w >= 0); 
    vector<ll> dis(N, LINF);
    dis[id[0]] = 0;
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({dis[id[0]], id[0]});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dis[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (chmin(dis[v], dis[u] + w)) {
                pq.push({dis[v], v});
            }
        }
    }
    rep (i, 1, n) cout << (dis[id[i]] == LINF ? -1 : dis[id[i]]) << " \n" [i == n - 1];
}   
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}