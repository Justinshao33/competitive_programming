// #ifdef LOCAL
// #define _GLIBCXX_DEBUG 1
// #endif
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
    int n, m, a, b; cin >> n >> m >> a >> b;
    n--;
    vector<pii> seg;
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        if (!seg.empty() && seg.back().se == a - 1) seg.back().se = b;
        else seg.push_back({a, b});
    }
    for (const auto &[l, r] : seg) {
        if (r - l + 1 >= b) {
            cout << "No\n";
            return;
        }
    }
    if (a == b) {
        bool f = n % b == 0;
        for (auto [l, r] : seg) {
            int np = (l + b - 1) / b * b;
            if (l <= np && np <= r) f = 0;
        }
        cout << (f ? "Yes\n" : "No\n");
        return;
    }
    // use B-1, B => B*(B-1) <= x are all reachable
    int bdd = b * (b - 1);
    vector<bool> ok(bdd, 0);
    ok[0] = 1;
    rep (i, 1, bdd) rep (j, a, b + 1) if (i - j >= 0 && ok[i - j]) ok[i] = 1;
    vector<bool> pre(b);
    pre[0] = 1;
    int la = 0;
    set<int> vis{0};
    for (const auto &[l, r] : seg) {
        vector<bool> ssuf(b);
        for (int i = l - b; i < l; i++) {
            if (i < la) continue;
            bool f = 0;
            rep (j, a, b + 1) if (vis.count(i - j)) f = 1;
            rep (j, 0, b) if (la + j <= i && pre[j]) {
                if (i - (la + j) >= bdd) f = 1;
                else if (ok[i - (la + j)]) f = 1;
            }
            if (!f) continue;
            vis.insert(i);
            rep (j, a, b + 1) if (i + j > r) {
                ssuf[i + j - r - 1] = 1;
                vis.insert(i + j);
            }
        }
        swap(pre, ssuf);
        la = r + 1;
    }
    rep (i, a, b + 1) if (vis.count(n - i)) {
        cout << "Yes\n";
        return;
    }
    rep (i, 0, b) if (pre[i]) {
        if (la + i > n) break;
        if (n - (la + i) >= bdd || ok[n - (la + i)]) {
            cout << "Yes\n";
            return;
        }        
    }
    cout << "No\n";
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}