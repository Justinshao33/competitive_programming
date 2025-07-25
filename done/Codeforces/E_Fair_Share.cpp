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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n; cin >> n;
    vector<vector<int>> arr;
    vector<int> dic;
    rep (i, 0, n) {
        int m; cin >> m;
        arr.pb({});
        rep (j, 0, m) {
            int b; cin >> b;
            arr.back().pb(b);
            dic.pb(b);
        }
    }
    sort(all(dic));
    dic.erase(unique(all(dic)), dic.end());
    int m = ssize(dic);
    vector<int> cnt(m, 0);
    vector<vector<pii>> adj(m + n);
    int tot = 0;
    for (int i = 0; auto &v : arr) {
        for (auto &x : v) {
            x = lower_bound(all(dic), x) - dic.begin();
            cnt[x]++;
            adj[x + n].pb({i, tot});
            adj[i].pb({x + n, tot});
            tot++;
        }
        i++;
    }
    rep (i, 0, m) if (cnt[i] & 1) {
        cout << "NO\n";
        return;
    }
    vector<bool> evis(tot, 0);
    vector<int> it(n + m, 0);
    vector<map<int, int>> L(n), R(n);
    auto dfs = [&](auto self, int u) -> void {
        for (; it[u] < ssize(adj[u]); it[u]++) {
            auto [v, id] = adj[u][it[u]];
            if (evis[id]) continue;
            evis[id] = 1;
            if (u < n) L[u][v - n]++;
            else R[v][u - n]++;
            self(self, v);
        }
    };
    rep (i, 0, n) dfs(dfs, i);
    cout << "YES\n";
    rep (i, 0, n) {
        for (int x : arr[i]) {
            if (L[i].count(x)) {
                cout << 'L';
                if (--L[i][x] == 0) {
                    L[i].erase(x);
                }
            } else {
                cout << 'R';
                if (--R[i][x] == 0) {
                    R[i].erase(x);
                }
            }
        }
        cout << '\n';
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