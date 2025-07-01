#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

int dsu[MAXN];

int find(int x) {
    return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
}

int main() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) dsu[i] = i;
    while (q--) {
        int t, u, v; cin >> t >> u >> v;
        u = find(u), v = find(v);
        if (t == 0) {
            dsu[u] = v;
        } else {
            cout << (u == v) << '\n';
        }
    }
}