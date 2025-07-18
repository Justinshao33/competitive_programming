#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
// #pragma GCC optimize("O3,unroll-loops")
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
    int n, q; cin >> n >> q;
    vector<int> a(n), X(n, 1);
    rep (i, 0, n) cin >> a[i];
    auto dic = a;
    sort(all(dic));
    dic.erase(unique(all(dic)), dic.end());
    for (int &v : a) v = lower_bound(all(dic), v) - dic.begin();
    int m = ssize(dic);
    vector<array<int, 4>> que;
    rep (i, 0, q) {
        int l, r, k; cin >> l >> r >> k;
        l--;
        que.pb({l, r, k, i});
    }
    sort(all(que), [&](const auto &a, const auto &b) {
        if (a[0] / B != b[0] / B) return a[0] < b[0];
        return (a[0] / B) & 1 ? a[1] > b[1] : a[1] < b[1];
    });
    const int C = 1e5 + 1;
    vector<int> cnt(C, 0), bcnt(C / B + 1, 0), sum(m, 0);
    auto add = [&](int x) -> void {
        if (sum[a[x]]) {
            cnt[sum[a[x]]]--;
            bcnt[sum[a[x]] / B]--;
        }
        sum[a[x]] += X[x];
        cnt[sum[a[x]]]++;
        bcnt[sum[a[x]] / B]++;
    };
    auto sub = [&](int x) -> void {
        cnt[sum[a[x]]]--;
        bcnt[sum[a[x]] / B]--;
        sum[a[x]] -= X[x];
        if (sum[a[x]]) {
            cnt[sum[a[x]]]++;
            bcnt[sum[a[x]] / B]++;
        }
    };
    int L = 0, R = 0;
    vector<int> ans(q);
    for (auto &[l, r, k, id] : que) {
        while (R < r) add(R++);
        while (L > l) add(--L);
        while (R > r) sub(--R);
        while (L < l) sub(L++);
        int kth = 0, blo = -1;
        rep (i, 0, C / B + 1) {
            if (kth + bcnt[i] >= k) {
                blo = i;
                break;
            }
            kth += bcnt[i];
        }  
        if (blo == -1) {
            ans[id] = -1;
        } else {
            for (int i = blo * B; i / B == blo; i++) {
                kth += cnt[i];
                if (kth >= k) {
                    ans[id] = i;
                    break;
                }
            }
        }
    }
    rep (i, 0, q) cout << ans[i] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}