#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
    int n, m; cin >> n >> m;
    string s, t; cin >> s >> t;
    vector<int> cnt(10, 0);
    rep (i, 0, m - 1) cnt[t[i] - '0']++;
    vector<int> take(n, -1);
    rep (i, 0, n) {
        for (int j = 9; j > s[i] - '0'; --j) {
            if (cnt[j] != 0) {
                take[i] = j;
                cnt[j]--;
                break;
            }
        }
    }
    int last = t.back() - '0';
    rep (i, 0, n) {
        if (max(s[i] - '0', take[i]) < last) {
            if (take[i] != -1) {
                set<pii> st;
                int sw = take[i];
                rep (j, i + 1, n) st.insert({j, max(s[j] - '0', take[j])});
                while (!st.empty()) {
                    auto [id, val] = *st.begin();
                    st.erase(st.begin());
                    if (val >= sw) continue;
                    swap(take[id], sw);
                    if (sw == -1) break;
                }
            }
            take[i] = last;
            rep (j, 0, n) if (take[j] != -1) {
                s[j] = (char)'0' + take[j];
            }
            cout << s << '\n';
            return;
        }
    }
    rep (i, 0, n) {
        if (max(s[i] - '0', take[i]) == last) {
            rep (j, 0, n) if (take[j] != -1) {
                s[j] = (char)'0' + take[j];
            }
            cout << s << '\n';
            return;
        }
    }
    take[n - 1] = last;
    rep (j, 0, n) if (take[j] != -1) {
        s[j] = (char)'0' + take[j];
    }
    cout << s << '\n';
    // vector<set<int>> dig(10);
    // rep (i, 0, n) {
    //     int cur = s[i] - '0';
    //     dig[cur].insert(i);
    // }
    // vector<bool> vis(n, 0);
    // rep (i, 0, m - 1) {
    //     int cur = t[i] - '0';
    //     int mi = n;
    //     rep (j, 0, cur) if (!dig[j].empty()) {
    //         chmin(mi, *dig[j].begin());
    //     }
    //     if (mi == n) {
    //         continue;
    //     } else {
    //         vis[mi] = 1;
    //         dig[s[mi] - '0'].erase(mi);
    //         s[mi] = t[i];
    //         dig[s[mi] - '0'].insert(mi);
    //     }
    // }
    // rep (i, 0, n + 1) {
    //     if (i == n) {
            
    //     }
    //     if (s[i] < t.back()) {
    //         s[i] = t.back();
    //         break;
    //     }
    // }
    // cout << s << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}