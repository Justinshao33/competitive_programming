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
    int n, m; cin >> n >> m;
    vector<int> a(n), b(n);
    rep (i, 0, n) cin >> a[i] >> b[i];
    vector<pii> mac;
    rep (i, 0, m) {
        int x, y; cin >> x >> y;
        x--, y--;
        if (x == y) {
            if (a[x] < b[x]) swap(a[x], b[x]);
        } else {
            mac.push_back({x, y});
        }
    }
    vector<int> A, B, id(n);
    rep (i, 0, n) {
        if (a[i] >= b[i]) {
            A.push_back(i);
            id[i] = ssize(A);
        } else {
            B.push_back(i);
            id[i] = -ssize(B);
        }
    }
    int sa = ssize(A), sb = ssize(B);
    int ans = accumulate(all(a), 0LL);
    int fli = 0;
    vector<int> ok(sa);
    for (auto [x, y] : mac) {
        if (id[x] < id[y]) swap(x, y);
        if (id[x] > 0 && id[y] > 0) continue;
        else if (id[x] < 0 && id[y] < 0) {
            fli |= (1LL << (-id[x] - 1)) | (1LL << (-id[y] - 1));
        } else {
            ok[id[x] - 1] |= 1LL << (-id[y] - 1);
        }
    }
    if (sa <= sb) {
        rep (bit, 0, 1 << sa) {
            int cur = fli, res = 0;
            rep (i, 0, sa) if (bit >> i & 1) cur |= ok[i];
            rep (i, 0, sa) {
                if (bit >> i & 1) res += a[A[i]] + b[A[i]];
                else res += 2 * a[A[i]];
            }
            rep (i, 0, sb) {
                if (cur >> i & 1) res += a[B[i]] + b[B[i]];
                else res += 2 * a[B[i]];
            }
            chmax(ans, res);
        }
    } else {
        vector<int> sum(1 << sb);
        rep (bit, 0, 1 << sb) {
            rep (i, 0, sb) if (bit >> i & 1) {
                sum[bit] += a[B[i]] + b[B[i]];
            }
        }
        vector<int> dp(1 << sb, -LINF);
        dp[fli] = sum[fli];
        rep (i, 0, sa) {
            vector<int> g(1 << sb, -LINF);
            rep (bit, 0, 1 << sb) {
                if (dp[bit] == -LINF) continue;
                chmax(g[bit], dp[bit] + 2 * a[A[i]]);
                chmax(g[bit | ok[i]], dp[bit] + a[A[i]] + b[A[i]] + sum[(bit ^ ok[i]) & ok[i]]);
            }
            swap(dp, g);
        }
        rep (bit, 0, 1 << sb) {
            if (dp[bit] == -LINF) continue;
            int res = 0;
            rep (i, 0, sb) if (bit >> i & 1 ^ 1) res += 2 * a[B[i]];
            chmax(ans, dp[bit] + res);
        }
    }
    cout << ans / 2;
    if (ans & 1) cout << ".5\n";
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}