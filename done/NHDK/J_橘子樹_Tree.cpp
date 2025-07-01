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
#define ld long double
#define F first
#define S second

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
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

int tree[MAXN << 2];

void mod(int pos, int l, int r, int idx, int val) {
    if (l == r) {
        tree[pos] += val;
        return;
    }
    int mid = l + r >> 1;
    if (idx <= mid) mod(lpos, l, mid, idx, val);
    else mod(rpos, mid + 1, r, idx, val);
    tree[pos] = tree[lpos] + tree[rpos];
}

int query(int pos, int l, int r, int k) {
    if (l == r) return l;
    int mid = l + r >> 1;
    if (tree[lpos] >= k) return query(lpos, l, mid, k);
    else return query(rpos, mid + 1, r, k - tree[lpos]);
}

struct info {
    int l, r, i;
};

void solve() {
    int bruh; cin >> bruh;
    int n, q; cin >> n >> q;
    vector<int> a(n), id(n);
    rep (i, 0, n) {
        cin >> a[i];
        id[i] = a[i];
    }
    sort(all(id));
    id.erase(unique(all(id)), id.end());
    rep (i, 0, n) a[i] = lower_bound(all(id), a[i]) - id.begin() + 1;
    // cout << a;
    vector<info> que;
    rep (i, 0, q) {
        int l, r; cin >> l >> r;
        l--;
        que.pb({l, r, i});
    }
    sort(all(que), [&](auto a, auto b) {
        if(a.l / B != b.l / B) return a.l < b.l;
        return (a.l / B) & 1 ? a.r < b.r : a.r > b.r;
    });
    auto add = [&](int x) -> void {
        mod(1, 1, n, x, 1);
    };
    auto sub = [&](int x) -> void {
        mod(1, 1, n, x, -1);
    };
    int L = 0, R = 0;
    int ans = 0;
    for (auto [l, r, i] : que) {
        while(R < r){
            add(a[R++]);
        }
        while(L > l){
            add(a[--L]);
        }
        while(R > r){
            sub(a[--R]);
        }
        while(L < l){
            sub(a[L++]);
        }
        // cout << query(1, 1, n, (r - l + 1) / 2) << '\n';
        ans = max(ans, id[query(1, 1, n, (r - l + 1) / 2) - 1]);
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}