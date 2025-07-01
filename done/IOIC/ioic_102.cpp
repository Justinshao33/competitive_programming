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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 8e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct Line {
    int m, k;
    Line() {}
    Line(int _m, int _k) : m(_m), k(_k) {}
    ll operator () (const int &x) const {
        return 1LL * m * x + k;
    }
};

// max LiChao

struct Node {
    Line line;
    int ls, rs;
    Node() {}
    Node(Line li) : ls(0), rs(0), line(li) {}
};

int root;

struct LiChao {

    vector<tuple<int, Line, int>> st;
    vector<Node> tree;
    int sz;

    LiChao (int n) : tree(n + 1), sz(0) {};

    int newnode(Line line) {
        tree[++sz] = Node(line);
        return sz;
    }

    void insert (int &pos, int l, int r, Line line, int fa) {
        if (pos == 0) {
            pos = newnode(line);
            st.pb({pos, line, fa});
            return;
        }
        auto &tr = tree[pos].line;
        if (l == r) {
            if (line(l) > tr(l)) tr = line;
            return;
        }
        int mid = (l + r) >> 1;
        if (tr(mid) < line(mid)) {
            st.pb({pos, tr, -1});
            swap(tr, line);
        }
        if (tr.m >= line.m) {
            insert(tree[pos].ls, l, mid, line, pos);
        } else {
            insert(tree[pos].rs, mid + 1, r, line, pos);
        }
    }

    ll query (int pos, int l, int r, int x) {
        if (pos == 0) return -LINF;
        if (l == r) return tree[pos].line(x);
        int mid = (l + r) >> 1;
        if (x <= mid) return max(query(tree[pos].ls, l, mid, x), tree[pos].line(x));
        else return max(query(tree[pos].rs, mid + 1, r, x), tree[pos].line(x));
    }

    void undo() {
        auto [pos, line, fa] = st.back();
        st.pop_back();
        if (fa == -1) {
            tree[pos].line = line;
        } else {
            tree[pos] = Node(Line());
            if (pos == tree[fa].ls) tree[fa].ls = 0;
            else tree[fa].rs = 0;
            sz--;
            if (sz == 0) root = 0;
        }
    }

} node(MAXN);

vector<Line> tree[MAXN << 2];
vector<pii> que;

void mod(int pos, int l, int r, int ml, int mr, Line line) {
    if (ml <= l && mr >= r) {
        tree[pos].pb(line);
        return;
    }
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr, line);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, line);
}
 
void dfs(int pos, int l, int r) {
    int sz = node.st.size();
    for (Line li : tree[pos]) {
        node.insert(root, 0, IINF, li, 0);
    }
    if (l == r) {
        if (que[l].se == IINF && que[l].fi != IINF) {
            if (root == 0) {
                cout << "double is good at problem setting\n";
            } else {
                cout << node.query(root, 0, IINF, que[l].fi) << '\n';
            }
        }
    } else {
        int mid = l + r >> 1;
        dfs(lpos, l, mid);
        dfs(rpos, mid + 1, r);
    }
    while(node.st.size() > sz) {
        node.undo();
    }
}

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
#define PU(x) vi[p3++] = x

const int BUF_SIZE = 1 << 16;
static char buf[BUF_SIZE], vi[10], *p1 = buf, *p2 = buf;
static int p3;
inline int in() {int re = 0, f = 1; char c = GU; while (c == ' ' || c == '\n') {c = GU;} if (c == '-') {f = -1, c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return f * re;}
inline void out(int x) {char str[10]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];} write(1, vi, p3);}

void solve() {
    int n = in();
    que.pb({-1, -1});
    bitset<MAXN> vis;
    vector<int> id;
    rep (i, 1, n + 1) {
        int t = in();
        if (t == 1) {
            int a = in(), b = in();
            id.pb(i);
            que.pb({a, b});
        } else if (t == 2) {
            int x = in();
            vis[id[x]] = 1;
            que.pb({IINF, IINF});
            mod(1, 1, n, id[x], i - 1, Line(que[id[x]].fi, que[id[x]].se));
        } else {
            int x = in();
            que.pb({x, IINF});
        }
    }
    rep (i, 1, n + 1) if (!vis[i] && que[i].se != IINF) mod(1, 1, n, i, n, Line(que[i].fi, que[i].se));
    dfs(1, 1, n);
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}