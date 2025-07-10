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

template<class T> inline constexpr T inf = numeric_limits<T>::max() / 2; 

template<class T>
tuple<T, vector<T>, vector<T>> KM(const vector<vector<T>> &w) {
    const int n = w.size();
    vector<T> lx(n), ly(n);
    vector<int> mx(n, -1), my(n, -1), pa(n);
    auto augment = [&](int y) {
        for (int x, z; y != -1; y = z) {
            x = pa[y];
            z = mx[x];
            my[y] = x;
            mx[x] = y;
        }
    };
    auto bfs = [&](int s) {
        vector<T> sy(n, inf<T>);
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
            T cut = inf<T>;
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
    return {ans, lx, ly};
}

void solve() {
    int n; cin >> n;
    vector a(n, vector<ll>(n));
    rep (i, 0, n) rep (j, 0, n) cin >> a[i][j];
    auto [ans, lx, ly] = KM<ll>(a); 
    cout << ans << '\n';
    rep (i, 0, n) cout << lx[i] << " \n" [i == n - 1];
    rep (i, 0, n) cout << ly[i] << " \n" [i == n - 1];
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}