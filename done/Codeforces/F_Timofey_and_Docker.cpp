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
    string s; cin >> s;
    int n = ssize(s), mx = n / 6;
    int m; cin >> m;
    vector<int> cnt(mx + 2, 0);
    rep (i, 0, m) {
        int l, r; cin >> l >> r;
        chmin(r, mx);
        if (l > r) continue;
        cnt[l]++;
        cnt[r + 1]--;
    }
    rep (i, 1, mx + 1) cnt[i] += cnt[i - 1];
    int upp = *max_element(all(cnt)), ans = n, ok = 0;
    vector<int> cost(n, 0);
    string aim = "docker";
    rep (i, 0, n - 5) {
        rep (j, 0, 6) if (s[i + j] != aim[j]) cost[i]++;
        if (cost[i] == 0) ok++;
    }
    rep (i, 1, ok + 1) if (cnt[i] == upp) {
        chmin(ans, ok - i);
    }
    int k = -1;
    rep (i, ok + 1, mx + 1) if (cnt[i] == upp) {
        k = i;
        break;
    }
    if (k == -1) {
        cout << ans << '\n';
        return;
    }
    auto calc = [&](int p) -> pii {
        vector<pii> dp(n + 1, {IINF, 0});
        dp[0] = {0, 0};
        rep (i, 0, n) {
            chmin(dp[i + 1], dp[i]);
            if (i + 6 <= n) {
                chmin(dp[i + 6], make_pair(dp[i].fi + cost[i] - p, dp[i].se + 1));
            }
        }
        return dp[n];
    };
    int l = 0, r = n + 1;
    while (r - l > 1) {
        int mid = l + r >> 1;
        auto cur = calc(mid);
        if (cur.se <= k) l = mid;
        else r = mid;
    }
    auto dp = calc(l);
    chmin(ans, dp.fi + l * k);
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}