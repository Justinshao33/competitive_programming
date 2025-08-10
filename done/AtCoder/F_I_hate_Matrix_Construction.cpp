#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n; cin >> n;
    vector<int> R(n), C(n);
    rep (i, 0, n) cin >> R[i];
    rep (i, 0, n) cin >> C[i];
    vector<ull> row(n), col(n);
    rep (i, 0, n) cin >> row[i];
    rep (i, 0, n) cin >> col[i];
    vector mat(n, vector<ull>(n, 0));
    auto get_bit = [&](ull x, int b) -> bool {
        return x >> b & 1;
    };
    rep (b, 0, 64) {
        int allC = 0, allR = 0;
        rep (i, 0, n) {
            if (!R[i] && get_bit(row[i], b)) {
                allR++;
                rep (j, 0, n) mat[i][j] |= 1ULL << b;
            }
            if (!C[i] && get_bit(col[i], b)) {
                allC++;
                rep (j, 0, n) mat[j][i] |= 1ULL << b;
            }
        }
        if (allR == n) {
            rep (j, 0, n) if (!C[j] && !get_bit(col[j], b)) {
                cout << -1 << '\n';
                return;
            }
        }
        if (allC == n) {
            rep (i, 0, n) if (!R[i] && !get_bit(row[i], b)) {
                cout << -1 << '\n';
                return;
            }
        }
        rep (i, 0, n) {
            if (R[i] && !get_bit(row[i], b)) rep (j, 0, n) if (get_bit(mat[i][j], b)) {
                cout << -1 << '\n';
                return;
            }
            if (C[i] && !get_bit(col[i], b)) rep (j, 0, n) if (get_bit(mat[j][i], b)) {
                cout << -1 << '\n';
                return;
            }
        }
        rep (i, 0, n) rep (j, 0, n) if (get_bit(row[i], b) == get_bit(col[j], b) && get_bit(row[i], b)) {
            mat[i][j] |= 1ULL << b;
        }
        rep (i, 0, n) if (R[i] && get_bit(row[i], b)) {
            ull cur = 0;
            rep (j, 0, n) cur |= mat[i][j];
            if (get_bit(cur, b)) continue;
            bool f = 0;
            rep (j, 0, n) if (!C[j] && !get_bit(col[j], b)) {
                int cnt = 0;
                rep (k, 0, n) if (!get_bit(mat[k][j], b)) cnt++;
                if (cnt >= 2) {
                    mat[i][j] |= 1ULL << b;
                    f = 1;
                    break;
                }
            }
            if (!f) {
                cout << -1 << '\n';
                return;
            }
        }
        rep (j, 0, n) if (C[j] && get_bit(col[j], b)) {
            ull cur = 0;
            rep (i, 0, n) cur |= mat[i][j];
            if (get_bit(cur, b)) continue;
            bool f = 0;
            rep (i, 0, n) if (!R[i] && !get_bit(row[i], b)) {
                int cnt = 0;
                rep (k, 0, n) if (!get_bit(mat[i][k], b)) cnt++;
                if (cnt >= 2) {
                    mat[i][j] |= 1ULL << b;
                    f = 1;
                    break;
                }
            }
            if (!f) {
                cout << -1 << '\n';
                return;
            }
        }
    }
    rep (i, 0, n) rep (j, 0, n) cout << mat[i][j] << " \n" [j == n - 1];
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}