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
 
const int MAXN = 5e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

struct info {
    int l, r; ll a, b;
    void pull();
} tree[MAXN << 5];

void info::pull() {
    a = tree[l].a + tree[r].a;
    b = tree[l].b + tree[r].b;
}

int newnode() {
    static int x = 0;
    return ++x;
}

int build(int l, int r) {
    int root = newnode();
    if (l == r) {
        tree[root].a = tree[root].b = 0;
        return root;
    }
    int mid = l + r >> 1;
    tree[root].l = build(l, mid);
    tree[root].r = build(mid + 1, r);
    tree[root].pull();
    return root;
}

int mod(int p, int l, int r, int id, ll av, ll bv) {
    int root = newnode();
    tree[root] = tree[p];
    if (l == r) {
        tree[root].a += av;
        tree[root].b += bv;
        return root;
    }
    int mid = l + r >> 1;
    if (id <= mid) tree[root].l = mod(tree[p].l, l, mid, id, av, bv);
    else tree[root].r = mod(tree[p].r, mid + 1, r, id, av, bv);
    tree[root].pull();
    return root;
}

pair<ll, ll> query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) {
        return make_pair(tree[p].a, tree[p].b);
    }
    int mid = l + r >> 1;
    pair<ll, ll> res{0, 0};
    if (ql <= mid) res = res + query(tree[p].l, l, mid, ql, qr);
    if (qr > mid) res = res + query(tree[p].r, mid + 1, r, ql, qr);
    return res;
}

void solve() {
    int n; cin >> n;
    vector<int> T(n + 1);
    const int N = 200001;
    T[0] = build(0, N);
    vector<ll> out(n + 1, 0);
    rep (i, 0, n) {
        int x1, x2, y1, a, b, y2; cin >> x1 >> x2 >> y1 >> a >> b >> y2;
        int pre = T[i];
        pre = mod(pre, 0, N, 0, 0, y1);
        pre = mod(pre, 0, N, x1 + 1, 0, -y1);
        pre = mod(pre, 0, N, x1 + 1, a, b);
        pre = mod(pre, 0, N, x2 + 1, -a, -b);
        pre = mod(pre, 0, N, x2 + 1, 0, y2);
        pre = mod(pre, 0, N, N, 0, -y2);
        T[i + 1] = pre;
        out[i + 1] = out[i] + y2;
    }
    int q; cin >> q;
    ll last = 0;
    while (q--) {
        int l, r; ll x; cin >> l >> r >> x;
        x = (x + last) % 1'000'000'000;
        if (x > N) {
            last = out[r] - out[l - 1];
            cout << last << '\n';
        } else {
            pair<ll, ll> R = query(T[r], 0, N, 0, x), L = query(T[l - 1], 0, N, 0, x);
            pair<ll, ll> res = R - L;
            last = res.first * x + res.second;
            cout << last << '\n';
        }
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