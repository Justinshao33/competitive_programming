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
using Real = long double;

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
// Pt rotate(Pt u) { return {-u.y, u.x}; }
Real abs2(Pt a) { return a * a; }
// floating point only
Pt rotate(Pt u, Real a) {
    Pt v{sinl(a), cosl(a)};
    // if (a < pi / 2 + eps<Real>) debug(u, a, v);
    // debug(u, a, v);
    return {u ^ v, u * v};
}
Real abs(Pt a) { return sqrtl(a * a); }
Real arg(Pt x) { return atan2l(x.y, x.x); }
Pt unit(Pt x) { return x / abs(x); }

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
    if (n == 1) {
        cout << "Yes\n";
        return;
    }
    vector<Pt> a(n), b(n);
    rep (i, 0, n) cin >> a[i].x >> a[i].y;
    rep (i, 0, n) cin >> b[i].x >> b[i].y; 
    // O(n^4)
    auto dis = [&](vector<Pt> &p) -> vector<int> {
        vector<int> d;
        rep (i, 0, n) d.push_back(abs2(p[i]));
        return d;
    };
    auto shift = [&]() -> bool {
        vector<Pt> aa, bb;
        rep (i, 0, n) aa.push_back(a[i] - a[0]);
        rep (i, 0, n) bb.push_back(b[i] - b[0]);
        auto da = dis(aa), db = dis(bb);
        auto rot = [&](Real x) -> bool {
            // x = x / pi * 180;
            if (a[0] == Pt{0, 0} && b[0] == Pt{3, 0}) debug(x);
            auto aaa = aa;
            auto bbb = bb;
            rep (i, 0, n) {
                aaa[i] = rotate(aa[i], x);
                bbb[i] = rotate(bb[i], x);
            }
            auto aaaa = aa;
            auto bbbb = bb;
            sort(all(aaa));
            sort(all(aaaa));
            sort(all(bbb));
            sort(all(bbbb));
            // if (a[0] == Pt{0, 0} && b[0] == Pt{3, 0}) debug(aaaa, bbbb);
            // if (a[0] == Pt{0, 0} && b[0] == Pt{3, 0}) debug(aaa, bbb);
            bool f = 1;
            rep (i, 0, n) {
                if (abs2(aaa[i] - bbbb[i]) > eps<Real>) f = 0;
            }
            if (f) return true;
            f = 1;
            rep (i, 0, n) {
                if (abs2(aaaa[i] - bbb[i]) > eps<Real>) f = 0;
            }
            return f;
        };
        rep (i, 1, n) if (da[1] == db[i]) {
            // if (a[0] == Pt{0, 0} && b[0] == Pt{3, 0}) {
            //     debug(aa, bb);
            //     debug(da[1], i, db[i]);
            // }
            Real angle = atan2l(bb[i].y, bb[i].x) - atan2l(aa[1].y, aa[1].x);
            if (rot(angle)) return true;
        } 
        return false;
    };
    rep (i, 0, n) {
        rep (j, 0, n) {
            // debug(a, b);
            if (shift()) {
                cout << "Yes\n";
                return; 
            }
            rotate(b.begin(), b.begin() + 1, b.end());
        }
        rotate(a.begin(), a.begin() + 1, a.end());
    }
    cout << "No\n";
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}