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

template <int mod>
struct ModInt {
    int val;
    int trim(int x) const { return x >= mod ? x - mod : x < 0 ? x + mod : x; }
    ModInt(int v = 0) : val(trim(v % mod)) {}
    ModInt(ll v) : val(trim(v % mod)) {}
    ModInt &operator = (int v) { return val = trim(v % mod), *this; };
    ModInt &operator = (const ModInt &oth) = default;
    ModInt operator + (const ModInt &oth) const { return trim(val + oth.val); }
    ModInt operator - (const ModInt &oth) const { return trim(val - oth.val); }
    ModInt operator * (const ModInt &oth) const { return 1LL * val * oth.val % mod; }
    ModInt operator / (const ModInt &oth) const {
        function<int(int, int, int, int)> modinv = [&](int a, int b, int x, int y) {
            if (b == 0) return trim(x);
            return modinv(b, a - a / b * b, y, x  - a / b * y);
        };
        return *this * modinv(oth.val, mod, 1, 0);
    }
    bool operator == (const ModInt &oth) { return val == oth.val; }
    bool operator != (const ModInt &oth) { return val != oth.val; }
    bool operator >= (const ModInt &oth) { return val >= oth.val; }
    bool operator <= (const ModInt &oth) { return val <= oth.val; }
    bool operator > (const ModInt &oth) { return val > oth.val; }
    bool operator < (const ModInt &oth) { return val < oth.val; }
    ModInt operator -() const { return trim(mod - val); }
    template<typename T> ModInt fpow(T e) {
        bool sign = false;
        if (e < 0) e = -e, sign = true;
        ModInt res = 1;
        for (ModInt cur = val; e; e >>= 1, cur = cur * cur) if (e & 1) {
            res = res * cur;
        }
        return sign ? ModInt{1} / res : res;
    }
};

using mint = ModInt<MOD>;

// need ModInt
// mod = 998244353
template<typename M = mint>
void NTT(vector<M> &P, M w, bool inv = 0) {
    int n = P.size(), lg = __builtin_ctz(n);
    assert(__builtin_popcount(n) == 1);

    for (int j = 1, i = 0; j < n - 1; ++j) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) swap(P[i], P[j]);
    }

    vector<M> ws = {inv ? M{1} / w : w};

    rep (i, 1, lg) ws.pb(ws[i - 1] * ws[i - 1]);
    reverse(all(ws));

    rep (i, 0, lg) {
        for (int k = 0; k < n; k += 2 << i) {
            M base = M{1};
            rep (j, k, k + (1 << i)) {
                auto t = base * P[j + (1 << i)];
                auto u = P[j];
                P[j] = u + t;
                P[j + (1 << i)] = u - t;
                base = base * ws[i];
            }
        }
    }

    if (inv) rep (i, 0, n) P[i] = P[i] / M(n);
}

const int N = 1 << 20;
const auto w = mint(3).fpow(952);

void solve() {
    int n, m; cin >> n >> m;
    vector<mint> a(N), b(N), c(N);
    rep (i, 0, n) cin >> a[i].val;
    rep (i, 0, m) cin >> b[i].val;
    NTT(a, w, 0);
    NTT(b, w, 0);
    rep (i, 0, N) c[i] = a[i] * b[i];
    NTT(c, w, 1);
    rep (i, 0, n + m - 1) cout << c[i].val << ' ';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}