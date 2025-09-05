#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

#define int i64
#define all(a) a.begin(), a.end()
#define rep(a, b, c) for (int a = b; a < c; a++)

#ifdef PEPPA
template <typename R>
concept I = ranges::range<R> && !std::same_as<ranges::range_value_t<R>, char>;
template <typename A, typename B>
std::ostream &operator<<(std::ostream &o, const std::pair<A, B> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}
template <I T>
std::ostream &operator<<(std::ostream &o, const T &v) {
    o << "{";
    int f = 0;
    for (auto &&i : v) o << (f++ ? " " : "") << i;
    return o << "}";
}
void debug__(int c, auto &&...a) {
    std::cerr << "\e[1;" << c << "m";
    (..., (std::cerr << a << " "));
    std::cerr << "\e[0m" << std::endl;
}
#define debug_(c, x...) debug__(c, __LINE__, "[" + std::string(#x) + "]", x)
#define debug(x...) debug_(93, x)
#else
#define debug(x...) void(0)
#endif

bool chmin(auto& a, auto b) { return (b < a and (a = b, true)); }
bool chmax(auto& a, auto b) { return (a < b and (a = b, true)); }

const int MOD = 998244353, MAXN = 2005;

void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

template<class T>
struct Fenwick {
    int n;
    vector<T> a;
    Fenwick() {}
    Fenwick(int _n) : n(_n), a(_n, 0) {}
    void mod(int p, T x) {
        for (int i = p; i < n; i = i | (i + 1)) {
            add(a[i], x);
        }
    }
    T qry(int p) { // sum [0, p]
        T s = 0;
        for (int i = p; i >= 0; i = (i & (i + 1)) - 1) {
            add(s, a[i]);
        }
        return s;
    }
    T qry(int l, int r) { // sum [l, r)
        T ret = qry(r - 1) - qry(l - 1);
        if (ret < 0) ret += MOD;
        return ret;
    }
    pair<int, T> select(T k) { // [first position >= k, sum [0, p) 
        T s{};
        int p = 0;
        for (int i = 1 << __lg(n); i; i >>= 1) {
            if (p + i <= n and s + a[p + i - 1] < k) {
                p += i;
                s = s + a[p - 1];
            }
        }
        return {p, s};
    }
};

struct segtree {
    int n;
    vector<Fenwick<int>> tree;
    
    #define lpos pos << 1
    #define rpos pos << 1 | 1

    void build(int pos, int l, int r) {
        if (l == r) {
            tree[pos] = Fenwick<int>(n);
            return;
        }
        int mid = l + r >> 1;
        build(lpos, l, mid);
        build(rpos, mid + 1, r);
    }

    segtree(int n) : n(n), tree(n << 2, Fenwick<int>(n)) {
        build(1, 0, n - 1);
    }

    void mod(int pos, int l, int r, int ml, int mr, int x, int val) {
        if (ml > mr) return;
        if (ml <= l && mr >= r) {
            tree[pos].mod(x, val);
            return;
        }
        int mid = l + r >> 1;
        if (ml <= mid) mod(lpos, l, mid, ml, mr, x, val);
        if (mr > mid) mod(rpos, mid + 1, r, ml, mr, x, val);
    }

    int query(int pos, int l, int r, int id, int L, int R) {
        if (L > R) return 0;
        int res = tree[pos].qry(L, R + 1);
        if (l == r) return res;
        int mid = l + r >> 1;
        if (id <= mid) add(res, query(lpos, l, mid, id, L, R));
        else add(res, query(rpos, mid + 1, r, id, L, R));
        return res;
    }

};

void solve() {
    int n, m; cin >> n >> m;
    string s, t; cin >> s >> t;
    vector match(n, vector<bool>(n, 0));
    rep (i, 0, n) {
        for (int j = 0; i + j < n && j < m; j++) {
            if (s[i + j] == t[j]) match[i][i + j] = true;
            else break;
        }
    }
    vector<int> r(n);
    rep (i, 0, n) {
        r[i] = i - 1;
        rep (j, i, n) {
            if (match[i][j]) r[i] = j; 
            else break;
        } 
    }
    vector dp(n, vector<int> (n, 0));
    segtree tr0(n + 1), tr1(n + 1);
    rep (i, 0, n) rep (j, i - 1, n) {
        if (j < 0) continue;
        dp[i][j] = 1;
    }
    for (int i = n - 1; i >= 0; --i) rep (j, i - 1, n) {
        if (j < 0) continue;
        // rep (k, i + 1, j + 1) {
        //     add(dp[i][j][2], dp[k][j][match[i][k - 1]]);
        // }
        if (i + 1 < n) {
            add(dp[i][j], tr1.query(1, 0, n - 1, j, i + 1, r[i] + 1));
            add(dp[i][j], tr0.query(1, 0, n - 1, j, r[i] + 2, j));
        }
        // rep (k, j + 1, n) {
        //     add(dp[i][k][match[j + 1][k]], dp[i][j][2]);
        // }
        if (j + 1 < n) {
            tr1.mod(1, 0, n - 1, j + 1, r[j + 1], i, dp[i][j]);
            tr0.mod(1, 0, n - 1, r[j + 1] + 1, n - 1, i, dp[i][j]);
        }
    }
    cout << dp[0][n - 1] << '\n';
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}