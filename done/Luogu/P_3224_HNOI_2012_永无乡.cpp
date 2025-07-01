// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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
#define ld long double
#define F first
#define S second

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
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct UnionFind {
    vector<int> sz;
    UnionFind(int n) : sz(n, -1) {}

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        // if (sz[a] > sz[b]) swap(a, b);
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

#include<bits/extc++.h>
using namespace __gnu_pbds;
template<typename T> using RBT = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n, m; cin >> n >> m;
    vector<RBT<pii>> tree(n);
    vector<int> p(n);
    rep (i, 0, n) cin >> p[i];
    UnionFind dsu(n);
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        dsu.Union(a, b);
    }
    rep (i, 0, n) {
        tree[dsu.find(i)].insert({p[i], i + 1});
    }
    int q; cin >> q;
    while (q--) {
        char c; cin >> c;
        if (c == 'Q') {
            int x, k; cin >> x >> k;
            x--;
            x = dsu.find(x);
            if (tree[x].size() < k) cout << -1 << '\n';
            else {
                cout << (*tree[x].find_by_order(k - 1)).S << '\n';
            }
        } else {
            int a, b; cin >> a >> b;
            a--, b--;
            if (dsu.size(a) < dsu.size(b)) swap(a, b);
            a = dsu.find(a), b = dsu.find(b);
            if (a != b) {
                for (pii p : tree[b]) {
                    tree[a].insert(p);
                }
                tree[b].clear();
                dsu.Union(a, b);
            }
        }
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}