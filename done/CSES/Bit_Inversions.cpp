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

string s;

struct info {
    ll pre, suf, sum, ans;
} tree[MAXN << 2][2];

void pull(int pos) {
    rep (i, 0, 2) {
        tree[pos][i].pre = max(tree[lpos][i].pre, tree[lpos][i].sum + tree[rpos][i].pre);
        tree[pos][i].suf = max(tree[rpos][i].suf, tree[rpos][i].sum + tree[lpos][i].suf);
        tree[pos][i].sum = tree[lpos][i].sum + tree[rpos][i].sum;
        tree[pos][i].ans = max({tree[lpos][i].ans, tree[rpos][i].ans, tree[lpos][i].suf + tree[rpos][i].pre});
    }
}

void build(int pos, int l, int r) {
    if (l == r) {
        if (s[l] == '0') {
            tree[pos][0] = {1, 1, 1, 1};
            tree[pos][1] = {-IINF, -IINF, -IINF, -IINF};
        } else {
            tree[pos][1] = {1, 1, 1, 1};
            tree[pos][0] = {-IINF, -IINF, -IINF, -IINF};
        }
        return;
    }
    int mid = l + r >> 1;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
    pull(pos);
}

void mod(int pos, int l, int r, int idx) {
    if (l == r) {
        if (tree[pos][0].sum == 1) {
            tree[pos][1] = {1, 1, 1, 1};
            tree[pos][0] = {-IINF, -IINF, -IINF, -IINF};
        } else {
            tree[pos][0] = {1, 1, 1, 1};
            tree[pos][1] = {-IINF, -IINF, -IINF, -IINF};
        }
        return;
    }
    int mid = l + r >> 1;
    if (idx <= mid) mod(lpos, l, mid, idx);
    else mod(rpos, mid + 1, r, idx);
    pull(pos);
}

void solve() {
    cin >> s;
    int n = s.size();
    s = '$' + s;
    build(1, 1, n);
    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        mod(1, 1, n, x);
        cout << max(tree[1][0].ans, tree[1][1].ans) << ' ';
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