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

struct info {
    ll sum, mx, mi, tag;
    info operator + (const info &oth) {
        return {
            sum + oth.sum,
            max(mx, oth.mx),
            min(mi, oth.mi),
            0
        };
    }
    void upd(int, int, ll);
} tree[MAXN << 2];

void pull(int pos) {
    tree[pos] = tree[lpos] + tree[rpos];
}

void build(int pos, int l, int r, vector<ll> &a) {
    if (l == r) {
        tree[pos] = {a[l], a[l], a[l], 0};
        return;
    }
    int mid = l + r >> 1;
    build(lpos, l, mid, a);
    build(rpos, mid + 1, r, a);
    tree[pos] = tree[lpos] + tree[rpos];
}

void info::upd(int l, int r, ll v) {
    sum = v * (r - l + 1);
    mx = mi = v;
    tag = v;
}

void push(int pos, int l, int r) {
    ll &tag = tree[pos].tag;
    if (tag) {
        int mid = l + r >> 1;
        tree[lpos].upd(l, mid, tag);
        tree[rpos].upd(mid + 1, r, tag);
        tag = 0;
    }
}

void mod(int pos, int l, int r, int ml, int mr, ll val) {
    if (ml <= l && mr >= r) {
        tree[pos].upd(l, r, val);
        return;
    }
    push(pos, l, r);
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr, val);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, val);
    pull(pos);
}

info query(int pos, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) return tree[pos];
    push(pos, l, r);
    int mid = l + r >> 1;
    info res = {0, 0, LINF, 0};
    if (ql <= mid) res = res + query(lpos, l, mid, ql, qr);
    if (qr > mid) res = res + query(rpos, mid + 1, r, ql, qr);
    return res;
}

int find_right(int pos, int l, int r, ll x) { // <= pos
    if (l == r) return l;
    push(pos, l, r);
    int mid = l + r >> 1;
    if (tree[rpos].mi > x) return find_right(lpos, l, mid, x);
    else return find_right(rpos, mid + 1, r, x);
}

int find_left(int pos, int l, int r, ll x) { // >= pos
    if (l == r) return l;
    push(pos, l, r);
    int mid = l + r >> 1;
    if (tree[lpos].mx < x) return find_left(rpos, mid + 1, r, x);
    else return find_left(lpos, l, mid, x);
}

const int offset = 1e8;

void solve() {
    int n; cin >> n;
    vector<ll> a(n + 1);
    rep (i, 1, n + 1) cin >> a[i], a[i] -= i, a[i] += offset;
    build(1, 1, n, a);
    int q; cin >> q;
    ll ans = 0;
    while (q--) {
        int i; ll x; cin >> i >> x;
        x -= i;
        x += offset;
        ll pos = query(1, 1, n, i, i).sum;
        if (pos >= x) {
            int l = find_left(1, 1, n, x);
            ans += query(1, 1, n, l, i).sum - x * (i - l + 1);
            mod(1, 1, n, l, i, x);
        } else {
            int r = find_right(1, 1, n, x);
            ans += x * (r - i + 1) - query(1, 1, n, i, r).sum;
            mod(1, 1, n, i, r, x);
        }
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