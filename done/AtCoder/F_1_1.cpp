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

ll CEIL(pii p) {
    auto [a, b] = p;
    return (a >= 0 ? (a + b - 1) / b : a / b);
}

ll FLOOR(pii p) {
    auto [a, b] = p;
    return (a >= 0 ? a / b : (a - b + 1) / b);
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    rep (i, 0, n) {
        cin >> a[i];
        a[i] -= i;
    }
    vector<pii> st;
    __int128_t ans = 0;
    rep (i, 0, n) {
        pii cur = {a[i], 1};
        while (!st.empty() && CEIL(st.back()) > FLOOR(cur)) {
            cur = cur + st.back();
            st.pop_back();
        }
        st.push_back(cur);
    }
    int ptr = 0;
    for (auto [s, c] : st) {
        // s / c, s / c, ... , s / c + 1, s / c + 1
        int md = (s % c + c) % c;
        vector<int> b;
        rep (i, 0, c - md) b.push_back(FLOOR({s, c}));
        rep (i, 0, md) b.push_back(CEIL({s, c}));
        rep (i, 0, c) {
            ans += a[ptr] * (n - ptr);
            ans -= b[i] * (n - ptr);
            ptr++;
        }
    }
    cout << (int)ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}