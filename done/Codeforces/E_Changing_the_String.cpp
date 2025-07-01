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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector to(3, vector<set<int>>(3));
    int ptr = 0;
    rep (i, 0, q) {
        char a, b; cin >> a >> b;
        a -= 'a', b -= 'a';
        to[a][b].insert(i);
    }
    rep (i, 0, ssize(s)) {
        if (s[i] == 'a') continue;
        if (s[i] == 'b') {
            auto it = to[1][0].begin();
            if (it != to[1][0].end()) {
                to[1][0].erase(it);
                s[i] = 'a';
                continue;
            }
            it = to[1][2].begin();
            if (it == to[1][2].end()) continue;
            auto it2 = to[2][0].lower_bound(*it);
            if (it2 != to[2][0].end()) {
                to[1][2].erase(it);
                to[2][0].erase(it2);
                s[i] = 'a';
            }
        } else {
            auto it = to[2][0].begin();
            if (it != to[2][0].end()) {
                to[2][0].erase(it);
                s[i] = 'a';
                continue;
            }
            it = to[2][1].begin();
            if (it == to[2][1].end()) continue;
            auto it2 = to[1][0].lower_bound(*it);
            if (it2 != to[1][0].end()) {
                to[2][1].erase(it);
                to[1][0].erase(it2);
                s[i] = 'a';
            } else {
                to[2][1].erase(it);
                s[i] = 'b';
            }
        }
    }
    cout << s << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}