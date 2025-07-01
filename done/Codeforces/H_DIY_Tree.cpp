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

struct UnionFind {
    vector<int> sz;
    UnionFind(int n) : sz(n, -1) {}

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

void solve() {
    int n, k; cin >> n >> k;
    vector<int> ori_d(n, IINF);
    rep (i, 0, k) cin >> ori_d[i];
    vector<array<int, 3>> edge, kedge;
    rep (i, 0, n) rep (j, i + 1, n) {
        int w; cin >> w;
        if (i < k && j < k) kedge.pb({i, j, w});
        else edge.pb({i, j, w});
    }
    {
        sort(all(edge), [&](auto a, auto b) {
            return a[2] < b[2];
        });
        vector<array<int, 3>> mst;
        UnionFind dsu(n);
        for (auto [u, v, w] : edge) {
            if ((u >= k && v >= k && dsu.Union(u, v)) || (u < k && v >= k)) {
                mst.pb({u, v, w});
            }
        }
        swap(mst, edge);
    }
    int m = edge.size(), m2 = kedge.size(), ans = IINF;
    rep (bit, 0, 1 << m2) {
        int res = 0;
        auto kd = ori_d;
        UnionFind ktree(n);
        {   // 檢查有沒有把前k個點搞成一個度數符合的森林
            if (__builtin_popcount(bit) >= k) continue;
            bool f = 0;
            rep (i, 0, m2) if (bit >> i & 1) {
                auto &[a, b, w] = kedge[i];
                if (ktree.Union(a, b)) {
                    kd[a]--, kd[b]--;
                    res += w;
                } else {
                    f = 1;
                }
            }
            rep (i, 0, k) if (kd[i] < 0) f = 1;
            if (f) continue;
        }
        // 熱血擬陣交時間
        /*
        M1 = graph matroid, M2 = color matroid
        y<-s if I+y   satisfies M1
        y->t if I+y   satisfies M2
        x<-y if I-x+y satisfies M2
        x->y if I-x+y satisfies M1
        交換圖點權w
        -w[e] if e \in I
         w[e] otherwise
        */
        vector<int> I(m, 0);
        while (true) {
            vector<vector<int>> adj(m + 2);
            int s = m, t = s + 1;
            auto M1 = [&]() -> void { // graph matroid
                {   // y<-s
                    auto tree = ktree;
                    rep (i, 0, m) if (I[i]) tree.Union(edge[i][0], edge[i][1]);
                    rep (i, 0, m) if (!I[i]) {
                        if (!tree.same(edge[i][0], edge[i][1])) adj[s].pb(i);
                    }
                }
                {   // x->y
                    rep (i, 0, m) if (I[i]) {
                        auto tree = ktree;
                        rep (j, 0, m) if (I[j]) if (j != i) tree.Union(edge[j][0], edge[j][1]);
                        rep (j, 0, m) if (!I[j]) {
                            if (!tree.same(edge[j][0], edge[j][1])) adj[i].pb(j);
                        }
                    }
                }
            };
            auto M2 = [&]() -> void { // color matroid
                {   // y->t
                    auto d = kd;
                    rep (i, 0, m) if (I[i]) d[edge[i][0]]--, d[edge[i][1]]--;
                    rep (i, 0, m) if (!I[i]) {
                        if (d[edge[i][0]] > 0 && d[edge[i][1]] > 0) adj[i].pb(t);
                    }
                }
                {   // x<-y
                    rep (i, 0, m) if (I[i]) {
                        auto d = kd;
                        rep (j, 0, m) if (I[j]) if (j != i) d[edge[j][0]]--, d[edge[j][1]]--;
                        rep (j, 0, m) if (!I[j]) {
                            if (d[edge[j][0]] > 0 && d[edge[j][1]] > 0) adj[j].pb(i);
                        }
                    }
                }
            };
            auto augment = [&]() -> bool { // min weight
                vector<int> vis(m + 2, 0), dis(m + 2, IINF), from(m + 2, -1);
                queue<int> q;
                vis[s] = 1;
                dis[s] = 0;
                q.push(s);
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    vis[u] = 0;
                    for (int v : adj[u]) {
                        int w = (v == t ? 0 : (I[v] ? -edge[v][2] : edge[v][2]));
                        if (chmin(dis[v], dis[u] + w)) {
                            from[v] = u;
                            if (!vis[v]) {
                                vis[v] = 1;
                                q.push(v);
                            }
                        }
                    }
                }
                if (from[t] == -1) return false;
                for (int cur = from[t];; cur = from[cur]) {
                    if (cur == -1 || cur == s) break;
                    I[cur] ^= 1;
                }
                return true;
            };
            M1(), M2();
            if (!augment()) break;
        }
        int cnt = __builtin_popcount(bit);
        rep (i, 0, m) if (I[i]) {
            res += edge[i][2];
            cnt++;
        }
        if (cnt == n - 1) chmin(ans, res);
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}