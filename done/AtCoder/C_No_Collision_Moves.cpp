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
    vector<int> s(n), t(n);
    rep (i, 0, n) {
        cin >> s[i] >> t[i];
    }
    vector<int> p(n), p2(n);
    iota(all(p), 0);
    sort(all(p), [&](int x, int y) {
        return s[x] < s[y];
    });
    iota(all(p2), 0);
    sort(all(p2), [&](int x, int y) {
        return t[x] < t[y];
    });
    if (p != p2) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    set<int> pos;
    rep (i, 0, n) { 
        pos.insert(s[i]);
    }
    queue<int> q;
    vector<bool> ok(n, 0);
    rep (k, 0, n) {
        int i = p[k];
        auto it = pos.find(s[i]);
        if (t[i] > s[i]) {
            if (next(it) == pos.end() || *next(it) > t[i]) {
                q.push(k);
                ok[k] = 1;
            }
        } else {
            if (it == pos.begin() || *prev(it) < t[i]) {
                q.push(k);
                ok[k] = 1;
            }
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        int i = p[u];
        pos.erase(s[i]);
        cout << i + 1 << ' ';
        if (u && !ok[u - 1]) {
            int j = p[u - 1];
            auto it = pos.find(s[j]);
            if (t[j] > s[j]) {
                if (next(it) == pos.end() || *next(it) > t[j]) {
                    q.push(u - 1);
                    ok[u - 1] = 1;
                }
            } else {
                if (it == pos.begin() || *prev(it) < t[j]) {
                    q.push(u - 1);
                    ok[u - 1] = 1;
                }
            }
        }
        if (u + 1 < n && !ok[u + 1]) {
            int j = p[u + 1];
            auto it = pos.find(s[j]);
            if (t[j] > s[j]) {
                if (next(it) == pos.end() || *next(it) > t[j]) {
                    q.push(u + 1);
                    ok[u + 1] = 1;
                }
            } else {
                if (it == pos.begin() || *prev(it) < t[j]) {
                    q.push(u + 1);
                    ok[u + 1] = 1;
                }
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