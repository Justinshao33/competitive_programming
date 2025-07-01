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

struct point{
    ll x, y;

    point() {}
    point(ll _x, ll _y) : x(_x), y(_y) {}
    
    point operator + (const point &p1) const { return {x + p1.x, y + p1.y}; }
    point operator - (const point &p1) const { return {x - p1.x, y - p1.y}; }
    ll    operator ^ (const point &p1) const { return x * p1.y - p1.x * y; }
    ll    operator * (const point &p1) const { return x * p1.x + y * p1.y; }
    
    bool in180() const {
        return (y > 0 || (y == 0 && x > 0));
    }
    
    bool operator < (const point &p1) const {
        if (in180() != p1.in180()) return in180();
        return ((*this) ^ p1) > 0;
    };
};

istream& operator >> (istream &is, point &p) { return is >> p.x >> p.y; }
ostream& operator << (ostream &os, const point &p) { return os << '(' << p.x << "," << p.y << ')'; }

double square(point o) { return o * o; }
double length(point o) { return sqrtl(square(o)); }

int sign(ll num){
    if (fabs(num) <= eps) return 0;
    return num > 0 ? 1 : -1;
}

int ori(point o, point a, point b) {
    return sign((a - o) ^ (b - o));
}
 
bool onseg(point p1, point p2, point p3) { // {online, online, other}
    point va = p1 - p3, vb = p2 - p3;
    return (va ^ vb) == 0 && (va * vb) <= 0;
}
 
bool banana(point p1, point p2, point q1, point q2) {
    if (onseg(p1, p2, q1) || onseg(p1, p2, q2) ||
       onseg(q1, q2, p1) || onseg(q1, q2, p2)) return 1;
    if (ori(p1, p2, q1) * ori(p1, p2, q2) < 0 &&
       ori(q1, q2, p1) * ori(q1, q2, p2) < 0) return 1;
    return 0;
}

double PointSegDist(point q0, point q1, point p) {
    if (sign(square(q0 - q1)) == 0) return square(q0 - p);
    if (sign((q1 - q0) * (p - q0)) >= 0 && sign((q0 - q1) * (p - q1)) >= 0)
        return fabs(((q1 - q0) ^ (p - q0)) / square(q0 - q1));
    return min(square(p - q0), square(p - q1));
}

bool PointInConvex(const vector<point> &C, point p, bool strict = true) {
    // no three points are collinear
    int a = 1, b = C.size() - 1, r = !strict;
    if (C.size() == 0) return false;
    if (C.size() < 3) return r && onseg(C[0], C.back(), p);
    if (ori(C[0], C[a], C[b]) > 0) swap(a, b);
    if (ori(C[0], C[a], p) >= r || ori(C[0], C[b], p) <= -r) return false;
    while (abs(a - b) > 1) {
        int c = a + b >> 1;
        (ori(C[0], C[c], p) > 0 ? b : a) = c;
    }
    return ori(C[a], C[b], p) < r;
}

void solve() {
    int n; cin >> n;
    vector<point> a(n), b(n);
    rep (i, 0, n) cin >> a[i] >> b[i];
    ll ans = 0;
    rep (i, 0, n) {
        point d = b[i] - a[i];
        ans += __gcd(abs(d.x), abs(d.y)) + 1;
    }
    rep (i, 0, n) {
        set<pll> st;
        rep (j, i + 1, n) {
            if (!banana(a[i], b[i], a[j], b[j])) continue;
            ll abc = (b[i] - a[i]) ^ (a[j] - a[i]);
            ll abd = (b[i] - a[i]) ^ (b[j] - a[i]);
            if ((b[j].x * abc - a[j].x * abd) % (abc - abd) || 
                (b[j].y * abc - a[j].y * abd) % (abc - abd)) continue;
            st.insert(pll((b[j].x * abc - a[j].x * abd) / (abc - abd), (b[j].y * abc - a[j].y * abd) / (abc - abd)));
        }
        ans -= st.size();
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