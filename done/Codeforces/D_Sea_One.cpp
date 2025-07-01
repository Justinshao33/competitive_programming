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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n; double C; cin >> n >> C;
    vector<array<double, 3>> pos, neg;
    double ans = 0;
    double l = 0, r = 0;
    rep (i, 0, n) {
        double q, c, p; cin >> q >> c >> p;
        if (q == 0) continue;
        if (c > 0 && p > 0) pos.pb({q, c, p});
        else if (c <= 0 && p >= 0) {
            continue;
        } else if (c >= 0 && p <= 0) {
            ans += c * q;
            C += -p * q;
        } else {
            neg.pb({q, -c, -p});
            r += q * -c;
        }
    }
    sort(all(pos), [&](const auto &a, const auto &b) {
        return a[1] * b[2] > a[2] * b[1];
    });
    sort(all(neg), [&](const auto &a, const auto &b) {
        return a[2] * b[1] > a[1] * b[2];
    });
    auto calc = [&](double x) -> double {
        double nC = C, res = ans - x;
        for (double sum = 0; auto &[q, c, p] : neg) {
            double d = min(q * c, x - sum);
            nC += d * (p / c);
            sum += d;
        }
        for (double sum = 0; auto &[q, c, p] : pos) {
            double d = min(q * p, nC - sum);
            // debug(nC, sum, d, c);
            res += d * (c / p);
            sum += d;
        }
        return res;
    };
    rep (t, 0, 100) {
        double lm = l + (r - l) / 3, rm = r - (r - l) / 3;
        if (calc(lm) < calc(rm)) l = lm;
        else r = rm;
    }
    cout << fixed << setprecision(15) << calc(l) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}