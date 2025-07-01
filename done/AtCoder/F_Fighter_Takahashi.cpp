#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
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

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<ll> g(n), s(n);
    vector<int> med, id(n);
    s[0] = -1;
    g[0] = 1;
    rep (i, 1, n) {
        int p, t; cin >> p >> t >> s[i] >> g[i];
        p--;
        adj[p].pb(i);
        if (t == 2) {
            id[i] = med.size();
            med.pb(i);
        }
    }
    int m = med.size();
    vector<ll> dp(1 << m, -1);
    using PQ = priority_queue<pll, vector<pll>, greater<pll>>;
    vector<PQ> mpq(1 << m);
    vector<int> mmed(1 << m, 0);
    const ll INF = IINF;
    auto calc = [&](int mask, PQ pq, int not_use, ll str) -> void {
        while (!pq.empty() && str >= pq.top().fi) {
            auto [_, u] = pq.top(); pq.pop();
            if (s[u] != 0) str = min(str + g[u], INF);
            for (int v : adj[u]) {
                if (s[v] == 0) {
                    not_use |= 1 << id[v];
                } else {
                    pq.push({s[v], v});
                }
            }
        }
        if (str > dp[mask]) {
            dp[mask] = str;
            mpq[mask] = pq;
            mmed[mask] = not_use;
        }
    };
    {   // init
        PQ pq;
        pq.push({s[0], 0});
        calc(0, pq, 0, 0);
    }
    rep (bit, 0, 1 << m) {
        rep (i, 0, m) if (mmed[bit] >> i & 1) {
            ll str = dp[bit];
            PQ pq = mpq[bit];
            pq.push({0, med[i]});
            str = min(str * g[med[i]], INF);
            calc(bit | 1 << i, pq, mmed[bit] ^ 1 << i, str);
        }
    }
    if (dp[(1 << m) - 1] >= *max_element(all(s))) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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