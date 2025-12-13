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
 
const int MAXN = 1e6 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

#define int long long

void solve() {
    int n, m, q; cin >> n >> m >> q;
    vector<string> g(n);
    rep (i, 0, n) cin >> g[i];
    vector<int> cnt(MAXN, 0);
    auto work = [&](int sx, int sy, int dx, int dy) -> void {
        vector<int> st;
        auto get = [&]() -> int {
            if (st.back() < 0) return 0;
            if (ssize(st) == 1) return st.back();
            reverse(all(st));
            int res = 0, op = -1;
            for (int x : st) {
                if (x > 0) {
                    if (op == -1) res += x;
                    else res *= x;
                } else {
                    op = x;
                }
            }
            reverse(all(st));
            return res;
        };
        while (sx >= 0 && sy >= 0 && sx < n && sy < m) {
            if (isdigit(g[sx][sy])) {
                if (st.empty() || st.back() < 0) st.push_back(g[sx][sy] - '0');
                else st.back() = st.back() * 10 + g[sx][sy] - '0';
                if (st.back() > 1e6) break;
            } else if (g[sx][sy] == '+') {
                if (st.back() < 0) break;
                int val = get();
                st = {val, -1};
            } else {
                if (st.back() < 0) break;
                if (ssize(st) > 1 && st.end()[-2] == -2) {
                    assert(ssize(st) >= 3);
                    int x = st.back(); st.pop_back();
                    st.pop_back();
                    int y = st.back(); st.pop_back();
                    st.push_back(x * y);
                    if (st.back() > 1e6) break;
                }
                st.push_back(-2);
            }
            int val = get();
            if (val > 1e6) break;
            cnt[val]++;
            sx += dx;
            sy += dy;
        }
    };
    rep (i, 0, n) {
        rep (j, 0, m) {
            if (!isdigit(g[i][j])) continue;
            cnt[g[i][j] - '0'] -= 7;
            for (int k : {-1, 0, 1}) {
                for (int l : {-1, 0, 1}) {
                    if (k == 0 && l == 0) continue;
                    work(i, j, k, l);
                }
            }
        }
    }
    while (q--) {
        int x; cin >> x;
        cout << cnt[x] << '\n';
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}