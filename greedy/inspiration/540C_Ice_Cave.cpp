#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <string.h>

using namespace std;

int n, m, r1, c1, r2, c2;
char g[501][501];
bool vis[501][501];

bool dfs(int r, int c) {
    if (r == r2 && c == c2) {
        return true;
    }

    if (r == 0 || c == 0 || r > n || c > m || vis[r][c]) {
        return false;
    }
    if (g[r][c] == 'X' && (r != r1 || c != c1)) {
        return false;
    }
    vis[r][c] = true;
    // cout << "r:" << r << " c:" << c << " v:" << g[r][c] << "\n";
    return (dfs(r+1,c) || dfs(r-1,c) || dfs(r,c+1) || dfs(r,c-1));
}

int main() {
    cin >> n >> m;

    // memset(g, 0, sizeof g);
    // memset(vis, 0, sizeof vis);

    for (int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            cin >> g[i][j];
        }
    }
    cin >> r1 >> c1 >> r2 >> c2;

    int d[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    if (r1==r2 && c1==c2) {
        int cnt = 0;
        for (int i=0; i<4; i++) {
            int r = r2 + d[i][0];
            int c = c2 + d[i][1];
            if (r == 0 || c == 0 || r > n || c > m || g[r][c] == 'X') {
                continue;
            }
            cout << "YES";
            return 0;
        }
        cout << "NO";
        return 0;
    }
    
    bool r = false;
    if(dfs(r1, c1)) {
        if(g[r2][c2] == 'X') {
            r = true;
        } else {
            int cnt = 0;
            g[r1][c1] = '.';
            for (int i=0; i<4; i++) {
                int r = r2 + d[i][0];
                int c = c2 + d[i][1];
                if (r == 0 || c == 0 || r > n || c > m || g[r][c] == 'X') {
                    continue;
                }
                cnt++;
            }
            if (cnt > 1) {
                r = true;
            }
        }
    }

    if (r) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}
