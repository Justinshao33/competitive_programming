#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n; cin >> n;
    vector<int> w(n), v(n);
    rep (i, 0, n) cin >> w[i] >> v[i];
    int q; cin >> q;
    vector<array<int, 4>> Q;
    rep (i, 0, q) {
        int l, r, c; cin >> l >> r >> c;
        l--, r--;
        Q.push_back({l, r, c, i});
    }
    vector<int> ans(q, 0);
    const int C = 501;
    vector dpL(n, vector<int>(C, 0));
    auto dpR = dpL;
    auto dc = [&](auto self, int l, int r, vector<array<int, 4>> &que) -> void {
        if (l > r || ssize(que) == 0) return;
        if (l == r) {
            for (const auto &[L, R, c, id] : que) {
                if (c >= w[l]) ans[id] = v[l];
            }
            return;
        }
        int mid = l + r >> 1;
        rep (j, 0, C) {
            rep (i, l, mid + 1) dpL[i][j] = 0;
            rep (i, mid + 1, r + 1) dpR[i][j] = 0;
        }
        rep (j, w[mid], C) dpL[mid][j] = v[mid];
        for (int i = mid - 1; i >= l; --i) {
            dpL[i] = dpL[i + 1];
            rep (j, w[i], C) chmax(dpL[i][j], dpL[i + 1][j - w[i]] + v[i]);
        }
        rep (j, w[mid + 1], C) dpR[mid + 1][j] = v[mid + 1];
        rep (i, mid + 2, r + 1) {
            dpR[i] = dpR[i - 1];
            rep (j, w[i], C) chmax(dpR[i][j], dpR[i - 1][j - w[i]] + v[i]);
        }
        vector<array<int, 4>> LQ, RQ;
        for (const auto &Q : que) {
            if (Q[1] <= mid) {
                LQ.push_back(Q);
            } else if (Q[0] > mid) {
                RQ.push_back(Q);
            } else {
                const auto &[L, R, c, id] = Q;
                int res = 0;
                rep (i, 0, c + 1) chmax(res, dpL[L][i] + dpR[R][c - i]);
                ans[id] = res;
            }
        }
        self(self, l, mid, LQ);
        self(self, mid + 1, r, RQ);
    };
    dc(dc, 0, n - 1, Q);
    rep (i, 0, q) cout << ans[i] << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}