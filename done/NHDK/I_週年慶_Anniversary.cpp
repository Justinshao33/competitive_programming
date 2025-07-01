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
#define ld long double
#define F first
#define S second

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
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct info {
    int v; ll d, e;
};

void solve() {
    int bruh; cin >> bruh;
    int n, m, s, t; ll D; cin >> n >> m >> D >> s >> t;
    s--, t--;
    vector<vector<info>> adj(n);
    rep (i, 0, m) {
        int u, v; ll d, e;
        cin >> u >> v >> d >> e;
        u--, v--;
        adj[u].pb({v, d, e});
        adj[v].pb({u, d, e});
    }
    if(s == t) {
        cout << 0 << '\n';
        return;
    }
    vector<ll> dis(n, LINF);
    int l = 0, r = IINF;
    bool f = 0;
    while (r - l > 1) {
        int mid = l + r >> 1;
        fill(all(dis), LINF);
        dis[s] = 0;
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push({dis[s], s});
        while (!pq.empty()) {
            auto [_, u] = pq.top();
            pq.pop();
            for (auto [v, d, e] : adj[u]) {
                if (e > mid) continue;
                if (chmin(dis[v], dis[u] + d)) {
                    pq.push({dis[v], v});
                }
            }
        }
        if (dis[t] <= D) {
            f = 1;
            r = mid;
        }
        else l = mid;
    }
    if (!f) r = -1;
    cout << r << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}