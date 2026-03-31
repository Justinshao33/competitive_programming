#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
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


template<typename T> using RBT = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> cnt(m);
    vector<int> A;
    rep (i, 0, n) {
        int a; cin >> a;
        a--;
        A.push_back(a);
        cnt[a]++;
    }
    int q; cin >> q;
    vector<pii> que(q);
    rep (i, 0, q) {
        cin >> que[i].fi;
        que[i].se = i;
    }
    vector<int> p(m);
    iota(all(p), 0);
    sort(all(p), [&](int x, int y) {
        if (cnt[x] == cnt[y]) return x < y;
        return cnt[x] < cnt[y];
    });
    sort(all(que));
    vector<int> ans(q, 0);
    int sum = 0;
    RBT<int> tr;
    for (int ptr = 0; auto [x, i] : que) {
        if (x <= n) {
            ans[i] = A[x - 1];
            continue;
        }
        x -= n;
        while (ptr < m && cnt[p[ptr]] * ptr - sum < x) {
            sum += cnt[p[ptr]];
            tr.insert(p[ptr]);
            ptr++;
        }
        int rem = x - (cnt[p[ptr - 1]] * ptr - sum); 
        ans[i] = *tr.find_by_order((rem - 1) % ptr);
    }
    rep (i, 0, q) cout << ans[i] + 1 << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}