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
    vector<ll> BIT;
    FenwickTree(int n) : BIT(n + 1, 0) {}

    void mod(int x, ll val) {
        while(x <= BIT.size()){
            BIT[x] += val;
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

    ll rquery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

struct info {
    ll need; int id;
};

void solve() {
    int n, m, q; cin >> n >> m >> q;
    vector<vector<pii>> seg(n);
    vector<int> last(n, 0);
    rep (i, 0, m) {
        int a; cin >> a;
        a--;
        if (last[a] != 0) seg[a].pb({last[a], i});
        last[a] = i + 1;
    }
    rep (i, 0, n) {
        if (last[i] != 0) seg[i].pb({last[i], m + 1});
    }
    vector<info> que;
    rep (i, 0, n) {
        int v; cin >> v;
        que.pb({v, i});
    }
    vector<tuple<int, int, int>> ope(q);
    for (auto &[l, r, c] : ope) cin >> l >> r >> c;
    ope.pb({1, m, 1e9});
    FenwickTree bit(m + 1);
    vector<int> ans(n);
    vector<ll> sum(n, 0);
    auto solve = [&](auto self, int l, int r, int ql, int qr) -> void {
        if (ql > qr || l > r) return;
        if (l == r) {
            rep (i, ql, qr + 1) ans[que[i].id] = l + 1;
            return;
        }
        int mid = l + r >> 1;
        vector<tuple<int, int, int>> li;
        rep (i, l, mid + 1) li.pb({get<0>(ope[i]), 0, i});
        rep (i, ql, qr + 1) {
            sum[que[i].id] = 0;
            for (auto [l, r] : seg[que[i].id]) li.pb({l, r, i});
        }
        sort(all(li));
        for (auto [l, r, i] : li) {
            if (r == 0) {
                bit.mod(get<1>(ope[i]), get<2>(ope[i]));
            } else {
                sum[que[i].id] += bit.rquery(l, r);
            }
        }
        vector<info> q1, q2;
        rep (i, ql, qr + 1) {
            auto &[k, id] = que[i];
            if (sum[id] >= k) q1.pb(que[i]);
            else {
                k -= sum[id];
                q2.pb(que[i]);
            }
        }
        rep (i, l, mid + 1) {
            auto [L, R, c] = ope[i];
            bit.mod(R, -c);
        }
        int sz = q1.size();
        rep (i, 0, sz) que[ql + i] = q1[i];
        rep (i, 0, q2.size()) que[ql + sz + i] = q2[i];
        self(self, l, mid, ql, ql + sz - 1);
        self(self, mid + 1, r, ql + sz, qr);
    };
    solve(solve, 0, q, 0, n - 1);
    rep (i, 0, n) {
        if (ans[i] == q + 1) ans[i] = -1;
        cout << ans[i] << '\n';
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}