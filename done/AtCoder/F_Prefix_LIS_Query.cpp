#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
 
const int MAXN = 1e6 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

template <typename T>
struct FenwickTree{
    vector<T> BIT;
    FenwickTree(int n) : BIT(n + 1, 0) {}

    void mod(int x, T val) {
        while(x < BIT.size()){
            chmax(BIT[x], val);
            x += x & -x;
        }
    }

    T query(int x) {
        T res = 0;
        while (x > 0) {
            chmax(res, BIT[x]);
            x -= x & -x;
        }
        return res;
    }

    T query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    rep (i, 0, n) cin >> a[i];
    vector<pii> b(n);
    rep (i, 0, n) {
        b[i] = {a[i], -i};
    }
    sort(all(b));
    // auto dic = a;
    // sort(all(dic));
    // dic.erase(unique(all(dic)), dic.end());
    vector<array<int, 3>> que;
    rep (i, 0, q) {
        int r, x; cin >> r >> x;
        r--;
        que.pb({x, r, i});
    }
    sort(all(que));
    // int m = dic.size();
    FenwickTree<int> bit(n + 1);
    vector<int> ans(q);
    int ptr = 0;
    for (auto [x, r, id] : que) {
        while (ptr < n && b[ptr].fi <= x) {
            int pre = bit.query(-b[ptr].se);
            bit.mod(-b[ptr].se + 1, pre + 1);
            ptr++;
        }
        ans[id] = bit.query(r + 1);
    }
    // vector<int> lis;
    // rep (i, 0, n) {
    //     auto it = lower_bound(all(lis), a[i]);
    //     if (it == lis.end()) lis.pb(a[i]);
    //     else *it = a[i];
    //     // cout << lis;
    //     int p = lower_bound(all(dic), a[i]) - dic.begin() + 1;
    //     bit.mod(p, lis.size());
    //     for (auto [x, id] : que[i]) {
    //         int pp = lower_bound(all(dic), x) - dic.begin() + 1;
    //         ans[id] = bit.query(pp);
    //     }
    // }
    rep (i, 0, q) cout << ans[i] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}