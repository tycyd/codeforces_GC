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

int t, n, a[1001], mx;

/*
Coin1: 0, 1 or 2
Coin2: 0, 1 or 2 

proof:
if coin1 > 2
    (3 1 1) always better than (1 1 1)
    because b%3 <= 2, at most (1 1)
if coin2 > 2
    (3 2 1) always better than (2 2 2)
    because (3 2 1) can handle all situations
*/

int get_min_c3(int a, int c1, int c2) {
    int c3 = 1e9;
    for(int i=0; i<=c1; i++) {
        for(int j=0; j<=c2; j++) {
            int r = a - i - 2*j;
            if (r % 3 == 0 && r >= 0) {
                c3 = min(c3, r / 3);
            }
        }
    }
    return c3;
}

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        mx = 0;
        for(int i=0; i<n; i++) {
            cin >> a[i];
            mx = max(mx, a[i]);
        }
        
        int ans = 1e9;
        for(int c1=0; c1<=2; c1++) {
            for(int c2=0; c2<=2; c2++) {
                int c3 = 0;
                for(int k=0; k<n; k++) {
                    int r = get_min_c3(a[k], c1, c2);
                    if (r == 1e9) {
                        c3 = -1;
                        break;
                    }
                    c3 = max(c3, r);
                }

                if (c3 != -1) {
                    ans = min(ans, c1 + c2 + c3);
                }
            }
        }
        cout << ans << "\n";
    }
}