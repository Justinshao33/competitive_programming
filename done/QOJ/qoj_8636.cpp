// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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

void solve() {
    int n; cin >> n;
    vector l(2, vector<int>(n, -1)), r(2, vector<int>(n, -1)), p(2, vector<int>(n, -1));
    rep (t, 0, 2) rep (i, 0, n - 1) {
        int x, y, c; cin >> x >> y >> c;
        x--, y--;
        if (c) r[t][x] = y;
        else l[t][x] = y;
        p[t][y] = x;
    }
    auto splay = [&](int t, int x) -> void {
        int P = p[t][x], L = l[t][x];
        p[t][L] = P;
        if (P != -1) r[t][P] = L;
        l[t][x] = r[t][L];
        if (r[t][L] != -1) p[t][r[t][L]] = x;
        r[t][L] = x;
        p[t][x] = L;
    };
    vector<vector<int>> ope(2);
    vector<int> cur(2);
    rep (t, 0, 2) {
        rep (i, 0, n) if (p[t][i] == -1) {
            cur[t] = i;
            break;
        }
        while (r[t][cur[t]] != -1) cur[t] = r[t][cur[t]];
        while (cur[t] != -1) {
            while (l[t][cur[t]] != -1) {
                if (t == 0) ope[t].pb(cur[t]);
                else ope[t].pb(l[t][cur[t]]);
                splay(t, cur[t]);
            }
            cur[t] = p[t][cur[t]];
        }
    }
    vector<vector<int>> a(2);
    rep (t, 0, 2) {
        // rep (i, 0, n) cout << r[t][i] << " \n" [i == n - 1];
        rep (i, 0, n) if (p[t][i] == -1) {
            cur[t] = i;
            break;
        }
        while (cur[t] != -1) {
            a[t].pb(cur[t]);
            cur[t] = r[t][cur[t]];
        }
    }
    if (a[0] != a[1]) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        cout << ope[0].size() + ope[1].size() << '\n';
        for (int x : ope[0]) cout << x + 1 << ' ' << 1 << '\n';
        reverse(all(ope[1]));
        for (int x : ope[1]) cout << x + 1 << ' ' << 0 << '\n';
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