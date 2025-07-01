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

struct info {
    int opt, l, r;
};

void solve() {
    int n; cin >> n;
    vector<ll> b(n + 1), w(n + 1), t(n + 1), preb(n + 1), prew(n + 1);
    t[0] = preb[0] = prew[0] = 0;
    rep (i, 1, n + 1) {
        cin >> b[i];
        preb[i] = preb[i - 1] + b[i];
    }
    rep (i, 1, n + 1) {
        cin >> w[i];
        prew[i] = prew[i - 1] + w[i];
    }
    rep (i, 1, n + 1) cin >> t[i]; 
    int lg = __lg(n);
    vector<vector<ll>> dp(n + 1, vector<ll>(2)), sp0(n + 1, vector<ll>(lg + 1)), sp1(n + 1, vector<ll>(lg + 1));
    // 0: b -> w
    // 1: w -> b
    rep (i, 0, n + 1) {
        sp0[i][0] = prew[i] + t[i]; // white
        sp1[i][0] = preb[i] + t[i]; // black
    }
    rep (j, 1, lg + 1) for (int i = 0; i + (1 << j) - 1 <= n; ++i) {
        sp0[i][j] = max(sp0[i][j - 1], sp0[i + (1 << (j - 1))][j - 1]);
        sp1[i][j] = max(sp1[i][j - 1], sp1[i + (1 << (j - 1))][j - 1]);
    }
    auto cost = [&](int l, int r, int t) -> int {
        if (l > r) return 0;
        int k = __lg(r - l + 1);
        if (t == 0) return max(sp0[l][k], sp0[r - (1 << k) + 1][k]);
        else return max(sp1[l][k], sp1[r - (1 << k) + 1][k]);
    };
    auto calc = [&](int l, int i, int t) -> int {
        if (t == 1) return dp[l][1] + cost(l, i - 1, 1) - preb[l];
        else return dp[l][0] + cost(l, i - 1, 0) - prew[l];
    };
    vector<info> st0, st1;
    st0.pb({0, 1, n});
    st1.pb({0, 1, n});
    dp[0][0] = dp[0][1] = 0;
    rep (i, 1, n + 1) {
        while (!st0.empty() && st0.back().r < i) st0.pop_back();
        while (!st1.empty() && st1.back().r < i) st1.pop_back();
        dp[i][0] = calc(st1.back().opt, i, 1) + w[i];
        dp[i][1] = calc(st0.back().opt, i, 0) + b[i];
        while (!st0.empty() && calc(i, st0.back().r, 0) <= calc(st0.back().opt, st0.back().r, 0)) st0.pop_back();
        while (!st1.empty() && calc(i, st1.back().r, 1) <= calc(st1.back().opt, st1.back().r, 1)) st1.pop_back();
        if (st0.empty()) {
            st0.pb({i, i + 1, n});
        } else {
            auto [opt, l, r] = st0.back();
            while (l < r) {
                int mid = l + r >> 1;
                if (calc(opt, mid, 0) < calc(i, mid, 0)) r = mid;
                else l = mid + 1;
            }
            st0.back().l = l;
            if (i + 1 <= l - 1) st0.pb({i, i + 1, l - 1});
        }
        if (st1.empty()) {
            st1.pb({i, i + 1, n});
        } else {
            auto [opt, l, r] = st1.back();
            while (l < r) {
                int mid = l + r >> 1;
                if (calc(opt, mid, 1) < calc(i, mid, 1)) r = mid;
                else l = mid + 1;
            }
            st1.back().l = l;
            if (i + 1 <= l - 1) st1.pb({i, i + 1, l - 1});
        }
    }
    ll ans = INT_MAX;
    rep (i, 0, n + 1) {
        ans = min({ans, dp[i][0] + (prew[n] - prew[i]), dp[i][1] + (preb[n] - preb[i])});
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