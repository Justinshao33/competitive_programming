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

void solve() {
    int n; cin >> n;
    vector<int> w(n);
    rep (i, 0, n) cin >> w[i];
    vector<array<int, 3>> seg;
    seg.push_back({n - 1, 0, 1});
    int q; cin >> q;
    while (q--) {
        int t, x; cin >> t >> x;
        if (t == 1 || t == 2) {
            x--;
            while (!seg.empty() && seg.back()[0] <= x) seg.pop_back();
            if (seg.empty()) {
                if (t == 1) seg.push_back({x, 0, t});
                else seg.push_back({x, w[x], t});
                continue;
            }
            if (seg.back()[2] == t) continue;
            if (t == 1) seg.push_back({x, seg.back()[1] - w[x], t});
            else seg.push_back({x, seg.back()[1] + w[x], t});
        } else {
            if (x < 0 || x >= w[n - 1]) {
                cout << 0 << '\n';
                continue;
            }
            auto calc = [&](int v) -> int {
                int l = 0, r = ssize(seg);
                while (r - l > 1) {
                    int mid = l + r >> 1;
                    if (seg[mid][0] >= v) l = mid;
                    else r = mid;
                }
                return l;
            };
            int l = -1, r = n - 1;
            // for (auto x : seg) {
            //     rep (i, 0, 3) cerr << x[i] << " \n" [i == 2];
            // }
            while (r - l > 1) {
                int mid = l + r >> 1;
                int id = calc(mid);
                int L, R;
                if (seg[id][2] == 1) {
                    L = seg[id][1], R = seg[id][1] + w[mid];
                } else {
                    L = seg[id][1] - w[mid], R = seg[id][1];
                }
                if (L <= x && x < R) r = mid;
                else l = mid;
            }
            cout << n - r << '\n';
        }
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