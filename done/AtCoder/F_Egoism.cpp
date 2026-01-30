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

template<class T>
struct Fenwick {
    int n;
    vector<T> a;
    Fenwick(int _n) : n(_n), a(_n) {}
    void add(int p, T x) {
        for (int i = p; i < n; i = i | (i + 1)) {
            a[i] = a[i] + x;
        }
    }
    T qry(int p) { // sum [0, p]
        T s{};
        for (int i = p; i >= 0; i = (i & (i + 1)) - 1) {
            s = s + a[i];
        }
        return s;
    }
    T qry(int l, int r) { // sum [l, r)
        return qry(r - 1) - qry(l - 1);
    }
    pair<int, T> select(T k) { // [first position >= k, sum [0, p) 
        T s{};
        int p = 0;
        for (int i = 1 << __lg(n); i; i >>= 1) {
            if (p + i <= n and s + a[p + i - 1] < k) {
                p += i;
                s = s + a[p - 1];
            }
        }
        return {p, s};
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n), b(n);
    rep (i, 0, n) cin >> a[i] >> b[i];
    int cnt = 0;
    const int C = 1e6 + 5;
    Fenwick<int> bit(C), bit2(C);
    multiset<int> mst, mst2;
    int sum = 0;
    rep (i, 0, n) {
        bit.add(a[i], 1);
        bit2.add(a[i], a[i]);
        if (b[i] == 2) mst.insert(a[i]);
        else mst2.insert(a[i]);
        cnt += b[i] == 2;
        sum += a[i];
    }
    while (q--) {
        int w, x, y; cin >> w >> x >> y;
        w--;
        cnt -= b[w] == 2;
        sum -= a[w];
        bit.add(a[w], -1);
        bit2.add(a[w], -a[w]);
        if (b[w] == 2) mst.extract(a[w]);
        else mst2.extract(a[w]);
        a[w] = x;
        b[w] = y;
        if (b[w] == 2) mst.insert(a[w]);
        else mst2.insert(a[w]);
        sum += a[w];
        cnt += b[w] == 2;
        bit.add(a[w], 1);
        bit2.add(a[w], a[w]);
        if (cnt == 0) {
            cout << sum << '\n';
            continue;
        }
        if (cnt == n) {
            cout << 2 * sum - *mst.begin() << '\n';
            continue;
        }
        int K = max(1LL, n - cnt);
        auto [p, c] = bit.select(K);
        auto [p2, c2] = bit.select(K + 1);
        if (mst.empty() || mst2.empty() || *mst.begin() <= *mst2.rbegin()) cout << 2 * sum - (bit2.qry(p) - p * (bit.qry(p) - K)) << '\n';
        else cout << 2 * sum - (bit2.qry(p) - p * (bit.qry(p) - K)) - *mst.begin() + *mst2.rbegin() << '\n';
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}