#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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

int tree[MAXN << 2], tree2[MAXN << 2], b[MAXN];

void pull(int pos) {
    tree[pos] = max(tree[lpos], tree[rpos]);
    tree2[pos] = min(tree2[lpos], tree2[rpos]);
}

void build(int pos, int l, int r) {
    if (l == r) {
        tree[pos] = 0;
        tree2[pos] = IINF;
        return;
    }
    int mid = l + r >> 1;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
    pull(pos);
} 

void mod(int pos, int l, int r, int idx, int val) {
    if (l == r) {
        if (val == -1) {
            tree[pos] = 0;
            tree2[pos] = IINF;
        }
        else tree[pos] = tree2[pos] = val;
        return;
    }
    int mid = l + r >> 1;
    if (idx <= mid) mod(lpos, l, mid, idx, val);
    else mod(rpos, mid + 1, r, idx, val);
    pull(pos);
}

pii query(int pos, int l, int r, int ql, int qr) {
    if (ql > qr) return {0, IINF};
    if (ql <= l && qr >= r) return {tree[pos], tree2[pos]};
    int mid = l + r >> 1;
    pii res = {0, IINF};
    if (ql <= mid) {
        auto [mx, mi] = query(lpos, l, mid, ql, qr);
        chmax(res.F, mx);
        chmin(res.S, mi);
    }
    if (qr > mid) {
        auto [mx, mi] = query(rpos, mid + 1, r, ql, qr);
        chmax(res.F, mx);
        chmin(res.S, mi);
    }
    return res;
}

void solve() {
    int n, m, q; cin >> n >> m >> q;
    vector<int> rk(n);
    rep (i, 0, n) {
        int a; cin >> a;
        a--;
        rk[a] = i;
    }
    rep (i, 1, m + 1) {
        cin >> b[i];
        b[i]--;
        b[i] = rk[b[i]];
    }
    build(1, 1, m);
    vector<set<int>> pos(n);
    rep (i, 1, m + 1) pos[b[i]].insert(i);
    rep (i, 0, n) if (!pos[i].empty()) mod(1, 1, m, *pos[i].begin(), i);
    int bad = 0;
    auto check = [&](int i) -> bool {
        int id = *pos[i].begin();
        auto [mx, _] = query(1, 1, m, 1, id - 1);
        auto [__, mi] = query(1, 1, m, id + 1, m);
        return (mx > i || mi < i);
    };
    rep (i, 0, n) if (!pos[i].empty()) {
        bad += check(i);
    }
    cout << (bad == 0 ? "YA\n" : "TIDAK\n");
    while (q--) {
        int s, t; cin >> s >> t;
        t--;
        if (*pos[b[s]].begin() == s) {
            bad -= check(b[s]);
            mod(1, 1, m, s, -1);
        }
        pos[b[s]].erase(pos[b[s]].begin());
        if (!pos[b[s]].empty()) {
            mod(1, 1, m, *pos[b[s]].begin(), b[s]);
        }
        if ()
        b[s] = t;
        cout << (bad == 0 ? "YA\n" : "TIDAK\n");
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