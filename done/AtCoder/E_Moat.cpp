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

struct UnionFind {
    vector<int> sz;
    UnionFind(int n) : sz(n, -1) {}

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

int dx[4] = {-1, 0, 0, 1}, dy[4] = {0, -1, 1, 0};

void solve() {
    vector a(4, vector<int>(4));
    rep (i, 0, 4) rep (j, 0, 4) cin >> a[i][j];
    int ans = 0;
    rep (bit, 1, 1 << 16) {
        bool f = 1;
        int cnt = 0;
        UnionFind dsu(17);
        rep (i, 0, 16) {
            int x = i / 4, y = i % 4;
            rep (j, 0, 4) {
                int nx = x + dx[j], ny = y + dy[j];
                if ((nx < 0 || ny < 0 || nx >= 4 || ny >= 4) && (bit >> i & 1 ^ 1)) dsu.Union(16, i);
                if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4 || (bit >> (nx * 4 + ny) & 1) != (bit >> i & 1)) continue;
                if (bit >> i & 1) cnt -= dsu.Union(i, nx * 4 + ny);
                else dsu.Union(i, nx * 4 + ny);
            }
            if (bit >> i & 1) {
                cnt++;
            } else {
                if (a[x][y]) f = 0;
            }
        }
        rep (i, 0, 16) if (bit >> i & 1 ^ 1) {
            if (!dsu.same(16, i)) f = 0;
        }
        if (cnt != 1) f = 0;
        ans += f;
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}