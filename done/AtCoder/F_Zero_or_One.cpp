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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    ll N; cin >> N;
    int ans = 0;
    // 10^3 ^ 6 = 10^18
    // 1000000
    // 5 4 3 2 1 0
    // 2^6
    auto check = [&](ll b) -> bool {
        ll n = N;
        while (n) {
            if (n % b > 1) return false;
            n /= b;
        }
        return true;
    };
    rep (i, 2, min(N + 1, 1001LL)) ans += check(i);
    if (N <= 1000) {
        cout << ans << '\n';
        return;
    }
    rep (bit, 1, 1 << 7) {
        // binary search
        auto check2 = [&](ll b) -> bool {
            __int128 num = 0;
            rep (i, 0, 7) if (bit >> i & 1) {
                __int128 mul = 1;
                rep (j, 0, i) {
                    mul *= b;
                    if (mul > N) return false;
                }
                num += mul;
                if (num > N) return false;
            }
            return true;
        };
        ll l = 1001, r = N + 1;
        while (r - l > 1) {
            ll mid = l + r >> 1;
            if (check2(mid)) l = mid;
            else r = mid;
        }
        __int128 num = 0;
        bool f = 1;
        rep (i, 0, 7) if (bit >> i & 1) {
            __int128 mul = 1;
            rep (j, 0, i) {
                mul *= l;
                if (mul > N) {
                    f = 0;
                    break;
                }
            }
            if (!f) break;
            num += mul;
            if (num > N) {
                f = 0;
                break;
            }
        }
        ans += (f && num == N);
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}