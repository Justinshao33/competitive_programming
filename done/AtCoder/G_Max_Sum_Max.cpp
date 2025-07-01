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
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct FenwickTree{
    vector<ll> BIT, cnt;
    int n;
    FenwickTree(int n) : BIT(n + 1, 0), cnt(n + 1, 0), n(n) {}

    void add(int x, ll val) {
        while(x <= n){
            BIT[x] += val;
            cnt[x]++;
            x += x & -x;
        }
    }

    void del(int x, ll val) {
        while(x <= n){
            BIT[x] -= val;
            cnt[x]--;
            x += x & -x;
        }
    }

    ll query(int x) {
        ll res = 0;
        while (x) {
            res += BIT[x];
            x -= x & -x;
        }
        return res;
    }

    ll kth(int k) {
        int x = 0;
        ll cur = 0, sum = 0;
        for (int i = 1 << __lg(n); i > 0; i >>= 1) {
            if (x + i <= n && cur + cnt[x + i] <= k) {
                x += i;
                cur += cnt[x];
                sum += BIT[x];
            }
        }
        return sum;
    }
};

void solve() {
    int n; cin >> n;
    vector<pll> info(n);
    for (auto &[a, b] : info) cin >> a >> b;
    sort(all(info), [](pll a, pll b) {
        return a.S < b.S;
    });
    vector<int> p(n), id(n);
    iota(all(p), 0);
    sort(all(p), [&](int a, int b) {
        return info[a].F > info[b].F;
    });
    rep (i, 0, n) id[p[i]] = i + 1;
    vector<ll> ans(n + 1, -LINF);
    int ptr = 0;
    FenwickTree bit(n);
    auto calc = [&](int i, int k) -> ll {
        while (ptr < i) {
            bit.add(id[ptr], info[ptr].F);
            ptr++;
        }
        while (ptr > i) {
            ptr--;
            bit.del(id[ptr], info[ptr].F);
        }
        return bit.kth(k);
    };
    auto dc = [&](auto self, int l, int r, int ql, int qr) -> void {
        if (l > r) return;
        if (ql == qr) {
            rep (i, l, r + 1) ans[i] = calc(ql, i) + info[ql].F - info[ql].S;
            return;
        }
        int mid = l + r >> 1, opt = max(ql, mid);
        rep (i, max(mid, ql), qr + 1) {
            ll res = calc(i, mid) + info[i].F - info[i].S;
            if (chmax(ans[mid], res)) {
                opt = i;
            }
        }
        self(self, l, mid - 1, ql, opt);
        self(self, mid + 1, r, opt, qr);
    };
    dc(dc, 0, n - 1, 0, n - 1);
    rep (i, 0, n) cout << ans[i] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}