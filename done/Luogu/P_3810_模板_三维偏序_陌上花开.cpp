// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;
#define fi first
#define se second

#ifdef LOCAL
#define ZTMYACANESOCUTE // freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

void dbg() { cerr << '\n'; }
template<typename T, typename ...U>
void dbg(T t, U ...u) { cerr << t << ' '; dbg(u...); }

pii operator + (const pii &p1, const pii &p2) { return make_pair(p1.fi + p2.fi, p1.se + p2.se); }
pii operator - (const pii &p1, const pii &p2) { return make_pair(p1.fi - p2.fi, p1.se - p2.se); }
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.fi + p2.fi, p1.se + p2.se); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.fi - p2.fi, p1.se - p2.se); }

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

struct Node {
    int ls, rs, sum;
    Node() : ls(0), rs(0), sum(0) {}
} tree[MAXN * 100];

int root[MAXN];

int newnode() {
    static int id = 0;
    tree[++id] = Node();
    return id;
}

void mod2(int &pos, int l, int r, int id, int v) {
    if (pos == 0) pos = newnode();
    auto &tr = tree[pos];
    if (l == r) return void(tr.sum += v);
    int mid = l + r >> 1;
    if (id <= mid) mod2(tr.ls, l, mid, id, v);
    else mod2(tr.rs, mid + 1, r, id, v);
    tr.sum = tree[tr.ls].sum + tree[tr.rs].sum;
}

int query2(int pos, int l, int r, int ql, int qr) {
    if (pos == 0) return 0;
    auto &tr = tree[pos];
    if (ql <= l && qr >= r) return tr.sum;
    int mid = l + r >> 1, res = 0;
    if (ql <= mid) res += query2(tr.ls, l, mid, ql, qr);
    if (qr > mid) res += query2(tr.rs, mid + 1, r, ql, qr);
    return res;
}

void mod(int x, int y) {
    while (x < MAXN) {
        mod2(root[x], 1, MAXN - 1, y, 1);
        x += x & -x;
    }
}

int query(int x, int y) {
    int res = 0;
    while (x) {
        res += query2(root[x], 1, MAXN - 1, 1, y);
        x -= x & -x;
    }
    return res;
}

void solve() {
    int n, k; cin >> n >> k;
    vector<array<int, 3>> a(n);
    rep (i, 0, n) rep (j, 0, 3) cin >> a[i][j];
    sort(all(a));
    vector<int> ans(n, 0);
    rep (i, 0, n) {
        mod(a[i][1], a[i][2]);
        if (i == n - 1 || a[i][0] != a[i + 1][0]) {
            for (int j = i; j >= 0 && a[j][0] == a[i][0]; --j) {
                int d = query(a[j][1], a[j][2]) - 1;
                // cout << d << '\n';
                ans[d]++;
            }
        }
    }
    rep (i, 0, n) cout << ans[i] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}