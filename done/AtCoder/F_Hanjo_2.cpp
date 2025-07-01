#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
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
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct Mat{
    vector<vector<ll>> a;
    int x, y;
    Mat(int _x, int _y){
        a.resize(_x, vector<ll>(_y, 0));
        x = _x;
        y = _y;
    }
    Mat operator * (Mat &inp){
        Mat res(x, inp.y);
        rep(i, 0, x) rep(j, 0, inp.y) rep(k, 0, y){
            res.a[i][j] += a[i][k] * inp.a[k][j] % MOD;
            res.a[i][j] %= MOD;
        }
        return res;
    }
};
 
void powpow(Mat &res, ll exp){
    Mat base = res;
    while (exp) {
        if(exp & 1) res = res * base;
        base = base * base;
        exp >>= 1;
    }
}

void solve() {
    int n; ll m; cin >> n >> m;
    Mat base(1 << n, 1 << n);
    rep (i, 0, 1 << n) {
        auto dfs = [&](auto self, int mask, int idx) -> void {
            if (idx == n) {
                base.a[i][mask]++;
                return;
            }
            if (i >> idx & 1) {
                self(self, mask, idx + 1);
            } else {
                if (idx + 1 < n && (i >> (idx + 1) & 1 ^ 1)) {
                    self(self, mask, idx + 2);
                }
                self(self, mask, idx + 1);
                self(self, mask | 1 << idx, idx + 1);
            }
        };
        dfs(dfs, 0, 0);
    }
    powpow(base, m - 1);
    cout << base.a[0][0] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}