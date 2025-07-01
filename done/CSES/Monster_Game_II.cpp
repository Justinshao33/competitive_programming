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
 
const int MAXN = 1e6 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct Line {
    ll m, k = LINF;
    ll val (int x) {
        return m * x + k;
    }
};

// min LiChao

struct LiChao {
    
    vector<Line> tree;
    
    LiChao (int n) : tree(n << 2) {};

    void insert (int pos, int l, int r, Line line) {
        if (l == r) {
            if (line.val(l) < tree[pos].val(l)) tree[pos] = line;
            return;
        }
        int mid = (l + r) >> 1;
        if (tree[pos].m < line.m) swap(tree[pos], line);
        if (tree[pos].val(mid) > line.val(mid)) {
            swap(tree[pos], line);
            insert(lpos, l, mid, line);
        } else {
            insert(rpos, mid + 1, r, line);
        }
    }

    ll query (int pos, int l, int r, int x) {
        if (l == r) return tree[pos].val(x);
        int mid = (l + r) >> 1;
        if (x <= mid) return min(query(lpos, l, mid, x), tree[pos].val(x));
        else return min(query(rpos, mid + 1, r, x), tree[pos].val(x));
    }

};

void solve() {
    int n, x; cin >> n >> x;
    vector<int> s(n + 1), f(n + 1);
    rep (i, 1, n + 1) cin >> s[i];
    rep (i, 1, n + 1) cin >> f[i];
    // dp[i] = min(dp[j] + s[i] * f[j])
    // m = f[j], k = dp[j];
    vector<ll> dp(n + 1);
    dp[0] = 0;
    f[0] = x;
    LiChao tree(1e6);
    tree.insert(1, 1, 1e6, (Line){f[0], dp[0]});
    rep (i, 1, n + 1) {
        dp[i] = tree.query(1, 1, 1e6, s[i]);
        tree.insert(1, 1, 1e6, (Line){f[i], dp[i]});
    }
    cout << dp[n] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}