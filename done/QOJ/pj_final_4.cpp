// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

#ifdef LOCAL
#define ZTMYACANESOCUTE freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

void dbg() { cerr << '\n'; }
template<typename T, typename ...U>
void dbg(T t, U ...u) { cerr << t << ' '; dbg(u...); }

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
 
const int c = 257;
 
int pa[MAXN];
 
int find(int x) {
    return pa[x] == x ? pa[x] : pa[x] = find(pa[x]);
}
 
void solve() {
    int n; cin >> n;
    vector<ll> a(2 * n);
    rep (i, 3, 2 * n) cin >> a[i];
    vector<int> rk(2 * n);
    iota(all(rk), 0);
    sort(rk.begin() + 3, rk.end(), [&](int x, int y) {
        return a[x] < a[y];
    });

    rep (i, 1, n + 1) pa[i] = i;
 
    FenwickTree h(n), h2(n);
    vector<vector<int>> id(n + 1);
    vector<ll> p(n + 1), inv(n + 1);
 
    p[0] = 1;
    rep (i, 1, n + 1) p[i] = p[i - 1] * c % MOD;
    inv[n] = fpow(p[n], MOD - 2, MOD);
    for (int i = n - 1; i >= 0; --i) inv[i] = inv[i + 1] * c % MOD;
 
    rep (i, 1, n + 1) {
        id[i].pb(i);
        h.mod(i, i * p[i] % MOD);
        h2.mod(n - i + 1, i * p[n - i + 1] % MOD);
    }
    
    auto calc = [&](int t, int l, int r) -> ll {
        if (t == 1) return (h.rquery(l, r) + MOD) % MOD * inv[l - 1] % MOD;
        else return (h2.rquery(l, r) + MOD) % MOD * inv[l - 1] % MOD;
    };
    
    auto check = [&](int l, int r) -> bool {
        return calc(1, l, r) == calc(2, n - r + 1, n - l + 1);
    };
 
    auto work = [&](int l, int r) -> int {
        int L = l + r + 1 >> 1, R = r + 1, cnt = 0;
        while (R - L > 1) {
            int mid = L + R >> 1;
            if (check(l + r - mid, mid)) L = mid;
            else R = mid;
        }
        if ((r - l) % 2 && L == (l + r + 1) >> 1 && !check(L - 1, L)) R--;
        for (int LL = l + r - R, RR = R; LL >= l && RR <= r; LL--, RR++) {
            int pl = find(LL), pr = find(RR);
            if (pl == pr) continue;
            cnt++;
            if (id[pl].size() < id[pr].size()) swap(pl, pr);
            while (!id[pr].empty()) {
                int v = id[pr].back();
                id[pr].pop_back();
                h.mod(v, (pl * p[v] % MOD) - (pr * p[v] % MOD));
                h2.mod(n - v + 1, (pl * p[n - v + 1] % MOD) - (pr * p[n - v + 1] % MOD));
                id[pl].pb(v);
                pa[v] = pl;
            }
        }
        return cnt;
    };
    
    ll ans = 0;
    rep (i, 3, 2 * n) {
        int l = 1, r = rk[i] - 1;
        if (r > n) r = n, l = rk[i] - n;
        if (check(l, r)) continue;
        ans += work(l, r) * a[rk[i]];
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}