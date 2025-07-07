#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
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
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

template <typename T>
struct FenwickTree{
    vector<T> BIT;
    FenwickTree(int n) : BIT(n + 1, 0) {}

    inline void mod(int x, T val) {
        while(x < BIT.size()){
            BIT[x] += val;
            x += x & -x;
        }
    }

    inline T query(int x) {
        T res = 0;
        while (x > 0) {
            res += BIT[x];
            x -= x & -x;
        }
        return res;
    }

    inline T query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

string s = "UDLR";

void solve() {
    int n; scanf("%d\n", &n);
    ll l = 0, r = 0;
    vector<pll> ope;
    bool f = 0;
    rep (i, 0, n) {
        char c; int x;
        c = getchar();
        getchar();
        scanf("%d\n", &x);
        ll t = find(all(s), c) - s.begin();
        if (!ope.empty() && ope.back().fi == t) {
            ope.back().se += x;
        } else if (!ope.empty() && abs(t - ope.back().fi) == 1 && min(t, ope.back().fi) != 1) {
            break;
        } else {
            ope.pb({t, x});
        }
        r += x;
    }
    ll sum = r;
    r += 1;
    n = ssize(ope);
    FenwickTree<int> bit(n + 1);
    auto check = [&](ll step) -> bool {
        pll cur = {0, 0};
        vector<pll> seg;
        vector<ll> dic;
        dic.pb(0);
        seg.pb(cur);
        int tot = 0;
        for (int i = 0; i < n && step > 0; i++) {
            tot++;
            ll go = min(step, ope[i].se);
            pll nxt = {cur.fi + dx[ope[i].fi] * go, cur.se + dy[ope[i].fi] * go};
            step -= go;
            seg.pb(nxt);
            dic.pb(nxt.se);
            cur = nxt;
        }
        sort(all(dic));
        dic.erase(unique(all(dic)), dic.end());
        int m = ssize(dic);
        vector<array<ll, 3>> event;
        vector<array<ll, 3>> seg2, seg3;
        seg[0].se = lower_bound(all(dic), seg[0].se) - dic.begin() + 1;
        rep (i, 0, ssize(seg) - 1) {
            seg[i + 1].se = lower_bound(all(dic), seg[i + 1].se) - dic.begin() + 1;
            pll L = min(seg[i], seg[i + 1]), R = max(seg[i], seg[i + 1]);
            if (L.se == R.se) {
                event.pb({L.fi, 1, L.se});
                event.pb({R.fi + 1, -1, R.se});
                seg2.pb({L.se, L.fi, R.fi});
            } else {
                event.pb({L.fi, 2 * L.se, R.se});
                seg3.pb({L.fi, L.se, R.se});
            }
        }
        sort(all(seg2));
        pll pre = {-LINF, -LINF};
        for (const auto &[x, y1, y2] : seg2) {
            if (pre.fi == x && y1 <= pre.se) return false;
            pre = {x, y2};
        }
        pre = {-LINF, -LINF};
        sort(all(seg3));
        for (const auto &[x, y1, y2] : seg3) {
            if (pre.fi == x && y1 <= pre.se) return false;
            pre = {x, y2};
        }
        sort(all(event));
        int cnt = 0;
        for (const auto &[x, t, y] : event) {
            if (abs(t) == 1) {
                bit.mod(y, t);
            } else {
                cnt += bit.query((t >> 1), y);
            }
        }
        return cnt == tot - 1;
    };
    if (check(sum)) {
        printf("%lld\n", sum);
        return;
    }
    if (sum >= 999999 && check(sum - 1000000 + 1)) {
        printf("%lld\n", sum - 1000000 + 2);
        return;
    }
    r = sum;
    while (r - l > 1) {
        ll mid = l + r >> 1;
        if (check(mid)) l = mid;
        else r = mid;
    }
    printf("%lld\n", min(sum, r));
}
 
int main() {
    // ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}