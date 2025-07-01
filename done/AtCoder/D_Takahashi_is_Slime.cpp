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
    if (r - l < 1) return IINF;
        int k = __lg(r - l);
        return max(sp[l][k], sp[r - (1 << k)][k]);
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<ll> pre(n + 1);
    pre[0] = 0;
    rep (i, 0, n) {
        cin >> a[i];
        pre[i + 1] = pre[i] + a[i];
    }
    SparseTable sp(a);
    auto get_l = [&](int pos, ll x) -> int {
        int l = -1, r = pos;
        while (r - l > 1) {
            int mid = l + r >> 1;
            if (sp.query(mid, pos) >= x) l = mid;
            else r = mid;
        }
        return r;
    };
    auto get_r = [&](int pos, ll x) -> int {
        int l = pos, r = n;
        while (r - l > 1) {
            int mid = l + r >> 1;
            if (sp.query(pos + 1, mid + 1) >= x) r = mid;
            else l = mid;
        }
        return l;
    };
    rep (i, 0, n) {
        ll cur = a[i];
        int l = i, r = i;
        while (true) {
            int cnt = 0;
            int L = get_l(i, cur);
            int R = get_r(i, cur);
            cnt = (L == l) + (R == r);
            l = L, r = R;
            cur = pre[r + 1] - pre[l];
            if (cnt == 2) break;       
        }
        cout << cur << " \n" [i == n - 1];
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