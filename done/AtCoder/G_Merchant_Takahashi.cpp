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
#define ld long double
#define F first
#define S second

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
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

ll tree[MAXN << 2][2];

void mod(int pos, int l, int r, int idx, ll val, int t) {
    if (l == r) {
        chmax(tree[pos][t], val);
        return;
    }
    int mid = l + r >> 1;
    if (idx <= mid) mod(lpos, l, mid, idx, val, t);
    else mod(rpos, mid + 1, r, idx, val, t);
    tree[pos][t] = max(tree[lpos][t], tree[rpos][t]);
}

ll query(int pos, int l, int r, int ql, int qr, int t) {
    if (l == ql && r == qr) {
        return tree[pos][t];
    }
    int mid = l + r >> 1;
    if (qr <= mid) return query(lpos, l, mid, ql, qr, t);
    else if (ql > mid) return query(rpos, mid + 1, r, ql, qr, t);
    else return max(query(lpos, l, mid, ql, mid, t), query(rpos, mid + 1, r, mid + 1, qr, t));
}

void solve() {
    int n; ll c; cin >> n >> c;
    int m; cin >> m;
    vector<ll> t(m + 1), p(m + 1);
    rep (i, 1, m + 1) {
        cin >> t[i] >> p[i];
    }
    vector<ll> dp(m + 1);
    // dp[i] = max(dp[j] - c * |t[i] - t[j]| + p[i])
    // t[i] >= t[j] dp[i] = max(dp[j] + c * t[j]) + p[i] - c * t[i]
    // t[i] < t[j] dp[i] = max(dp[j] - c * t[j]) + p[i] + c * t[i];
    memset(tree, -LINF, sizeof(tree));
    dp[0] = 0;
    mod(1, 1, n, 1, dp[0] + c, 0);
    mod(1, 1, n, 1, dp[0] - c, 1);  
    rep (i, 1, m + 1) {
        // cerr << t[i] << '\n';
        dp[i] = query(1, 1, n, 1, t[i], 0) + p[i] - c * t[i];
        if (t[i] != n) dp[i] = max(dp[i], query(1, 1, n, t[i] + 1, n, 1) + p[i] + c * t[i]);
        mod(1, 1, n, t[i], dp[i] + c * t[i], 0);
        mod(1, 1, n, t[i], dp[i] - c * t[i], 1);
    }
    cout << *max_element(all(dp)) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}