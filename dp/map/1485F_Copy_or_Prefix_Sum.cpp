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

int t, n, ans, k;
int b[200001];
map<long long, long long> mp;
long long MOD = 1000000007;
/*
1 -1 1

1. a[i]=b[i]
dp[i][j] = dp[i-1][j-b[i]]

2. a[i]=a[1]+a[2]...a[i-1]
dp[i][b[i]] = sum(dp[i-1][j]) - dp[i-1][0]

1. a[i]=b[i]
dp[i][j] => dp[i+1][j+b[i]]

2. a[i]=a[1]+a[2]...a[i-1]
dp[i][0->j] => dp[i+1][b[i]]
*/



void solve() {
    mp.clear();
    mp[0] = 1; ans = 1; k = 0;
    for(int i=1; i<=n; i++) {
        // a[i]=b[i]
        // dp[i][j] => dp[i+1][j+b[i]]
        

        // a[i]=a[1]+a[2]...a[i-1]
        // dp[i][0->j] => dp[i+1][b[i]]
        
        int a = mp[k];
        mp[k] = ans;
        k -= b[i];
        ans = (2 * ans - a + MOD) % MOD;
    }
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for(int i=1; i<=n; i++) {
            cin >> b[i];
        }
        solve();
        cout << ans << "\n";
    }
}
