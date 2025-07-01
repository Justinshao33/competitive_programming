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

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
#define PU(x) vi[p3++] = x

const int BUF_SIZE = 1 << 16;
static char buf[BUF_SIZE], vi[10], *p1 = buf, *p2 = buf;
static int p3;
inline int in() {int re = 0; char c = GU; while (c == ' ' || c == '\n') {c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return re;}
inline void out(int x) {char str[10]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];} write(1, vi, p3);}

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

int dx[6] = {1, -1, 0, 0, 0, 0}, dy[6] = {0, 0, 1, -1, 0, 0}, dz[6] = {0, 0, 0, 0, 1, -1};

struct info {
    int a, b, c, x, y, z, id;
};

void solve() {
    int f = in(), m = in(), n = in();
    vector dis(f, vector<vector<int>>(m, vector<int>(n, IINF)));
    int R = in();
    queue<tuple<int, int, int>> q;
    rep (i, 0, R) {
        int x = in(), y = in(), z = in();
        x--, y--, z--;
        dis[x][y][z] = 0;
        q.push({x, y, z});
    }
    int mx = 0;
    while (!q.empty()) {
        auto [x, y, z] = q.front();
        q.pop();
        rep (i, 0, 6) {
            int nx = x + dx[i], ny = y + dy[i], nz = z + dz[i];
            if (nx < 0 || nx >= f || ny < 0 || ny >= m || nz < 0 || nz >= n) continue;
            if (chmin(dis[nx][ny][nz], dis[x][y][z] + 1)) {
                q.push({nx, ny, nz});
                chmax(mx, dis[nx][ny][nz]);
            }
        }
    }
    int Q = in();
    vector<int> ans(Q);
    vector<info> que;
    rep (i, 0, Q) {
        int a = in(), b = in(), c = in(), x = in(), y = in(), z = in();
        a--, b--, c--, x--, y--, z--;
        if (a == x && b == y && c == z) {
            ans[i] = dis[a][b][c];
        } else {
            que.pb({a, b, c, x, y, z, i});
        }
    }
    vector<vector<tuple<int, int, int>>> pt(mx + 1);
    rep (i, 0, f) rep (j, 0, m) rep (k, 0, n) {
        pt[dis[i][j][k]].pb({i, j, k});
    }
    int tot = f * m * n;
    UnionFind dsu(tot);
    vector<bool> vis(tot, 0);
    auto solve = [&](auto self, int l, int r, int ql, int qr) -> void {
        if (ql > qr || l > r) return;
        if (l == r) {
            rep (i, ql, qr + 1) ans[que[i].id] = l;
            return;
        }
        int mid = l + r + 1 >> 1;
        vector<info> q1, q2;
        rep (i, mid, mx + 1) {
            for (auto [x, y, z] : pt[i]) {
                int cur = x * n * m + y * n + z;
                vis[cur] = 1;
                rep (j, 0, 6) {
                    int nx = x + dx[j], ny = y + dy[j], nz = z + dz[j];
                    if (nx < 0 || nx >= f || ny < 0 || ny >= m || nz < 0 || nz >= n) continue;
                    int nxt = nx * m * n + ny * n + nz;
                    if (vis[nxt]) {
                        dsu.Union(cur, nxt);
                    }
                }
            }
        }
        rep (i, ql, qr + 1) {
            auto [a, b, c, x, y, z, id] = que[i];
            if (dsu.same(a * m * n + b * n + c, x * m * n + y * n + z)) {
                q2.pb(que[i]);
            } else {
                q1.pb(que[i]);
            }
        }
        rep (i, mid, mx + 1) {
            for (auto [x, y, z] : pt[i]) {
                int cur = x * n * m + y * n + z;
                dsu.sz[cur] = -1;
                vis[cur] = 0;
            }
        }
        int sz = q1.size();
        rep (i, 0, sz) que[ql + i] = q1[i];
        rep (i, 0, q2.size()) que[ql + sz + i] = q2[i];
        self(self, l, mid - 1, ql, ql + sz - 1);
        self(self, mid, r, ql + sz, qr);
    };
    solve(solve, 0, mx, 0, que.size() - 1);
    rep (i, 0, Q) cout << ans[i] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}