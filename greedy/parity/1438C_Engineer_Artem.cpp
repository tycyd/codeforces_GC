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

typedef long long LL;

int t, n, m, a[100][100];

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                cin >> a[i][j];
            }
        }
        int r = 0;
        for(int i=0; i<n; i++) {
            int c = r;
            for(int j=0; j<m; j++) {
                cout << a[i][j] + (a[i][j]%2 == c ? 0 : 1) << " ";
                c ^= 1;
            }
            cout << "\n";
            r ^= 1;
        }
    }
}
