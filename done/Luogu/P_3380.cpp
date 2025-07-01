#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
using namespace std;
#define rep(X, a, b) for(int X = a; X < b; ++X)

#define lpos pos << 1
#define rpos pos << 1 | 1
 
const int MAXN = 5e4 + 5;
 
int ls[MAXN * 40], rs[MAXN * 40], siz[MAXN * 40], key[MAXN * 40], pri[MAXN * 40];

inline int newnode(int val) {
    static int id = 0;
    id++;
    ls[id] = rs[id] = 0;
    siz[id] = 1;
    key[id] = val;
    pri[id] = rand();
    return id;
}

inline int sz(int p) {
    return p ? siz[p] : 0;
}

inline void pull(int p) {
    siz[p] = siz[ls[p]] + siz[rs[p]] + 1;
}

inline int merge(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (pri[a] < pri[b]) {
        rs[a] = merge(rs[a], b);
        pull(a);
        return a;
    } else {
        ls[b] = merge(a, ls[b]);
        pull(b);
        return b;
    }
}
 
inline void split(int root, int &a, int &b, int k) {
    if (root == 0) {
        a = b = 0;
        return;
    }
    if (key[root] < k) {
        a = root;
        split(rs[root], rs[a], b, k);
        pull(a);
    } else {
        b = root;
        split(ls[root], a, ls[b], k);
        pull(b);
    }
}

inline void insert(int &root, int k){
    int l = 0, r = 0;
    split(root, l, r, k);
    root = merge(merge(l, newnode(k)), r);
}

inline void erase(int &root, int k){
    int a = 0, b = 0, c = 0;
    split(root, a, b, k);
    split(b, b, c, k + 1);
    b = merge(ls[b], rs[b]);
    root = merge(a, merge(b, c));
}

inline int les(int &root, int k) {
    int a = 0, b = 0;
    split(root, a, b, k);
    int res = siz[a];
    root = merge(a, b);
    return res;
}

inline int pre(int p, int k) {
    if (siz[p] == 0) return -2147483647;
    if (key[p] >= k) return pre(ls[p], k);
    return max(key[p], pre(rs[p], k));
}

inline int suf(int p, int k) {
    if (siz[p] == 0) return 2147483647;
    if (key[p] <= k) return suf(rs[p], k);
    return min(key[p], suf(ls[p], k));
}

int root[MAXN << 2];
int a[MAXN];

inline void build(int pos, int l, int r) {
    root[pos] = newnode(a[l]);
    rep (i, l + 1, r + 1) {
        insert(root[pos], a[i]);
    }
    if (l == r) return;
    int mid = l + r >> 1;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
}

inline void mod(int pos, int l, int r, int id, int val) {
    erase(root[pos], a[id]);
    insert(root[pos], val);
    if (l == r) return;
    int mid = l + r >> 1;
    if (id <= mid) mod(lpos, l, mid, id, val);
    else mod(rpos, mid + 1, r, id, val);
}

inline int que1(int pos, int l, int r, int ql, int qr, int k) {
    if (ql <= l && qr >= r) return les(root[pos], k);
    int mid = l + r >> 1;
    int res = 0;
    if (ql <= mid) res += que1(lpos, l, mid, ql, qr, k);
    if (qr > mid) res += que1(rpos, mid + 1, r, ql, qr, k);
    return res;
}

inline int que2(int ql, int qr, int k, int n) {
    k--;
    int l = 0, r = 1e8 + 1;
    while (r - l > 1) {
        int mid = l + r >> 1;
        int cnt = que1(1, 1, n, ql, qr, mid);
        if (cnt <= k) l = mid;
        else r = mid;
    }
    return l;
}

inline int que4(int pos, int l, int r, int ql, int qr, int k) {
    if (ql <= l && qr >= r) return pre(root[pos], k);
    int mid = l + r >> 1;
    int res = -2147483647;
    if (ql <= mid) res = max(res, que4(lpos, l, mid, ql, qr, k));
    if (qr > mid) res = max(res, que4(rpos, mid + 1, r, ql, qr, k));
    return res;
}

inline int que5(int pos, int l, int r, int ql, int qr, int k) {
    if (ql <= l && qr >= r) return suf(root[pos], k);
    int mid = l + r >> 1;
    int res = 2147483647;
    if (ql <= mid) res = min(res, que5(lpos, l, mid, ql, qr, k));
    if (qr > mid) res = min(res, que5(rpos, mid + 1, r, ql, qr, k));
    return res;
}

template<typename T>
void read(T &x) {
    char c=getchar();T p=1;x=0;
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c))
    {
        x=(x<<1)+(x<<3)+(c^'0');
        c=getchar();
    }x*=p;
}
 
int main() {
    int n, q; read(n), read(q);
    rep (i, 1, n + 1) read(a[i]);
    build(1, 1, n);
    while (q--) {
        int t; read(t);
        if (t == 3) {
            int p, k; read(p), read(k);
            mod(1, 1, n, p, k);
            a[p] = k;
        } else {
            int l, r, k; read(l), read(r), read(k);
            if (t == 1) {
                cout << que1(1, 1, n, l, r, k) + 1 << '\n';
            } else if (t == 2) {
                cout << que2(l, r, k, n) << '\n';
            } else if (t == 4) {
                cout << que4(1, 1, n, l, r, k) << '\n';
            } else {
                cout << que5(1, 1, n, l, r, k) << '\n';
            }
        }
    }
}