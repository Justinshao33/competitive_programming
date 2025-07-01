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

struct SparseTable{
    vector<vector<int>> sp;
    SparseTable(vector<int> &a) {
        int n = a.size();
        sp.resize(n, vector<int>(__lg(n) + 1));
        for (int i = n - 1; i >= 0; i--) {
            sp[i][0] = a[i];
            for (int j = 1; i + (1 << j) <= n; j++) {
                sp[i][j] = max(sp[i][j - 1], sp[i + (1 << j - 1)][j - 1]);
            }
        }
    }
    auto query(int l, int r) { // [l, r)
        if (l == r) return 0;
        int k = __lg(r - l);
        return max(sp[l][k], sp[r - (1 << k)][k]);
    }
};

void solve() {
    // for all i find its leftmost bottom mochi b[i]
    // for a query [l, r], fix ans
    // for all i in [l, l + ans - 1], b[i] <= r - ans + 1 + (i - l)
    // = b[i] <= (r - l + 1) - ans + i = b[i] - i <= r - l + 1 - ans = fixed const.
    // find maximum b[i] - i in [l, l + ans)
    int n; cin >> n;
    vector<int> a(n), b(n);
    rep (i, 0, n) cin >> a[i];
    rep (i, 0, n) b[i] = lower_bound(all(a), a[i] * 2) - a.begin() - i;
    SparseTable sp(b);
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        l--, r--;
        int len = r - l + 1;
        int L = 0, R = len / 2 + 1;
        while (R - L > 1) {
            int mid = L + R >> 1;
            if (sp.query(l, l + mid) <= len - mid) L = mid;
            else R = mid;
        }
        cout << L << '\n';
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