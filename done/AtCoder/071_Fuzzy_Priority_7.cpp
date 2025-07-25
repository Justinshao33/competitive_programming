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
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> adj(n);
    vector<int> ind(n, 0);
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        ind[b]++;
    }
    vector<int> st, P;
    rep (i, 0, n) if (!ind[i]) st.pb(i);
    vector<vector<int>> ans;
    auto dfs = [&](auto self, vector<int>& q, vector<int>& p) -> bool {
        if (p.size() == n) {
            ans.pb(p);
            return true;
        }
        if (q.empty()) return false;
        // cout << "hehe\n";
        int sz = q.size();
        rep (i, 0, sz) {
            // cout << q.size() << '\n';
            if (ans.size() == k) break;
            int u = q[i];
            q.erase(q.begin() + i);
            p.pb(u);
            for (int v : adj[u]) {
                ind[v]--;
                if (!ind[v]) q.pb(v);
            }
            if(!self(self, q, p)) return false; 
            for (int v : adj[u]) {
                if (!ind[v]) q.pop_back();
                ind[v]++;
            }
            q.insert(q.begin() + i, u);
            p.pop_back();
        }
        return true;
    };
    dfs(dfs, st, P);
    // cout << ans.size() << '\n';
    if (ans.size() < k) cout << -1 << '\n';
    else {
        rep (i, 0, k) rep (j, 0, n) {
            cout << ans[i][j] + 1 << " \n" [j == n - 1];
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