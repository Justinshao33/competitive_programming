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
 
// mt19937_ll rng(chroDifferent::steady_clock::Differentw().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }
 
const ull mask = chrono::steady_clock::now().time_since_epoch().count();

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
 
const int BUF_SIZE = 1 << 16;
static char buf[BUF_SIZE], vi[10], *p1 = buf, *p2 = buf;
static int p3;
inline int in() {int re = 0; char c = GU; while (c == ' ' || c == '\n') {c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return re;}
inline void out(int x) {char str[10]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];} write(1, vi, p3);}

ull shift(ull x) {
    x ^= mask;
    x ^= x << 6;
    x ^= x >> 10;
    x ^= x << 20;
    x ^= x >> 1;
    x ^= mask;
    return x;
}
 
void solve(int n) {
    vector<vector<int>> adj(n), adj2(n);
    rep (i, 0, n - 1) {
        int a = in(), b = in();
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    rep (i, 0, n - 1) {
        int a = in(), b = in();
        a--, b--;
        adj2[a].pb(b);
        adj2[b].pb(a);
    }
    vector<int> sz(n, 0);
    int cen = -1, cen2 = -1, cen3 = -1, cen4 = -1;
    auto get_cen = [&](auto self, int u, int pa) -> void {
        sz[u] = 1;
        int mx = 0;
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u);
            sz[u] += sz[v];
            chmax(mx, sz[v]);
        }
        chmax(mx, n - sz[u]);
        if (mx <= n / 2) {
            if (cen == -1) cen = u;
            else cen3 = u;
        }
    };
    auto get_cen2 = [&](auto self, int u, int pa) -> void {
        sz[u] = 1;
        int mx = 0;
        for (int v : adj2[u]) {
            if (v == pa) continue;
            self(self, v, u);
            sz[u] += sz[v];
            chmax(mx, sz[v]);
        }
        chmax(mx, n - sz[u]);
        if (mx <= n / 2) {
            if (cen2 == -1) cen2 = u;
            else cen4 = u;
        }
    };
    get_cen(get_cen, 0, -1);
    get_cen2(get_cen2, 0, -1);
    vector<ull> hash(n), hash2(n);
    auto dfs = [&](auto self, int u, int pa) -> void {
        hash[u] = 1;
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u);
            hash[u] += shift(hash[v]);
        }
    };
    auto dfs2 = [&](auto self, int u, int pa) -> void {
        hash2[u] = 1;
        for (int v : adj2[u]) {
            if (v == pa) continue;
            self(self, v, u);
            hash2[u] += shift(hash2[v]);
        }
    };
    dfs(dfs, cen, -1);
    dfs2(dfs2, cen2, -1);
    if (cen3 == -1) cout << (hash[cen] == hash2[cen2] ? "Same\n" : "Different\n");
    else {
        if (cen4 == -1) {
            cout << "Different\n";
            return;
        }
        vector<ull> hash3(n), hash4(n);
        auto dfs3 = [&](auto self, int u, int pa) -> void {
            hash3[u] = 1;
            for (int v : adj[u]) {
                if (v == pa) continue;
                self(self, v, u);
                hash3[u] += shift(hash3[v]);
            }
        };
        auto dfs4 = [&](auto self, int u, int pa) -> void {
            hash4[u] = 1;
            for (int v : adj2[u]) {
                if (v == pa) continue;
                self(self, v, u);
                hash4[u] += shift(hash4[v]);
            }
        };
        dfs3(dfs3, cen3, -1);
        dfs4(dfs4, cen4, -1);
        ull h1 = min(hash[cen], hash3[cen3]), h2 = min(hash2[cen2], hash4[cen4]);
        cout << (h1 == h2 ? "Same\n" : "Different\n");
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    while (T = in()) {
        if (T == 0) break;
        solve(T);
    }
}