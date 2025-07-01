#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n; ll m; cin >> n >> m;
    vector<ll> a(n);
    rep (i, 0, n) cin >> a[i], a[i] %= m;
    // rep (i, 0, n) a[i] -= m / 2;
    sort(all(a));
    // assert(n <= 1000);
    ll ans = LINF, s = 0, s2 = 0, s3 = 0, s4 = 0, c = 0, c2 = 0, c3 = 0, c4 = 0;
    int ptr = 0, ptr2 = 0, ptr3 = n;
    rep (i, 0, n) {
        if (a[i] <= abs(m - a[i])) s3 += a[i], c3++;
        else {
            chmin(ptr3, i);
            s4 += a[i];
            c4++;
        }
    }
    rep (i, 0, n) {
        while (ptr3 < n && abs(a[ptr3] - a[i]) <= abs(m - (a[ptr3] - a[i]))) {
            s4 -= a[ptr3];
            s3 += a[ptr3];
            c4--;
            c3++;
            ptr3++;
        }
        while (ptr2 < n && a[ptr2] - a[i] < 0) {
            s3 -= a[ptr2];
            s2 += a[ptr2];
            c3--;
            c2++;
            ptr2++;
        }
        while (ptr < n && abs(-m - (a[ptr] - a[i])) < abs(a[ptr] - a[i])) {
            s2 -= a[ptr];
            s += a[ptr];
            c2--;
            c++;
            ptr++;
        }
        chmin(ans, c4 * m - (s4 - a[i] * c4) + (s3 - a[i] * c3) + 
            -(s2 - a[i] * c2) + (s - c * a[i]) - (-m) * c);
    }
    // cout << a;
    // ll l = -m, r = m;
    // auto check = [&](ll x) -> ll {
    //     ll sum = 0;
    //     rep (i, 0, n) {
    //         ll cur = (a[i] + x) % m;
    //         sum += min(abs(cur), abs(m - cur));
    //     }
    //     return sum;
    // };
    // ll l = -m / 2 - 1, r = m / 2;
    // while (r - l >= 3) {
    //     ll len = (r - l) / 3;
    //     ll m1 = l + len, m2 = r - len;
    //     if (check(m1) < check(m2)) r = m2 - 1;
    //     else l = m1;
    // }
    // ll ans = LINF;
    // rep (x, l, r + 1) {
    //     chmin(ans, check(x));
    // }
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