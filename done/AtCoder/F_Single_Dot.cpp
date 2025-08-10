#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

void solve() {
    int n, m; cin >> n >> m;
    vector<int> dicx(1, 0), dicy(1, 0);
    vector<array<int, 3>> ns, ew;
    rep (i, 0, n) {
        int a, b, c; cin >> a >> b >> c;
        ns.pb({a, b, c});
        dicx.pb(a);
        dicx.pb(b);
        dicy.pb(c);
    }
    rep (i, 0, m) {
        int d, e, f; cin >> d >> e >> f;
        ew.pb({d, e, f});
        dicx.pb(d);
        dicy.pb(e);
        dicy.pb(f);
    }
    sort(all(dicx));
    dicx.erase(unique(all(dicx)), dicx.end());
    sort(all(dicy));
    dicy.erase(unique(all(dicy)), dicy.end());
    int h = ssize(dicx), w = ssize(dicy);
    auto get = [&](vector<int> &v, int id) -> int {
        return lower_bound(all(v), id) - v.begin();
    };
    vector blh(h, vector<int>(w, 0));
    auto blw = blh;
    for (auto &[x1, x2, y] : ns) {
        x1 = get(dicx, x1);
        x2 = get(dicx, x2);
        y = get(dicy, y);
        rep (i, x1, x2) blh[i][y] = 1;
    }
    for (auto &[x, y1, y2] : ew) {
        x = get(dicx, x);
        y1 = get(dicy, y1);
        y2 = get(dicy, y2);
        rep (j, y1, y2) blw[x][j] = 1;
    }
    queue<pii> q;
    q.push({get(dicx, 0), get(dicy, 0)});
    vector vis(h, vector<bool>(w, 0));
    vis[q.front().fi][q.front().se] = 1;
    ll ans = 0;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (x + 1 < h && y + 1 < w)
            ans += 1LL * (dicx[x + 1] - dicx[x]) * (dicy[y + 1] - dicy[y]);
        rep (k, 0, 4) {
            if (k == 1 && blw[x][y]) continue;
            if (k == 3 && blh[x][y]) continue;
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w) {
                cout << "INF\n";
                return;
            }
            if (vis[nx][ny]) continue;
            if (k == 0 && blw[nx][ny]) continue;
            if (k == 2 && blh[nx][ny]) continue;
            q.push({nx, ny});
            vis[nx][ny] = 1;
        }
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