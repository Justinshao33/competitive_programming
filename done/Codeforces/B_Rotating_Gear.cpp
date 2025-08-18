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

template<class T>
struct Fenwick {
    int n;
    vector<T> a;
    Fenwick(int _n) : n(_n), a(_n) {}
    void add(int p, T x) {
        for (int i = p; i < n; i = i | (i + 1)) {
            a[i] = a[i] + x;
        }
    }
    T qry(int p) { // sum [0, p]
        T s{};
        for (int i = p; i >= 0; i = (i & (i + 1)) - 1) {
            s = s + a[i];
        }
        return s;
    }
    T qry(int l, int r) { // sum [l, r)
        return qry(r - 1) - qry(l - 1);
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

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    } 
    vector pa(n, vector<int>(17));
    vector<int> dep(n), sz(n), dfn(n);
    int cnt = 0;
    auto dfs = [&](auto self, int u, int p) -> void {
        sz[u] = 1;
        dfn[u] = cnt++;
        for (int v : adj[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            pa[v][0] = u;
            self(self, v, u);
            sz[u] += sz[v];
        }
    };
    dfs(dfs, 0, -1);
    rep (j, 1, 17) rep (i, 0, n) pa[i][j] = pa[pa[i][j - 1]][j - 1];
    vector<bool> exi(n, 1);
    Fenwick<int> danc(n + 1), dsub(n + 1), bit(n + 1), tag(n + 1);
    // 有多少祖先被刪，有多少子樹的點不連通，總共旋轉角度，牛皮標記
    // 標記：角度總和隨著時間累加，標記會打在有事件發生的時間戳，在算貢獻時就可以做很像對時間做前綴和的效果
    auto findroot = [&](int x) -> int {
        for (int i = 16; i >= 0; --i) {
            if (danc.qry(dfn[x]) == danc.qry(dfn[pa[x][i]])) 
                x = pa[x][i];
        }
        return x;
    };
    auto del = [&](int x) -> void {
        exi[x] = 0;
        // subtree(x)'s ancestor got delete
        danc.add(dfn[x] + 1, 1);
        danc.add(dfn[x] + sz[x], -1);
        // calc remain node in subtree(x)
        int rem = sz[x] - (dsub.qry(dfn[x] + sz[x] - 1) - dsub.qry(dfn[x]));
        // component's root to x's path dsub need to add rem
        // 這部分反著做差分，(dsub[end] - dsub[begin])，rem值會在begin是path上的點時被算到。
        int rt = findroot(x), val = tag.qry(dfn[x]);
        dsub.add(dfn[x], rem); // end
        // 如果rt不是根節點再差分
        if (rt) {
            rt = pa[rt][0];
            dsub.add(dfn[rt], -rem); // begin
            val -= tag.qry(dfn[rt]);
        }
        // 打上時間戳懶標
        tag.add(dfn[x], -val);
        tag.add(dfn[x] + 1, val);
    };
    auto add = [&](int x) -> void { // 大部分跟del差不多
        exi[x] = 1;
        danc.add(dfn[x] + 1, -1);
        danc.add(dfn[x] + sz[x], 1);
        int rem = sz[x] - (dsub.qry(dfn[x] + sz[x] - 1) - dsub.qry(dfn[x]));
        int rt = findroot(x), val = tag.qry(dfn[x]);
        dsub.add(dfn[x], -rem);
        if (rt) {
            rt = pa[rt][0];
            dsub.add(dfn[rt], rem);
            val -= tag.qry(dfn[rt]);
        }
        tag.add(dfn[x], -val);
        tag.add(dfn[x] + sz[x], val);
        // adjust the value in the subtree(x), by subtracting the redundant value.
        bit.add(dfn[x], -val);
        bit.add(dfn[x] + sz[x], val);
    };
    int q; cin >> q;
    while (q--) {
        int t, x; cin >> t >> x;
        x--;
        if (t == 1) {
            del(x);
        } else if (t == 2) {
            add(x);
        } else {
            int ang; cin >> ang;
            if (dep[x] & 1) ang *= -1;
            x = findroot(x);
            // add value to subtree(rt[x])
            bit.add(dfn[x], ang);
            bit.add(dfn[x] + sz[x], -ang);
            tag.add(dfn[x], ang);
            tag.add(dfn[x] + sz[x], -ang);
            cout << abs(ang) * (sz[x] - (dsub.qry(dfn[x] + sz[x] - 1) - dsub.qry(dfn[x]))) << '\n';
        }
    }
    rep (i, 0, n) if (!exi[i]) add(i);
    int ans = 0;
    rep (i, 0, n) {
        int val = (dep[i] & 1 ? -1 : 1) * bit.qry(dfn[i]);
        val = ((val % 360) + 360) % 360;
        ans += val;
    }
    cout << ans << '\n';
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    // std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}