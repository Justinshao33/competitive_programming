#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops,no-stack-protector")
using namespace std;
typedef long long loli;
typedef pair<int, int> pii;
typedef pair<loli, loli> pll;
#define F first
#define S second

const int N=505, mod=1e9+7;
char mp[N][N];
short p[N];
const short moves[9][2]={{0, 0}, {2, -1}, {2, 1}, {1, -2}, {1, 2}, {-1, -2}, {-1, 2}, {-2, -1}, {-2, 1}};

short n, m;
void add(int& x, const int& k){
    x+=k;
    if (x>=mod) x-=mod;
}

inline bool valid(short dd, short x){
    short y=p[x]+moves[dd][1];
    x+=moves[dd][0];
    return (1<=x&&x<=n&&1<=y&&y<=m&&mp[x][y]=='.');
}

inline bool collide(short di, short dj, short ii, short jj){
    if (di==0) return 0;
    if (ii<0) return 1;
    short x1=ii+moves[di][0], y1=p[ii]+moves[di][1];
    short x2=jj+moves[dj][0], y2=p[jj]+moves[dj][1];
    return (x1==x2)&&(y1==y2);
}

short i, j, a, b, c, d, k, na, nb, nc, nd;

const int C = 1 << 11;

void _solve(){
    scanf("%hd%hd", &n, &m);
    for(i=1;i<=n;i++) for(j=1;j<=m;j++){
        char cc;
        cc=getchar();
        while (cc!='.'&&cc!='*'&&cc!='#') cc=getchar();
        mp[i][j]=cc;
        if (mp[i][j]=='*') p[i]=j;
    }
    vector dp(2, vector<int>(C));
    vector state(2, bitset<C>());
    dp[0][0] = 1;
    state[0][0] = 1;
    for(i=1;i<=n;i++){
        for (auto cur = int(state[i & 1 ^ 1]._Find_first()); cur != C; cur = int(state[i & 1 ^ 1]._Find_next(cur))) {
            a = cur >> 9, b = cur >> 6 & 7, c = cur >> 3 & 7, d = cur & 7;
            if (a) mp[i-4+moves[a][0]][p[i-4]+moves[a][1]] = '#';
            if (b) mp[i-3+moves[b][0]][p[i-3]+moves[b][1]] = '#';
            if (c) mp[i-2+moves[c][0]][p[i-2]+moves[c][1]] = '#';
            if (d) mp[i-1+moves[d][0]][p[i-1]+moves[d][1]] = '#';
            for(k=1;k<=8;k++) if (valid(k, i) && mp[i + moves[k][0]][p[i] + moves[k][1]] == '.') {
                na=b, nb=c, nc=d, nd=k;
                if (na>2) na=0;
                if (nb>4) nb=0;
                if (nc>4) nc=0;
                if (nd>6) nd=0;
                int nxt = (na<<9) | (nb<<6) | (nc<<3) | nd;
                add(dp[i & 1][nxt], dp[i & 1 ^ 1][cur]);
                state[i & 1][nxt] = 1;
            }
            if (a) mp[i-4+moves[a][0]][p[i-4]+moves[a][1]] = '.';
            if (b) mp[i-3+moves[b][0]][p[i-3]+moves[b][1]] = '.';
            if (c) mp[i-2+moves[c][0]][p[i-2]+moves[c][1]] = '.';
            if (d) mp[i-1+moves[d][0]][p[i-1]+moves[d][1]] = '.';
            dp[i & 1 ^ 1][cur] = 0;
            state[i & 1 ^ 1][cur] = false;
        }
    }
    int ans = accumulate(dp[n & 1].begin(), dp[n & 1].end(), 0LL) % mod;
    printf("%d\n", ans);
}

int main(){
    freopen("knights.in", "r", stdin);
    short _t;
    scanf("%hd", &_t);
    while(_t--) _solve();
}