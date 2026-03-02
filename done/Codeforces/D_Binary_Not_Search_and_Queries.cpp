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
    int n, q; cin >> n >> q;
    vector<set<int>> ran(n), len(n), left(n);
    vector<int> cnt(n), sum(n);
    vector<int> a(n);
    multiset<int> mst;
    
    auto get = [&](int v) -> pair<int, int> {
        if (ssize(ran[v]) <= 1) return {-1, -1};
        return {*ran[v].begin(), *ran[v].rbegin() - *ran[v].begin()};
    };
    
    auto C2 = [&](int x) -> int {
        return x * (x + 1) / 2;
    };
    
    auto mv = [&](int w, int L, int R, int v) -> void {
        sum[w] -= C2(cnt[L]);
        sum[w] -= C2(cnt[R]);
        cnt[L] += v;
        cnt[R] -= v;
        sum[w] += C2(cnt[L]);
        sum[w] += C2(cnt[R]);
    };
    
    auto ins = [&](int v) -> void {
        auto [l, w] = get(v);
        if (l < 0) return; 
        left[w].insert(l);
        auto it = len[w].upper_bound(l);
        cnt[l] += 1, sum[w] += 1;
        if (it != len[w].end() && l + 1 == *it) {
            mv(w, l, *it, cnt[*it]);
            len[w].erase(it);
        }
        len[w].insert(l);
        it = len[w].lower_bound(l);
        if (it != len[w].begin()) it = prev(it);
        if (*it < l && left[w].find(l - 1) != left[w].end()) {
            len[w].erase(l);
            mv(w, *it, l, cnt[l]);
        }
        mst.insert(w);
    };
    
    auto era = [&](int v) -> void {
        auto [l, w] = get(v); 
        if (l < 0) return; 
        auto it = prev(len[w].upper_bound(l));
        if (*it != l && left[w].find(l - 1) != left[w].end()) {
            mv(w, l, *it, cnt[*it] - (l - *it));
        }
        if (*it == l) len[w].erase(l);
        sum[w] -= C2(cnt[l]);
        cnt[l]--;
        sum[w] += C2(cnt[l]);
        if (left[w].find(l + 1) != left[w].end()) {
            len[w].insert(l + 1);
            mv(w, l + 1, l, cnt[l]);
        }
        left[w].erase(l);
        mst.extract(w);
    };
    
    auto ope = [&](int i, bool f) -> void {
        era(a[i]);
        if (!f) ran[a[i]].insert(i);
        if (f) ran[a[i]].erase(i);
        ins(a[i]);
    };

    mst.insert(0);
    rep (i, 0, n) cin >> a[i], a[i]--;
    rep (i, 0, n) ope(i, 0);
    while (q--) {
        int i, x; cin >> i >> x;
        i--, x--;
        ope(i, 1);
        a[i] = x;
        ope(i, 0);
        int mx = *mst.rbegin();
        cout << mx << ' ' << sum[mx] << '\n';
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}