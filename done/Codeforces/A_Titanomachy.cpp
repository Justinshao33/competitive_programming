#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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
 
const int MAXN = 3e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
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
__int128_t ori(Pt a, Pt b, Pt c) { 
    return (__int128_t)(b.x - a.x) * (c.y - a.y) - (__int128_t)(b.y - a.y) * (c.x - a.x); 
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
            hull.pb(pt[i]);
        }
        sz = ssize(hull);
        reverse(all(pt));
    }
    hull.pop_back();
    return hull;
}

// P, Q, R(return) are counterclockwise order convex polygon
vector<Pt> Minkowski(vector<Pt> P, vector<Pt> Q) {
    assert(P.size() >= 2 && Q.size() >= 2);
    auto cmp = [&](Pt a, Pt b) {
        return Pt{a.y, a.x} < Pt{b.y, b.x};
    };
    auto reorder = [&](auto &R) {
        rotate(R.begin(), min_element(all(R), cmp), R.end());
        R.push_back(R[0]), R.push_back(R[1]);
    };
    const int n = P.size(), m = Q.size();
    reorder(P), reorder(Q);
    vector<Pt> R;
    for (int i = 0, j = 0, s; i < n || j < m; ) {
        R.push_back(P[i] + Q[j]);
        s = sgn((P[i + 1] - P[i]) ^ (Q[j + 1] - Q[j]));
        if (s >= 0) i++;
        if (s <= 0) j++;
    }
    return R; // May not be a strict convexhull
}

struct info {
    int pre, suf, ans, sum;
    info operator+(const info &oth) {
        return info{max(pre, sum + oth.pre), max(suf + oth.sum, oth.suf), max({ans, oth.ans, suf + oth.pre}), sum + oth.sum};
    }
};

int add = 0;

struct Bao {
    vector<Pt> pt;
    int ptr = 0;

    inline Pt operator[](const int &i) const {
        return pt[i];
    }

    void push(Pt p) {
        pt.push_back(p);
    }

    void convex() {
        pt = BuildHull(pt);
    }

    int val() {
        int n = pt.size();
        if (n == 0) return 0;
        if (n == 1) return pt[0].y + add * pt[0].x;
        auto get = [&](int i) { return pt[i].y + add * pt[i].x; };
        while (get(ptr) < get((ptr + 1) % n)) ptr = (ptr + 1) % n;
        while (get(ptr) < get((ptr - 1 + n) % n)) ptr = (ptr - 1 + n) % n;
        return pt[ptr].y + add * pt[ptr].x;
    }
};

Bao pre[MAXN << 2], suf[MAXN << 2], ans[MAXN << 2];
int sum[MAXN << 2];

void build(int pos, int l, int r, vector<int> &a) {
    if (l == r) {
        pre[pos].push(Pt{0, 0}), pre[pos].push(Pt{1, a[l]});
        suf[pos].push(Pt{0, 0}), suf[pos].push(Pt{1, a[l]});
        ans[pos].push(Pt{0, 0}), ans[pos].push(Pt{1, a[l]});
        sum[pos] = a[l];
        pre[pos].convex();
        suf[pos].convex();
        ans[pos].convex();
        return;    
    }
    int mid = l + r >> 1;
    build(lpos, l, mid, a);
    build(rpos, mid + 1, r, a);
    {   // pre
        rep (i, 0, ssize(pre[lpos].pt)) pre[pos].push(pre[lpos][i]);
        rep (i, 0, ssize(pre[rpos].pt)) pre[pos].push(Pt{mid - l + 1, sum[lpos]} + pre[rpos][i]);
        pre[pos].convex();
    }
    {   // suf
        rep (i, 0, ssize(suf[rpos].pt)) suf[pos].push(suf[rpos][i]);
        rep (i, 0, ssize(suf[lpos].pt)) suf[pos].push(Pt{r - mid, sum[rpos]} + suf[lpos][i]);
        suf[pos].convex();
    }
    {   // ans
        ans[pos].push(Pt{0, 0});           
        for (Pt p : ans[lpos].pt) ans[pos].push(p);
        for (Pt p : ans[rpos].pt) ans[pos].push(p);
        auto S = Minkowski(suf[lpos].pt, pre[rpos].pt);
        for (Pt p : S) ans[pos].push(p);
        ans[pos].convex();
    }
    {   // sum
        sum[pos] = sum[lpos] + sum[rpos];
    }
}

info query(int pos, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) return info{pre[pos].val(), suf[pos].val(), ans[pos].val(), sum[pos] + (r - l + 1) * add};
    int mid = l + r >> 1;
    info res{-LINF, -LINF, -LINF, 0};
    if (ql <= mid) res = res + query(lpos, l, mid, ql, qr);
    if (qr > mid) res = res + query(rpos, mid + 1, r, ql, qr);
    return res;
}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    rep (i, 0, n) cin >> a[i];
    vector<array<int, 4>> que;
    vector<int> ans(q, -1);
    int ps = 0;
    rep (i, 0, q) {
        string s; cin >> s;
        if (s[0] == 'A') {
            int l, r; cin >> l >> r;
            que.push_back({ps, l - 1, r - 1, i});
        } else {
            int x; cin >> x;
            ps += x;
        }
    }
    if (!que.empty()) {
        sort(all(que));
        rep (i, 0, n) a[i] += que[0][0];
        for (int i = ssize(que) - 1; i >= 0; --i) que[i][0] -= que[0][0];
    }
    build(1, 0, n - 1, a);
    for (const auto &[x, l, r, id] : que) {
        add = x;
        ans[id] = query(1, 0, n - 1, l, r).ans;
        // debug(x, l, r, id, ans[id]);
    }
    rep (i, 0, q) if (ans[i] != -1) {
        cout << ans[i] << '\n';
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) solve();
}