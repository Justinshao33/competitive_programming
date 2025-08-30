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

struct Convex {
    int n; 
    vector<Pt> A, V, L, U;
    Convex() {}
    Convex(const vector<Pt> &_A) : A(_A), n(_A.size()) { // n >= 3
        auto it = max_element(all(A));
        L.assign(A.begin(), it + 1);
        U.assign(it, A.end()), U.push_back(A[0]);
        rep (i, 0, n) {
            V.push_back(A[(i + 1) % n] - A[i]);
        }
    }
    int inside(Pt p, const vector<Pt> &h, auto f) {
        auto it = lower_bound(all(h), p, f);
        if (it == h.end()) return 0;
        if (it == h.begin()) return p == *it;
        return 1 - sgn(ori(*prev(it), p, *it));
    }
    // 0: out, 1: on, 2: in
    int inside(Pt p) { 
        return min(inside(p, L, less{}), inside(p, U, greater{}));
    }
    static bool cmp(Pt a, Pt b) { return sgn(a ^ b) > 0; }
    // A[i] is a far/closer tangent point
    int tangent(Pt v, bool close = true) {
        assert(v != Pt{});
        auto l = V.begin(), r = V.begin() + L.size() - 1;
        if (v < Pt{}) l = r, r = V.end();
        if (close) return (lower_bound(l, r, v, cmp) - V.begin()) % n;
        return (upper_bound(l, r, v, cmp) - V.begin()) % n;
    } 
    // closer tangent point
    array<int, 2> tangent2(Pt p) {
        array<int, 2> t{-1, -1};
        if (inside(p) == 2) return t;
        if (auto it = lower_bound(all(L), p); it != L.end() and p == *it) {
            int s = it - L.begin();
            return {(s + 1) % n, (s - 1 + n) % n};
        }
        if (auto it = lower_bound(all(U), p, greater{}); it != U.end() and p == *it) {
            int s = it - U.begin() + L.size() - 1;
            return {(s + 1) % n, (s - 1 + n) % n};
        }
        for (int i = 0; i != t[0]; i = tangent((A[t[0] = i] - p), 0));
        for (int i = 0; i != t[1]; i = tangent((p - A[t[1] = i]), 1));
        return t;
    }
    int find(int l, int r, Line L) {
        if (r < l) r += n;
        int s = PtSide(A[l % n], L);
        return *ranges::partition_point(views::iota(l, r),
            [&](int m) {
                return PtSide(A[m % n], L) == s;
            }) - 1;
    };
    // Line A_x A_x+1 interset with L
    vector<int> intersect(Line L) {
        int l = tangent(L.a - L.b), r = tangent(L.b - L.a);
        if (PtSide(A[l], L) * PtSide(A[r], L) >= 0) return {};
        return {find(l, r, L) % n, find(r, l, L) % n};
    }
};

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

vector<Pt> a;

#define lpos pos << 1
#define rpos pos << 1 | 1

const int MAXN = 1e5 + 5;

Convex tree[MAXN << 2];

void build(int pos, int l, int r) {
    tree[pos] = Convex(BuildHull(vector(a.begin() + l, a.begin() + r + 1)));
    if (l == r) return;
    int mid = l + r >> 1;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
}

pair<Real, Real> query(int pos, int l, int r, int ql, int qr, Pt p) {
    if (ql <= l && qr >= r) {
        pair<Real, Real> pi{1e18, -1e18};
        auto ata = [&](Pt pp) -> Real {
            return atan2(pp.y, pp.x);
        };
        if (ssize(tree[pos].A) <= 2) {
            rep (i, 0, ssize(tree[pos].A)) {
                chmin(pi.first, ata(tree[pos].A[i] - p));
                chmax(pi.second, ata(tree[pos].A[i] - p));
            }
        } else {
            auto pt = tree[pos].tangent2(p);
            rep (i, 0, 2) if (pt[i] != -1) {
                chmin(pi.first, ata(tree[pos].A[pt[i]] - p));
                chmax(pi.second, ata(tree[pos].A[pt[i]] - p));
            }
        }
        return pi;
    }
    int mid = l + r >> 1;
    if (qr <= mid) return query(lpos, l, mid, ql, qr, p);
    if (ql > mid) return query(rpos, mid + 1, r, ql, qr, p);
    auto lp = query(lpos, l, mid, ql, qr, p);
    auto rp = query(rpos, mid + 1, r, ql, qr, p);
    return make_pair(min(lp.first, rp.first), max(lp.second, rp.second));
}

void solve() {
    int n, q; cin >> n >> q;
    a.resize(n);
    for (auto &[x, y] : a) {
        int xx, yy; cin >> xx >> yy;
        x = xx, y = yy;
    }
    build(1, 0, n - 1);
    cout << fixed << setprecision(15);
    while (q--) {
        int l, r, x, y; cin >> l >> r >> x >> y;
        l--, r--;
        auto [L, R] = query(1, 0, n - 1, l, r, Pt{x, y});
        cout << (R - L) / acosl(-1) * 180 << '\n';
    }
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