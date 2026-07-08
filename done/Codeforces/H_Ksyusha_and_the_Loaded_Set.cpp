#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

// #define int long long

using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
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

template<class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

#define lpos pos << 1
#define rpos pos << 1 | 1
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename A> ostream& operator << (ostream &os, const vector<A> &p) { for(const auto &a : p) os << a << " "; os << '\n'; return os; }
 
const int MAXN = 2e6 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

struct info {
    int lz, rz, mx, len;
};

info op(info a, info b) {
    info res;
    res.len = a.len + b.len;
    res.lz = (a.len == a.lz) ? a.len + b.lz : a.lz;
    res.rz = (b.len == b.rz) ? a.rz + b.len : b.rz;
    res.mx = max({a.mx, b.mx, a.rz + b.lz});
    return res;
}

info e() {
    return info{0, 0, 0, 0};
}

info tree[MAXN << 2];

const int C = 2e6 + 1;

void build(int pos, int l, int r) {
    if (l == r) {
        if (l == C) return void(tree[pos] = info{IINF, IINF, IINF, 1});
        return void(tree[pos] = info{1, 1, 1, 1});
    }
    int mid = l + r >> 1;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
    tree[pos] = op(tree[lpos], tree[rpos]);
}

void mod(int pos, int l, int r, int id) {
    if (l == r) {
        tree[pos].lz ^= 1;
        tree[pos].rz ^= 1;
        tree[pos].mx ^= 1;
        tree[pos].len = 1;
        return;
    }
    int mid = l + r >> 1;
    if (id <= mid) mod(lpos, l, mid, id);
    else mod(rpos, mid + 1, r, id);
    tree[pos] = op(tree[lpos], tree[rpos]);
}

int query(int pos, int l, int r, int k, int t) {
    if (l == r) return l;
    int mid = l + r >> 1;
    if (t == 0) {
        if (tree[lpos].mx >= k) return query(lpos, l, mid, k, t);
        if (tree[lpos].rz > 0 && tree[lpos].rz + tree[rpos].lz >= k) return query(lpos, l, mid, k, 1);
        return query(rpos, mid + 1, r, k, t);
    } else {
        if (tree[lpos].rz > 0 && tree[rpos].mx == tree[rpos].len) return query(lpos, l, mid, k, t);
        return query(rpos, mid + 1, r, k, t);
    }
}


void solve() {
    int n; cin >> n;
    set<int> st;
    rep (i, 0, n) {
        int a; cin >> a;
        st.insert(a);
        mod(1, 1, C, a);
    }
    int q; cin >> q;
    while (q--) {
        char c; cin >> c;
        int x; cin >> x;
        if (c == '+') {
            st.insert(x);
            mod(1, 1, C, x);   
        } else if (c == '-') {
            st.erase(x);
            mod(1, 1, C, x);
        } else {
            cout << query(1, 1, C, x, 0) << ' ';
        }
    }
    cout << '\n';
    for (int x : st) mod(1, 1, C, x);
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    build(1, 1, C);
    while (T--) {
        solve();
    }
}