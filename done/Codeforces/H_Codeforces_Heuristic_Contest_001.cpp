#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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


void solve() {
    int n; cin >> n;
    vector<array<int, 6>> tri;
    // vector tmp(5, vector<int>(9, 0));
    // auto col = tmp;
    // bool f = 0;
    // auto dfs = [&](auto self, int id) -> void {
    //     if (f) return;
    //     if (id == 15) {
    //         col = tmp;
    //         f = 1;
    //         return;
    //     } 
    //     debug(id);
    //     id++;
    //     rep (i, 0, 5) rep (j, 0, 9) if (tmp[i][j] == 0) {
    //         if (j + 1 < 9 && i + 1 < 5 && tmp[i][j] == 0 && tmp[i + 1][j] == 0 && tmp[i][j + 1] == 0) {
    //             tmp[i][j] = tmp[i + 1][j] = tmp[i][j + 1] = id;
    //             self(self, id);
    //             tmp[i][j] = tmp[i + 1][j] = tmp[i][j + 1] = 0;
    //         }
    //         if (j + 1 < 9 && i + 1 < 5 && tmp[i][j] == 0 && tmp[i + 1][j] == 0 && tmp[i + 1][j + 1] == 0) {
    //             tmp[i][j] = tmp[i + 1][j] = tmp[i + 1][j + 1] = id;
    //             self(self, id);
    //             tmp[i][j] = tmp[i + 1][j] = tmp[i + 1][j + 1] = 0;
    //         }
    //         if (j + 1 < 9 && i + 1 < 5 && tmp[i][j] == 0 && tmp[i][j + 1] == 0 && tmp[i + 1][j + 1] == 0) {
    //             tmp[i][j] = tmp[i][j + 1] = tmp[i + 1][j + 1] = id;
    //             self(self, id);
    //             tmp[i][j] = tmp[i][j + 1] = tmp[i + 1][j + 1] = 0;
    //         }
    //         if (j - 1 >= 0 && i + 1 < 5 && tmp[i][j] == 0 && tmp[i + 1][j] == 0 && tmp[i + 1][j - 1] == 0) {
    //             tmp[i][j] = tmp[i + 1][j] = tmp[i + 1][j - 1] = id;
    //             self(self, id);
    //             tmp[i][j] = tmp[i + 1][j] = tmp[i + 1][j - 1] = 0;
    //         }
    //     }
    // };
    // dfs(dfs, 0);
    // rep (i, 0, 5) rep (j, 0, 9) cout << col[i][j] << " \n"[j == 8];
    if (n == 1) {
        tri.push_back({1, 1, 1, 2, 2, 1});
        tri.push_back({2, 3, 3, 2, 3, 3});
    } else if (n % 2 == 0) {
        for (int i = 1; i <= 3 * n; i += 2) {
            for (int j = 1; j <= 3 * n; j += 3) {
                tri.push_back({i, j, i + 1, j, i, j + 1});
                tri.push_back({i + 1, j + 2, i + 1, j + 1, i, j + 2});
            }
        }
    } else {
        auto dfs = [&](auto self, int x, int y) -> void {
            if (x == 9 && y == 9) {
                for (int i = 3 * n - x + 1; i <= 3 * n; i += 2) {
                    if (i + 4 == 3 * n) {
                        for (int j = 3 * n - y + 1; j <= 3 * n; j += 9) {
                            tri.push_back({i, j, i + 1, j, i, j + 1});
                            tri.push_back({i, j + 2, i + 1, j + 1, i + 1, j + 2});
                            tri.push_back({i, j + 3, i + 1, j + 3, i, j + 4});
                            tri.push_back({i, j + 5, i + 1, j + 5, i, j + 6});
                            tri.push_back({i, j + 7, i, j + 8, i + 1, j + 8});
                            tri.push_back({i + 1, j + 4, i + 2, j + 4, i + 2, j + 5});
                            tri.push_back({i + 1, j + 6, i + 2, j + 6, i + 1, j + 7});
                            tri.push_back({i + 2, j, i + 3, j, i + 2, j + 1});
                            tri.push_back({i + 2, j + 2, i + 3, j + 2, i + 2, j + 3});
                            tri.push_back({i + 2, j + 7, i + 2, j + 8, i + 3, j + 8});
                            tri.push_back({i + 3, j + 5, i + 3, j + 6, i + 4, j + 6});
                            tri.push_back({i + 3, j + 4, i + 4, j + 4, i + 4, j + 5});
                            tri.push_back({i + 3, j + 7, i + 4, j + 7, i + 4, j + 8});
                            tri.push_back({i + 4, j + 2, i + 3, j + 3, i + 4, j + 3});
                            tri.push_back({i + 4, j, i + 4, j + 1, i + 3, j + 1});
                        }
                        break;
                    } else {
                        for (int j = 3 * n - y + 1; j <= 3 * n; j += 3) {
                            tri.push_back({i, j, i + 1, j, i, j + 1});
                            tri.push_back({i + 1, j + 2, i + 1, j + 1, i, j + 2});
                        }
                    }
                }
                return;
            }
            if (x > y) {
                for (int i = 3 * n - x + 1; i <= 3 * n - (x - 6); i += 2) {
                    for (int j = 3 * n - y + 1; j <= 3 * n; j += 3) {
                        tri.push_back({i, j, i + 1, j, i, j + 1});
                        tri.push_back({i + 1, j + 2, i + 1, j + 1, i, j + 2});
                    }
                }
                self(self, x - 6, y);
            } else {
                for (int i = 3 * n - y + 1; i <= 3 * n - (y - 6); i += 2) {
                    for (int j = 3 * n - x + 1; j <= 3 * n; j += 3) {
                        tri.push_back({i, j, i + 1, j, i, j + 1});
                        for (int k = 0; k < 6; k += 2) swap(tri.back()[k], tri.back()[k + 1]);
                        tri.push_back({i + 1, j + 2, i + 1, j + 1, i, j + 2});
                        for (int k = 0; k < 6; k += 2) swap(tri.back()[k], tri.back()[k + 1]);
                    }
                }
                self(self, x, y - 6);
            }
        };
        dfs(dfs, 3 * n, 3 * n);
    }
    cout << ssize(tri) << '\n';
    // vector col(5, vector<int>(9));
    // for (int i = ssize(tri) - 15; i < ssize(tri); i++) {
    //     for (int j = 0; j < 6; j += 2) {
    //         // debug(tri[i][j], tri[i][j + 1]);
    //         col[tri[i][j] - 5][tri[i][j + 1] - 1] = i;
    //     }
    // }
    // rep (i, 0, 5) rep (j, 0, 9) cout << col[i][j] << " \n" [j == 8];
    for (auto t : tri) rep (j, 0, 6) cout << t[j] << " \n" [j == 5];
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}