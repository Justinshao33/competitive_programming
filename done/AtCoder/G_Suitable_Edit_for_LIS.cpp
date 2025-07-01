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
 
const int MAXN = 4e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

int tree[MAXN << 2][2];

void mod(int pos, int l, int r, int idx, int val, int t) {
    if (l == r) {
        tree[pos][t] = max(tree[pos][t], val);
        return;
    }
    int mid = l + r >> 1;
    if (idx <= mid) mod(lpos, l, mid, idx, val, t);
    else mod(rpos, mid + 1, r, idx, val, t);
    tree[pos][t] = max(tree[lpos][t], tree[rpos][t]);
}

int query(int pos, int l, int r, int ql, int qr, int t) {
    if (ql > qr) return 0;
    if (ql <= l && qr >= r) return tree[pos][t];
    int mid = l + r >> 1;
    int res = 0;
    if (ql <= mid) res = max(res, query(lpos, l, mid, ql, qr, t));
    if (qr > mid) res = max(res, query(rpos, mid + 1, r, ql, qr, t));
    return res;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n), dic;
    dic.pb(0);
    rep (i, 0, n) {
        cin >> a[i];
        dic.pb(a[i]);
        dic.pb(a[i] + 1);
    }
    sort(all(dic));
    dic.erase(unique(all(dic)), dic.end());
    int m = dic.size();
    int ch = 0, val = 1;
    rep (i, 0, n) {
        int cur = lower_bound(all(dic), a[i]) - dic.begin() + 1;
        int dp0 = query(1, 1, m, 1, cur - 1, 0),
            dp1 = query(1, 1, m, 1, cur - 1, 1);
        mod(1, 1, m, cur, dp0 + 1, 0);
        mod(1, 1, m, cur, dp1 + 1, 1);
        mod(1, 1, m, ch, val, 1);
        ch = cur + 1, val = dp0 + 2;
    }
    cout << tree[1][1] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}