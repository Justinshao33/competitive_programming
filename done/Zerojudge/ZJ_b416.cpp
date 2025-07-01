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

int cnt = 1, tree[MAXN << 5], L[MAXN << 5], R[MAXN << 5];
int T[MAXN];

int build(int l, int r){
    int root = cnt++;
    if(l == r) return root;
    int mid = (l + r) >> 1;
    L[root] = build(l, mid);
    R[root] = build(mid + 1, r);
    return root;
}

int mod(int pre, int l, int r, int idx){
    int root = cnt++;
    L[root] = L[pre]; R[root] = R[pre];
    tree[root] = tree[pre] + 1;
    if(l == r) return root;
    int mid = (l + r) >> 1;
    if(idx <= mid) L[root] = mod(L[pre], l, mid, idx);
    else R[root] = mod(R[pre], mid + 1, r, idx);
    return root;
}

int query(int v, int l, int r, int ql, int qr){
    if(l == ql && r == qr) return tree[v];
    int mid = (l + r) >> 1;
    if(qr <= mid) return query(L[v], l, mid, ql, qr);
    else if(ql > mid) return query(R[v], mid + 1, r, ql, qr);
    else return query(L[v], l, mid, ql, mid) + query(R[v], mid + 1, r, mid + 1, qr);
}

void solve() {
    int n, q; cin >> n >> q;
    vector<pii> a(n);
    rep (i, 0, n) {
        cin >> a[i].F;
        a[i].S = i + 1;
    }
    sort(all(a));
    vector<int> val;
    T[0] = build(1, n);
    rep (i, 0, n) {
        val.pb(a[i].F);
        T[i + 1] = mod(T[i], 1, n, a[i].S);
    }
    // cout << query(T[4], 1, n, 1, n) << '\n';
    while (q--) {
        int l, r, a, b; cin >> l >> r >> a >> b;
        a = lower_bound(all(val), a) - val.begin();
        b = upper_bound(all(val), b) - val.begin();
        // cout << a << ' ' << b << '\n';
        cout << query(T[b], 1, n, l, r) - query(T[a], 1, n, l, r) << '\n';
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}