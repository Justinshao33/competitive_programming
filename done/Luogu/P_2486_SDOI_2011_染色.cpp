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

struct info {
    int l, r, tag, ans;
    void update(int);
} tree[MAXN << 2];

void info::update(int c) {
    l = r = c;
    tag = c;
    ans = 1;
}

void push(int pos) {
    if (tree[pos].tag) {
        tree[lpos].update(tree[pos].tag);
        tree[rpos].update(tree[pos].tag);
        tree[pos].tag = 0;
    }
}

void pull(int pos) {
    tree[pos].l = tree[lpos].l;
    tree[pos].r = tree[rpos].r;
    tree[pos].ans = tree[lpos].ans + tree[rpos].ans;
    if(tree[lpos].r == tree[rpos].l) tree[pos].ans--;
}

void mod(int pos, int l, int r, int ml, int mr, int val) {
    if (l == ml && r == mr) {
        tree[pos].update(val);
        return; 
    }
    push(pos);
    int mid = l + r >> 1;
    if (mr <= mid) mod(lpos, l, mid, ml, mr, val);
    else if (ml > mid) mod(rpos, mid + 1, r, ml, mr, val);
    else {
        mod(lpos, l, mid, ml, mid, val);
        mod(rpos, mid + 1, r, mid + 1, mr, val);
    }
    pull(pos);
}

info get(int pos, int l, int r, int ql, int qr) {
    if (l == ql && r == qr) {
        return tree[pos];
    }
    push(pos);
    int mid = l + r >> 1;
    if (qr <= mid) return get(lpos, l, mid, ql, qr);
    else if (ql > mid) return get(rpos, mid + 1, r, ql, qr);
    else {
        info a = get(lpos, l, mid, ql, mid), b = get(rpos, mid + 1, r, mid + 1, qr);
        return (info) {
            a.l, b.r, 0, a.ans + b.ans - (a.r == b.l)
        };
    }
}
 
void solve() {
    int n, q; cin >> n >> q;

    vector<int> col(n);
    vector<vector<int>> adj(n);

    rep (i, 0, n) cin >> col[i];
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    vector<int> dep(n), tp(n), hson(n), id(n), fa(n), sub(n);
    int cnt = 0;

    auto dfs = [&](auto self, int u, int pa) -> void {
        sub[u] = 1;
        fa[u] = pa;
        hson[u] = -1;
        for (int v : adj[u]) {
            if (v == pa) continue;
            dep[v] = dep[u] + 1;
            self(self, v, u);
            sub[u] += sub[v];
            if(hson[u] == -1 || sub[hson[u]] < sub[v]) {
                hson[u] = v;
            }
        }
    };

    auto HLD = [&](auto self, int u, int top) -> void {
        tp[u] = top;
        id[u] = ++cnt;
        mod(1, 1, n, id[u], id[u], col[u]);
        if (hson[u] != -1) {
            self(self, hson[u], top);
        }
        for (int v : adj[u]) {
            if(v == fa[u] || v == hson[u]) continue;
            self(self, v, v);
        }
    };

    dep[0] = 0;
    dfs(dfs, 0, -1);
    HLD(HLD, 0, 0);

    auto modify = [&](int a, int b, int c) -> void {
        while(tp[a] != tp[b]){
            if(dep[tp[a]] < dep[tp[b]]) swap(a, b);
            mod(1, 1, n, id[tp[a]], id[a], c);
            a = fa[tp[a]];
        }
        if(dep[a] > dep[b]) swap(a, b);
        mod(1, 1, n, id[a], id[b], c);
    };

    auto query = [&](int a, int b) -> int {
        int res = 0, cl = 0, cr = 0;
        while(tp[a] != tp[b]){
            if(dep[tp[a]] < dep[tp[b]]) swap(a, b), swap(cl, cr);
            info tmp = get(1, 1, n, id[tp[a]], id[a]);
            res += tmp.ans;
            if(cl == tmp.r) res--;
            cl = tmp.l;
            a = fa[tp[a]];
        }
        if(dep[a] > dep[b]) swap(a, b), swap(cl, cr);
        info tmp = get(1, 1, n, id[a], id[b]);
        res += tmp.ans;
        if(cl == tmp.l) res--;
        if(cr == tmp.r) res--;
        return res;
    };

    while (q--) {
        char ch; cin >> ch;
        if (ch == 'C') {
            int a, b, c; cin >> a >> b >> c;
            a--, b--;
            modify(a, b, c);
        } else {
            int a, b; cin >> a >> b;
            a--, b--;
            cout << query(a, b) << '\n';
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