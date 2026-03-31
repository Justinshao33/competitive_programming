#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
    int n, m, k; cin >> n >> m >> k;
    vector<vector<pii>> adj(n);
    rep (i, 0, m) {
        int a, b, w; cin >> a >> b >> w;
        a--, b--;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }
    vector<int> basis(30, 0);
    auto insert = [&](int x) -> void {
        for (int i = 29; i >= 0; --i) if (x >> i & 1) {
            if (basis[i]) {
                x ^= basis[i];
            } else {
                basis[i] = x;
                break;
            }
        }
    };
    vector<int> dis(n), vis(n);
    auto dfs = [&](auto self, int u, int pa) -> void {
        vis[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (v == pa) continue;
            if (vis[v]) {
                insert(dis[u] ^ dis[v] ^ w);
            } else {
                dis[v] = dis[u] ^ w;
                self(self, v, u);
            }
        }
    };
    dfs(dfs, 0, -1);
    rep (i, 0, n) {
        for (int j = 29; j >= 0; --j) if (basis[j] && (dis[i] >> j & 1)) {
            dis[i] ^= basis[j];
        }
    }
    int id = 0;
    vector trie(1, vector<int>(2));
    vector<int> w(1);
    auto newnode = [&]() -> int {
        id++;
        trie.push_back(vector<int>(2, 0));
        w.push_back(0);
        return id;
    };
    auto ins = [&](int x) -> void {
        int cur = 0;
        for (int i = 29; i >= 0; --i) {
            int b = x >> i & 1;
            if (!trie[cur][b]) trie[cur][b] = newnode();
            cur = trie[cur][b];
            w[cur]++;
        }        
    };
    auto que = [&](int x) -> int {
        int res = 0, cur = 0;
        for (int i = 29; i >= 0; --i) {
            int b = x >> i & 1, b2 = k >> i & 1;
            if (b2) {
                res += w[trie[cur][b]];
                cur = trie[cur][b ^ 1];
            } else {
                cur = trie[cur][b];
            }
            if (cur == 0) break;
        }
        res += w[cur];
        return res;
    };
    int ans = 0;
    rep (i, 0, n) {
        ans += que(dis[i]);
        ins(dis[i]);
    }
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}