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

struct zvalue {
    vector<int> z;
    int operator[] (const int &x) const {
        return z[x];
    }
    zvalue(string s) {
        int n = s.size();
        z.resize(n);
        z[0] = 0;
        int l = 1, r = 0;
        rep (i, 1, n) {
            z[i] = min(z[i - l], max(0LL, r - i));
            while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
    }
};

void solve() {
    int n; cin >> n;
    vector<string> s(n);
    vector<zvalue> z;
    rep (i, 0, n) {
        cin >> s[i];
        z.push_back(zvalue(s[i]));
    }
    vector<int> p(n);
    iota(all(p), 0);
    sort(all(p), [&](int x, int y) {
        int f = 0, sx = ssize(s[x]), sy = ssize(s[y]);
        if (sx > sy) {
            swap(x, y);
            swap(sx, sy);
            f = 1;
        }
        // x < y, xy ? yx
        // xy[0,y-x-1]y[y-x,y-1] ? y[0,x-1]y[x,y-1]x
        rep (i, 0, sx) {
            if (s[x][i] != s[y][i]) {
                return (s[x][i] < s[y][i]) ^ f;
            }
        }
        if (sx != sy && z[y][sx] < sy - sx) {
            return (s[y][z[y][sx]] < s[y][sx + z[y][sx]]) ^ f;
        } 
        rep (i, 0, sx) {
            if (s[y][sy - sx + i] != s[x][i]) {
                return (s[y][sy - sx + i] < s[x][i]) ^ f;
            }
        }
        return (int)0;
    });
    auto concat = [&]() -> string {
        string ret = "";
        rep (i, 0, n) ret += s[p[i]];
        return ret;
    };
    rep (i, 0, n - 1) if (s[p[i]] + s[p[i + 1]] == s[p[i + 1]] + s[p[i]]) {
        cout << concat() << '\n';
        return;
    }
    string s1, s2;
    swap(p[n - 2], p[n - 1]);
    s1 = concat();
    if (n <= 2) cout << s1 << '\n';
    else {
        swap(p[n - 2], p[n - 1]);
        swap(p[n - 3], p[n - 2]);
        s2 = concat();
        cout << min(s1, s2) << '\n'; 
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}