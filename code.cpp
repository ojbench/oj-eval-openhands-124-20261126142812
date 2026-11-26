#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;

int tree_max[4 * MAXN];
int lazy[4 * MAXN];
int X, K, P;

inline void push_up(int rt) {
    tree_max[rt] = max(tree_max[2 * rt], tree_max[2 * rt + 1]);
}

inline void push_down(int rt) {
    if (lazy[rt]) {
        lazy[2 * rt] += lazy[rt];
        tree_max[2 * rt] += lazy[rt];
        lazy[2 * rt + 1] += lazy[rt];
        tree_max[2 * rt + 1] += lazy[rt];
        lazy[rt] = 0;
    }
}

void build(int l, int r, int rt) {
    lazy[rt] = 0;
    tree_max[rt] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, 2 * rt);
    build(mid + 1, r, 2 * rt + 1);
}

// Query max in [ql, qr]
int query(int l, int r, int rt, int ql, int qr) {
    if (ql <= l && r <= qr) return tree_max[rt];
    push_down(rt);
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res = max(res, query(l, mid, 2 * rt, ql, qr));
    if (qr > mid) res = max(res, query(mid + 1, r, 2 * rt + 1, ql, qr));
    return res;
}

// Range add val to [qL, qR]
void update(int l, int r, int rt, int qL, int qR, int val) {
    if (qL <= l && r <= qR) {
        tree_max[rt] += val;
        lazy[rt] += val;
        return;
    }
    push_down(rt);
    int mid = (l + r) >> 1;
    if (qL <= mid) update(l, mid, 2 * rt, qL, qR, val);
    if (qR > mid) update(mid + 1, r, 2 * rt + 1, qL, qR, val);
    push_up(rt);
}

int main() {
    scanf("%d %d %d", &X, &K, &P);
    
    // Stations 1..X, segments are 1..X-1
    // Segment i represents the track from station i to station i+1
    if (X > 1) {
        build(1, X - 1, 1);
    }
    
    while (P--) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        if (u >= v) {
            printf("N\n");
            continue;
        }
        
        int max_occ = 0;
        if (X > 1) {
            max_occ = query(1, X - 1, 1, u, v - 1);
        }
        
        if (max_occ + n <= K) {
            if (X > 1) {
                update(1, X - 1, 1, u, v - 1, n);
            }
            printf("T\n");
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}
