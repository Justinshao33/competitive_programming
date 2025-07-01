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
 
const int MAXN = 3e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

ll tree[MAXN << 2], a[MAXN];

void build(int pos, int l, int r) {
    if (l == r) {
        tree[pos] = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
    tree[pos] = tree[lpos] + tree[rpos];
}

void mod(int pos, int l, int r, int ml, int mr) {
    if (ml <= l && mr >= r && tree[pos] == r - l + 1) return;
    if (l == r) {
        tree[pos] = sqrt(tree[pos]);
        return;
    }
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr);
    tree[pos] = tree[lpos] + tree[rpos];
}

ll query(int pos, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) return tree[pos];
    int mid = l + r >> 1;
    ll res = 0;
    if (ql <= mid) res += query(lpos, l, mid, ql, qr);
    if (qr > mid) res += query(rpos, mid + 1, r, ql, qr);
    return res;
}

void solve() {
    int n, q; cin >> n >> q;
    rep (i, 1, n + 1) cin >> a[i];
    build(1, 1, n);
    while (q--) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 0) {
            cout << query(1, 1, n, l, r) << '\n';
        } else {
            mod(1, 1, n, l, r);
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