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

void solve() {
    int n, K; cin >> n >> K;
    vector<int> a(n), to(n);
    rep (i, 0, n) cin >> a[i];
    auto build = [&]() -> void {
        vector<int> st;
        fill(all(to), n);
        rep (i, 0, n) {
            while (!st.empty() && a[st.back()] > a[i]) {
                to[st.back()] = i;
                st.pop_back();
            }
            st.push_back(i);
        }
    };
    vector<int> ans(n, n + 1);
    auto calc = [&](int k, int fr) -> vector<int> {
        // cout << a << to;
        // cout << k << ' ' << fr << '\n';
        vector<int> res;
        for (int i = 0; i < n; i++) {
            int sub = max<int>(0, to[i] - i - max<int>(0, fr - i));
            while (sub <= k) {
                // cout << i << ' ' << to[i] << ' ';
                // cout << k << ' ' << k - max<int>(0, to[i] - i - max<int>(0, fr - i)) << '\n';
                k -= sub;
                i = to[i];
                if (i >= n) break;
                sub = max<int>(0, to[i] - i - max<int>(0, fr - i));
            }
            res.push_back(i < n ? a[i] : 0);
        }
        while (ssize(res) < n) res.push_back(0);
        return res;
    };
    {
        build();
        int k = K;
        ans = min(ans, calc(k, 0));
    }
    {
        int mn = n + 1, rot = n;
        rep (i, 0, K) {
            if (chmin(mn, a[n - 1 - i])) rot = i + 1;
        }
        int k = K - rot;
        rotate(a.begin(), a.begin() + n - rot, a.end());
        build();
        ans = min(ans, calc(k, rot % n));
    }
    rep (i, 0, n) if (ans[i] != 0) cout << ans[i] << ' ';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}