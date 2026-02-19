#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define int long long

using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
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
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

// https://github.com/warner1129/CompetitiveProgrammingCodebook/tree/master/code/Geometry
using numbers::pi;
template<class T> inline constexpr T eps = numeric_limits<T>::epsilon() * 1E6;
using Real = long long;

struct Pt {
    Real x{}, y{};
    Pt operator+ (Pt a) const { return {x + a.x, y + a.y}; }
    Pt operator- (Pt a) const { return {x - a.x, y - a.y}; }
    Pt operator* (Real k) const { return {x * k, y * k}; }
    Pt operator/ (Real k) const { return {x / k, y / k}; }
    Real operator* (Pt a) const { return x * a.x + y * a.y; }
    Real operator^ (Pt a) const { return x * a.y - y * a.x; }
    auto operator<=> (const Pt&) const = default;
    bool operator== (const Pt&) const = default;
    friend ostream& operator<< (ostream &os, const Pt& p) { os << '(' << p.x << "," << p.y << ')'; return os; }
};

int sgn(Real x) { return (x > -eps<Real>) - (x < eps<Real>); }
Real ori(Pt a, Pt b, Pt c) { return (b - a) ^ (c - a); }
bool argcmp(const Pt &a, const Pt &b) { // arg(a) < arg(b)
    int f = (Pt{a.y, -a.x} > Pt{} ? 1 : -1) * (a != Pt{});
    int g = (Pt{b.y, -b.x} > Pt{} ? 1 : -1) * (b != Pt{});
    return f == g ? (a ^ b) > 0 : f < g;
}
Pt rotate(Pt u) { return {-u.y, u.x}; }
Real abs2(Pt a) { return a * a; }
// floating point only
Pt rotate(Pt u, Real a) {
    Pt v{sinl(a), cosl(a)};
    return {u ^ v, u * v};
}
Real abs(Pt a) { return sqrtl(a * a); }
Real arg(Pt x) { return atan2l(x.y, x.x); }
Pt unit(Pt x) { 
    int g = gcd(x.x, x.y);
    assert(g != 0);
    x.x /= g, x.y /= g;
    if (x.x < 0 || (x.x == 0 && x.y < 0)) x = x * -1;
    return x;
}

struct Line { 
    Pt a, b;
    Pt dir() const { return b - a; }
};

int PtSide(Pt p, Line L) {
    return sgn(ori(L.a, L.b, p)); // for int
    return sgn(ori(L.a, L.b, p) / abs(L.a - L.b));
}
bool PtOnSeg(Pt p, Line L) {
    return PtSide(p, L) == 0 && sgn((p - L.a) * (p - L.b)) <= 0;
}
Pt proj(Pt p, Line l) {
    Pt dir = unit(l.b - l.a);
    return l.a + dir * (dir * (p - l.a));
}
bool isInter(Line l, Line m) {
    if (PtOnSeg(m.a, l) || PtOnSeg(m.b, l) ||
        PtOnSeg(l.a, m) || PtOnSeg(l.b, m))
        return true;
    return PtSide(m.a, l) * PtSide(m.b, l) < 0 &&
           PtSide(l.a, m) * PtSide(l.b, m) < 0;
}
Pt LineInter(Line l, Line m) {
    double s = ori(m.a, m.b, l.a), t = ori(m.a, m.b, l.b);
    return (l.b * s - l.a * t) / (s - t);
}
bool strictInter(Line l, Line m) {
    int la = PtSide(m.a, l);
    int lb = PtSide(m.b, l);
    int ma = PtSide(l.a, m);
    int mb = PtSide(l.b, m);
    if (la == 0 && lb == 0) return false;
    return la * lb < 0 && ma * mb < 0;
}

void solve() {
    int n; cin >> n;
    vector<Pt> pt;
    vector<int> c(n);
    map<array<int, 3>, vector<pair<Pt, int>>> mp;
    int ans = -1; 
    rep (i, 0, n) {
        int x, y; cin >> x >> y >> c[i];
        pt.push_back({x, y});
        rep (j, 0, i) {
            auto oth = unit(rotate(pt[i] - pt[j]));
            Pt mid = pt[i] + pt[j];
            mp[{oth.y, -oth.x, oth ^ mid}].push_back({mid, c[i] + c[j]});
        }        
    }
    for (auto [k, v] : mp) {
        sort(all(v));
        int mx = -LINF;
        rep (i, 0, ssize(v)) {
            int ptr = i, cmx = 0;
            while (ptr < ssize(v) && v[i].fi == v[ptr].fi) {
                chmax(ans, mx + v[ptr].se);
                chmax(cmx, v[ptr].se);
                ptr++;
            }
            chmax(mx, cmx);
            i = ptr - 1;
        }
    }
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}