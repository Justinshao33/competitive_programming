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
 
const int MAXN = 5e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

ll tree[MAXN << 2], tag[MAXN << 2];

void upd(int pos, int l, int r, ll val) {
    tree[pos] += val * (r - l + 1);
    tag[pos] += val;
}

void push(int pos, int l, int r) {
    if (tag[pos]) {
        int mid = l + r >> 1;
        upd(lpos, l, mid, tag[pos]);
        upd(rpos, mid + 1, r, tag[pos]);
        tag[pos] = 0;
    }
}

void pull(int pos) {
    tree[pos] = tree[lpos] + tree[rpos]; 
}

void mod(int pos, int l, int r, int ml, int mr, ll val) {
    if (ml <= l && mr >= r) {
        upd(pos, l, r, val);
        return;
    }
    push(pos, l, r);
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr, val);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, val);
    pull(pos);
}

ll query(int pos, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) return tree[pos];
    push(pos, l, r);
    int mid = l + r >> 1;
    ll res = 0;
    if (ql <= mid) res += query(lpos, l, mid, ql, qr);
    if (qr > mid) res += query(rpos, mid + 1, r, ql, qr);
    return res;
}

int a[500005], ind[500005], pre[500005];
ll TAG[500005], ans[500005];
pii q[500005];
bool cmp(pii x, pii y){
    return x.second < y.second;
}
void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        q[i - 1] = {ind[a[i]], i};
        pre[i] = ind[a[i]];
        ind[a[i]] = i;
    }
    sort(q, q + n, cmp);
    //for(int i = 0; i < n; i++) printf("%d %d\n", q[i].first, q[i].second);
    //for(int i = 1; i <= n; i++) printf("%d ", pre[i]);
    //printf("\n");
    int R = 0;
    for(int i = 0; i < n; i++){
        auto [l, r] = q[i];
        while(R < r){
            R++;
            if(pre[R]) mod(1, 1, n, pre[R], pre[R], -1);
            mod(1, 1, n, R, R, 1);
        }
        int tmp = query(1, 1, n, l, r);
        TAG[tmp - 1]++;
        //printf("%d\n", tmp);
    }
    for(int i = m; i >= 1; i--){
        ans[i] += TAG[i] + ans[i + 1];
    }
    for(int i = 1; i <= m; i++) printf("%lld ", ans[i]);
}
 
int main() {
    //ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}