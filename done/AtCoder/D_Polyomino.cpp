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

int a[3][4][4], p[4][4];

void rotate(int t) {
    int tmp[4][4];
    rep (i, 0, 4) rep (j, 0, 4) {
        tmp[i][j] = a[t][3 - j][i];
    }
    swap(a[t], tmp);
}

void solve() {
    vector<int> cnt(3, 0);
    rep (t, 0, 3) rep (i, 0, 4) rep (j, 0, 4) {
        char c; cin >> c;
        a[t][i][j] = c == '#';
        cnt[t] += c == '#';
    }
    if (accumulate(all(cnt), 0) != 16) {
        cout << "No\n";
        return;
    }
    rep (r0, 0, 4) {
        rep (r1, 0, 4) {
            rep (r2, 0, 4) {
                rep (x0, -3, 4) rep (y0, -3, 4) {
                    rep (x1, -3, 4) rep (y1, -3, 4) {
                        rep (x2, -3, 4) rep (y2, -3, 4) {
                            rep (i, 0, 4) rep (j, 0, 4) p[i][j] = 0;
                            bool ok = 1;
                            rep (i, 0, 4) rep (j, 0, 4) {
                                int ni = i + x0, nj = j + y0;
                                if (a[0][i][j] == 0 || ni < 0 || ni > 3 || nj < 0 || nj > 3) continue;
                                if (p[ni][nj] == 1) ok = 0;
                                else p[ni][nj] = 1;
                            }
                            rep (i, 0, 4) rep (j, 0, 4) {
                                int ni = i + x1, nj = j + y1;
                                if (a[1][i][j] == 0 || ni < 0 || ni > 3 || nj < 0 || nj > 3) continue;
                                if (p[ni][nj] == 1) ok = 0;
                                else p[ni][nj] = 1;
                            }
                            rep (i, 0, 4) rep (j, 0, 4) {
                                int ni = i + x2, nj = j + y2;
                                if (a[2][i][j] == 0 || ni < 0 || ni > 3 || nj < 0 || nj > 3) continue;
                                if (p[ni][nj] == 1) ok = 0;
                                else p[ni][nj] = 1;
                            }
                            rep (i, 0, 4) rep (j, 0, 4) if (p[i][j] == 0) ok = 0;
                            if (ok) {
                                cout << "Yes\n";
                                return;
                            }
                        }
                    }
                }
                rotate(2);
            }
            rotate(1);
        }
        rotate(0);
    }
    cout << "No\n";
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}