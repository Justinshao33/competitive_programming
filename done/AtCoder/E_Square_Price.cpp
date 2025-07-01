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

void read(__int128 &x) {
    x = 0;
    int f = 1;
    char ch;
    if((ch = getchar()) == '-') f = -f;
    else x = x * 10 + ch - '0';
    while((ch = getchar()) >= '0' && ch <= '9')
        x = x * 10 + ch - '0';
    x *= f;
}

void print(__int128 x) {
    if (x < 0) {
        x = -x;
        putchar('-');
    }
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

void solve() {
    int n; ll m; cin >> n >> m;
    vector<ll> p(n);
    rep (i, 0, n) cin >> p[i];
    ll l = 0, r = m + 1;
    auto check = [&](ll x) -> pair<ll, ll> {
        __int128 sum = 0;
        ll cnt = 0;
        rep (i, 0, n) {
            // (2k - 1) * p[i] <= x
            ll k = (x / p[i] + 1) / 2;
            cnt += k;
            sum += __int128(k) * k * p[i];
            if (sum > m) return {m + 1, cnt};
        }
        return {sum, cnt};
    };
    while (r - l > 1) {
        ll mid = l + r >> 1;
        auto [ch, _] = check(mid);
        if (ch <= m) l = mid;
        else r = mid;
    }
    auto [sum, ans] = check(l);
    rep (i, 0, n) {
        ll k = (l / p[i] + 1) / 2 + 1;
        if ((2 * k - 1) * p[i] == l + 1 && sum + l + 1 <= m) {
            ans++;
            sum += l + 1;
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