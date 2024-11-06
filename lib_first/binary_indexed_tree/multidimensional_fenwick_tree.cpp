// verified 
// https://atcoder.jp/contests/abc366/submissions/56579538
template<typename T>
struct multi_dimensional_fenwick_tree {
    int H;
    int W;
    int D;
    vector<vector<vector<T>>> b;
    multi_dimensional_fenwick_tree(int h, int w, int d) : H(h), W(w), D(d), b(h + 1, vector<vector<T>> (w + 1, vector<T> (d+1, T()))) {
    }
    // add
    void add(int x, int y, int z, T val) {
        assert(0 <= x);
        assert(0 <= y);
        assert(0 <= z);
        int nx = x + 1;
        while (nx <= H) {
            int ny = y + 1;
            while (ny <= W) {
                int nz = z + 1;
                while (nz <= D) {
                    b[nx][ny][nz] += val;
                    nz += nz & -nz;
                }
                ny += ny & -ny; 
            }
            nx += nx & -nx;
        }
    }
    // change value of ( x, y ) to val
    void update(int x, int y, int z, T val) {
        add(x, y, z, val-b[x + 1][y + 1][z + 1]);
    }
    // sum of [0, H) * [0, W)
    // can use 0 <= x <= H and 0 <= y <= W
    T sum(int x, int y, int z) {
        int nx = x;
        T res = 0;
        while (nx > 0) {
            int ny = y;
            while (ny > 0) {
                int nz = z;
                while (nz > 0) {
                    res += b[nx][ny][nz];
                    nz -= nz & -nz;
                }
                ny -= ny & -ny;
            }
            nx -= nx & -nx;
        }
        return res;
    }
    // sum of [lx, rx) * [ly, ry)
    T sum(int lx, int rx, int ly, int ry, int lz, int rz) {
        assert(0 <= lx && lx <= H && 0 <= rx);
        assert(0 <= ly && ly <= W && 0 <= ry);
        assert(0 <= lz && lz <= D && 0 <= rz);
        return sum(rx, ry, rz)-sum(rx, ry, lz)-sum(rx, ly, rz)-sum(lx, ry, rz)+sum(rx, ly, lz)+sum(lx, ry, lz)+sum(lx, ly, rz)-sum(lx, ly, lz);
    }
};
