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
 
const int MAXN = 1e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

int n, cnt = 1, L[MAXN << 5], R[MAXN << 5], fa[MAXN << 5], dep[MAXN << 5];
int T[MAXN];

int build(int l, int r) {
    int root = cnt++;
    if (l == r) {
        fa[root] = l;
        return root;
    }
    int mid = l + r >> 1;
    L[root] = build(l, mid);
    R[root] = build(mid + 1, r);
    return root;
}

int merge(int pre, int l, int r, int idx, int pa) {
    int root = cnt++;
    L[root] = L[pre]; R[root] = R[pre];
    if (l == r) {
        fa[root] = pa;
        dep[root] = dep[pre];
        return root;
    }
    int mid = l + r >> 1;
    if(idx <= mid) L[root] = merge(L[pre], l, mid, idx, pa);
    else R[root] = merge(R[pre], mid + 1, r, idx, pa);
    return root;
}

void update(int v, int l, int r, int idx) {
    if (l == r) {
        dep[v]++;
        return;
    }
    int mid = l + r >> 1;
    if (idx <= mid) update(L[v], l, mid, idx);
    else update(R[v], mid + 1, r, idx);
}

int query(int v, int l, int r, int idx) {
    if (l == r) return v;
    int mid = l + r >> 1;
    if (idx <= mid) return query(L[v], l, mid, idx);
    else return query(R[v], mid + 1, r, idx);
}

int find(int v, int x) {
    int cur = query(v, 1, n, x);
    return (fa[cur] == x ? cur : find(v, fa[cur]));
}

void Union(int x, int y, int i) {
    x = find(T[i - 1], x), y = find(T[i - 1], y);
    if(x == y) return; 
    if (dep[x] > dep[y]) swap(x, y);
    T[i] = merge(T[i - 1], 1, n, fa[x], fa[y]);
    if (dep[x] == dep[y]) update(T[i], 1, n, fa[y]);
}

bool same(int x, int y, int i){
    x = find(T[i - 1], x), y = find(T[i - 1], y);
    return x == y;
}

void solve() {
    int q; cin >> n >> q;
    T[0] = build(1, n);
    int ans = 0;
    rep (i, 1, q + 1) {
        int t; cin >> t;
        t ^= ans;
        if (t == 0) {
            int k; cin >> k;
            k ^= ans;
            T[i] = T[k];
        } else if (t == 1) {
            int x, y; cin >> x >> y;
            x ^= ans, y ^= ans;
            T[i] = T[i - 1];
            Union(x, y, i);
        } else {
            int x, y; cin >> x >> y;
            x ^= ans, y ^= ans;
            T[i] = T[i - 1];
            ans = same(x, y, i);
            cout << ans << '\n';
        }
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