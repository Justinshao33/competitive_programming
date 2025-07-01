#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
 
const int MAXN = 1e6 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct Line {
    ll m, k = -LINF;
    Line() {}
    Line(ll _m, ll _k) : m(_m), k(_k) {}
    ll operator () (const int &x) const {
        return 1LL * m * x + k;
    }
};

// max LiChao

struct Node {
    Line line;
    int ls, rs;
    Node() {}
    Node(Line li) : ls(0), rs(0), line(li) {}
};

struct LiChao {
    
    vector<Node> tree;
    int sz = 0;

    LiChao() {}
    LiChao(int n) : tree(n * 30 + 1), sz(0) {}

    int newnode(Line line) {
        tree[++sz] = Node(line);
        return sz;
    }

    void insert (int &pos, int l, int r, Line line) {
        if (pos == 0) {
            pos = newnode(line);
            return;
        }
        auto &tr = tree[pos].line;
        if (l == r) {
            if (line(l) > tr(l)) tr = line;
            return;
        }
        int mid = (l + r) >> 1;
        if (tr(mid) < line(mid)) swap(tr, line);
        if (tr.m >= line.m) {
            insert(tree[pos].ls, l, mid, line);
        } else {
            insert(tree[pos].rs, mid + 1, r, line);
        }
    }

    ll query (int pos, int l, int r, int x) {
        if (pos == 0) return -LINF;
        ll res = tree[pos].line(x);
        if (l == r) return res;
        int mid = l + r >> 1;
        if (x <= mid) return max(query(tree[pos].ls, l, mid, x), res);
        else return max(query(tree[pos].rs, mid + 1, r, x), res);
    }

} tr;

const int C = 3e8;

int root[MAXN], n;

void mod(int x, Line line) {
    x++;
    while (x <= n + 1) {
        tr.insert(root[x], -C, C, line);
        x += x & -x;
    }
}

ll query(int x, int p) {
    x++;
    ll res = -LINF;
    while (x > 0) {
        res = max(res, tr.query(root[x], -C, C, p));
        x -= x & -x;
    }
    return res;
}

void solve() {
    int k; cin >> n >> k;
    vector<ll> a(n + 1, 0), pre(n + 1, 0), pre2(n + 1, 0), b(n + 1, 0);
    rep (i, 1, n + 1) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
        pre2[i] = pre2[i - 1] + a[i] * i;
    }
    rep (i, 1, n + 1) cin >> b[i];
    tr = LiChao(n);
    mod(0, Line(0, 0));
    vector<ll> dp(n + 1);
    rep (i, 1, n + 1) {
        dp[i] = query(i - 1, pre[i]) - query(max(0, i - k), pre[i]) + pre2[i];
        mod(i, Line(b[i] - i, (i - b[i]) * pre[i] - pre2[i] + dp[i]));
    }
    cout << dp[n] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}