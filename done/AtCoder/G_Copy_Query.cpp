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

#define chmax(a, b) a = (a) > (b) ? (a) : (b)
#define chmin(a, b) a = (a) < (b) ? (a) : (b)

#define lpos pos << 1
#define rpos pos << 1 | 1

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename A> ostream& operator << (ostream &os, const vector<A> &p) { for(const auto &a : p) os << a << " "; os << '\n'; return os; }

const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int n){ return uniform_int_distribution<int>(0, n)(rng); }

ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

int L[MAXN << 5], R[MAXN << 5], a[MAXN], cnt = 0;
ll tree[MAXN << 5];

void pull(int v){
    tree[v] = tree[L[v]] + tree[R[v]];
}

int build(int l, int r){
    int root = ++cnt;
    if(l == r){
        tree[root] = a[l];
        return root;
    }
    int mid = (l + r) >> 1;
    L[root] = build(l, mid);
    R[root] = build(mid + 1, r);
    pull(root);
    return root;
}

int mod(int pre, int l, int r, int idx, int val) {
    int root = ++cnt;
    L[root] = L[pre], R[root] = R[pre], tree[root] = tree[pre];
    if(l == r){
        tree[root] = val;
        return root;
    }
    int mid = (l + r) >> 1;
    if(idx <= mid) L[root] = mod(L[pre], l, mid, idx, val);
    else R[root] = mod(R[pre], mid + 1, r, idx, val);
    pull(root);
    return root;
}

ll query(int v, int l, int r, int ql, int qr) {
    if(l == ql && r == qr) return tree[v];
    int mid = (l + r) >> 1;
    if(qr <= mid) return query(L[v], l, mid, ql, qr);
    else if(ql > mid) return query(R[v], mid + 1, r, ql, qr);
    else return query(L[v], l, mid, ql, mid) + query(R[v], mid + 1, r, mid + 1, qr);
}

int main(){
    ZTMYACANESOCUTE;
    int n, m, q; cin >> n >> m >> q;
    vector<int> T(n + 1);
    T.pb(0);
    T[0] = build(1, n);
    while (q--) {
        int t; cin >> t;
        if (t == 1){
            int x, y; cin >> x >> y;
            T[x] = T[y];
        }
        else if (t == 2) {
            int x, y, z; cin >> x >> y >> z;
            T[x] = mod(T[x], 1, m, y, z);
        }
        else{
            int x, l, r; cin >> x >> l >> r;
            cout << query(T[x], 1, m, l, r) << '\n';
        }
    }
}
