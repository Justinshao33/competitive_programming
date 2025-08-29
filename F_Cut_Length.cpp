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
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

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

struct info {
    vector<Pt> v; int id; Real dis;
};

void solve() {
    int n, q; cin >> n >> q;
    vector<Pt> gon;
    rep (i, 0, n) {
        Real x, y; cin >> x >> y;
        while (gon.size() > 1 && sgn(ori(gon.end()[-2], gon.back(), Pt{x, y})) == 0) gon.pop_back();
        gon.push_back(Pt{x, y});
    }
    while (gon.size() > 2 && sgn(ori(gon[1], gon[0], gon.back())) == 0) gon.erase(gon.begin());
    n = ssize(gon);
    Real A = 0;
    rep (i, 0, n) A += gon[(i + 1) % n] ^ gon[i];
    if (A < 0) reverse(all(gon));
    cout << fixed << setprecision(15);
    while (q--) {
        Pt A, B; cin >> A.x >> A.y >> B.x >> B.y;
        if (A > B) swap(A, B);
        Pt DIR = unit(B - A);
        A = A - DIR * 2000000, B = B + DIR * 2000000;
        Line li{A, B};
        vector<info> event;
        rep (i, 0, n) {
            Line cur{gon[i], gon[(i + 1) % n]};
            if (!isInter(li, cur)) continue;
            if ((li.dir() ^ cur.dir()) == 0) { // parallel
                if (abs2(cur.b - A) - abs2(cur.a - A) > eps<Real>) event.push_back({{cur.a, cur.b}, i, abs2(cur.a - A)});
                else event.push_back({{cur.b, cur.a}, i, abs2(cur.b - A)});
            } else {
                Pt p = LineInter(li, cur);
                event.push_back({{p}, i, abs2(p - A)});
                // debug(A, B, event.back().v);    
            }
        }
        sort(all(event), [&](const auto &a, const auto &b) {
            if (b.dis - a.dis < eps<Real>) return ssize(a.v) < ssize(b.v);
            return a.dis < b.dis;
        });
        bool isin = false;
        Real pre = 0, ans = 0;
        for (auto &[v, id, dis] : event) {
            // debug(v, pre, dis);    
            // debug(dis - pre);
            // cout << v << ' ' << pre << ' ' << dis << '\n';
            dis = sqrtl(dis);
            if (isin) ans += dis - pre;
            bool f = PtOnSeg(gon[id], li), g = PtOnSeg(gon[(id + 1) % n], li);
            if ((!f && !g) || (f && !g)) isin = !isin;
            if (f && !g && PtSide(gon[(id + 1) % n], li) == PtSide(gon[(id - 1 + n) % n], li)) {
                assert(PtSide(gon[(id + 1) % n], li) != 0);    
                isin = !isin;
            }
            if (ssize(v) == 2) {
                assert(abs(v[0] - A) < abs(v[1] - A));
                ans += abs(v[0] - v[1]);
                pre = abs(v[1] - A);
            } else {
                pre = dis;
            }
        }
        cout << ans << '\n';
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}