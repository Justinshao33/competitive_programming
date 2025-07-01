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

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pii>> adj(n + 1);
    rep (i, 0, m) {
        int t; cin >> t;
        if (t == 1) {
            int a, b, c; cin >> a >> b >> c;
            // a >= b + c => b <= a - c
            adj[a].pb({b, -c});
        } else if (t == 2) {
            int a, b, c; cin >> a >> b >> c;
            // a <= b + c
            adj[b].pb({a, c});
        } else {
            int a, b; cin >> a >> b;
            adj[a].pb({b, 0});
            adj[b].pb({a, 0});
        }
    }
    rep (i, 1, n + 1) adj[0].pb({i, 0});
    auto SPFA = [&](int st) -> bool {
        vector<bool> vis(n + 1, 0);
        vector<int> dis(n + 1, IINF), cnt(n + 1, 0);
        queue<int> q;
        vis[st] = 0;
        dis[st] = 0;
        q.push(st);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (auto [v, w] : adj[u]) {
                if (chmin(dis[v], dis[u] + w)) {
                    cnt[v]++;
                    if(cnt[v] == n) {
                        return false;
                    }
                    if (!vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return true;
    };
    if(SPFA(0)) cout << "Yes\n";
    else cout << "No\n";
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}