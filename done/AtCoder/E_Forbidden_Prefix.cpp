// #ifdef LOCAL
// #define _GLIBCXX_DEBUG 1
// #endif
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
 
const int MAXN = 5e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

int trie[MAXN * 12][26], trie2[MAXN * 12][26];
int cnt[MAXN * 26];
int id = 0, id2 = 0;

set<int> who[MAXN * 26];

void insert(string s) {
    int cur = 0;
    for (char c : s) {
        c -= 'a';
        if (!trie[cur][c]) trie[cur][c] = ++id;
        cur = trie[cur][c];
    }
    cnt[cur]++;
}

void insert2(string s, int i) {
    int cur = 0;
    for (char c : s) {
        c -= 'a';
        if (!trie2[cur][c]) trie2[cur][c] = ++id2;
        cur = trie2[cur][c];
        who[cur].insert(i);
    }
}

void remove(string s, int i) {
    int cur = 0;
    for (char c : s) {
        c -= 'a';
        if (!trie2[cur][c]) trie2[cur][c] = ++id2;
        cur = trie2[cur][c];
        if (who[cur].contains(i)) who[cur].erase(i);
    }
}

int query(string s) {
    int cur = 0, res = 0;
    for (char c : s) {
        c -= 'a';
        if (!trie[cur][c]) break;
        cur = trie[cur][c];
        res += cnt[cur];
    }
    return res;
}

set<int> query2(string s) {
    set<int> st;
    int cur = 0;
    for (char c : s) {
        c -= 'a';
        if (!trie2[cur][c]) return st;
        cur = trie2[cur][c];
    }
    return who[cur];
}

void solve() {
    int q; cin >> q;
    set<int> st;
    vector<string> ss;
    rep (i, 0, q) {
        int t; cin >> t;
        string s; cin >> s;
        ss.pb(s);
        if (t == 1) {
            insert(s);
            auto v = query2(s);
            for (int x : v) {
                if (st.contains(x)) st.erase(x);
                remove(ss[x], x);
            }
        } else {
            int res = query(s);
            if (res == 0) {
                st.insert(i);
                insert2(s, i);
            }
        }
        cout << st.size() << '\n';
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