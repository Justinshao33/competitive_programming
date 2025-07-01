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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = __int128(res) * x % mod; x = __int128(x) * x % mod; exp >>= 1;} return res; }

bool Miller_Rabin(ll n) {
    const int lim = 10;
    if (n < 3 || n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    ll d = n - 1, t = 0;
    while (d & 1 ^ 1) d >>= 1, t++;
    rep (i, 0, lim) {
        ll x = rng() % (n - 3) + 2, val = fpow(x, d, n);
        if (val == 1) continue;
        int s = 0;
        while (s < t) {
            if (val == n - 1) break;
            val = __int128(val) * val % n;
            s++;
        }
        if (s == t) return false;
    }    
    return true;
}

ll Pollard_Rho(ll n) {
    ll c = rng() % (n - 1) + 1;
    auto calc = [&](ll x) -> ll {
        return (__int128(x) * x + c) % n;
    };
    ll s = 0, t = 0;
    ll val = 1;
    for (int goal = 1;; goal <<= 1, s = t, val = 1) {
        rep (step, 1, goal + 1) {
            t = calc(t);
            val = __int128(val) * abs(s - t) % n;
            if (val == 0) return n;
            if (step % 127 == 0) {
                ll d = __gcd(val, n);
                if (d > 1) return d;
            }
        }
        ll d = __gcd(val, n);
        if (d > 1) return d;
    }
}

ll mx;

void fac(ll x) {
    if (x < 2 || x <= mx) return;
    if (Miller_Rabin(x)) {
        chmax(mx, x);
        return;
    }
    ll p = x;
    while (p >= x) p = Pollard_Rho(x);
    while (x % p == 0) x /= p;
    fac(x), fac(p);
}

void solve() {
    ll k; cin >> k;
    mx = 0;
    if (Miller_Rabin(k)) {
        cout << "Prime\n";
        return;
    }
    fac(k);
    cout << mx << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}