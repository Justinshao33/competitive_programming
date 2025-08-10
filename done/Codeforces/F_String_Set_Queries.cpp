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
 
const int MAXN = 3e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

struct ACM {
    int idx = 0;
    vector<array<int, 26>> tr;
    vector<int> cnt, fail, id;
    
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

    void insert(string &s, int i) {
        int u = 0;
        id.push_back(i);
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
                    cnt[tr[u][i]] += cnt[fail[tr[u][i]]];
                    q.push(tr[u][i]);
                } else {
                    tr[u][i] = tr[fail[u]][i];
                }
            }
        }
    }

    int query(string &s) {
        int u = 0, res = 0;
        for (char c : s) {
            c -= 'a';
            u = tr[u][c];
            res += cnt[u];
        }
        return res;
    }
};

string s[MAXN];

struct ACM2 {
    vector<ACM> st;
    
    void insert(int id) {
        vector<int> str;
        str.push_back(id);
        while (!st.empty() && ssize(st.back().id) == ssize(str)) {
            str.insert(str.end(), all(st.back().id));
            st.pop_back();
        }
        ACM acm;
        for (int x : str) acm.insert(s[x], x);
        acm.build();
        st.push_back(acm);
    }

    int query(int id) {
        int res = 0;
        for (ACM &acm : st) res += acm.query(s[id]);
        return res;
    }
};

void solve() {
    ACM2 add, del;
    int q, cnt = 0; cin >> q;
    while (q--) {
        int t; cin >> t;
        cin >> s[cnt];
        if (t == 1) add.insert(cnt); 
        else if (t == 2) del.insert(cnt);
        else cout << add.query(cnt) - del.query(cnt) << endl;
        cnt++;
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