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

struct Line {
    ll m, k;
    ll val (int x) {
        return m * x + k;
    }
};

struct LiChao {
    
    vector<Line> tree;
    vector<int> L, R;
 
    int new_node() {
        tree.pb((Line){0, 0});
        L.pb(-1);
        R.pb(-1);
        return tree.size() - 1;
    }
 
    void init() {
        new_node();
    }
 
    void insert(ll v, ll l, ll r, Line li) {
        if (l == r) {
            if(li.val(l) > tree[v].val(l)) tree[v] = li;
            return;
        }
        ll mid = l + r >> 1;
        if (tree[v].m > li.m) swap(tree[v], li);
        if (tree[v].val(mid) < li.val(mid)) {
            swap(tree[v], li);
            if(L[v] == -1) L[v] = new_node();
            insert(L[v], l, mid, li);
        } else {
            if(R[v] == -1) R[v] = new_node();
            insert(R[v], mid + 1, r, li);
        }
    }
 
    ll query(ll v, ll l, ll r, ll x) {
        if (v == -1) return -LINF;
        if (l == r) return tree[v].val(x);
        ll mid = l + r >> 1;
        ll cur = tree[v].val(x);
        if (x <= mid) return max(cur, query(L[v], l, mid, x));
        else return max(cur, query(R[v], mid + 1, r, x));
    }
} LiChao;

const int R = 1e9 + 5;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> b(n);
    rep (i, 0, n) cin >> b[i];
    sort(all(b), greater<int>());
    LiChao.init();
    rep (i, 0, n) LiChao.insert(0, 0, R, {(i + 1), 1LL * (i + 1) * b[i]});
    rep (i, 0, m) {
        int c; cin >> c;
        cout << LiChao.query(0, 0, R, c) << ' ';
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