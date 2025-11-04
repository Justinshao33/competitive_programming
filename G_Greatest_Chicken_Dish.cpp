#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

// #define int i64
#define all(a) begin(a), end(a)
#define rep(a, b, c) for (int a = b; a < c; a++) 

const int MOD = 1e9 + 7;

template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

template<class T>
struct SparseTable{
    function<T(T, T)> F;
    vector<vector<T>> sp;
    SparseTable(vector<T> &a, const auto &f) {
        F = f;
        int n = a.size();
        sp.resize(n, vector<T>(__lg(n) + 1));
        for (int i = n - 1; i >= 0; i--) {
            sp[i][0] = a[i];
            for (int j = 1; i + (1 << j) <= n; j++) {
                sp[i][j] = F(sp[i][j - 1], sp[i + (1 << j - 1)][j - 1]);
            }
        }
    }
    T query(int l, int r) { // [l, r)
        int k = __lg(r - l);
        return F(sp[l][k], sp[r - (1 << k)][k]);
    }
};

const int MAXN = 1e5 + 5;

i64 tree[MAXN << 2], tag[MAXN << 2];

#define lpos pos << 1
#define rpos pos << 1 | 1

void push(int pos, int l, int r) {
    if (tag[pos]) {
        int mid = l + r >> 1;
        tree[lpos] += tag[pos] * (mid - l + 1);
        tree[rpos] += tag[pos] * (r - mid);
        tag[lpos] += tag[pos];
        tag[rpos] += tag[pos];
        tag[pos] = 0;
    }
}

void mod(int pos, int l, int r, int ml, int mr, int val) {
    if (ml <= l && mr >= r) {
        tag[pos] += val;
        tree[pos] += (r - l + 1) * val;
        return;
    }
    int mid = l + r >> 1;
    push(pos, l, r);
    if (ml <= mid) mod(lpos, l, mid, ml, mr, val);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, val);
    tree[pos] = tree[lpos] + tree[rpos];
}

i64 query(int pos, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) return tree[pos];
    push(pos, l, r);
    int mid = l + r >> 1;
    i64 res = 0;
    if (ql <= mid) res += query(lpos, l, mid, ql, qr);
    if (qr > mid) res += query(rpos, mid + 1, r, ql, qr);
    return res;
}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    rep (i, 0, n) cin >> a[i];
    auto F = [&](const int x, const int y) -> int {
        return gcd(x, y);
    };
    SparseTable<int> sp(a, F);
    vector<array<int, 4>> info, info2;
    vector<int> dic;
    rep (i, 0, n) {
        int R = i;
        while (R >= 0) {
            int g = sp.query(R, i + 1);
            int l = -1, r = R;
            while (r - l > 1) {
                int mid = l + r >> 1;
                if (sp.query(mid, i + 1) == g) r = mid;
                else l = mid;
            }
            info.push_back({g, i, r, R}); // R, ml, mr
            R = r - 1;
        }
    }
    rep (i, 0, q) {
        int l, r, d; cin >> l >> r >> d;
        l--, r--;
        dic.push_back(d);
        info2.push_back({d, r, l, i});
    }
    sort(all(dic));
    dic.erase(unique(all(dic)), dic.end());
    auto get = [&](int x) -> int {
        int xx = lower_bound(all(dic), x) - dic.begin();
        if (xx >= ssize(dic) || dic[xx] != x) return -1;
        return xx;
    };
    vector<vector<array<int, 3>>> ope(ssize(dic)), que(ssize(dic));
    for (const auto &[g, i, r, R] : info) {
        int id = get(g);
        if (id == -1) continue;
        ope[id].push_back({i, r, R});
    }
    for (const auto &[d, r, l, i] : info2) que[get(d)].push_back({r, l, i});
    vector<i64> ans(q);
    rep (d, 0, ssize(dic)) {
        sort(all(ope[d]));
        sort(all(que[d]));
        for (int ptr = 0; const auto &[R, L, id] : que[d]) {
            while (ptr < ssize(ope[d]) && ope[d][ptr][0] <= R) {
                mod(1, 0, n - 1, ope[d][ptr][1], ope[d][ptr][2], 1);
                ptr++;
            }
            ans[id] = query(1, 0, n - 1, L, R);
        }
        for (int ptr = 0; const auto &[R, L, id] : que[d]) {
            while (ptr < ssize(ope[d]) && ope[d][ptr][0] <= R) {
                mod(1, 0, n - 1, ope[d][ptr][1], ope[d][ptr][2], -1);
                ptr++;
            }
        }
    }
    rep (i, 0, q) cout << ans[i] << '\n';
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // std::freopen("gcdrng.in", "r", stdin);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}