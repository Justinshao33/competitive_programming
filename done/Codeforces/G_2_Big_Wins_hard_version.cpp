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
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

struct info {
    ll pre, suf, sum, ans;
    info operator+ (const info &oth) const {
        info res;
        res.pre = max(pre, sum + oth.pre);
        res.suf = max(oth.suf, oth.sum + suf);
        res.sum = sum + oth.sum;
        res.ans = max({ans, oth.ans, suf + oth.pre});
        return res;
    }
};

struct segtree {
    vector<info> tree;
    segtree(int n) : tree(n << 2) {}
    void build(int pos, int l, int r) {
        if (l == r) {
            tree[pos] = {1, 1, 1, 1};
            return;
        }
        int mid = l + r >> 1;
        build(lpos, l, mid); build(rpos, mid + 1, r);
        tree[pos] = tree[lpos] + tree[rpos];
    }
    void mod(int pos, int l, int r, int id, ll x) {
        if (l == r) {
            tree[pos] = {0, 0, x, 0};
            return;
        }
        int mid = l + r >> 1;
        if (id <= mid) mod(lpos, l, mid, id, x);
        else mod(rpos, mid + 1, r, id, x);
        tree[pos] = tree[lpos] + tree[rpos];
    }
    info query(int pos, int l, int r, int ql, int qr) {
        if (ql > qr) return info{0, 0, 0, 0};
        if (ql <= l && qr >= r) return tree[pos];
        int mid = l + r >> 1;
        info res{0, 0, 0, 0};
        if (ql <= mid) res = res + query(lpos, l, mid, ql, qr);
        if (qr > mid) res = res + query(rpos, mid + 1, r, ql, qr);
        return res;
    }
};

void solve() {
    int n; cin >> n;
    vector<vector<int>> id(n + 2);
    vector<int> a(n + 1);
    rep (i, 1, n + 1) {
        cin >> a[i];
        id[a[i]].pb(i);
    }
    vector<int> l(n + 1, 1), r(n + 1, n), st;
    rep (i, 1, n + 1) {
        while (!st.empty() && a[st.back()] >= a[i]) {
            st.pop_back();
        }
        if (!st.empty()) l[i] = st.back() + 1;
        st.pb(i);
    }
    st.clear();
    for (int i = n; i > 0; --i) {
        while (!st.empty() && a[st.back()] >= a[i]) {
            st.pop_back();
        }
        if (!st.empty()) r[i] = st.back() - 1;
        st.pb(i);
    }
    // debug(l, r);
    segtree tree(n);
    tree.build(1, 1, n);
    int ans = 0;
    for (int p : id[1]) tree.mod(1, 1, n, p, -1);
    for (int i = 1, med = 1; i <= n; i++) {
        for (int p : id[i]) {
            while (med <= n && tree.query(1, 1, n, l[p], p - 1).suf + tree.query(1, 1, n, p + 1, r[p]).pre + (a[p] >= med + 1 ? 1 : -1) >= 0) {
                med++;
                for (int p2 : id[med]) tree.mod(1, 1, n, p2, -1);
            }
        }
        chmax(ans, med - i);
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}