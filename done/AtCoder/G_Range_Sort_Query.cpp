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

ll tree[MAXN << 2], tree2[MAXN << 2], tag[MAXN << 2], tag2[MAXN << 2];

void upd(int pos, int l, int r, ll val, int t) {
    if (t == 1) {
        tree[pos] = val * (r - l + 1);
        tag[pos] = val;
    } else {
        tree2[pos] = val * (r - l + 1);
        tag2[pos] = val;
    }
}

void push(int pos, int l, int r) {
    if (tag[pos] != -1) {
        int mid = l + r >> 1;
        upd(lpos, l, mid, tag[pos], 1);
        upd(rpos, mid + 1, r, tag[pos], 1);
        tag[pos] = -1;
    }
    if (tag2[pos] != -1) {
        int mid = l + r >> 1;
        upd(lpos, l, mid, tag2[pos], 2);
        upd(rpos, mid + 1, r, tag2[pos], 2);
        tag2[pos] = -1;
    }
}

void pull(int pos) {
    tree[pos] = tree[lpos] + tree[rpos]; 
    tree2[pos] = tree2[lpos] + tree2[rpos]; 
}

void mod(int pos, int l, int r, int ml, int mr, ll val, int t) {
    if (ml > mr) return;
    if (ml <= l && mr >= r) {
        if (t == 1) upd(pos, l, r, val, 1);
        else upd(pos, l, r, val, 2);
        return;
    }
    push(pos, l, r);
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr, val, t);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, val, t);
    pull(pos);
}

ll query(int pos, int l, int r, int ql, int qr, int t) {
    if (ql <= l && qr >= r) return t == 1 ? tree[pos] : tree2[pos];
    push(pos, l, r);
    int mid = l + r >> 1;
    ll res = 0;
    if (ql <= mid) res += query(lpos, l, mid, ql, qr, t);
    if (qr > mid) res += query(rpos, mid + 1, r, ql, qr, t);
    return res;
}

void solve() {
    int n, q, X; cin >> n >> q >> X;
    rep (i, 0, n << 2) tag[i] = tag2[i] = -1;
    vector<int> p(n + 1);
    rep (i, 1, n + 1) {
        int p; cin >> p;
        if (p <= X) {
            mod(1, 1, n, i, i, 0, 1);
        } else {
            mod(1, 1, n, i, i, 1, 1);
        }
        if (p < X) {
            mod(1, 1, n, i, i, 0, 2);
        } else {
            mod(1, 1, n, i, i, 1, 2);
        }
    }
    // rep (i, 1, n + 1) cout << query(1, 1, n, i, i, 1) << ' ' << query(1, 1, n, i, i, 2) << '\n';
    while (q--) {
        int c, l, r; cin >> c >> l >> r;
        int x = query(1, 1, n, l, r, 1), y = query(1, 1, n, l, r, 2);
        if (c == 1) {
            x = r - l + 1 - x, y = r - l + 1 - y;
            mod(1, 1, n, l, l + x - 1, 0, 1);
            mod(1, 1, n, l + x, r, 1, 1);
            mod(1, 1, n, l, l + y - 1, 0, 2);
            mod(1, 1, n, l + y, r, 1, 2);
        } else {
            mod(1, 1, n, l + x, r, 0, 1);
            mod(1, 1, n, l, l + x - 1, 1, 1);
            mod(1, 1, n, l + y, r, 0, 2);
            mod(1, 1, n, l, l + y - 1, 1, 2);
        }
    }
    rep (i, 1, n + 1) if (query(1, 1, n, i, i, 1) != query(1, 1, n, i, i, 2)) {
        cout << i << '\n';
        return;
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