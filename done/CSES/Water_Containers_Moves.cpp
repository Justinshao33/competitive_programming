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

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int A, B, C; cin >> A >> B >> C;
    if (C > A || C % gcd(A, B) != 0) {
        cout << "-1\n";
        return;
    }
    int sz = (A + 1) * (B + 1);
    vector<vector<array<int, 3>>> adj(sz);
    auto enc = [&](int x, int y) -> int {
        return x * (B + 1) + y;
    };
    rep (i, 0, A + 1) rep (j, 0, B + 1) {
        adj[enc(i, j)].push_back({enc(A, j), A - i, 0});
        adj[enc(i, j)].push_back({enc(i, B), B - j, 1});
        adj[enc(i, j)].push_back({enc(0, j), i, 2});
        adj[enc(i, j)].push_back({enc(i, 0), j, 3});
        adj[enc(i, j)].push_back({enc(i - min(i, B - j), min(B, j + i)), min(i, B - j), 4});
        adj[enc(i, j)].push_back({enc(min(A, i + j), j - min(j, A - i)), min(j, A - i), 5});
    }
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> dis(sz, IINF);
    dis[enc(0, 0)] = 0;
    pq.push({dis[enc(0, 0)], enc(0, 0)});
    vector<pii> from(sz, {-1, -1});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        for (auto [v, w, t] : adj[u]) {
            if (chmin(dis[v], dis[u] + w)) {
                pq.push({dis[v], v});
                from[v] = {u, t};
            }
        }
    }
    int mn = IINF, cur;
    rep (i, 0, B + 1) {
        if (chmin(mn, dis[enc(C, i)])) {
            cur = enc(C, i);
        }
    }
    vector<int> ope;
    while (from[cur].fi != -1) {
        ope.push_back(from[cur].se);
        cur = from[cur].fi;
    }
    reverse(all(ope));
    vector<string> s{"FILL A", "FILL B", "EMPTY A", "EMPTY B", "MOVE A B", "MOVE B A"};
    cout << ssize(ope) << ' ' << mn << '\n';
    for (int x : ope) {
        cout << s[x] << '\n';
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