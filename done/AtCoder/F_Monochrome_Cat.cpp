#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
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
    int n; cin >> n;
    vector<vector<int>> preG(n);
    vector<pii> edge;
    vector<int> ind(n, 0);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        edge.pb({a, b});
        preG[a].pb(b);
        preG[b].pb(a);
        ind[a]++;
        ind[b]++;
    }
    vector<int> col(n);
    rep (i, 0, n) {
        char c; cin >> c;
        col[i] = c == 'B';
    }
    if (accumulate(all(col), 0) == n) {
        cout << 0 << '\n';
        return;
    }
    if (accumulate(all(col), 0) == n - 1) {
        cout << 1 << '\n';
        return;
    }
    queue<int> q;
    vector<bool> no(n, 0);
    rep (i, 0, n) if (col[i] && ind[i] == 1) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        no[u] = 1;
        for (int v : preG[u]) if (col[v] && ind[v] != 1) {
            ind[v]--;
            if (ind[v] == 1) q.push(v);
        }
    }
    vector<int> dic;
    rep (i, 0, n) if (!no[i]) dic.pb(i);
    n = dic.size();
    vector<vector<int>> adj(n);
    vector<int> c(n);
    rep (i, 0, n) c[i] = col[dic[i]];
    for (auto [a, b] : edge) {
        if (no[a] || no[b]) continue;
        a = lower_bound(all(dic), a) - dic.begin();
        b = lower_bound(all(dic), b) - dic.begin();
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int tot = 2 * (n - 1);
    // ope2 -> black ^ (deg & 1 ^ 1)
    vector<int> w(n, 0);
    rep (i, 0, n) w[i] = (c[i] ^ (adj[i].size() & 1 ^ 1));
    tot += accumulate(all(w), 0);
    int sub = 0;
    // ans = tot - sub
    // define st and ed where the cat start and end    
    // sub = #(edge in path) + #(w[i] = 1) - (#w[i] = 0) [excluding ed] 
    // => #edge - #(w[i] == 0) = #(w[i] = 1)
    // => sub = 2 * #(w[i] = 1)
    vector<int> dp(n, 0);
    auto dfs = [&](auto self, int u, int pa) -> void {
        dp[u] = w[u] * 2;
        int mx = 0, smx = 0;
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u);
            if (dp[v] > mx) {
                smx = mx;
                mx = dp[v];
            } else if (dp[v] > smx) {
                smx = dp[v];
            }
        }
        chmax(sub, dp[u] + mx + smx);
        dp[u] += mx;
    };
    dfs(dfs, 0, -1);
    chmax(sub, *max_element(all(dp)));
    cout << tot - sub << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}