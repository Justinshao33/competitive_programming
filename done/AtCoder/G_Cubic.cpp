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
 
const int MAXN = 1e6 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 500;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
#define PU(x) vi[p3++] = x

const int BUF_SIZE = 1 << 16;
static char buf[BUF_SIZE], vi[10], *p1 = buf, *p2 = buf;
static int p3;
inline int in() {int re = 0, f = 1; char c = GU; while (c == ' ' || c == '\n') {c = GU;} if (c == '-') {f = -1, c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return f * re;}
inline void out(int x) {char str[10]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];} write(1, vi, p3);}

int lp[MAXN], cnt[MAXN];

void solve() {
    int n = in(), q = in();
    vector<int> a(n);
    rep (i, 0, n) a[i] = in();
    vector<array<int, 3>> que(q);
    rep (i, 0, q) {
        int l = in(), r = in();
        l--;
        que[i] = {l, r, i};
    }
    sort(all(que), [&](auto x, auto y) {
        if (x[0] / B != y[0] / B) return x[0] < y[0];
        return (x[0] / B) & 1 ? x[1] < y[1] : x[1] > y[1];
    });
    vector<int> prime;
    rep (i, 1, MAXN) lp[i] = 1;
    rep (i, 2, MAXN) {
        if (lp[i] == 1) lp[i] = i, prime.pb(i);
        for (int p : prime) {
            if (i * p >= MAXN) break;
            lp[i * p] = p;
            if (p == lp[i]) break;
        }
    }
    vector<vector<pii>> div(n);
    rep (i, 0, n) {
        while (a[i] > 1) {
            int d = lp[a[i]];
            div[i].pb({d, 0});
            while (a[i] % d == 0) {
                a[i] /= d;
                div[i].back().S++;
            }
            div[i].back().S %= 3;
        }
    }
    vector<bool> ans(q);
    int L = 0, R = 0, no = 0;
    auto add = [&](int x) -> void {
        for (auto [d, c] : div[x]) {
            bool f = cnt[d] == 0;
            cnt[d] = (cnt[d] + c) % 3;
            if (f && cnt[d]) no++;
            if (!f && cnt[d] == 0) no--;
        }
    };
    auto sub = [&](int x) -> void {
        for (auto [d, c] : div[x]) {
            bool f = cnt[d] == 0;
            cnt[d] = (cnt[d] - c + 3) % 3;
            if (f && cnt[d]) no++;
            if (!f && cnt[d] == 0) no--;
        }
    };
    for (auto [l, r, id] : que) {
        while (L > l) add(--L);
        while (R < r) add(R++);
        while (R > r) sub(--R);
        while (L < l) sub(L++);
        ans[id] = (no == 0);
    }
    rep (i, 0, q) cout << (ans[i] ? "Yes\n" : "No\n");
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}