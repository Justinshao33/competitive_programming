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
        while(x < BIT.size()){
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

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n), da, db, ab(n), ba(n), ida(n), idb(n);
    rep (i, 0, n) cin >> a[i], da.pb(a[i]);
    rep (i, 0, n) cin >> b[i], db.pb(b[i]);
    da.pb(-1), db.pb(-1);
    sort(all(da));    
    sort(all(db));
    da.erase(unique(all(da)), da.end());
    db.erase(unique(all(db)), db.end());
    rep (i, 0, n) {
        ab[i] = lower_bound(all(db), a[i]) - db.begin() - 1;
        ba[i] = lower_bound(all(da), b[i]) - da.begin() - 1;
        ida[i] = lower_bound(all(da), a[i]) - da.begin();
        idb[i] = lower_bound(all(db), b[i]) - db.begin();
    }
    // cout << ab << ba << ida << idb;
    int q; cin >> q;
    vector<array<int, 3>> que(q);
    rep (i, 0, q) {
        auto &[l, r, id] = que[i];
        cin >> l >> r;
        // l--, r--;
        id = i;
    }
    sort(all(que), [&](auto x, auto y) {
        if (x[0] / B != y[0] / B) return x[0] < y[0];
        return (x[0] / B) & 1 ? x[1] < y[1] : x[1] > y[1];
    });
    FenwickTree va(n), ca(n), vb(n), cb(n);
    ll sum = 0;
    auto add = [&](int x, int t) -> void {
        if (t == 0) {
            va.mod(ida[x], a[x]);
            ca.mod(ida[x], 1);
            ll cnt = cb.query(ab[x]), val = vb.query(ab[x]);
            sum += a[x] * cnt - val + (vb.query(n) - val) - a[x] * (cb.query(n) - cnt);
        } else {
            vb.mod(idb[x], b[x]);
            cb.mod(idb[x], 1);
            ll cnt = ca.query(ba[x]), val = va.query(ba[x]);
            sum += b[x] * cnt - val + (va.query(n) - val) - b[x] * (ca.query(n) - cnt);
        }
    };
    auto sub = [&](int x, int t) -> void {
        if (t == 0) {
            va.mod(ida[x], -a[x]);
            ca.mod(ida[x], -1);
            ll cnt = cb.query(ab[x]), val = vb.query(ab[x]);
            sum -= a[x] * cnt - val + (vb.query(n) - val) - a[x] * (cb.query(n) - cnt);
        } else {
            vb.mod(idb[x], -b[x]);
            cb.mod(idb[x], -1);
            ll cnt = ca.query(ba[x]), val = va.query(ba[x]);
            sum -= b[x] * cnt - val + (va.query(n) - val) - b[x] * (ca.query(n) - cnt);
        }
    };
    int L = 0, R = 0;
    vector<ll> ans(q);
    for (auto [l, r, id] : que) {
        while (R < r) add(R++, 1);  
        while (L < l) add(L++, 0);
        // cout << L << ' ' << R << '\n';
        while (R > r) sub(--R, 1);
        while (L > l) sub(--L, 0);
        ans[id] = sum;
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