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
1
7
1 2 1 1 3 2 6
1    1 1 , 3 2 , 6

1
3
1 2 3

k(k-1)/2 = 100000
*/
typedef long long LL;
int t, n, a[100001], ans;
LL dp[500][100001], ps[100001];

void solve() {
    dp[1][n] = a[n];
    for(int i=n-1; i>0; i--) {
        dp[1][i] = max((LL)a[i], dp[1][i+1]);
    }
    for(int k=2; k<500; k++) {
        for(int i=n; i>0; i--) {
            int pre = i+k;
            if (pre > n || dp[k-1][pre] == -1) {
                dp[k][i] = -1;
                continue;
            }
            LL sum = ps[i+k-1] - ps[i-1];
            if (sum >= dp[k-1][pre]) {
                dp[k][i] = dp[k][i+1];
                continue;
            }
            dp[k][i] = max(sum, dp[k][i+1]);
        }
        if (dp[k][1] < 0) {
            ans = k-1;
            return;
        }
    }
}

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        a[0] = 0;
        ps[0] = 0;
        for (int i=1; i<=n; i++) {
            cin >> a[i];
            ps[i] = ps[i-1] + a[i];
        }
        solve();
        cout << ans << '\n';
    }
}