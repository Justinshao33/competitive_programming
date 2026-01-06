#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define int long long

using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
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
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    auto check = [&](pii no) -> bool {
        vector<int> ind(n, 0);
        rep (i, 0, n) {
            for (int v : adj[i]) {
                if (make_pair(i, v) == no) continue;
                ind[v]++;
            }
        }
        queue<int> q;
        rep (i, 0, n) if (!ind[i]) q.push(i);
        int cnt = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cnt++;
            for (int v : adj[u]) {
                if (make_pair(u, v) == no) continue;
                ind[v]--;
                if (!ind[v]) q.push(v);
            }
        }
        return cnt == n;
    };
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
    }
    vector<bool> inst(n, 0);
    vector<int> cyc, vis(n, 0);
    stack<int> st;
    auto dfs = [&](auto self, int u) -> void {
        if (!cyc.empty()) return;
        st.push(u);
        inst[u] = true;
        vis[u] = 1;
        for (int v : adj[u]) {
            if (!cyc.empty()) return;
            if (vis[v]) {
                if (!inst[v]) continue;
                cyc.push_back(v);
                while (st.top() != v) {
                    cyc.push_back(st.top());
                    inst[st.top()] = false;
                    st.pop();
                }
                st.pop();
                inst[v] = false;
                cyc.push_back(v);
                return;
            }
            self(self, v);
        }
        if (inst[u]) {
            st.pop();
            inst[u] = false;
        }
    };
    rep (i, 0, n) if (!vis[i]) dfs(dfs, i);
    // cout << cyc;
    if (cyc.empty()) cout << "YES\n";
    else {
        reverse(all(cyc));
        assert(ssize(cyc) <= n + 1);
        rep (i, 0, ssize(cyc) - 1) {
            if (check(make_pair(cyc[i], cyc[i + 1]))) {
                cout << "YES\n";
                return;
            }
        }
        cout << "NO\n";
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}