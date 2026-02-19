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

const int C = 1e7 + 5;

int mo[C], lp[C], phi[C], isp[C]; 
vector<int> prime;

void sieve() {
    mo[1] = phi[1] = 1;
    rep (i, 1, C) lp[i] = 1;
    rep (i, 2, C) {
        if (lp[i] == 1) {
            lp[i] = i;
            prime.pb(i);
            isp[i] = 1;
            mo[i] = -1;
            phi[i] = i - 1;
        }
        for (int p : prime) {
            if (i * p >= C) break;
            lp[i * p] = p;
            if (i % p == 0) {
                phi[p * i] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
            mo[i * p] = mo[i] * mo[p];
        }
    }
}

int mx[C], smx[C];

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> vis;
    rep (i, 0, n) {
        cin >> a[i];
        int x = a[i];
        while (x > 1) {
            int p = lp[x], cnt = 0;
            while (x % p == 0) {
                cnt++;
                x /= p;
            }
            if (mx[p] == -1) mx[p] = cnt;
            else if (cnt > mx[p]) {
                smx[p] = mx[p];
                mx[p] = cnt;
            } else if (cnt > smx[p]) {
                smx[p] = cnt;
            }
            vis.push_back(p);
        }
    }
    sort(all(vis));
    vis.erase(unique(all(vis)), vis.end());
    int LCM = 1;
    for (int x : vis) LCM = LCM * fpow(x, mx[x], MOD) % MOD;
    rep (i, 0, n) {
        int x = a[i];
        int ans = LCM;
        while (x > 1) {
            int p = lp[x], cnt = 0;
            while (x % p == 0) {
                cnt++;
                x /= p;
            }
            if (mx[p] == cnt) {
                if (smx[p] == -1) {
                    ans *= fpow(fpow(p, mx[p], MOD), MOD - 2, MOD);
                } else {
                    ans *= fpow(fpow(p, mx[p] - smx[p], MOD), MOD - 2, MOD);
                }
                ans %= MOD;
            }
        }
        cout << ans << " \n" [i == n - 1];
    }
    for (int x : vis) mx[x] = smx[x] = -1;
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    sieve();
    while (T--) {
        solve();
    }
}