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

void solve() {
    vector<pair<Pt, Pt>> P(3);
    for (auto &[x, y] : P) cin >> x.x >> x.y;
    for (auto &[x, y] : P) cin >> y.x >> y.y;
    sort(all(P));
    if (sgn(ori(P[0].first, P[1].first, P[2].first)) == 0) {
        if (sgn(ori(P[0].second, P[1].second, P[2].second)) != 0) {
            cout << "No\n";
            return;
        }
        if (sgn((P[1].first - P[0].first) ^ (P[1].second - P[0].second)) != 0) {
            cout << "No\n";
            return;
        }
        if (sgn((P[0].first - P[0].second) ^ (P[1].first - P[0].second)) != 0) {
            cout << "No\n";
            return;
        }
        vector<pair<Pt, int>> id;
        rep (i, 0, 3) id.push_back({P[i].second, i});
        sort(all(id));
        int cnt = 0;
        rep (i, 0, 3) if (i != id[i].second) cnt++;
        if (cnt == 2) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
        }
    } else {
        if (sgn(ori(P[0].second, P[1].second, P[2].second)) == 0) {
            cout << "No\n";
            return;
        }
        // abc/4R = A
        Real R1 = (abs(P[1].first - P[0].first) * abs(P[2].first - P[1].first) * abs(P[0].first - P[2].first)) / fabs((P[1].first - P[0].first) ^ (P[2].first - P[0].first)), 
             R2 = (abs(P[1].second - P[0].second) * abs(P[2].second - P[1].second) * abs(P[0].second - P[2].second)) / fabs((P[1].second - P[0].second) ^ (P[2].second - P[0].second));
        if (fabs(R1 - R2) < eps<Real>) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}