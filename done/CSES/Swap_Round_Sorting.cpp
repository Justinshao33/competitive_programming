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

void solve() {
    int n; cin >> n;
    vector<int> to(n), p(n);
    rep (i, 0, n) {
        cin >> p[i];
        p[i]--;
        to[i] = p[i];
    }
    vector<bool> vis(n, 0);
    vector<vector<int>> cyc;
    vector<int> sz(n + 1, 0);
    rep (i, 0, n) if (!vis[i]) {
        int cur = i;
        cyc.pb({});
        while (!vis[cur]) {
            vis[cur] = 1;
            cyc.back().pb(cur);
            cur = to[cur];
        }
        sz[cyc.back().size()]++;
    }
    if (sz[1] == n) {
        cout << 0 << '\n';
    } else if (sz[1] + sz[2] * 2 == n) {
        cout << 1 << '\n' << sz[2] << '\n';
        rep (i, 0, n) if (to[i] < i) {
            cout << i + 1 << ' ' << to[i] + 1 << '\n';
        }
    } else {
        cout << 2 << '\n';
        vector<pii> ope, ope2;
        for (auto &c : cyc) {
            // sort(all(c));
            int csz = c.size();
            if (csz > 2) {
                int l = 0, r = csz - 1;
                while (l < r) {
                    ope.pb({c[l] + 1, c[r] + 1});
                    swap(p[c[l]], p[c[r]]);
                    l++, r--;
                }
            }
        }
        rep (i, 0, n) to[i] = p[i];
        rep (i, 0, n) if (to[i] < i) {
            ope2.pb({i + 1, to[i] + 1});
        }
        cout << ope.size() << '\n';
        for (auto [a, b] : ope) cout << a << ' ' << b << '\n';
        cout << ope2.size() << '\n';
        for (auto [a, b] : ope2) cout << a << ' ' << b << '\n';
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