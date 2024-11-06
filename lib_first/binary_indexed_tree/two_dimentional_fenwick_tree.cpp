template<typename T = long long>
struct two_dimensional_fenwick_tree {
    int H, W;
    vector<vector<T>> b;
    two_dimensional_fenwick_tree(int h, int w) : H(h), W(w), b(h + 1, vector<T> (w + 1, T())) {}
    // add
    void add(int x, int y, T val) {
        assert(0 <= x && x < H && 0 <= y && y < W);
        int nx = x + 1;
        while (nx <= H) {
            int ny = y + 1;
            while (ny <= W) {
                b[nx][ny] += val;
                ny += ny & -ny; 
            }
            nx += nx & -nx;
        }
    }
    // change value of ( x, y ) to val
    void update(int x, int y, T val) {
        add(x, y, val-b[x + 1][y + 1]);
    }
    // sum of [0, H) * [0, W)
    // can use 0 <= x <= H and 0 <= y <= W
    T sum(int x, int y) {
        T res = 0;
        int nx = x;
        while (nx > 0) {
            int ny = y;
            while (ny > 0) {
                res += b[nx][ny];
                ny -= ny & -ny;
            }
            nx -= nx & -nx;
        }
        return res;
    }
    // sum of [lx, rx) * [ly, ry)
    T sum(int lx, int rx, int ly, int ry) {
        assert(0 <= rx && rx <= H && 0 <= lx && lx <= H);
        assert(0 <= ry && ry <= W && 0 <= ly && ly <= W);
        return sum(rx, ry) - sum(rx, ly) - sum(lx, ry) + sum(lx, ly);
    }
};
/*
    int lower_bound_by_x(int w, T x) {
        int res = 0;
        T t = x;
        int k = 1;
        while (k << 1 <= siz) k <<= 1;
        for (; k > 0; k >>= 1) {
            if (res + k <= siz && b[res + k][w] < t) {
                t -= b[res + k][w];
                res += k;
            }
        }
        return res;
    }
    int lower_bound_by_y(int h, T x) {
        int res = 0;
        T t = x;
        int k = 1;
        while (k << 1 <= siz) k <<= 1;
        for (; k > 0; k >>= 1) {
            if (res + k <= siz && b[res + k][h] < t) {
                t -= b[res + k][h];
                res += k;
            }
        }
        return res;
    }
*/