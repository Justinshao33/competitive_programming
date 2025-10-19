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
    int n, m, k; cin >> n >> m >> k;
    vector<pair<int, int>> fire;
    rep (i, 0, k) {
        int x, y; cin >> x >> y;
        fire.push_back({x, y});
    }
    auto check = [&](int t) -> bool {
        vector<int> dic;
        dic.push_back(1);
        dic.push_back(n);
        map<int, vector<array<int, 3>>> mp;
        mp.insert({1, {}});
        mp.insert({m, {}});
        for (const auto &[x, y] : fire) {
            dic.push_back(max(1, x - t));
            dic.push_back(max(1, x - t - 1));
            dic.push_back(min(n, x + t));
            dic.push_back(min(n, x + t + 1));
        }
        sort(all(dic));
        dic.erase(unique(all(dic)), dic.end());
        auto get = [&](int x) -> int {
            return lower_bound(all(dic), x) - dic.begin();
        };
        for (const auto &[x, y] : fire) {
            mp[max(1, y - t)].push_back({get(max(1, x - t)), get(min(n, x + t)), 1});
            if (max(1, y - t) > 1 && !mp.count(y - t - 1)) mp.insert({y - t - 1, {}});
            if (y + t + 1 <= m) mp[y + t + 1].push_back({get(max(1, x - t)), get(min(n, x + t)), -1});
        }
        int sz = ssize(dic);
        vector<int> block(sz, 0);
        array<int, 4> bd{n + 1, 0, m + 1, 0};
        for (const auto &[y, vec] : mp) {
            for (const auto &[l, r, v] : vec) {
                rep (i, l, r + 1) {
                    block[i] += v;
                }
            }
            rep (i, 0, sz) if (block[i] == 0) {
                chmin(bd[0], dic[i]);
                chmax(bd[1], dic[i]);
                chmin(bd[2], y);
                chmax(bd[3], y);
            }
        }
        if (bd[1] - bd[0] > 2 * t || bd[3] - bd[2] > 2 * t) return false;
        return true;
    };
    int l = -1, r = max(n, m);
    while (r - l > 1) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid;
    }
    cout << r << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}