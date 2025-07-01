/* ProbId: D2-C-Optimal-RMQ */
#include<bits/stdc++.h>
using namespace std;
using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
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

int len;
const int B = 9;

struct SparseTable{
    vector<vector<pii>> sp;
    SparseTable() {}
    SparseTable(vector<pii> &a) {
        int n = a.size();
        sp.resize(n, vector<pii>(__lg(n) + 1));
        for (int i = n - 1; i >= 0; i--) {
            sp[i][0] = a[i];
            for (int j = 1; i + (1 << j) <= n; j++) {
                sp[i][j] = min(sp[i][j - 1], sp[i + (1 << j - 1)][j - 1]);
            }
        }
    }
    auto query(int l, int r) { // [l, r)
        if (l >= r) return pii(INT_MAX, -1);
        int k = __lg(r - l);
        return min(sp[l][k], sp[r - (1 << k)][k]);
    }
} sp;

int vis[(1 << 18) + 5], enc[4500005], cnt, mn[(1 << 18) + 5][B][B], val[40000005];

int get_hash(vector<int> &a, int k) {
    vector<int> L(k, -1), R(k, -1), st;
    int hash = 0;
    rep (i, 0, k) {
        int lst = -1;
        while (!st.empty() && a[st.back()] > a[i]) {
            lst = st.back();
            st.pop_back();
        }
        if (lst != -1) {
            L[i] = lst;
        }
        if (!st.empty()) {
            R[st.back()] = i;
        }
        st.pb(i);
    }
    auto dfs = [&](auto self, int u) -> void {
        if (L[u] != -1) self(self, L[u]);
        if (R[u] != -1) self(self, R[u]);
        hash = hash * 2 + (L[u] == -1 ? 0 : 1);
        hash = hash * 2 + (R[u] == -1 ? 0 : 1);
    };
    if (!st.empty()) dfs(dfs, st[0]);
    if (!vis[hash]) {
        vis[hash] = 1;
        rep (i, 0, k) {
            int mi = INT_MAX, pos = 0;
            rep (j, i, k) {
                if (mi > a[j]) {
                    mi = a[j];
                    pos = j;
                }
                mn[hash][i][j] = pos;
            }
        }
    }
    return hash;
}

void warm_up( int seq[], int n) {
    vector<pii> a;
    len = n;
    for (int i = 0; i < n; i += B) {
        int mi = INT_MAX, pos = i;
        vector<int> tmp;
        rep (j, i, min(n, i + B)) {
            tmp.pb(seq[j]);
            val[j] = seq[j];
            if (mi > seq[j]) {
                mi = seq[j];
                pos = j;
            }
        }
        while (tmp.size() < B) tmp.pb(INT_MAX - tmp.size());
        enc[i / B] = get_hash(tmp, tmp.size());
        a.pb({mi, pos});
    }
    sp = SparseTable(a);
}

int query( int left, int right ) {
    if (left > right || left < 0 || right >= len) return -1;
    int lb = left / B, rb = right / B;
    int l = lb * B, r = rb * B;
    if (lb == rb) return l + mn[enc[lb]][left - l][right - r];
    auto [ret, pos] = sp.query(lb + 1, rb);
    if (ret > val[l + mn[enc[lb]][left - l][B - 1]]) {
        ret = val[l + mn[enc[lb]][left - l][B - 1]];
        pos = l + mn[enc[lb]][left - l][B - 1];
    }
    if (ret > val[r + mn[enc[rb]][0][right - r]]) {
        ret = val[r + mn[enc[rb]][0][right - r]];
        pos = r + mn[enc[rb]][0][right - r];
    }
    return pos;
}

// int A[10] = { 1, 2, 3, 5, 4, 6, 8, 10, 9, 7 };
// int main() {
//     ZTMYACANESOCUTE;
//     warm_up(A,10);
//     rep (i, 0, B) rep (j, i, B) debug(i, j, mn[enc[0]][i][j]);
//     // cout << query(0, 9) << '\n';
//     cout << query(3, 9) << '\n';
//     // cout << query(1, 8) << '\n';
//     // cout << query(1, 7) << '\n';
// }