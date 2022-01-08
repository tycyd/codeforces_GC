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

typedef long long ll;

int n, k;
const ll MOD = 998244353;
ll p[50001];
string s;

/*
00100100 | 110
001 | 00100 1 | 10

c = c0 + c1

c*(c-1)*(c-2)….  /  c0*(c0-1)*(c0-2)…
—— c0 ——

7 2
1100110

1100  => 4*3/2 = 6
(100)1 => 6 - 3 = 3
 (001)10 => 5*4/2 - 3 = 7
*/

ll bpow(ll a, ll b) {
    if (b == 0) {
        return 1;
    }
    ll c = bpow(a, b/2);
    c *= c;
    c %= MOD;
    if (b%2) {
        c *= a;
        c %= MOD;
    }
    return c;
}

ll inv(ll a) {
    return bpow(a, MOD - 2);
}

ll count_ways(int cnt1, int ttl) {
    ll r = p[ttl] * inv(p[ttl - cnt1]);
    r %= MOD;
    r *= inv(p[cnt1]);
    r %= MOD;
    return r;
}

int main() {
    cin >> n >> k >> s;

    p[0] = 1;
    p[1] = 1;
    for(int i=2; i<= n; i++) {
        p[i] = i*p[i-1];
        p[i] %= MOD;
        // cout << p[i] << "\n";
    }

    int cnt1 = 0;
    int i = 0;
    int j = 0;
    ll res = 0;
    int last1 = -1;

    while(j < s.size()) {
        if (s[j] == '1') {
            if (cnt1 == k) {
                res += count_ways(k, j - i);
                res %= MOD;
                if (i > 0) {
                    if (k==1) {
                        res -= 1;
                    } else {
                        res -= count_ways(k-1, last1 - i);
                    }
                    if (res < 0) {
                        res += MOD;
                    }
                    // res %= MOD;
                }
                // cout << i << " " << j << " " << res << " oops\n";

                while(s[i] != '1') {
                    i++;
                }
                i++;
                cnt1--;
            }
            last1 = j;
            cnt1++;
        }
        j++;
    }

    if (k > 0 && cnt1 == k) {
        res += count_ways(k, j - i);
        res %= MOD;
        if (i > 0) {
            if (k==1) {
                res -= 1;
            } else {
                res -= count_ways(k-1, last1 - i);
            }
            if (res < 0) {
                res += MOD;
            }
            // res %= MOD;
        }
        // cout << i << " " << j << " " << res << " oops\n";
    } else {
        res = 1;
    }
    cout << res;
}