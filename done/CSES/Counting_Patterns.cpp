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
 
const int MAXN = 5e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

int tr[MAXN][26], idx = 0;
int fail[MAXN], cnt[MAXN], ind[MAXN], ans[MAXN];
vector<int> w[MAXN];

void insert(string s, int id) {
    int u = 0;
    for (char c : s) {
        if (tr[u][c - 'a'] == 0) tr[u][c - 'a'] = ++idx;
        u = tr[u][c - 'a'];
    }
    w[u].pb(id);
}

void build() {
    queue<int> q;
    rep (i, 0, 26) if (tr[0][i]) q.push(tr[0][i]);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        rep (i, 0, 26) {
            if (tr[u][i]) {
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
                ind[fail[tr[u][i]]]++;
            } else {
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
}

void record(string s) {
    int u = 0;
    for (char c : s) {
        u = tr[u][c - 'a'];
        cnt[u]++;
    }
}

void topo() {
    queue<int> q;
    rep (i, 0, idx + 1) if (!ind[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int x : w[u]) ans[x] = cnt[u];
        int v = fail[u];
        cnt[v] += cnt[u];
        ind[v]--;
        if (!ind[v]) q.push(v);
    }
}

void solve() {
    string s; cin >> s;
    int k; cin >> k;
    rep (i, 0, k) {
        string t; cin >> t;
        insert(t, i);
    }
    build();
    record(s);
    topo();
    rep (i, 0, k) cout << ans[i] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}