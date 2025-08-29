#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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

void solve() {
    int n; cin >> n;
    map<string, int> mp;
    vector<string> str;
    int id = 0;
    mp[""] = id++;
    str.push_back("");
    rep (i, 0, 26) {
        mp[string(1, 'a' + i)] = id++;
        str.push_back(string(1, 'a' + i));
    }
    rep (i, 0, 26) rep (j, 0, 26) {
        mp[string(1, 'a' + i) + string(1, 'a' + j)] = id++;
        str.push_back(string(1, 'a' + i) + string(1, 'a' + j));
    }
    map<string, int> val;
    rep (i, 0, n) {
        string s; int p; cin >> s >> p;
        val[s] = p;
    }
    vector<array<ll, 3>> edge;
    for (string &s : str) {
        for (int c = 'a'; c <= 'z'; c++) {
            string t = s + char(c);
            ll w = 0;
            for (int j = 1; j <= ssize(t); j++) {
                w += val[string(t.end() - j, t.end())];
            }
            if (ssize(t) == 3) t.erase(t.begin());
            edge.push_back({mp[s], mp[t], -w});
        }
    }
    vector<ll> dis(ssize(str), LINF);
    dis[0] = 0;
    bool f = 0;
    rep (i, 0, ssize(str)) {
        for (auto &[u, v, w] : edge) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (i == ssize(str) - 1) f = 1;
            }
        }
    }
    if (f) {
        cout << "Infinity\n";
    } else {
        cout << -(*min_element(dis.begin() + 1, dis.end())) << '\n';
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