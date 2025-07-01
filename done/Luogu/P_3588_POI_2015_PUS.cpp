// #pragma GCC optimize("O3,unroll-loops")
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
 
const int MAXN = 1e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

int cnt = 0, out[MAXN << 2], id[MAXN], ind[MAXN * 6];
vector<pii> adj[MAXN * 6]; // (MAXN << 2) + m

void build(int pos, int l, int r) {
    if (l == r) {
        out[pos] = id[l] = ++cnt;
        return;
    }
    int mid = l + r >> 1;
    out[pos] = ++cnt;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
    adj[out[pos]].pb({out[lpos], 0});
    ind[out[lpos]]++;
    adj[out[pos]].pb({out[rpos], 0});
    ind[out[rpos]]++;
}

void add(int pos, int l, int r, int al, int ar, int v) {
    if (ar < al) return;
    if (al == l && ar == r) {
        adj[v].pb({out[pos], 0});
        ind[out[pos]]++;
        return;
    }
    int mid = l + r >> 1;
    if (ar <= mid) add(lpos, l, mid, al, ar, v);
    else if (al > mid) add(rpos, mid + 1, r, al, ar, v);
    else {
        add(lpos, l, mid, al, mid, v);
        add(rpos, mid + 1, r, mid + 1, ar, v);
    }
}

void solve() {
    int n, s, m; cin >> n >> s >> m;
    build(1, 1, n);
    vector<int> dis(cnt + 1 + m, IINF);
    vector<bool> vis(cnt + 1 + m, 0);
    rep (i, 0, s) {
        int p, d; cin >> p >> d;
        dis[id[p]] = d;
        vis[id[p]] = 1;
    }
    while (m--) {
        int l, r, k; cin >> l >> r >> k;
        int sp = ++cnt;
        rep (i, 0, k) {
            int x; cin >> x;
            adj[id[x]].pb({sp, 1});
            ind[sp]++;
            add(1, 1, n, l, x - 1, sp);
            l = x + 1;
        }
        add(1, 1, n, l, r, sp);
    }
    queue<int> q;
    rep (i, 1, cnt + 1) if (!ind[i]) {
        q.push(i);
        if (!vis[i]) dis[i] = 1e9;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : adj[u]) {
            ind[v]--;
            if (!ind[v]) q.push(v);
            if (vis[v]) {
                if (dis[u] - w < dis[v]) {
                    cout << "NIE\n";
                    return;
                }
            } else {
                chmin(dis[v], dis[u] - w);
            }
        }
    }
    rep (i, 1, n + 1) if (ind[id[i]] || dis[id[i]] < 1) {
        cout << "NIE\n";
        return;
    }
    cout << "TAK\n";
    rep (i, 1, n + 1) {
        cout << dis[id[i]] << " \n" [i == n];
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