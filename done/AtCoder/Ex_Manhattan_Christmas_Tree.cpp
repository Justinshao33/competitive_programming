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

struct wavelet_tree {

    int mn, mx;
    vector<int> lf;
    wavelet_tree *lc, *rc;

    wavelet_tree(int l, int r, int vl, int vr, vector<int> &val) : mn(vl), mx(vr) { // 0-base [l, r)
        lc = rc = nullptr;
        if (l >= r || mn == mx) return;
        lf.pb(0);
        int mid = mn + mx >> 1;
        auto cmp = [&](int x) -> bool { return x <= mid; };
        rep (i, l, r) lf.pb(lf.back() + cmp(val[i]));
        int pivot = stable_partition(val.begin() + l, val.begin() + r, cmp) - val.begin();
        lc = new wavelet_tree(l, pivot, mn, *max_element(val.begin() + l, val.begin() + pivot), val);
        rc = new wavelet_tree(pivot, r, *min_element(val.begin() + pivot, val.begin() + r), mx, val);
    }

    // all operations below are 1-base [l, r]

    int kth(int l, int r, int k) { // count kth smallest in [l, r]
        if (mn == mx) 
            return mn;
        int cnt = lf[r] - lf[l - 1];
        if (cnt >= k) 
            return lc->kth(lf[l - 1] + 1, lf[r], k);
        else 
            return rc->kth(l - lf[l - 1], r - lf[r], k - cnt);
    }

    int count(int l, int r, int k) { // count val[i] = k, i in [l, r]
        if (l > r || k > mx || k < mn) 
            return 0;
        if (mn == mx) 
            return r - l + 1;
        int mid = mn + mx >> 1;
        if (k <= mid) 
            return lc->count(lf[l - 1] + 1, lf[r], k);
        else
            return rc->count(l - lf[l - 1], r - lf[r], k);
    }

    int LTE(int l, int r, int k) { //count val[i] <= k, i in [l, r]
        if (l > r || k < mn) 
            return 0;
        if (mx <= k)
            return r - l + 1;
        return lc->LTE(lf[l - 1] + 1, lf[r], k) + rc->LTE(l - lf[l - 1], r - lf[r], k);
    }

};

void solve() {
    int n; cin >> n;
    vector<pii> pt;
    rep (i, 0, n) {
        int x, y; cin >> x >> y;
        tie(x, y) = make_pair(x + y, x - y + 100000);
        pt.pb({x, y});
    }
    sort(all(pt));
    vector<int> y_val(n), x_ord(n);
    rep (i, 0, n) tie(x_ord[i], y_val[i]) = pt[i];
    wavelet_tree tree(0, n, 0, 200005, y_val);
    int q; cin >> q;
    rep (i, 0, q) {
        int x, y, k; cin >> x >> y >> k;
        tie(x, y) = make_pair(x + y, x - y + 100000);
        int l = -1, r = 200005;
        while (r - l > 1) {
            int mid = l + r >> 1;
            int L = lower_bound(all(x_ord), x - mid) - x_ord.begin() + 1,
                R = upper_bound(all(x_ord), x + mid) - x_ord.begin();
            int cnt = tree.LTE(L, R, y + mid) - tree.LTE(L, R, y - mid - 1);
            // debug(mid, cnt);
            if (cnt >= k) r = mid;
            else l = mid;
        }
        cout << r << '\n';
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