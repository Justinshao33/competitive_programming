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

const int N = 52 * 52 * 52;

void solve() {
    int n; cin >> n;
    vector<vector<pii>> adj(N);
    vector<int> ind(N, 0);
    rep (i, 0, n) {
        string s; cin >> s;
        int m = s.size();
        int head = 0, tail = 0;
        rep (j, 0, 3) {
            if (islower(s[j])) head = head * 52 + (s[j] - 'a' + 26);
            else head = head * 52 + (s[j] - 'A');
        }
        rep (j, m - 3, m) {
            if (islower(s[j])) tail = tail * 52 + (s[j] - 'a' + 26);
            else tail = tail * 52 + (s[j] - 'A');
        }
        adj[tail].pb({head, i});
        ind[head]++;
    }
    vector<int> ans(n, -1), stat(N, -1);
    queue<int> q;
    rep (i, 0, N) if (!ind[i]) {
        q.push(i);
        stat[i] = 1;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, i] : adj[u]) {
            ans[i] = stat[u];
            if (stat[v] == -1) {
                ind[v]--;
                if (stat[u] == 1) {
                    stat[v] = 0;
                    q.push(v);
                } else if (ind[v] == 0) {
                    stat[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    rep (i, 0, n) {
        if (ans[i] == -1) cout << "Draw\n";
        if (ans[i] == 0) cout << "Aoki\n";
        if (ans[i] == 1) cout << "Takahashi\n";
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