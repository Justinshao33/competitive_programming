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
    int n, m; cin >> n >> m;
    int A, B, C; cin >> A >> B >> C;
    A--, B--, C--;
    vector<vector<int>> adj(n);
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<vector<int>> bcc;
    vector<int> dfn(n, 0), low(n, 0), st;
    vector<bool> is_ap(n, 0);
    int cnt = 0;
    auto dfs = [&](auto self, int u, int pa) -> void {
        dfn[u] = low[u] = ++cnt;
        st.pb(u);
        for(int v : adj[u]) {
            if(v == pa) continue;
            if(dfn[v]) {
                chmin(low[u], dfn[v]);
            }
            else{
                self(self, v, u);
                chmin(low[u], low[v]);
                if(low[v] >= dfn[u]) {
                    is_ap[u] = (dfn[u] > 1 || dfn[v] > 2);
                    bcc.pb({u});
                    while(bcc.back().back() != v) {
                        bcc.back().pb(st.back());
                        st.pop_back();
                    }
                }
            }
        }
    };
    dfs(dfs, 0, -1);
    vector<vector<int>> BCT(1);
    vector<int> id(n);
    cnt = 0;
    rep(i, 0, n) if(is_ap[i]) {
        id[i] = cnt++;
        BCT.pb({});
    }
    for(auto BCC : bcc) {
        int cur_id = cnt++;
        BCT.pb({});
        for(int u : BCC) {
            if(!is_ap[u]) id[u] = cur_id;
            else {
                BCT[cur_id].pb(id[u]);
                BCT[id[u]].pb(cur_id);
            }
        }
    }
    A = id[A], B = id[B], C = id[C];
    if (A == C) {
        cout << "Yes\n";
        return;
    }
    vector<int> p(cnt);
    auto dfs2 = [&](auto self, int u, int pa) -> void {
        for (int v : BCT[u]) {
            if (v == pa) continue;
            p[v] = u;
            self(self, v, u);
        }
    };
    p[A] = A;
    dfs2(dfs2, A, -1);
    while (p[C] != C) {
        if (C == B) {
            cout << "Yes\n";
            return;
        }
        C = p[C];
    }
    if (C == B) cout << "Yes\n";
    else cout << "No\n";
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}