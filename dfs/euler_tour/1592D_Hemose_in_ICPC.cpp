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

int n, u, v, ans;
vector<int> vt[1001];
int et[2001][2];
int sz;
bool vis[1001];

/*
      1
  2      5
3   4

1 2, 2 3, 3 2, 2 4, 4 2, 2 1, 1 5, 5 1
*/
void euler_tour(int cur, int pre) {
    if (pre != -1) {
        et[sz][0] = cur;
        et[sz][1] = pre;
        sz++;
    }

    for(int nxt : vt[cur]) {
        if (nxt != pre) {
            euler_tour(nxt, cur);
            et[sz][0] = nxt;
            et[sz][1] = cur;
            sz++;
        }
    }
}

int check(int l, int h) {
    memset(vis, false, n + 1);

    int k = 0;
    int res = 0;

    for(int i=l; i<=h; i++) {
        if (!vis[et[i][0]]) {
            k++;
            vis[et[i][0]] = true;
        }
        if (!vis[et[i][1]]) {
            k++;
            vis[et[i][1]] = true;
        }
    }

    cout << "? " << k;
    for(int i=1; i<=n; i++) {
        if (vis[i]) {
            cout << " " << i;
        }
    }
    cout << "\n";
    cout.flush();
    cin >> res;
    return res;
}

int main() {
    cin >> n;
    for (int i=0; i<n-1; i++) {
        cin >> u >> v;

        vt[u].push_back(v);
        vt[v].push_back(u);
    }

    cout << "? " << n;
    for (int i=1; i<=n; i++) {
        cout << " " << i;
    }
    cout << "\n";
    cout.flush();
    cin >> ans;

    sz = 0;
    euler_tour(1, -1);

    int l=0;
    int h=sz-1;

    while (l < h) {
        int m = (l + h) / 2;
        int res = check(l, m);
        if (res == ans) {
            h = m;
        } else {
            l = m + 1;
        }
    }

    cout << "! " << et[l][0] << " " << et[l][1];
    cout << "\n";
    cout.flush();
}