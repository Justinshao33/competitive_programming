#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
// #pragma GCC optimize("O3,unroll-loops")
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
    int n, m; cin >> n >> m;
    vector<string> G(n + 1);
    int ex, ey;
    rep (i, 0, n) {
        cin >> G[i];
        rep (j, 0, m) {
            if (G[i][j] == '.') tie(ex, ey) = tie(i, j);
            else G[i][j] = 0;
        }
        G[i].pb(0);
    }
    G[n] = string(m + 1, 0);
    vector<int> fr(m + 1, 0);
    fr[0] = 1;
    rep (i, 1, m + 1) fr[i] = fr[i - 1] << 2;
    map<int, ll> dp;
    dp[0] = 1;
    ll ans = 0;
    auto get = [&](int msk, int b) -> int {
        return (msk >> (b * 2)) & 3;
    };
    rep (i, 0, n) {
        { // left line
            map<int, ll> g;
            for (const auto &[k, v] : dp) {
                g[k << 2] += v;
            }
            swap(dp, g);
        }
        rep (j, 0, m) {
            map<int, ll> g;
            for (const auto &[k, v] : dp) {
                int left = get(k, j), up = get(k, j + 1);
                if (!G[i][j]) {
                    if (!left && !up) g[k] += v;
                } else if (!left && !up) {
                    if (G[i + 1][j] && G[i][j + 1]) g[k + fr[j + 1] * 2 + fr[j]] += v;
                } else if (!left && up) {
                    if (G[i + 1][j]) g[k - up * fr[j + 1] + up * fr[j]] += v;
                    if (G[i][j + 1]) g[k] += v;
                } else if (left && !up) {
                    if (G[i + 1][j]) g[k] += v;
                    if (G[i][j + 1]) g[k - left * fr[j] + left * fr[j + 1]] += v;
                } else if (left == 1 && up == 1) {
                    int cnt = 1;
                    rep (l, j + 2, m) {
                        int cur = get(k, l);
                        if (cur == 1) cnt++;
                        if (cur == 2) cnt--;
                        if (cnt == 0) {
                            g[k - fr[j] - fr[j + 1] - fr[l]] += v;
                            break;
                        }
                    }
                } else if (left == 2 && up == 2) {
                    int cnt = 1;
                    for (int l = j - 1; j >= 0; --l) {
                        int cur = get(k, l);
                        if (cur == 2) cnt++;
                        if (cur == 1) cnt--;
                        if (cnt == 0) {
                            g[k - 2 * fr[j] - 2 * fr[j + 1] + fr[l]] += v;
                            break;
                        }
                    }
                } else if (left == 2 && up == 1) {
                    g[k - 2 * fr[j] - fr[j + 1]] += v;
                } else if (i == ex && j == ey) {
                    ans += v;
                }
            }
            swap(dp, g);
        }
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}