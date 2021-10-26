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

// 1 5, 2 3
long long n, k, ans;
long long dp[501][501];   //ith shrub with red remaining
long long a[501];
long long b[501];

int main() {
    cin >> n >> k;
    for(int i=1; i<=n; i++) {
        cin >> a[i] >> b[i];    
    }

    for(int i=0; i<501; i++) {
        for(int j=0; j<501; j++) {
            dp[i][j] = -1;
        }
    }

    dp[0][0] = 0;
    long long ttl_a = 0;
    long long ttl_b = 0;
    for(int i=1; i<=n; i++) {
        for(int j=0; j<=k-1; j++) {
            if(dp[i-1][j] >= 0) {
                long long pre_b = ttl_a + ttl_b - dp[i-1][j]*k - j;

                for(int need_a=1; need_a<=min(k-1, a[i]);need_a++) {
                    int need_b = k - need_a;
                    if (need_b <= b[i]) {
                        int rem_a=a[i] - need_a;
                        int rem_b=b[i] - need_b;
                        int cnt = 1 + (rem_a + j) / k + (rem_b + pre_b) / k;
                        dp[i][(rem_a + j) % k] = max(dp[i][(rem_a + j) % k], dp[i-1][j] + cnt);
                    }
                }

                int cnt2 = (a[i] + j) / k + (b[i] + pre_b) / k;
                dp[i][(a[i] + j) % k] = max(dp[i][(a[i] + j) % k], dp[i-1][j] + cnt2);
            }
        }
        ttl_a += a[i];
        ttl_b += b[i];
    }

    ans = 0;
    for(int j=0; j<=k-1; j++) {
        ans = max(ans, dp[n][j]);
    }

    cout << ans << "\n";
}
