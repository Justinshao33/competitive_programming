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
 
const int MAXN = 1e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

int tree[MAXN << 5], L[MAXN << 5], R[MAXN << 5];

int newnode() {
    static int id = 0;
    return ++id;
}

int build(int l, int r) {
    int root = newnode();
    if (l == r) {
        tree[root] = 0;
        return root;
    }
    int mid = l + r >> 1;
    L[root] = build(l, mid);
    R[root] = build(mid + 1, r);
    tree[root] = tree[L[root]] + tree[R[root]];
    return root;
}

int mod(int pre, int l, int r, int id, int v) {
    int root = newnode();
    tie(L[root], R[root], tree[root]) = make_tuple(L[pre], R[pre], tree[pre]);
    if (l == r) {
        tree[root] = v;
        return root;
    }
    int mid = l + r >> 1;
    if (id <= mid) L[root] = mod(L[pre], l, mid, id, v);
    else R[root] = mod(R[pre], mid + 1, r, id, v);
    tree[root] = tree[L[root]] + tree[R[root]];
    return root;
}

int query(int v, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) return tree[v];
    int mid = l + r >> 1;
    int res = 0;
    if (ql <= mid) res += query(L[v], l, mid, ql, qr);
    if (qr > mid) res += query(R[v], mid + 1, r, ql, qr);
    return res;
}

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    rep (i, 1, n + 1) cin >> a[i];
    vector pre(n + 1, vector<int>(18, 0));
    vector<queue<int>> val(*max_element(all(a)) + 1);
    vector<int> b(n + 1, 0);
    rep (i, 1, n + 1) {
        if (ssize(val[a[i]]) > k) val[a[i]].pop();
        if (ssize(val[a[i]]) == k) b[i] = val[a[i]].front();
        val[a[i]].push(i);
    }
    vector<int> p(n);
    iota(all(p), 1);
    sort(all(p), [&](const int &x, const int &y) {
        return b[x] < b[y];
    });
    vector<int> T(n + 1);
    T[0] = build(1, n);
    rep (i, 1, n + 1) {
        T[i] = mod(T[i - 1], 1, n, p[i - 1], 1);
    }
    sort(all(b));
    int q; cin >> q;
    int last = 0;
    while (q--) {
        int l, r; cin >> l >> r;
        l = (l + last) % n + 1, r = (r + last) % n + 1;
        if (l > r) swap(l, r);
        int x = lower_bound(all(b), l) - b.begin();
        last = query(T[x - 1], 1, n, l, r);
        cout << last << '\n';
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}