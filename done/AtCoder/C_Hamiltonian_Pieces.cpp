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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int R, B; cin >> R >> B; // n: R, m: B
    // 2R1B or
    // R % 2 == 0 or
    // B % 2 == 0.
    if (R == 1 && B == 1) {
        cout << "No\n";
        return;
    }
    if (R == 0 && B % 2 == 1) {
        cout << "No\n";
        return;
    }
    if (B == 0 && R % 2 == 1) {
        cout << "No\n";
        return;
    }
    vector<array<int, 3>> pt;
    if (R % 2 == 0 && B % 2 == 0) {
        int x = 0, y = 0;
        if (R) pt.pb({0, 0, 0});
        x = 0, y = 1;
        vector<array<int, 3>> pt2;
        while (B > 0) {
            pt.pb({x, y, 1});
            pt2.pb({x + 1, y - 1, 1});
            x++, y++;
            B -= 2;
        }
        reverse(all(pt2));
        for (auto p : pt2) pt.pb(p);
        x = 0, y = -1;
        pt2.clear();
        while (R > 0) {
            pt.pb({x, y, 0});
            if (x != 0) pt2.pb({x, y + 1, 0});
            x--;
            R -= 2;
        }
        reverse(all(pt2));
        for (auto p : pt2) pt.pb(p);
    } else if (R % 2 == 0 && B % 2 == 1) {
        int x = 0, y = 0;
        if (R) pt.pb({0, 0, 0});
        x = 0, y = 1;
        vector<array<int, 3>> pt2;
        B--;
        while (B > 0) {
            pt.pb({x, y, 1});
            pt2.pb({x + 1, y - 1, 1});
            x++, y++;
            B -= 2;
        }
        reverse(all(pt2));
        for (auto p : pt2) pt.pb(p);
        x = 0, y = -1;
        pt2.clear();
        while (R > 0) {
            pt.pb({x, y, 0});
            if (x != 0) pt2.pb({x, y + 1, 0});
            x--;
            R -= 2;
        }
        pt.pb({x, y, 1});
        reverse(all(pt2));
        for (auto p : pt2) pt.pb(p);
    } else if (R % 2 == 1 && B % 2 == 0) {
        cout << "No\n";
        return;
    } else {
        cout << "No\n";
        return;
    }
    vector g(20, vector<char>(20, '.'));
    cout << "Yes\n";
    for (auto [x, y, t] : pt) cout << (t == 0 ? 'R' : 'B') << ' ' << x + 100000000 << ' ' << y + 100000000 << '\n';
    // for (auto [x, y, t] : pt) {
    //     if (t == 0) g[x + 10][y + 10] = 'R';
    //     else g[x + 10][y + 10] = 'B';
    // }
    // rep (i, 0, 20) {
    //     rep (j, 0, 20) cout << g[i][j];
    //     cout << '\n';
    // }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}