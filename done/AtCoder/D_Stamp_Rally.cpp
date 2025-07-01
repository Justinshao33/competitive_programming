#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

#ifdef LOCAL
#define ZTMYACANESOCUTE freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

void dbg() { cerr << '\n'; }
template<typename T, typename ...U>
void dbg(T t, U ...u) { cerr << t << ' '; dbg(u...); }

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
    vector<tuple<int, int, int>> st;
    UnionFind(int n) : sz(n, -1) {}

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        st.pb({a, b, sz[b]});
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
    
    void undo(int x) {
        while (st.size() > x) {
            auto [a, b, v] = st.back();
            st.pop_back();
            sz[a] -= v;
            sz[b] = v;
        }
    }
};

struct info {
    int x, y, z, id;
};

void solve() {
    int n, m; cin >> n >> m;
    vector<pii> edge(m);
    for (auto &[a, b] : edge) cin >> a >> b, a--, b--;
    int q; cin >> q;
    vector<info> que(q);
    rep (i, 0, q) {
        auto &[x, y, z, id] = que[i];
        cin >> x >> y >> z;
        x--, y--;
        id = i;
    }
    UnionFind dsu(n);
    vector<int> ans(q);
    auto bs = [&](auto self, int l, int r, int ql, int qr) -> void {
        if (ql > qr || l > r) return;
        if (l == r) {
            rep (i, ql, qr + 1) ans[que[i].id] = l;
            return;
        }
        int mid = l + r >> 1, ori = dsu.st.size();
        rep (i, l, mid + 1) dsu.Union(edge[i].F, edge[i].S);
        vector<info> q1, q2;
        rep (i, ql, qr + 1) {
            auto [x, y, z, id] = que[i];
            int sum = dsu.size(x) + (dsu.same(x, y) ? 0 : dsu.size(y));
            if (sum >= z) q1.pb(que[i]);
            else q2.pb(que[i]);
        } 
        int sz = q1.size();
        rep (i, 0, sz) que[ql + i] = q1[i];
        rep (i, 0, q2.size()) que[ql + sz + i] = q2[i];
        self(self, mid + 1, r, ql + sz, qr);
        dsu.undo(ori);
        self(self, l, mid, ql, ql + sz - 1);
    };
    bs(bs, 0, m - 1, 0, q - 1);
    rep (i, 0, q) cout << ans[i] + 1 << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}