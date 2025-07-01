// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

#ifdef LOCAL
#define ZTMYACANESOCUTE freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

void dbg() { cerr << '\n'; }
template<typename T, typename ...U>
void dbg(T t, U ...u) { cerr << t << ' '; dbg(u...); }

pii operator + (const pii &p1, const pii &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pii operator - (const pii &p1, const pii &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }

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
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct point{
    ll x, y;
    
    point operator + (point p1) { return {x + p1.x, y + p1.y}; }
    point operator - (point p1) { return {x - p1.x, y - p1.y}; }
    ll    operator ^ (point p1) { return x * p1.y - p1.x * y; }
    ll    operator * (point p1) { return x * p1.x + y * p1.y; }
};

ostream& operator << (ostream &os, const point &p) { return os << '(' << p.x << "," << p.y << ')'; }

int sign(ll num){
    if (fabs(num) <= eps) return 0;
    return num > 0 ? 1 : -1;
}
 
bool onseg(point p1, point p2, point p3) { // {online, online, other}
    point va = p1 - p3, vb = p2 - p3;
    return (va ^ vb) == 0 && (va * vb) <= 0;
}
 
bool banana(point p1, point p2, point q1, point q2) {
    if (onseg(p1, p2, q1) || onseg(p1, p2, q2) ||
       onseg(q1, q2, p1) || onseg(q1, q2, p2)) return 1;
    if (sign((p2 - p1) ^ (q1 - p1)) * sign((p2 - p1) ^ (q2 - p1)) < 0 &&
       sign((q2 - q1) ^ (p1 - q1)) * sign((q2 - q1) ^ (p2 - q1)) < 0) return 1;
    return 0;
}

void solve() {
    int n; cin >> n;
    vector<point> pt(n);
    for (auto &[x, y] : pt) cin >> x >> y;
    rep (i, 0, n) pt.pb(pt[i]);
    int ans = 0;
    rep (i, 1, n + 1) {
        point u = pt[i] - pt[i - 1], v = pt[i + 1] - pt[i];
        if (u.y < 0 && v.y > 0) {
            if ((u ^ v) > 0) ans++;
        } else if (u.y < 0 && v.y == 0) {
            int ptr = i + 1;
            while ((pt[ptr + 1] - pt[ptr]).y == 0) ptr++;
            if ((pt[ptr + 1] - pt[ptr]).y > 0 && pt[ptr].x > pt[i].x) ans++; 
            i = ptr;
        }
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