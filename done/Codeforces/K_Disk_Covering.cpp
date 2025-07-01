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

struct Cir { 
    Pt o;
    double r; 
};
bool disjunct(const Cir &a, const Cir &b) {
    return sgn(abs(a.o - b.o) - a.r - b.r) >= 0; 
}
bool contain(const Cir &a, const Cir &b) {
    return sgn(a.r - b.r - abs(a.o - b.o)) >= 0; 
}

vector<Pt> CircleInter(Cir a, Cir b) {
    double d2 = abs2(a.o - b.o), d = sqrt(d2);
    if (d < max(a.r, b.r) - min(a.r, b.r) || d > a.r + b.r) return {};
    Pt u = (a.o + b.o) / 2 + (a.o - b.o) * ((b.r * b.r - a.r * a.r) / (2 * d2));
    double A = sqrt((a.r + b.r + d) * (a.r - b.r + d) * (a.r + b.r - d) * (-a.r + b.r + d));
    Pt v = rotate(b.o - a.o) * A / (2 * d2);
    if (sgn(v.x) == 0 and sgn(v.y) == 0) return {u};
    return {u - v, u + v}; // counter clockwise of a
}

struct UnionFind {
    vector<int> sz;
    UnionFind(int n) : sz(n, -1) {}

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

void solve() {
    int n; cin >> n;
    vector<Cir> cir;
    rep (i, 0, n) {
        int x, y, r; cin >> x >> y >> r;
        cir.pb({Pt{x, y}, r});
    }
    { // 刪除有被完全包覆的圓
        vector<Cir> tmp;
        rep (i, 0, n) {
            bool f = 1;
            rep (j, 0, n) if (i != j && contain(cir[j], cir[i])) {
                f = 0;
            }
            if (f) tmp.pb(cir[i]);
        }
        swap(cir, tmp);
        n = ssize(cir);
    }

    vector adj(n, vector<vector<pii>>(n)); // 對圓交點建邊，邊可以看做是一段弧
    UnionFind dsu(n); // 確認圓的聯通性，以及拿來做之後內外弧的判斷

    struct info { // 點, 圓1, 圓2, 進去/出去
        Pt p; int i, j, v;
    };

    // (以下皆以逆時針觀點)
    rep (i, 0, n) { // 對每一個圓的圓周上所有事件點(或著說是弧)建立關係圖
        vector<info> event;
        int cnt = 0; // 紀錄目前看到的這段弧被多少其他圓覆蓋
        rep (j, 0, n) if (i != j) {
            auto v = CircleInter(cir[i], cir[j]); // 求交點
            if (v.empty()) continue;
            dsu.Union(i, j); // 建連通關係
            if (ori(cir[i].o, cir[j].o, v[0]) > 0) 
                swap(v[0], v[1]); /* 在這裡我們令v[0]是進去點而v[1]是出去點，
                                    可以想像v[0]應該要在o1指向o2的順時針方向才是好的，否則要交換。*/
            if (argcmp(v[1] - cir[i].o, v[0] - cir[i].o)) 
                cnt++; /* 這裡是十分重要的細節，由於極角排序後通常由正x軸方向開始掃，
                          因此若這段被另一個圓覆蓋的弧包含o1正x軸，代表起始位置要多記錄有一個圓覆蓋。 */
            // 下面建邊時(i, j)要互換是當成兩個圓的兩個交點 v[0]:(i, j) v[1]:(j, i)
            event.pb({v[0], i, j, 1});
            event.pb({v[1], j, i, -1});
        }
        if (event.empty()) continue;
        sort(all(event), [&](auto a, auto b){ // 對事件極角排序
            return argcmp(a.p - cir[i].o, b.p - cir[i].o);
        });
        int pi = event.back().i, pj = event.back().j; // 記得要做環狀
        // 這裡的建邊邏輯是，如果對於這段圓的某兩個相鄰事件點間沒有被其他圓覆蓋，我們就將這兩個點(圓)建一條邊。
        // 因此對於一個圓可以想像如果有被切割(其他圓覆蓋)，他的弧會被分配在不同的連通塊，而那些連通塊即會形成內外輪廓線
        for (auto [p, i, j, v] : event) {
            if (cnt == 0) {
                adj[i][j].pb({pi, pj});
                adj[pi][pj].pb({i, j});
            }
            cnt += v;
            tie(pi, pj) = pii(i, j);
        }
    }
    vector vis(n, vector<bool>(n, 0));
    vector<bool> vis2(n, 0);
    // 判弧連通
    auto dfs = [&](auto self, int i, int j) -> void {
        vis[i][j] = 1;
        for (auto [ni, nj] : adj[i][j]) {
            if (vis[ni][nj]) continue;
            self(self, ni, nj);
        }
    };
    rep (i, 0, n) rep (j, 0, n) {
        // 這裡的dsu很重要，可以想像如果一個圓的輪廓線屬於兩個以上不同的連通塊，即代表有答案要的空間
        // 因此dsu使得一個圓上只會有一條輪廓線的連通塊被看過，若存在其他未檢查的輪廓線連通塊就代表有解
        if (!vis2[dsu.find(i)] && !vis[i][j] && !adj[i][j].empty()) {
            vis2[dsu.find(i)] = 1;
            dfs(dfs, i, j);
        }
    }
    rep (i, 0, n) rep (j, 0, n) if (!adj[i][j].empty()) {
        if (!vis[i][j]) {
            cout << 1 << '\n';
            return;
        }
    }
    cout << 0 << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}