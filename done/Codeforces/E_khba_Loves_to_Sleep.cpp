#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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

void solve() {
    int n, k; cin >> n >> k;
    int x; cin >> x;
    vector<int> a(n);
    rep (i, 0, n) cin >> a[i];
    sort(all(a));
    int l = 0, r = x + 1;
    auto check = [&](int d) -> bool {
        ll res = 0;
        if (a[0] - d + 1 >= 0) res += a[0] - d + 1;
        rep (i, 1, n) {
            if (a[i] - a[i - 1] >= 2 * d) {
                res += (a[i] - d) - (a[i - 1] + d) + 1;
            }
        }
        if (x - (a.back() + d) + 1 >= 0) res += x - (a.back() + d) + 1;
        return res >= k;
    };
    while (r - l > 1) {
        int mid = l + r >> 1;
        if (check(mid)) l = mid;
        else r = mid;
    }
    if (l == 0) {
        rep (i, 0, k) cout << i << ' ';
        cout << '\n';
        return;
    }
    vector<int> ans;
    rep (i, 0, a[0] - l + 1) {
        ans.push_back(i);
        if (ssize(ans) == k) break;
    }
    if (ssize(ans) < k) {
        rep (i, 1, n) {
            if (a[i] - a[i - 1] < 2 * l) continue;
            rep (j, a[i - 1] + l, a[i] - l + 1) {
                ans.push_back(j);
                if (ssize(ans) == k) break;
            }       
            if (ssize(ans) == k) break;
        }
        if (ssize(ans) < k) {
            rep (i, a.back() + l, x + 1) {
                ans.push_back(i);
                if (ssize(ans) == k) break;
            }
        }
    }
    for (int x : ans) cout << x << ' ';
    cout << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}