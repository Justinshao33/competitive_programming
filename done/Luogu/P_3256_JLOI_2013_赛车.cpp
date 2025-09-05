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
template<class T> inline constexpr T eps = numeric_limits<T>::epsilon() * 1E6;
using Real = long double;
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
    return sgn(ori(L.a, L.b, p)); // for int
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

using i128 = __int128;

bool cover(Line L, Line P, Line Q) {
    // for double, i128 => Real
    i128 u = (Q.a - P.a) ^ Q.dir();
    i128 v = P.dir() ^ Q.dir();
    i128 x = P.dir().x * u + (P.a - L.a).x * v;
    i128 y = P.dir().y * u + (P.a - L.a).y * v;
    return sgn(x * L.dir().y - y * L.dir().x) * sgn(v) > 0;
}
vector<pair<Line, int>> HPI(vector<pair<Line, int>> P) {
    sort(all(P), [&](auto l, auto m) {
        if (argcmp(l.first.dir(), m.first.dir())) return true;
        if (argcmp(m.first.dir(), l.first.dir())) return false;
        return ori(m.first.a, m.first.b, l.first.a) > 0;
    });
    // for (auto [li, _] : P) cout << li.dir().x << ' ' << li.dir().y << '\n';
    int n = P.size(), l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        if (i and !argcmp(P[i - 1].first.dir(), P[i].first.dir())) continue;
        while (l < r and cover(P[i].first, P[r - 1].first, P[r].first)) r--;
        while (l < r and cover(P[i].first, P[l].first, P[l + 1].first)) l++;
        P[++r] = P[i];
    }
    while (l < r and cover(P[l].first, P[r - 1].first, P[r].first)) r--;
    while (l < r and cover(P[r].first, P[l].first, P[l + 1].first)) l++;
    if (r - l <= 1 or !argcmp(P[l].first.dir(), P[r].first.dir()))
        return {}; // empty
    if (cover(P[l + 1].first, P[l].first, P[r].first))
        return {}; // infinity
    return vector(P.begin() + l, P.begin() + r + 1);
}

void solve() {
    int n; cin >> n;
    vector<int> b(n), v(n);
    rep (i, 0, n) cin >> b[i];
    rep (i, 0, n) cin >> v[i];
    vector<pair<Line, int>> line;
    map<pair<int, int>, int> mp;
    line.push_back({{{0, 1}, {0, 0}}, -1});
    line.push_back({{{1, 1e18 + 5}, {0, 1e18 + 5}}, -1});
    line.push_back({{{0, 0}, {1, 0}}, -1});
    line.push_back({{{1e18 + 5, 0}, {1e18 + 5, 1}}, -1});
    rep (i, 0, n) line.push_back({{{0, b[i]}, {1, v[i] + b[i]}}, i});
    auto hpi = HPI(line);
    sort(all(hpi), [&](auto a, auto b) {
        return a.second < b.second;
    });
    for (auto [_, id] : hpi) {
        if (id == -1) continue;
        mp[{b[id], v[id]}] = 1;
    }
    vector<int> ans;
    rep (i, 0, n) if (mp.count({b[i], v[i]})) ans.push_back(i);
    cout << ssize(ans) << '\n';
    for (int x : ans) cout << x + 1 << ' ';
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
