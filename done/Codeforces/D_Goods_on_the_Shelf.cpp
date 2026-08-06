#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


void solve() {
    int n; cin >> n;
    vector<int> a, c;
    map<int, int> mp;
    rep (i, 0, n) {
        int b; cin >> b;
        if (a.empty() || b != a.back()) a.push_back(b);
        c.push_back(b);
    }
    int dif = 0, cur = ssize(a) - 1;
    for (int x : a) mp[x]++;
    dif = ssize(mp) - 1;
    int mx = 0, cnt = 0;
    set<int> stt;
    for (auto [k, v] : mp) {
        chmax(mx, v);
        cnt += v >= 2;
        if (v >= 2) {
            stt.insert(k);
        }
    }
    if (mx >= 4 || cnt >= 3) {
        cout << "NO\n";
        return;
    }
    if (mx == 1) {
        cout << "YES\n";
        return;
    }
    vector<int> cand;
    rep (i, 0, n) {
        int ptr = i;
        while (ptr < n && c[i] == c[ptr]) ptr++;
        if (stt.contains(c[i])) {
            cand.push_back(i - 1);
            cand.push_back(i);
            cand.push_back(ptr);
            cand.push_back(ptr - 1);
        }
        i = ptr - 1;
    }
    // ? * n ?
    sort(all(cand));
    cand.erase(unique(all(cand)), cand.end());
    int m = ssize(cand);
    rep (i, 0, m) rep (j, i + 1, m) {
        int x = cand[i], y = cand[j];
        if (x < 0 || y >= n) continue;
        if (c[x] == c[y]) continue;
        int now = cur;
        if (x - 1 >= 0 && c[x] != c[x - 1]) now--;
        if (x + 1 < n && c[x] != c[x + 1]) now--;
        if (y - 1 >= 0 && c[y] != c[y - 1]) now--;
        if (y + 1 < n && c[y] != c[y + 1]) now--;
        swap(c[x], c[y]);
        if (x - 1 >= 0 && c[x] != c[x - 1]) now++;
        if (x + 1 < n && c[x] != c[x + 1]) now++;
        if (y - 1 >= 0 && c[y] != c[y - 1]) now++;
        if (y + 1 < n && c[y] != c[y + 1]) now++;
        if (now == dif) {
            cout << "YES\n";
            return;
        }
        swap(c[x], c[y]);
    }
    cout << "NO\n";
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}