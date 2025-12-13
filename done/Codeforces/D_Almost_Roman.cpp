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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<vector<array<int, 3>>> que(n + 1);
    rep (i, 0, q) {
        int x, v, I; cin >> x >> v >> I;
        que[I].push_back({x, v, i});
    }
    int sub = 0, sub2 = 0, sub3 = 0, sub4 = 0, sub5 = 0;
    vector<bool> no(n, 0);
    rep (i, 1, n - 1) if (s[i - 1] == 'I' && s[i] == '?' && (s[i + 1] == 'V' || s[i + 1] == 'X')) {
        no[i] = 1;
        sub3++;
    }
    rep (i, 0, n - 1) if (!no[i]) {
        if (s[i] == '?' && (s[i + 1] == 'V' || s[i + 1] == 'X')) {
            sub++;
            no[i] = 1;
        }
    }
    rep (i, 1, n) if (!no[i]) {
        if (s[i] == '?' && s[i - 1] == 'I') {
            sub2++;
            no[i] = 1;
        }
    }
    rep (i, 0, n) if (!no[i] && s[i] == '?') {
        int ptr = i;
        while (ptr < n && s[ptr] == '?' && !no[ptr]) ptr++;
        int len = ptr - i;
        sub4 += len / 2;
        sub5 += len % 2;
        i = ptr;
    }
    int ori = 0;
    rep (i, 0, n) {
        if (s[i] == '?') continue;
        if (s[i] == 'I') {
            if (i != n - 1 && (s[i + 1] == 'V' || s[i + 1] == 'X')) ori--;
            else ori++;
        } else if (s[i] == 'V') {
            ori += 5;
        } else {
            ori += 10;
        }
    }
    // ?V / I? / I?V / ????? / rest
    // debug(sub, sub2, sub3, sub4, sub5);
    // debug(ori);
    vector<int> ans(q, 0);
    rep (i, 0, n + 1) {
        for (auto [x, v, id] : que[i]) {
            int res = ori - sub3 * 2;
            int tot = sub + sub2 + sub3 + sub4 * 2 + sub5;
            int nono = i + x + v - tot;
            int mn = min(nono, x);
            x -= mn;
            nono -= mn;
            mn = min(nono, v);
            v -= mn;
            nono -= mn;
            int ri = i;
            mn = min(nono, i);
            ri -= mn;
            nono -= mn;
            assert(nono == 0);
            // debug(ri, v, x);
            res += ri + v * 5 + x * 10;
            // debug(res);
            res -= 2 * (min(ri, sub) + min(v + x, sub2) + min(sub4, min(max(0, ri - sub), max(0, v + x - sub2))));
            ans[id] = res;
        }
    }
    rep (i, 0, q) cout << ans[i] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}