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

const int C = 5e6 + 5;

int lp[C], isp[C]; 
vector<int> prime;

void sieve() {
    rep (i, 1, C) lp[i] = 1;
    rep (i, 2, C) {
        if (lp[i] == 1) {
            lp[i] = i;
            prime.pb(i);
            isp[i] = 1;
        }
        for (int p : prime) {
            if (i * p >= C) break;
            lp[i * p] = p;
            if (i % p == 0) {
                break;
            }
        }
    }
}

int mp[C], cnt[C];

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    rep (i, 0, n) cin >> a[i];
    vector<vector<int>> adj(n);
    bool f2 = 1;
    vector<int> tmp;
    auto clear = [&]() -> void {
        for (int x : tmp) cnt[x] = mp[x] = 0;
    };
    rep (i, 0, n) {
        int x = a[i];
        while (x != 1) {
            int cur = lp[x];
            if (cnt[cur] == 1) {
                f2 = 0;
                adj[mp[cur]].pb(i);
                adj[i].pb(mp[cur]);
            }
            mp[cur] = i;
            cnt[cur]++;
            tmp.pb(cur);
            if (cnt[cur] > 2) {
                clear();
                cout << 0 << '\n';
                return;
            }
            while (x % cur == 0) x /= cur;
        }
    }
    if (f2) {
        cout << (fpow(2, n, MOD) - 2 + MOD) % MOD << '\n';
        clear();
        return;
    }
    vector<int> col(n, -1);
    bool f = 1;
    auto dfs = [&](auto self, int u) -> void {
        for (int v : adj[u]) {
            if (col[v] == -1) {
                col[v] = col[u] ^ 1;
                self(self, v);
            } else {
                if (col[v] == col[u]) f = 0;
            }
        }
    };
    ll ans = 1;
    rep (i, 0, n) if (col[i] == -1) {
        f = 1;
        col[i] = 0;
        dfs(dfs, i);
        if (!f) {
            clear();
            cout << 0 << '\n';
            return;
        }
        ans = ans * 2 % MOD;
    }
    clear();
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    sieve();
    while (T--) {
        solve();
    }
}