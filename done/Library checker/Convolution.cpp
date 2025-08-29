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

inline int add(int a, int b) {
    a += b;
    return a >= MOD ? a - MOD : a;
} 

inline int sub(int a, int b) {
    return a >= b ? a - b : a + MOD - b;
}

inline int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

struct ntt {
    vector<int> ws;
    ntt(int N) : ws(N) {
        int wb = fpow(3, (MOD - 1) / N, MOD);
        ws[0] = 1;
        rep (i, 1, N) ws[i] = mul(ws[i - 1], wb);
    }
    void operator()(vector<int> &P, bool inv = 0) {
        int n = P.size(), lg = __builtin_ctz(n);
        assert(__builtin_popcount(n) == 1);
        for (int j = 1, i = 0; j < n - 1; ++j) {
            for (int k = n >> 1; k > (i ^= k); k >>= 1); // !!!
            if (j < i) swap(P[i], P[j]);
        }
        for (int L = 2; L <= n; L <<= 1) {
            int dx = n / L, dl = L >> 1;
            for (int k = 0; k < n; k += L) {
                for (int j = k, x = 0; j < k + dl; j++, x += dx) {
                    int t = mul(ws[x], P[j + dl]);
                    P[j + dl] = sub(P[j], t);
                    P[j] = add(P[j], t);
                }
            }
        }
        if (inv) {
            reverse(1 + all(P));
            int invn = fpow(n, MOD - 2, MOD);
            rep (i, 0, n) P[i] = mul(P[i], invn);
        }
    }
};
const int N = 1 << 20;
ntt NTT(N);

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(N), b(N);
    rep (i, 0, n) cin >> a[i];
    rep (i, 0, m) cin >> b[i];
    NTT(a, 0);
    NTT(b, 0);
    rep (i, 0, N) a[i] = mul(a[i], b[i]);
    NTT(a, 1);
    rep (i, 0, n + m - 1) cout << a[i] << " \n" [i == n + m - 2];
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}