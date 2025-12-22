#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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

struct UnionFind {
    vector<int> sz;
    UnionFind(int n) : sz(n, -1) {}

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    rep (i, 0, n) cin >> a[i];
    n++;
    const int C = 18;
    UnionFind dsu(n);
    int ans = 0;
    while (true) {
        vector<pair<pii, pii>> dp(1 << C, {{-1, -1}, {-1, -1}});
        rep (i, 0, n) {
            int cost = a[i];
            if (cost >= dp[a[i]].fi.fi) {
                if (dsu.find(i) != dp[a[i]].fi.se) dp[a[i]].se = dp[a[i]].fi;
                dp[a[i]].fi = {cost, dsu.find(i)};
            } else if (cost > dp[a[i]].se.fi && dsu.find(i) != dp[a[i]].fi.se) {
                dp[a[i]].se = {cost, dsu.find(i)};
            }
        }
        rep (i, 0, C) rep (bit, 0, 1 << C) if (bit >> i & 1) {
            int nxt = bit ^ (1 << i);
            if (dp[nxt].fi.fi >= dp[bit].fi.fi) {
                if (dp[nxt].fi.se != dp[bit].fi.se) {
                    dp[bit].se = dp[bit].fi;
                }
                dp[bit].fi = dp[nxt].fi;
                if (dp[nxt].se.fi > dp[bit].se.fi && dp[bit].se.se != dp[nxt].se.se) {
                    dp[bit].se = dp[nxt].se;
                }
            } else if (dp[nxt].fi.fi > dp[bit].se.fi && dp[nxt].fi.se != dp[bit].fi.se) {
                dp[bit].se = dp[nxt].fi;
            } else if (dp[nxt].se.fi > dp[bit].se.fi && dp[nxt].se.se != dp[bit].fi.se) {
                dp[bit].se = dp[nxt].se;
            }
        }
        vector<pii> to(n, {-1, -1});
        rep (i, 0, n) {
            int msk = (1 << C) - 1 - a[i];
            if (dp[msk].fi.se == -1) continue;
            if (dp[msk].fi.se != dsu.find(i) && dp[msk].fi.se != -1) {
                chmax(to[dsu.find(i)], make_pair(dp[msk].fi.fi + a[i], dp[msk].fi.se));
            } else if (dp[msk].se.se != dsu.find(i) && dp[msk].se.se != -1) {
                chmax(to[dsu.find(i)], make_pair(dp[msk].se.fi + a[i], dp[msk].se.se));
            }
        }
        bool f = 0;
        rep (i, 0, n) if (to[i].fi != -1 && !dsu.same(i, to[i].se)) {
            dsu.Union(i, to[i].se);
            ans += to[i].fi;
            f = 1;
        }
        if (!f) break;
    }
    ans = ans - accumulate(all(a), 0LL);
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}