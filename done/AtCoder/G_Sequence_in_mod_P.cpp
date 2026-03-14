#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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

int power(int a, int b, int p, int res = 1) {
    for (; b; b /= 2, a = 1LL * a * a % p) {
        if (b & 1) {
            res = 1LL * res * a % p;
        }
    }
    return res;
}

int exbsgs(int a, int b, int p) {
    a %= p;
    b %= p;
    if (b == 1 || p == 1) {
        return 0;
    }
    if (a == 0) {
        return b == 0 ? 1 : -1;
    }

    int g, k = 0, t = 1;  // t : a ^ k / sum{d}
    while ((g = std::gcd(a, p)) > 1) {
        if (b % g) {
            return -1;
        }
        b /= g;
        p /= g;
        k++;
        t = t * (a / g) % p;
        if (t == b) {
            return k;
        }
    }

    const int n = std::sqrt(p) + 1;
    std::unordered_map<int, int> mp;
    mp[b] = 0;

    int x = b, y = t;
    int mi = power(a, n, p);
    for (int i = 1; i < n; i++) {
        x = 1LL * x * a % p;
        mp[x] = i;
    }

    for (int i = 1; i <= n; i++) {
        t = 1LL * t * mi % p;
        if (mp.contains(t)) {
            return 1LL * i * n - mp[t] + k;
        }
    }

    return -1; // no solution
}

void solve() {
    int p, a, b, s, g; cin >> p >> a >> b >> s >> g;
    int x1 = (a * s + b) % p;
    if (s == g) {
        cout << 0 << '\n';
        return;
    }
    if (x1 == g) {
        cout << 1 << '\n';
        return;
    }
    if (a == 0) {
        cout << -1 << '\n';
        return;
    }
    if (a == 1) {
        g = (g - s + p) % p;
        if (b == 0) {
            cout << -1 << '\n';
        } else {
            cout << g * fpow(b, p - 2, p) % p << '\n';
        }
        return;
    }
    if ((b + s * a - s) % p == 0) {
        cout << -1 << '\n';
        return;
    }
    g = (g + b * fpow(a - 1, p - 2, p) % p) % p;
    g = g * (a - 1) % p * fpow((b + s * a - s) % p, p - 2, p) % p;
    cout << exbsgs(a, g, p) << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}