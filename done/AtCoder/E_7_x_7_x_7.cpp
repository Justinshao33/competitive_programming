#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0)
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define debug(x) cerr << #x << " = " << x << '\n';
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

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

struct info {
    vector<int> p;
    info(int x, int y, int z) : p({x, y, z}) {}
};

void solve() {
    vector<int> v(3);
    rep (i, 0, 3) cin >> v[i];
    if (v[0] + v[1] * 2 + v[2] * 3 != 3 * 7 * 7 * 7) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    info c1(0, 0, 0);
    rep (x, -7, 8) rep (y, -7, 8) rep (z, -7, 8) {
        info c2(x, y, z);
        rep (i, -7, 8) rep (j, -7, 8) rep (k, -7, 8) {
            info c3(i, j, k);
            auto calc = [&](info a, info b) -> int {
                int vol = 1;
                rep (i, 0, 3) {
                    int l = max(a.p[i], b.p[i]), r = min(a.p[i] + 6, b.p[i] + 6);
                    if (l > r) return 0;
                    vol *= r - l + 1;
                }
                return vol;
            };
            auto calc2 = [&](info a, info b, info c) -> int {
                int vol = 1;
                rep (i, 0, 3) {
                    int l = max({a.p[i], b.p[i], c.p[i]}), r = min({a.p[i] + 6, b.p[i] + 6, c.p[i] + 6});
                    if (l > r) return 0;
                    vol *= r - l + 1;
                }
                return vol;
            };
            int ch = calc2(c1, c2, c3);
            int a1 = calc(c1, c2);
            int a2 = calc(c1, c3);
            int a3 = calc(c2, c3);
            if (ch == v[2] && a1 + a2 + a3 - v[2] * 3 == v[1]) {
                rep (i, 0, 3) cout << c1.p[i] << ' ';
                rep (i, 0, 3) cout << c2.p[i] << ' ';
                rep (i, 0, 3) cout << c3.p[i] << ' ';
                return;
            }
        }
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