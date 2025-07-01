#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
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
 
const int MAXN = 3e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

struct info {
    int sum, pre, suf, ans;
    info(int x = 0) : sum(x), pre(max(0, x)), suf(max(0, x)), ans(max(0, x)) {}
    info operator+(const info &oth) const {
        info ret;
        ret.sum = sum + oth.sum;
        ret.pre = max(pre, sum + oth.pre);
        ret.suf = max(oth.suf, suf + oth.sum);
        ret.ans = max({ans, oth.ans, suf + oth.pre});
        return ret;
    }
} tree[MAXN << 2];

void mod(int pos, int l, int r, int id, int val) {
    if (l == r) {
        tree[pos] = info(val);
        return;
    }
    int mid = l + r >> 1;
    if (id <= mid) mod(lpos, l, mid, id, val);
    else mod(rpos, mid + 1, r, id, val);
    tree[pos] = tree[lpos] + tree[rpos];
}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n + 1);
    vector<vector<array<int, 3>>> ope(n + 1);
    rep (i, 1, n + 1) {
        cin >> a[i];
        ope[a[i]].pb({0, i, 1});
    }
    rep (i, 0, q) {
        int id, x; cin >> id >> x;
        if (x == a[id]) continue;
        ope[a[id]].pb({i, id, -1});
        a[id] = x;
        ope[a[id]].pb({i, id, 1});
    }
    rep (i, 1, n + 1) mod(1, 1, n, i, -1);
    vector<vector<pii>> ope2(q);
    for (auto &op : ope) {
        rep (i, 0, ssize(op)) {
            int ptr = i;
            while (ptr < ssize(op) && op[i][0] == op[ptr][0]) {
                mod(1, 1, n, op[ptr][1], op[ptr][2]);
                ptr++;
            }
            int res = tree[1].ans / 2;
            ope2[op[i][0]].pb({1, res});
            if (ptr < ssize(op)) ope2[op[ptr][0]].pb({0, res});
            i = ptr - 1;
        }
        for (auto &[i, id, t] : op) {
            mod(1, 1, n, id, -1);
        }
    }
    multiset<int> mst;
    rep (i, 0, q) {
        for (auto &[t, val] : ope2[i]) {
            if (t) mst.insert(val);
            else mst.extract(val);
        } 
        cout << *mst.rbegin() << " \n" [i == q - 1];
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}