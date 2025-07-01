#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
    int n, K; cin >> n >> K;
    vector<int> a(n);
    rep (i, 0, n) cin >> a[i];
    ll ans = 0;
    vector<int> lmx(n), lmn(n), rmx(n), rmn(n);
    map<int, int> cnt;
    auto dc = [&](auto self, int l, int r) -> void {
        if (l == r) {
            ans++;
            return;
        }
        int mid = l + r >> 1;
        self(self, l, mid);
        self(self, mid + 1, r);
        lmx[mid] = lmn[mid] = a[mid];
        for (int i = mid - 1; i >= l; --i) {
            lmx[i] = max(lmx[i + 1], a[i]);
            lmn[i] = min(lmn[i + 1], a[i]);
        }
        rmx[mid + 1] = rmn[mid + 1] = a[mid + 1];
        rep (i, mid + 2, r + 1) {
            rmx[i] = max(rmx[i - 1], a[i]);
            rmn[i] = min(rmn[i - 1], a[i]);
        }
        // mx: L, mn: L
        for (int L = mid; L >= l; --L) {
            rep (k, 0, K + 1) {
                int R = lmx[L] - lmn[L] + L - k;
                if (R > mid && R <= r) ans += lmx[L] > rmx[R] && lmn[L] < rmn[R];
            }
        }
        // mx: R, mn: R
        rep (R, mid + 1, r + 1) {
            rep (k, 0, K + 1) {
                int L = R - rmx[R] + rmn[R] + k;
                if (L >= l && L <= mid) ans += rmx[R] > lmx[L] && rmn[R] < lmn[L];
            }
        }
        // mx: L, mn: R -> max + L - K = min + R
        for (int L = mid, R = mid + 1, RR = mid + 1; L >= l; --L) {
            while (R <= r && rmx[R] < lmx[L]) {
                cnt[R + rmn[R]]++;
                R++;
            }
            while (RR < R && rmn[RR] > lmn[L]) {
                cnt[RR + rmn[RR]]--;
                RR++;
            }
            rep (k, 0, K + 1) {
                ans += cnt[lmx[L] + L - k];
            }
        }
        rep (R, mid + 1, r + 1) cnt[R + rmn[R]] = 0;
        // mx: R, mn: L -> L - min - K = R - max
        for (int L = mid, R = mid + 1, RR = mid + 1; L >= l; --L) {
            while (R <= r && rmn[R] > lmn[L]) {
                cnt[R - rmx[R]]++;
                R++;
            }
            while (RR < R && rmx[RR] < lmx[L]) {
                cnt[RR - rmx[RR]]--;
                RR++;
            }
            rep (k, 0, K + 1) {
                ans += cnt[L - lmn[L] - k];
            }
        }
        rep (R, mid + 1, r + 1) cnt[R - rmx[R]] = 0;
    };
    dc(dc, 0, n - 1);
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}