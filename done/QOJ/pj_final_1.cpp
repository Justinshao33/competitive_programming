// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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
#define F first
#define S second

#ifdef LOCAL
#define ZTMYACANESOCUTE freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

void dbg() { cerr << '\n'; }
template<typename T, typename ...U>
void dbg(T t, U ...u) { cerr << t << ' '; dbg(u...); }

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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct RollingHash {
    string s;
    int n, c, mod;
    vector <long long> pre, pw;
    RollingHash(string _s, int _c, int _mod) : s(_s), n(s.size()), c(_c), mod(_mod) {
        pre.resize(n + 1, 0);
        pw.resize(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            pre[i] = ((pre[i - 1] * c) + s[i - 1]) % mod;
        }
        for (int i = 1; i <= n; ++i) {
            pw[i] = pw[i - 1] * c % mod;
        }
    }
    long long query(int l, int r) {
        return (pre[r] - ((pre[l] * pw[r - l]) % mod) + mod) % mod;
    }
};

void solve() {
    string s, p; cin >> s >> p;
    int n = s.size();
    if (count(all(p), '1') == 0) {
        cout << s << 'a' << '\n';
        return; 
    }
    int st = n - 1;
    for (int i = n - 1; i >= 0; --i) if (p[i] == '1') {
        st = i;
        break;
    }
    RollingHash h(s, get_rand(128, 512), MOD), h2(s, get_rand(128, 512), MOD2);
    int l = 0, r = n - st;
    auto check = [&](int x) -> bool {
        ll cmp = h.query(st, st + x + 1), cmp2 = h2.query(st, st + x + 1);
        rep (i, 0, n - x) if (p[i] == '1') {
            if (h.query(i, i + x + 1) != cmp || h2.query(i, i + x + 1) != cmp2) return false;
        }
        return true;
    };
    while (r - l > 1) {
        int mid = l + r >> 1;
        if (check(mid)) l = mid;
        else r = mid;
    }
    if (!check(l)) {
        cout << -1 << '\n';
        return;
    }
    l++;
    debug(l);
    vector<int> no(l + 1, 0);
    rep (i, 0, n) if (p[i] == '0') {
        if (s[i] != s[st]) continue;
        int L = 0, R = l;
        while (R - L > 1) {
            int mid = L + R >> 1;
            if (h.query(st, st + mid + 1) == h.query(i, i + mid + 1) && h2.query(st, st + mid + 1) == h2.query(i, i + mid + 1)) L = mid;
            else R = mid;
        }
        no[0]++;
        no[L + 1]--;
    }
    rep (i, 0, l) no[i + 1] += no[i];
    debug(no);
    rep (i, 0, l) if (no[i] == 0) {
        cout << s.substr(st, i + 1) << '\n';
        return;
    }
    cout << -1 << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}