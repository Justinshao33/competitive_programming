#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0)
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define debug(x) cerr << #x << " = " << x << '\n';
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

pii operator + (const pii &p1, const pii &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pii operator - (const pii &p1, const pii &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }

template<class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

#define lpos pos << 1
#define rpos pos << 1 | 1
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename A> ostream& operator << (ostream &os, const vector<A> &p) { for(const auto &a : p) os << a << " "; os << '\n'; return os; }
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 400;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    rep (i, 0, n) {
        cin >> a[i];
        a[i]--;
    }
    int q; cin >> q;
    vector<array<int, 3>> que(q);
    rep (i, 0, q) {
        int l, r; cin >> l >> r;
        l--;
        que[i] = {l, r, i};
    }
    sort(all(que), [&](auto a, auto b) {
        if (a[0] / B != b[0] / B) return a[0] < b[0];
        return (a[0] / B) & 1 ? a[1] < b[1] : a[1] > b[1];
    });
    vector<ll> ans(q);
    vector<int> cnt(n, 0);
    ll tmp = 0;
    auto add = [&](int x) -> void {
        tmp -= cnt[x] / 2;
        cnt[x]++;
        tmp += cnt[x] / 2;
    };
    auto sub = [&](int x) -> void {
        tmp -= cnt[x] / 2;
        cnt[x]--;
        tmp += cnt[x] / 2;
    };
    int L = 0, R = 0;
    for (auto [l, r, i] : que) {
        while (R < r) add(a[R++]);
        while (L > l) add(a[--L]);
        while (R > r) sub(a[--R]);
        while (L < l) sub(a[L++]);
        ans[i] = tmp;
    }
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