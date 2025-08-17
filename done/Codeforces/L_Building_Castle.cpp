#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

#define int i64
#define all(a) a.begin(), a.end()
#define rep(a, b, c) for (int a = b; a < c; a++)

#ifdef PEPPA
template <typename R>
concept I = ranges::range<R> && !std::same_as<ranges::range_value_t<R>, char>;
template <typename A, typename B>
std::ostream &operator<<(std::ostream &o, const std::pair<A, B> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}
template <I T>
std::ostream &operator<<(std::ostream &o, const T &v) {
    o << "{";
    int f = 0;
    for (auto &&i : v) o << (f++ ? " " : "") << i;
    return o << "}";
}
void debug__(int c, auto &&...a) {
    std::cerr << "\e[1;" << c << "m";
    (..., (std::cerr << a << " "));
    std::cerr << "\e[0m" << std::endl;
}
#define debug_(c, x...) debug__(c, __LINE__, "[" + std::string(#x) + "]", x)
#define debug(x...) debug_(93, x)
#else
#define debug(x...) void(0)
#endif

bool chmin(auto& a, auto b) { return (b < a and (a = b, true)); }
bool chmax(auto& a, auto b) { return (a < b and (a = b, true)); }

using numbers::pi;
template<class T> inline constexpr T eps = numeric_limits<T>::epsilon() * 1E8;
using Real = double;
struct Pt {
    Real x{}, y{};
    Pt operator+(Pt a) const { return {x + a.x, y + a.y}; }
    Pt operator-(Pt a) const { return {x - a.x, y - a.y}; }
    Pt operator*(Real k) const { return {x * k, y * k}; }
    Pt operator/(Real k) const { return {x / k, y / k}; }
    Real operator*(Pt a) const { return x * a.x + y * a.y; }
    Real operator^(Pt a) const { return x * a.y - y * a.x; }
    auto operator<=>(const Pt&) const = default;
    bool operator==(const Pt&) const = default;
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
Pt unit(Pt x) { return x / abs(x); }

struct Line { 
    Pt a, b;
    Pt dir() const { return b - a; }
};
int PtSide(Pt p, Line L) {
    // return sgn(ori(L.a, L.b, p)); // for int
    return sgn(ori(L.a, L.b, p) / abs(L.a - L.b));
}
bool PtOnSeg(Pt p, Line L) {
    return PtSide(p, L) == 0 and sgn((p - L.a) * (p - L.b)) <= 0;
}
Pt proj(Pt p, Line l) {
    Pt dir = unit(l.b - l.a);
    return l.a + dir * (dir * (p - l.a));
}

bool isInter(Line l, Line m) {
    if (PtOnSeg(m.a, l) or PtOnSeg(m.b, l) or
        PtOnSeg(l.a, m) or PtOnSeg(l.b, m))
        return true;
    return PtSide(m.a, l) * PtSide(m.b, l) < 0 and
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
    if (la == 0 and lb == 0) return false;
    return la * lb < 0 and ma * mb < 0;
}

bool cover(Line L, Line P, Line Q) {
    // return PtSide(LineInter(P, Q), L) <= 0; for double
    Real u = (Q.a - P.a) ^ Q.dir();
    Real v = P.dir() ^ Q.dir();
    Real x = P.dir().x * u + (P.a - L.a).x * v;
    Real y = P.dir().y * u + (P.a - L.a).y * v;
    return sgn(x * L.dir().y - y * L.dir().x) * sgn(v) >= 0;
}
vector<Line> HPI(vector<Line> &P) {
    sort(all(P), [&](Line l, Line m) {
        if (argcmp(l.dir(), m.dir())) return true;
        if (argcmp(m.dir(), l.dir())) return false;
        return ori(m.a, m.b, l.a) > 0;
    });
    int n = P.size(), l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        if (i and !argcmp(P[i - 1].dir(), P[i].dir())) continue;
        while (l < r and cover(P[i], P[r - 1], P[r])) r--;
        while (l < r and cover(P[i], P[l], P[l + 1])) l++;
        P[++r] = P[i];
    }
    while (l < r and cover(P[l], P[r - 1], P[r])) r--;
    while (l < r and cover(P[r], P[l], P[l + 1])) l++;
    if (r - l <= 1 or !argcmp(P[l].dir(), P[r].dir()))
        return {}; // empty
    if (cover(P[l + 1], P[l], P[r]))
        return {}; // infinity
    return vector(P.begin() + l, P.begin() + r + 1);
}

vector<Pt> BuildHull(vector<Pt> pt) {
    sort(all(pt));
    pt.erase(unique(all(pt)), pt.end());
    if (pt.size() <= 2) return pt;
    vector<Pt> hull;
    int sz = 1;
    rep (t, 0, 2) {
        rep (i, t, ssize(pt)) {
            while (ssize(hull) > sz && ori(hull.end()[-2], pt[i], hull.back()) >= 0)
                hull.pop_back();
            hull.push_back(pt[i]);
        }
        sz = ssize(hull);
        reverse(all(pt));
    }
    hull.pop_back();
    return hull;
}

void solve() {
    int n; cin >> n;
    vector<Pt> pt;
    Real l = 1e8, r = -1e8;
    rep (i, 0, n) {
        int x, y; cin >> x >> y;
        l = min<Real>(l, x);
        r = max<Real>(r, x);
        pt.push_back(Pt{x, y});
    }
    auto nxt = [&](int i, int sz) -> int { i++; return i >= sz ? i - sz : i; };
    auto Area = [&](const vector<Pt> &p) -> Real {
        Real A = 0;
        rep (i, 0, ssize(p)) {
            A += p[nxt(i, ssize(p))] ^ p[i];
        }
        return fabs(A);
    };
    Real oA = Area(pt);
    auto calc2 = [&](Pt P) -> Real {
        vector<Pt> B;
        rep (i, 0, n) B.push_back(pt[i] + (P - pt[i]) * 2.);
        vector<Line> S;
        rep (i, 0, n) {
            S.push_back(Line{pt[i], pt[nxt(i, n)]});
            S.push_back(Line{B[i], B[nxt(i, n)]});
        }
        auto HP = HPI(S);
        vector<Pt> IN;
        rep (i, 0, ssize(HP)) IN.push_back(LineInter(HP[i], HP[nxt(i, ssize(HP))]));
        return oA - Area(IN);
    };
    auto calc = [&](Real x) -> Real {
        Line ver = Line{Pt{x, -1e8}, Pt{x, 1e8}};
        Real u = 1e8, d = -1e8;
        rep (i, 0, n) if (isInter(ver, Line{pt[i], pt[nxt(i, n)]})) {
            Real y = LineInter(ver, Line{pt[i], pt[nxt(i, n)]}).y;
            u = min(u, y);
            d = max(d, y);
        }
        rep (t, 0, 80) {
            Real mu = (u + u + d) / 3, md = (u + d + d) / 3;
            if (calc2(Pt{x, mu}) + eps<Real> < calc2(Pt{x, md})) d = md; 
            else u = mu;
        }
        return calc2(Pt{x, u});
    };
    rep (t, 0, 80) {
        Real ml = (l + l + r) / 3, mr = (l + r + r) / 3;
        if (calc(ml) + eps<Real> < calc(mr)) r = mr;
        else l = ml;
    }
    cout << fixed << setprecision(15) << calc(l) * 0.5 << '\n';
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    // std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

