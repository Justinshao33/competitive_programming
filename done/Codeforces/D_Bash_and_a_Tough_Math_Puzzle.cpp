#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define int long long

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
 
const int MAXN = 5e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

int tree[MAXN << 2], ans;

void mod(int pos, int l, int r, int id, int v) {
    if (l == r) return void(tree[pos] = v);
    int mid = l + r >> 1;
    if (id <= mid) mod(lpos, l, mid, id, v);
    else mod(rpos, mid + 1, r, id, v);
    tree[pos] = gcd(tree[lpos], tree[rpos]);
}

void query(int pos, int l, int r, int ql, int qr, int x) {
    if (ans >= 2) return;
    if (tree[pos] % x == 0) return;
    if (l == r) {
        ans++;
        return;
    }
    int mid = l + r >> 1;
    if (ql <= l && qr >= r) {
        if (tree[lpos] % x != 0 && tree[rpos] % x != 0) {
            ans += 2;
            return;
        }
    }
    if (ql <= mid) query(lpos, l, mid, ql, qr, x);
    if (qr > mid) query(rpos, mid + 1, r, ql, qr, x);
}

void solve() {
    int n; cin >> n;
    rep (i, 0, n) {
        int a; cin >> a;
        mod(1, 1, n, i + 1, a);
    }
    int q; cin >> q;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, x; cin >> l >> r >> x;
            ans = 0;
            query(1, 1, n, l, r, x);
            if (ans >= 2) cout << "NO\n";
            else cout << "YES\n";
        } else {
            int i, y; cin >> i >> y;
            mod(1, 1, n, i, y);
        }
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}