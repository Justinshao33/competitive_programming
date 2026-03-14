#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define int long long

using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
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
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    string s, t; cin >> s >> t;
    bool sw = 0;
    if (ssize(s) < ssize(t)) {
        swap(s, t);
        sw = 1;
    }
    string ss = s, tt = t;
    auto calc = [&](int x, int y) -> int {
        vector<int> a(10, 0), b(10, 0);
        for (char c : ss) a[c - '0']++;
        for (char c : tt) b[c - '0']++;
        if (a[x] == 0 || b[y] == 0) return IINF;
        int res = 0, f = 0;
        s.clear();
        t.clear();
        s.push_back('0' + x);
        t.push_back('0' + y);
        a[x]--, b[y]--;
        res += (x + y) % 10;
        f = (x + y >= 10);
        while (true) {
            bool ff = 0;
            rep (i, 1, 10) if (a[i]) {
                rep (j, 1, 10) if (b[j]) {
                    if (i + j >= 10 - f) {
                        a[i]--;
                        b[j]--;
                        s.push_back('0' + i);
                        t.push_back('0' + j);
                        res += (i + j + f) % 10;
                        f = 1;
                        ff = 1;
                        break;
                    }
                }
                if (ff) break;
            }
            if (!ff) break;
        }
        for (int i = 9; i > 0; --i) {
            while (a[i]) {
                s.push_back('0' + i);
                res += (i + f) % 10;
                if (i + f >= 10) f = 1;
                else f = 0;
                a[i]--;
            }
            while (b[i]) {
                t.push_back('0' + i);
                res += (i + f) % 10;
                if (i + f >= 10) f = 1;
                else f = 0;
                b[i]--;
            }
        }
        return res + f;
    };
    string as, at;
    int ans = IINF;
    rep (i, 1, 10) rep (j, 1, 10) {
        if (chmin(ans, calc(i, j))) {
            as = s, at = t;
        }
    }
    reverse(all(as));
    reverse(all(at));
    if (sw) swap(as, at);
    cout << as << '\n' << at << '\n';
    // cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}