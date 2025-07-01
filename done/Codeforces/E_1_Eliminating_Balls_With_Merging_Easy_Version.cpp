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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n, x; cin >> n >> x;
    vector<int> a(n);
    rep (i, 0, n) cin >> a[i];
    vector<int> L(n, -1), R(n, -1), Pa(n, -1);
    vector<int> st;
    rep (i, 0, n) {
        int lst = -1;
        while (!st.empty() && a[st.back()] <= a[i]) {
            lst = st.back();
            st.pop_back();
        }
        if (lst != -1) {
            L[i] = lst;
            Pa[lst] = i;
        }
        if (!st.empty()) {
            Pa[i] = st.back();
            R[st.back()] = i;
        }
        st.pb(i);
    }
    int ans = 0;
    vector<ll> sum(n, 0);
    vector<bool> ok(n, 0);
    auto dfs = [&](auto self, int u) -> void {
        sum[u] = a[u];
        if (L[u] != -1) {
            self(self, L[u]);
            sum[u] += sum[L[u]];
        }
        if (R[u] != -1) {
            self(self, R[u]);
            sum[u] += sum[R[u]];
        }
    };
    int root = st[0];
    dfs(dfs, root);
    auto dfs2 = [&](auto self, int u) -> void {
        if (Pa[u] == -1 || (ok[Pa[u]] && sum[u] >= a[Pa[u]])) {
            ok[u] = 1;
            ans++;
        }
        if (L[u] != -1) self(self, L[u]);
        if (R[u] != -1) self(self, R[u]);
    };
    dfs2(dfs2, root);
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}