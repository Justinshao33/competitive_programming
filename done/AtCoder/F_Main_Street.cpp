#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
    ll B, k, sx, sy, gx, gy; cin >> B >> k >> sx >> sy >> gx >> gy;
    auto dis = [&](pll a, pll b) -> ll {
        return abs(a.fi - b.fi) + abs(a.se - b.se);
    };
    ll ans = dis({sx, sy}, {gx, gy}) * k;
    auto select = [&](ll x, ll y) -> vector<pll> {
        if (x % B == 0 || y % B == 0) return vector<pll>(1, {x, y});
        ll px = x / B * B, py = y / B * B;
        vector<pll> ret;
        ret.pb({x, py});
        ret.pb({x, py + B});
        ret.pb({px, y});
        ret.pb({px + B, y});
        return ret;
    };
    auto X = select(sx, sy), Y = select(gx, gy);
    auto calc = [&](pll a, pll b) -> ll {
        if (a.fi > b.fi) swap(a, b);
        if ((a.fi % B == 0 && b.se % B == 0) || (a.se % B == 0 && b.fi % B == 0) || 
        (a.fi % B == 0 && b.fi % B == 0 && a.se / B != b.se / B) || 
        (a.se % B == 0 && b.se % B == 0 && a.fi / B != b.fi / B) ) return dis(a, b);
        if (a.se % B == 0) {
            swap(a.fi, a.se);
            swap(b.fi, b.se);
        }
        ll bt = a.se / B * B, tp = bt + B;
        return min({abs(a.fi - b.fi) + a.se - bt + b.se - bt,
                    abs(a.fi - b.fi) + tp - a.se + tp - b.se,
                    abs(a.fi - b.fi) * k + abs(a.se - b.se)});
    };
    for (pll a : X) for (pll b : Y) {
        chmin(ans, dis({sx, sy}, a) * k + dis(b, {gx, gy}) * k + calc(a, b));
    } 
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