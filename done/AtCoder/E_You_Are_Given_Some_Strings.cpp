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

struct ACM {
    int idx = 0;
    vector<array<int, 26>> tr;
    vector<int> cnt, fail;
    
    void clear() {
        tr.resize(1, array<int, 26>{});
        cnt.resize(1, 0);
        fail.resize(1, 0);
    }

    ACM() {
        clear();
    }

    int newnode() {
        tr.push_back(array<int, 26>{});
        cnt.push_back(0);
        fail.push_back(0);
        return ++idx;
    }

    void insert(string &s) {
        int u = 0;
        for (char c : s) {
            c -= 'a';
            if (tr[u][c] == 0) tr[u][c] = newnode();
            u = tr[u][c];
        }
        cnt[u]++;
    }

    void build() {
        queue<int> q;
        rep (i, 0, 26) if (tr[0][i]) q.push(tr[0][i]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            rep (i, 0, 26) {
                if (tr[u][i]) {
                    fail[tr[u][i]] = tr[fail[u]][i];
                    cnt[tr[u][i]] += cnt[fail[tr[u][i]] ];
                    q.push(tr[u][i]);
                } else {
                    tr[u][i] = tr[fail[u]][i];
                }
            }
        }
    }

    vector<int> query(string &s) {
        vector<int> res(ssize(s));
        int u = 0;
        for (int i = 0; char c : s) {
            c -= 'a';
            u = tr[u][c];
            res[i] += cnt[u];
            i++;
        }
        return res;
    }
};

void solve() {
    string t; cin >> t;
    ACM ac, ac2;
    int n; cin >> n;
    rep (i, 0, n) {
        string s; cin >> s;
        ac.insert(s);
        reverse(all(s));
        ac2.insert(s);
    }
    ac.build();
    ac2.build();
    auto a = ac.query(t);
    reverse(all(t));
    auto b = ac2.query(t);
    reverse(all(b));
    int ans = 0;
    rep (i, 0, ssize(t) - 1) {
        ans += a[i] * b[i + 1];
    }
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}