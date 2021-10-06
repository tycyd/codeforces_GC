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

int n;
long long xy[5001][2];
bool vis[5001];

int main() {
    cin >> n;
    for(int i=1; i<=n; i++) {
        cin >> xy[i][0];
        cin >> xy[i][1];
    }

    cout << 1 << " ";
    long long px = xy[1][0];
    long long py = xy[1][1];
    for (int i=2; i<=n; i++) {
        int idx = -1;
        long long dis = 0;

        for (int j=2; j<=n; j++) {
            if (vis[j]) {
                continue;
            }

            long long d = (px-xy[j][0])*(px-xy[j][0]) + (py-xy[j][1])*(py-xy[j][1]);
            if (d > dis) {
                dis = d;
                idx = j;
            }
        }

        vis[idx] = true;
        px = xy[idx][0];
        py = xy[idx][1];
        cout << idx << " ";
    }
}