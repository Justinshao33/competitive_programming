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

ll tree[MAXN << 2], tag[MAXN << 2];

void push(int pos) {
    if (tag[pos]) {
        tree[lpos] += tag[pos];
        tag[lpos] += tag[pos];
        tree[rpos] += tag[pos];
        tag[rpos] += tag[pos];
        tag[pos] = 0;
    }
}

void mod(int pos, int l, int r, int ml, int mr, ll val) {
    if (l >= ml && mr >= r) {
        tree[pos] += val;
        tag[pos] += val;
        return;
    }
    push(pos);
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr, val);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, val);
    tree[pos] = max(tree[lpos], tree[rpos]);
}

ll query(int pos, int l, int r, int ql, int qr) {
    if (ql > qr) return 0;
    if (l >= ql && qr >= r) return tree[pos];
    push(pos);
    int mid = l + r >> 1;
    ll res = -LINF;
    if (ql <= mid) res = max(res, query(lpos, l, mid, ql, qr));
    if (qr > mid) res = max(res, query(rpos, mid + 1, r, ql, qr));
    return res;
}

void solve() {
    int n, m; cin >> n >> m;
    mod(1, 0, n + 1, 1, n + 1, -LINF);
    vector<vector<pll>> pos(n + 3);
    rep (i, 0, m) {
        int l, r, a; cin >> l >> r >> a;
        pos[l].pb({l - 1, a});
        pos[r + 1].pb({l - 1, -a});
    }
    vector<ll> dp(n + 1, 0);
    rep (i, 1, n + 1) {
        for (auto [p, v] : pos[i]) mod(1, 0, n + 1, 0, p, v);
        dp[i] = query(1, 0, n + 1, 0, i - 1);
        ll tmp = query(1, 0, n + 1, i, i);
        mod(1, 0, n + 1, i, i, -tmp);
        mod(1, 0, n + 1, i, i, dp[i]);
    }
    for (auto [p, v] : pos[n + 1]) mod(1, 0, n + 1, 0, p, v);
    cout << tree[1] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}