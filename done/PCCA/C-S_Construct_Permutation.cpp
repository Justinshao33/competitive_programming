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

void solve() {
    int n, M, K; cin >> n >> M >> K;
    map<int, vector<pair<int, int>>> adj;
    vector<int> p(n);
    map<int, int> it, ind;
    rep (i, 0, n) {
        cin >> p[i];
        adj[p[i]].push_back({((K - p[i] * p[i]) % M + M) % M, i});
        ind[((K - p[i] * p[i]) % M + M) % M]++;
        ind[p[i]] += 0;
    }
    vector<int> ans;
    auto dfs = [&](auto self, int u) -> void {
        for (; it[u] < adj[u].size();) {
            auto [v, id] = adj[u][it[u]++];
            self(self, v);
            ans.push_back(id);
            break;
        }
    };
    int st = ind.begin()->first;
    for (auto [k, v] : ind) {
        if (ind[st] > v) st = k;
    }
    if (ind[st] == 0) dfs(dfs, st);
    else {
        for (auto [k, v] : ind) {
            if (adj[k].size() - v == 1) {
                st = k;
                break;
            }
        }
        dfs(dfs, st);
    }
    if (ans.size() < n) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int x : ans) cout << p[x] << ' ';
    }
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