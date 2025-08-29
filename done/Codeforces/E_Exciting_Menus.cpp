#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define int i64
#define all(a) begin(a), end(a)
#define rep(a, b, c) for (int a = b; a < c; a++) 

const int MOD = 1e9 + 7;

template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

struct ACM {
    int idx = 0;
    vector<array<int, 26>> tr;
    vector<int> cnt, fail, dep, mx, ind;
    
    void clear() {
        tr.resize(1, array<int, 26>{});
        cnt.resize(1, 0);
        dep.resize(1, 0);
        fail.resize(1, 0);
        mx.resize(1, 0);
        ind.resize(1, 0);
    }
 
    ACM() {
        clear();
    }
 
    int newnode() {
        tr.push_back(array<int, 26>{});
        cnt.push_back(0);
        fail.push_back(0);
        dep.push_back(0);
        mx.push_back(0);
        ind.push_back(0);
        return ++idx;
    }
 
    void insert(string &s, vector<int> &a) {
        int u = 0;
        for (char c : s) {
            c -= 'a';
            if (tr[u][c] == 0) tr[u][c] = newnode();
            dep[tr[u][c]] = dep[u] + 1; 
            u = tr[u][c];
            cnt[u]++;
            chmax(mx[u], a[dep[u] - 1]);
        }
    }
 
    void build() {
        queue<int> q;
        rep (i, 0, 26) if (tr[0][i]) q.push(tr[0][i]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            rep (i, 0, 26) {
                if (tr[u][i]) {
                    fail[tr[u][i]] = tr[fail[u]][i];
                    ind[fail[tr[u][i]]]++;
                    q.push(tr[u][i]);
                } else {
                    tr[u][i] = tr[fail[u]][i];
                }
            }
        }
    }

    int query() {
        int ans = 0;
        queue<int> q;
        rep (i, 0, idx + 1) if (!ind[i]) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            chmax(ans, dep[u] * cnt[u] * mx[u]);
            chmax(mx[fail[u]], mx[u]);
            ind[fail[u]]--;
            if (!ind[fail[u]]) q.push(fail[u]);
        }
        return ans;
    }
};

void solve() {
    int n; cin >> n;
    ACM ac;
    vector<string> s(n);
    rep (i, 0, n) cin >> s[i];
    rep (i, 0, n) {
        vector<int> b;
        rep (j, 0, ssize(s[i])) {
            int c; cin >> c;
            b.push_back(c);
        }
        ac.insert(s[i], b);
    }
    ac.build();
    cout << ac.query() << '\n';
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("exciting.in", "r", stdin);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}