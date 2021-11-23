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

int INF = 0x3f3f3f3f;
int n, m, cnt[30][30], dp[1 << 20];
string s;

/*
abacdabadabacdabad

a, (b,c,d)
=> a:1  (b,c,d):2

a, b, (c,d)
=> a:1  b:2  (c,d):3

a, b, c, d
=> a:1  b:2  c:3  d:4

dp[mask] = min(dp[mask ^ (1 << i)] + sum[cnt])
*/
int main() {
    cin >> n >> m >> s;
    memset(cnt, 0, sizeof cnt);
    memset(dp, INF, sizeof dp);

    for(int i=1; i<=s.length(); i++) {
        cnt[s[i-1] - 'a'][s[i] - 'a']++;
        cnt[s[i] - 'a'][s[i-1] - 'a']++;
    }

    dp[0] = 0;
    for(int mk=1; mk < (1 << m); mk++) {
        dp[mk] = INF;
        int add = 0;
        for(int i=0; i<m; i++) {
            for(int j=i+1; j<m; j++) {
                if((mk>>i & 1) ^ (mk>>j & 1)) {
                    add += cnt[i][j];                        
                }
            }
        }
        for(int i=0; i<m; i++) {
            if (mk>>i & 1) {
                dp[mk] = min(dp[mk], dp[mk ^ (1<<i)] + add);
            }
        }
    }

    cout << dp[(1<<m) - 1] << "\n";
}