#include <stdio.h>
#include <string.h>

static const int MAXN = 1000005;

static int tree_max[4 * MAXN];
static int lazy_tag[4 * MAXN];
static int X, K, P;

static inline int imax(int a, int b) { return a > b ? a : b; }

static void push_up(int rt) {
    tree_max[rt] = imax(tree_max[2 * rt], tree_max[2 * rt + 1]);
}

static void push_down(int rt) {
    if (lazy_tag[rt]) {
        lazy_tag[2 * rt] += lazy_tag[rt];
        tree_max[2 * rt] += lazy_tag[rt];
        lazy_tag[2 * rt + 1] += lazy_tag[rt];
        tree_max[2 * rt + 1] += lazy_tag[rt];
        lazy_tag[rt] = 0;
    }
}

static void build(int l, int r, int rt) {
    lazy_tag[rt] = 0;
    tree_max[rt] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, 2 * rt);
    build(mid + 1, r, 2 * rt + 1);
}

static int query(int l, int r, int rt, int ql, int qr) {
    if (ql <= l && r <= qr) return tree_max[rt];
    push_down(rt);
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res = imax(res, query(l, mid, 2 * rt, ql, qr));
    if (qr > mid) res = imax(res, query(mid + 1, r, 2 * rt + 1, ql, qr));
    return res;
}

static void update(int l, int r, int rt, int qL, int qR, int val) {
    if (qL <= l && r <= qR) {
        tree_max[rt] += val;
        lazy_tag[rt] += val;
        return;
    }
    push_down(rt);
    int mid = (l + r) >> 1;
    if (qL <= mid) update(l, mid, 2 * rt, qL, qR, val);
    if (qR > mid) update(mid + 1, r, 2 * rt + 1, qL, qR, val);
    push_up(rt);
}

int main(void) {
    scanf("%d %d %d", &X, &K, &P);

    if (X > 1) {
        build(1, X - 1, 1);
    }

    while (P--) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);

        if (u >= v) {
            putchar('N');
            putchar('\n');
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
            putchar('T');
            putchar('\n');
        } else {
            putchar('N');
            putchar('\n');
        }
    }

    return 0;
}
