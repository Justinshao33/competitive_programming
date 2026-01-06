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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

array<int, 100> tag[MAXN << 2];

void build(int pos, int l, int r) {
    rep (i, 0, 100) tag[pos][i] = i;
    if (l == r) return;
    int mid = l + r >> 1;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
}

void merge(array<int, 100> &o, array<int, 100> &t) {
    rep (i, 0, 100) o[i] = t[o[i]];
}

void push(int pos) {
    merge(tag[lpos], tag[pos]);
    merge(tag[rpos], tag[pos]);
    rep (i, 0, 100) tag[pos][i] = i;
}

void mod(int pos, int l, int r, int ml, int mr, array<int, 100> &tr) {
    if (ml <= l && mr >= r) {
        merge(tag[pos], tr);
        return;
    }
    push(pos);
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr, tr);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, tr);
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    rep (i, 0, n) cin >> a[i], a[i]--;
    build(1, 0, n - 1);
    int q; cin >> q;
    while (q--) {
        int l, r, x, y; cin >> l >> r >> x >> y;
        l--, r--, x--, y--;
        array<int, 100> tr;
        rep (i, 0, 100) tr[i] = i;
        tr[x] = y;
        mod(1, 0, n - 1, l, r, tr);
    }
    auto dfs = [&](auto self, int pos, int l, int r) -> void {
        if (l == r) {
            cout << tag[pos][a[l]] + 1 << ' ';
            return;
        }
        push(pos);
        int mid = l + r >> 1;
        self(self, lpos, l, mid);
        self(self, rpos, mid + 1, r);
    };
    dfs(dfs, 1, 0, n - 1);
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}