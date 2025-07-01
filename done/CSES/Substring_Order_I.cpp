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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

int buc[MAXN], r1[MAXN], sa[MAXN], r2[MAXN], n, m, lcp[MAXN];
int *rk = r1, *tmp = r2;
string s;

inline void Rsort() {
    rep (i, 0, m + 1) buc[i] = 0;
    rep (i, 1, n + 1) buc[rk[tmp[i]]]++;
    rep (i, 1, m + 1) buc[i] += buc[i - 1];
    for (int i = n; i > 0; --i) sa[buc[rk[tmp[i]]]--] = tmp[i];
}

inline void SA() {
    rep (i, 0, n) {
        rk[i + 1] = s[i];
        tmp[i + 1] = i + 1;
    }
    Rsort();
    for (int len = 1; len <= n; len <<= 1) {
        int cnt = 0;
        rep (i, n - len + 1, n + 1) tmp[++cnt] = i;
        rep (i, 1, n + 1) if (sa[i] > len) tmp[++cnt] = sa[i] - len;
        Rsort();
        swap(rk, tmp);
        rk[sa[1]] = 1;
        cnt = 1;
        rep (i, 2, n + 1) 
            rk[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + len] == tmp[sa[i - 1] + len]) ? cnt : ++cnt;  
        if (cnt == n) break;
        m = cnt;
    }
} 

inline void get_lcp() {
    int k = 0;
    rep (i, 1, n + 1) rk[sa[i]] = i;
    rep (i, 1, n + 1) {
        if (rk[i] == 1) continue;
        k = max(0, k - 1);
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k - 1] == s[j + k - 1]) k++;
        lcp[rk[i]] = k;
    }
}

void solve() {
    cin >> s;
    n = s.size();
    m = 122;
    SA();
    get_lcp();
    // rep (i, 1, n + 1) cout << sa[i] << ' ' << lcp[i] << "\n";
    ll k; cin >> k;
    rep (i, 1, n + 1) {
        if (k > n - sa[i] - lcp[i] + 1) k -= n - sa[i] - lcp[i] + 1;
        else {
            // cout << sa[i] << ' ' << lcp[i] << ' ' << k << '\n';
            cout << s.substr(sa[i] - 1, k + lcp[i]);
            break;
        }
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}