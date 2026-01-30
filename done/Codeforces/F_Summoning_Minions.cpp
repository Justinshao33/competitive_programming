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

template<class T>
struct KM {
    vector<T> lx, ly;
    vector<int> mx, my, pa;
    T work(const vector<vector<T>> &w) {
        const T INF = numeric_limits<T>::max() / 2;
        const int n = w.size();
        lx.resize(n), ly.resize(n);
        mx.resize(n, -1), my.resize(n, -1), pa.resize(n);
        auto augment = [&](int y) {
            for (int x, z; y != -1; y = z) {
                x = pa[y];
                z = mx[x];
                my[y] = x;
                mx[x] = y;
            }
        };
        auto bfs = [&](int s) {
            vector<T> sy(n, INF);
            vector<bool> vx(n), vy(n);
            queue<int> q;
            q.push(s);
            while (true) {
                while (q.size()) {
                    int x = q.front();
                    q.pop();
                    vx[x] = 1;
                    for (int y = 0; y < n; y++) {
                        if (vy[y]) continue;
                        T d = lx[x] + ly[y] - w[x][y];
                        if (d == 0) {
                            pa[y] = x;
                            if (my[y] == -1) {
                                augment(y);
                                return;
                            }
                            vy[y] = 1;
                            q.push(my[y]);
                        } else if (chmin(sy[y], d)) {
                            pa[y] = x;
                        }
                    }
                }
                T cut = INF;
                for (int y = 0; y < n; y++)
                    if (!vy[y])
                        chmin(cut, sy[y]);
                for (int j = 0; j < n; j++) {
                    if (vx[j]) lx[j] -= cut;
                    if (vy[j]) ly[j] += cut;
                    else sy[j] -= cut;
                }
                for (int y = 0; y < n; y++)
                    if (!vy[y] and sy[y] == 0) {
                        if (my[y] == -1) {
                            augment(y);
                            return;
                        }
                        vy[y] = 1;
                        q.push(my[y]);
                    }
            }
        };
        for (int x = 0; x < n; x++)
            lx[x] = ranges::max(w[x]);
        for (int x = 0; x < n; x++)
            bfs(x);
        T ans = 0;
        for (int x = 0; x < n; x++)
            ans += w[x][mx[x]];
        return ans;
    }
};

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    rep (i, 0, n) cin >> a[i] >> b[i];
    vector w(n, vector<int>(n, 0));
    rep (i, 0, n) rep (j, 0, n) {
        if (j < k - 1 || j == n - 1) w[i][j] = a[i] + b[i] * min(j, k - 1);
        else w[i][j] = b[i] * (k - 1);
    }
    KM<int> f;
    f.work(w);
    cout << k - 1 + (n - k) * 2 + 1 << '\n';
    rep (i, 0, n) {
        if (i < k - 1 || i == n - 1) cout << f.my[i] + 1 << ' ';
        else cout << f.my[i] + 1 << ' ' << -(f.my[i] + 1) << ' ';
    }    
    cout << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}