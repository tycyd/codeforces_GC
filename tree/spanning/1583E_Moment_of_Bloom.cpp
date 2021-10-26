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

int m, n, x, y, q, a, b;
vector<int> res[300001];
int ua[300001];
int ct[300001];
vector<int> vt[300001];

int uf(int i) {
    if (ua[i] != i) {
        ua[i] = uf(ua[i]);
    }
    return ua[i];
}

// i <- j
void un(int i, int j) {
    int ri = uf(i);
    int rj = uf(j);
    ua[ri] = rj;
}

int dfs(int i, int c, int p, int e) {
    if (c == e) {
        res[i].push_back(c);
        return 1;
    }

    for(int nxt: vt[c]) {
        if (nxt != p) {
            if(dfs(i, nxt, c, e)) {
                res[i].push_back(c);
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    cin >> n >> m;
    for(int i=1; i<=n; i++) {
        ua[i] = i;
    }

    for(int i=0; i<m; i++) {
        cin >> x >> y;

        if (uf(x) != uf(y)) {
            vt[x].push_back(y);
            vt[y].push_back(x);
            un(x, y);
        }
    }

    cin >> q;
    for(int i=0; i<q; i++) {
        cin >> a >> b;
        dfs(i, a, -1, b);
        ct[a]++;
        ct[b]++;
    }

    int odd_cnt = 0;
    for(int i=1; i<=n; i++) {
        if (ct[i] % 2) {
            odd_cnt++;
        }
    }

    if (odd_cnt) {
        cout << "NO\n" << odd_cnt / 2 << "\n";
    } else {
        cout << "YES\n";
        for(int i=0; i<q; i++) {
            cout << res[i].size() << "\n";

            for (vector<int>::reverse_iterator j = res[i].rbegin(); j != res[i].rend(); ++j ) { 
                cout << *j << " ";
            }
            cout << "\n";
        }
    }
}
