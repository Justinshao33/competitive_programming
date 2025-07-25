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
 
const int MAXN = 1e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n; ll m; cin >> n >> m;
    vector<ll> a(n), pre(n);
    rep (i, 0, n) cin >> a[i];
    sort(all(a));
    pre[0] = a[0];
    rep (i, 1, n) pre[i] = pre[i - 1] + a[i];
    int l = 0, r = 2e5 + 5;
    auto check = [&](int x) -> bool {
        ll cnt = 0;
        rep (i, 0, n) if (a[i] + a[n - 1] >= x) {
            cnt += n - (lower_bound(all(a), x - a[i]) - a.begin());
        }
        return cnt >= m;
    };
    while (r - l > 1) {
        int mid = l + r >> 1;
        if (check(mid)) l = mid;
        else r = mid;
    }
    ll ans = 0;
    l++;
    rep (i, 0, n) if (a[i] + a[n - 1] >= l) {
        int id = n - (lower_bound(all(a), l - a[i]) - a.begin());
        ans += pre[n - 1] - (n - id < 1 ? 0 : pre[n - id - 1]) + a[i] * id;
        // cout << id << ' ' << ans << '\n';
        m -= id;
    }
    l--;
    ans += 1LL * l * m;
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