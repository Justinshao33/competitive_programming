#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

// #define int long long

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

vector<array<int, 3>> tree[MAXN << 2];
int pa[MAXN], sz[MAXN], we[MAXN], basis[30];
vector<pii> st;

void init(int n) {
    rep (i, 0, n) {
        pa[i] = i;
        sz[i] = 1;
    }
}

void mod(int pos, int l, int r, int ml, int mr, array<int, 3> x) {
    if (ml <= l && mr >= r) {
        tree[pos].push_back(x);
        return;
    }
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr, x);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, x);
}
 
int find(int x) {
    while (pa[x] != x) x = pa[x];
    return x;
}

int get_val(int x) {
    int res = 0;
    while (pa[x] != x) {
        res ^= we[x];
        x = pa[x];
    }
    return res;
} 

bool Union(int a, int b, int w) {
    int ra = find(a), rb = find(b);
    if (ra == rb) return false;
    if (sz[ra] < sz[rb]) swap(ra, rb);
    we[rb] = w ^ get_val(a) ^ get_val(b);
    sz[ra] += sz[rb], pa[rb] = ra;
    st.pb({ra, rb});
    return true;
}
 
bool same(int a, int b) {
    return find(a) == find(b);
}
 
void undo() {
    auto [a, b] = st.back();
    st.pop_back();
    pa[b] = b;
    sz[a] -= sz[b];
    we[b] = 0;
}
 
void dfs(int pos, int l, int r) {
    int cnt = 0;
    vector<int> ub;
    int qx = -1, qy = -1;
    for (const auto &[x, y, w] : tree[pos]) {
        if (w == -1) {
            qx = x, qy = y;
            continue;
        }
        if (!Union(x, y, w)) {
            int v = w ^ get_val(x) ^ get_val(y);
            for (int i = 29; i >= 0; --i) if (v >> i & 1) {
                if (!basis[i]) {
                    basis[i] = v;
                    ub.push_back(i);
                    break;
                }
                v ^= basis[i];
            }
        } else {
            cnt++;
        }
    }
    if (l == r) {
        if (qx != -1) {
            int ans = get_val(qx) ^ get_val(qy);
            for (int i = 29; i >= 0; --i) if (ans >> i & 1) {
                ans ^= basis[i];
            }
            cout << ans << '\n';
        }
    } else {
        int mid = l + r >> 1;
        dfs(lpos, l, mid);
        dfs(rpos, mid + 1, r);
    }
    rep (i, 0, cnt) undo();
    for (int i : ub) basis[i] = 0;
}

void solve() {
    int n, m; cin >> n >> m;
    init(n);
    map<pair<int, int>, pair<int, int>> mp;
    rep (i, 0, m) {
        int a, b, w; cin >> a >> b >> w;
        a--, b--;
        mp[{a, b}] = {w, 0};
    }
    int q; cin >> q;
    rep (i, 0, q) {
        int t, x, y; cin >> t >> x >> y;
        x--, y--;
        if (t == 1) {
            int w; cin >> w;
            mp[{x, y}] = {w, i};
        } else if (t == 2) {
            mod(1, 0, q - 1, mp[{x, y}].second, i, {x, y, mp[{x, y}].first});
            mp.erase({x, y});
        } else {
            mod(1, 0, q - 1, i, i, {x, y, -1});
        }
    }
    for (const auto &[k, v] : mp) {
        mod(1, 0, q - 1, v.second, q - 1, {k.first, k.second, v.first});
    }
    dfs(1, 0, q - 1);
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}