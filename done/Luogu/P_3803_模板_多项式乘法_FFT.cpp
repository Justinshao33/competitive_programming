// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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

template<typename C = complex<double>>
void FFT(vector<C> &P, C w, bool inv = 0) {
    int n = P.size(), lg = __builtin_ctz(n);
    assert(__builtin_popcount(n) == 1);

    for (int j = 1, i = 0; j < n - 1; ++j) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) swap(P[i], P[j]);
    }

    vector<C> ws = {inv ? C{1} / w : w};

    rep (i, 1, lg) ws.pb(ws[i - 1] * ws[i - 1]);
    reverse(all(ws));

    rep (i, 0, lg) {
        for (int k = 0; k < n; k += 2 << i) {
            C base = C{1};
            rep (j, k, k + (1 << i)) {
                auto t = base * P[j + (1 << i)];
                auto u = P[j];
                P[j] = u + t;
                P[j + (1 << i)] = u - t;
                base = base * ws[i];
            }
        }
    }

    if (inv) rep (i, 0, n) P[i] = P[i] / C(n);
}

const int N = 1 << 21;
const double PI = acos(-1);
const auto w = exp(-complex<double>(0, 2.0 * PI / N));

void solve() {
    int n, m; cin >> n >> m;
    vector<complex<double>> F(N), G(N), R(N);
    rep (i, 0, n + 1) cin >> F[i];
    rep (i, 0, m + 1) cin >> G[i];
    FFT(F, w, false);
    FFT(G, w, false);
    rep (i, 0, N) R[i] = F[i] * G[i];
    FFT(R, w, true);
    rep (i, 0, n + m + 1) cout << (int)(R[i].real() + 0.5) << " \n" [i == n + m];
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}