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
#include <unordered_map>

using namespace std;

int n, ans;
int a[1000000];
int BIT=20;
int pxor, cur, nxt;
// unordered_map<int, int> mp;
map<int, int> mp;

/*
1000000
1010011
0111111
0010101
1111111
1000000

A ^ B = C
A = C ^ B ?= 0 => C == B

010
110
*/
void solve() {
    ans = 0;
    for (int i=0; i<20; i++) {
        pxor = 0;
        mp.clear();
        if ((a[0] >> i) & 1) {
            mp[0] = -1;    
        }
        for (int j=0; j<n; j++) {
            cur = (a[j] >> i) & 1;
            pxor ^= ((a[j] >> i) << i);
            nxt = j < n-1 ? (a[j+1] >> i) & 1 : 0;

            if (mp.find(pxor) != mp.end() ) {
                ans = max(ans, j - mp[pxor]);
            }

            if (nxt) {
                if (mp.find(pxor) == mp.end()) {
                    mp[pxor] = j;
                }
            } else {
                mp.clear();
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> a[i];
    }

    solve();    
}