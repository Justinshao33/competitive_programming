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
    int n; cin >> n;
    vector<pll> pt(n);
    for (auto &[x, y] : pt) cin >> x >> y;
    pll s, t; cin >> s.fi >> s.se >> t.fi >> t.se;
    n += 2;
    pt.pb(s);
    pt.pb(t);
    // need vector<pll> pt
    sort(all(pt));
    auto cross = [&](pll a, pll b) -> ll {
        return a.fi * b.se - a.se * b.fi;
    };
    vector<pll> hull;
    rep (i, 0, n) {
        while (hull.size() >= 2 && cross(pt[i] - hull.end()[-2], hull.back() - hull.end()[-2]) > 0) {
            hull.pop_back();
        }
        hull.pb(pt[i]);
    }
    int sz = hull.size();
    for(int i = n - 2; i >= 0; --i){
        while(hull.size() > sz && cross(pt[i] - hull.end()[-2], hull.back() - hull.end()[-2]) > 0) hull.pop_back();
        hull.pb(pt[i]);
    }
    hull.pop_back();
    sz = hull.size();
    int sid = -1, tid = -1;
    rep (i, 0, sz) {
        if (hull[i] == s) sid = i;
        if (hull[i] == t) tid = i;
    }
    ld ans;
    auto dis = [&](ll x, ll y) -> ld { return sqrtl(x * x + y * y); };
    if (sid == -1 || tid == -1) {
        ans = dis(s.fi - t.fi, s.se - t.se);
    } else {
        ld L = 0, R = 0;
        auto pre = [&](int x) -> int { return (x - 1 + sz) % sz; };
        auto nxt = [&](int x) -> int { return (x + 1) % sz; };
        for (int cur = sid; cur != tid; cur = nxt(cur)) L += dis(hull[cur].fi - hull[nxt(cur)].fi, hull[cur].se - hull[nxt(cur)].se);
        for (int cur = sid; cur != tid; cur = pre(cur)) R += dis(hull[cur].fi - hull[pre(cur)].fi, hull[cur].se - hull[pre(cur)].se);
        ans = min(L, R);
    }
    cout << fixed << setprecision(15) << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}