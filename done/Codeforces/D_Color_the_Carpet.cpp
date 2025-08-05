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
    int n, m, k; cin >> n >> m >> k;
    vector<string> row(n), col(n);
    rep (i, 0, n) {
        if (i) cin >> col[i];
        cin >> row[i];
    }
    if (k == 1) {
        int cnt = 0;
        rep (i, 0, n) {
            cnt += count(all(row[i]), 'E');
            if (i) cnt += count(all(col[i]), 'E');
        }
        if (((m * (n - 1) + (m - 1) * n) * 3 + 3) / 4 <= cnt) {
            cout << "YES\n";
            rep (i, 0, n) rep (j, 0, m) cout << 1 << " \n" [j == m - 1];
        } else {
            cout << "NO\n";
        }
        return;
    }
    cout << "YES\n";
    vector ans(n, vector<int>(m, 0));
    if (m >= n) {
        rep (i, 0, n) {
            rep (j, 0, m - 1) {
                if (row[i][j] == 'N') ans[i][j + 1] = ans[i][j] ^ 1;
                else ans[i][j + 1] = ans[i][j];
            }
            if (i) {
                int cnt = 0;
                rep (j, 0, m) {
                    if (col[i][j] == 'N' && ans[i - 1][j] != ans[i][j]) cnt++;
                    if (col[i][j] == 'E' && ans[i - 1][j] == ans[i][j]) cnt++;
                }
                if (cnt < (m + 1) / 2) {
                    rep (j, 0, m) ans[i][j] ^= 1;
                }
            }
        }
        rep (i, 0, n) rep (j, 0, m) cout << ans[i][j] + 1 << " \n" [j == m - 1];
    } else {
        rep (j, 0, m) {
            rep (i, 0, n - 1) {
                if (col[i + 1][j] == 'N') ans[i + 1][j] = ans[i][j] ^ 1;
                else ans[i + 1][j] = ans[i][j];
            }
            if (j) {
                int cnt = 0;
                rep (i, 0, n) {
                    if (row[i][j - 1] == 'N' && ans[i][j - 1] != ans[i][j]) cnt++;
                    if (row[i][j - 1] == 'E' && ans[i][j - 1] == ans[i][j]) cnt++;
                }
                if (cnt < (n + 1) / 2) {
                    rep (i, 0, n) ans[i][j] ^= 1;
                }
            }
        }
        rep (i, 0, n) rep (j, 0, m) cout << ans[i][j] + 1 << " \n" [j == m - 1];   
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