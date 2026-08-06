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

using info = array<array<int, 2>, 2>;

int c[MAXN];

info e() {
    return info{array<int, 2>{LINF, LINF}, array<int, 2>{LINF, LINF}};
}

info op(info a, info b, int &v) {
    info res = e();
    rep (i, 0, 2) rep (j, 0, 2) rep (k, 0, 2) rep (l, 0, 2) {
        chmin(res[i][l], a[i][j] + b[k][l] + ((j == 1 && k == 0) ? v : 0LL));
    }
    return res;
}

info tree[MAXN << 2];

void mod(int pos, int l, int r, int id, info v) {
    if (l == r) {
        tree[pos] = v;
        return;
    }
    int mid = l + r >> 1;
    if (id <= mid) mod(lpos, l, mid, id, v);
    else mod(rpos, mid + 1, r, id, v);
    tree[pos] = op(tree[lpos], tree[rpos], c[mid]);
}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n), b(n);
    rep (i, 0, n) cin >> a[i];
    rep (i, 0, n) cin >> b[i];
    rep (i, 0, n - 1) cin >> c[i];
    rep (i, 0, n) mod(1, 0, n - 1, i, info{array<int, 2>{a[i], LINF}, array<int, 2>{LINF, b[i]}});
    while (q--) {
        int p, A, B, C; cin >> p >> A >> B >> C;
        p--;
        c[p] = C;
        mod(1, 0, n - 1, p, info{array<int, 2>{A, LINF}, array<int, 2>{LINF, B}});
        int ans = LINF;
        rep (i, 0, 2) rep (j, 0, 2) chmin(ans, tree[1][i][j]);
        cout << ans << '\n';
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