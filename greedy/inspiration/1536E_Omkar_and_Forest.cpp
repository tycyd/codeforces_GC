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

/*
4 3 2 1 2
3 2 1 0 1
2 1 0 1 2
3 2 1 2 3

inspiration:
1. multi-source bfs, get only configration
2. cannot make any cell -1 or +1
    +1: will violate the rule that difference to adjacent cell at most 1
    -1: will end up making extra 0 cell
*/

typedef long long ll;

const ll MOD=1000000007;
ll ans;
bool hasZero;
int t, n, m;
char c;

int main() {
    cin >> t;
    while(t--) {
        cin >> n >> m;
        ans = 1;
        hasZero = false;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                cin >> c;
                if(c == '#') {
                    ans *= 2;
                    ans %= MOD;
                } else {
                    hasZero = true;
                }
            }
        }
        cout << ans - (hasZero?0:1) << "\n";
    }
}
