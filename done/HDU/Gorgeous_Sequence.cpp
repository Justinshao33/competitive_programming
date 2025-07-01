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
 
const int MAXN = 1e6 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct info {
    int mx, mxcnt, smx;
    ll sum;
    int tag;
    void update(int);
} tree[MAXN << 2];

int a[MAXN];

template<typename T>inline void read(T &x) {
    x = 0;
    static int p; p = 1;
    static char c; c = getchar();
    while (!isdigit(c)) { if (c == '-') p = -1; c = getchar();}
    while (isdigit(c)) { x = (x << 1) + (x << 3) + (c - 48); c = getchar();}
    x *= p;
}

inline void info::update(int val) {
    if (mx <= val) return;
    sum += 1LL * (val - mx) * mxcnt;
    mx = tag = val;
}

inline void push(int pos) {
    if (tree[pos].tag != -1) {
        tree[lpos].update(tree[pos].tag);
        tree[rpos].update(tree[pos].tag);
        tree[pos].tag = -1;
    }
}

inline void pull(int pos) {
    int smx = (tree[lpos].mx == tree[rpos].mx) ? -1 : min(tree[lpos].mx, tree[rpos].mx);
    smx = max({smx, tree[lpos].smx, tree[rpos].smx});
    tree[pos] = {
        max(tree[lpos].mx, tree[rpos].mx),
        tree[lpos].mxcnt * (tree[lpos].mx >= tree[rpos].mx) + tree[rpos].mxcnt * (tree[lpos].mx <= tree[rpos].mx),
        smx,
        tree[lpos].sum + tree[rpos].sum,
        tree[pos].tag
    };
}

void build(int pos, int l, int r) {
    tree[pos].tag = -1;
    if (l == r) {
        tree[pos] = {a[l], 1, -1, a[l], -1};
        return;
    }
    int mid = l + r >> 1;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
    pull(pos);
}

void mod(int pos, int l, int r, int ml, int mr, int val) {
    if (ml <= l && mr >= r && val > tree[pos].smx) {
        tree[pos].update(val);
        return;
    }
    push(pos);
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr, val);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, val);
    pull(pos);
}

int query(int pos, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) return tree[pos].mx;
    push(pos);
    int mid = l + r >> 1;
    int mx = -1;
    if (ql <= mid) mx = max(mx, query(lpos, l, mid, ql, qr));
    if (qr > mid) mx = max(mx, query(rpos, mid + 1, r, ql, qr));
    return mx;
}

ll query2(int pos, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) return tree[pos].sum;
    push(pos);
    int mid = l + r >> 1;
    ll res = 0;
    if (ql <= mid) res += query2(lpos, l, mid, ql, qr);
    if (qr > mid) res += query2(rpos, mid + 1, r, ql, qr);
    return res;
}

void solve() {
    int n, q; read(n), read(q);
    rep (i, 1, n + 1) read(a[i]);
    build(1, 1, n);
    while (q--) {
        int t, l, r; read(t), read(l), read(r);
        if (t == 0) {
            int x; read(x);
            mod(1, 1, n, l, r, x);
        } else if (t == 1) {
            cout << query(1, 1, n, l, r) << '\n';
        } else {
            cout << query2(1, 1, n, l, r) << '\n';
        }
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    read(T);
    while (T--) {
        solve();
    }
}