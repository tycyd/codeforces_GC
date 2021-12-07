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

int n, a[1000000];
int B = 22;
int M = 1 << 22;
int dp[1 << 22];

/*
x: 01001100
y: 10110011

z: X0XX00XX

SOS DP, n*(2^n)
*/
int main() {
    memset(dp, -1, sizeof dp);

    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> a[i];
        dp[a[i]] = a[i];
    }

    for (int i=0; i<B; i++) {
        for (int m=0; m<M; m++) {
            if (~dp[m]) {
                dp[m | 1 << i] = dp[m];
            }
        }
    }

    for(int i=0; i<n; i++) {
        cout << dp[~a[i] & M-1] << " ";
    }
}