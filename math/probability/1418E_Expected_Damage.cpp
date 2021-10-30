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

const int N = 200001;
const ll MOD = 998244353;
int n, m, a, b;
ll d[N];
ll ps[N];

/*
c => counts of d
c1 => counts of b > d
sd1 => sum damage of c1
c2 => counts of b <= d
sd2 => sum damage of c2

p1: percentage of getting damage (b > d)
p2: percentage of getting damage (b <= d)
1. p1 = max(0, c1 - a) / c1
S S S S S

p1 * c1 * (sd1) / c1

2. p2 = max(0, c1 - a + 1) / (c1 + 1)
| S | S | S | S | S |  

ans = p1 * c1 * sd1 / c1 + p2 * c2 * sd2 / c2
    = p1 * sd1 + p2 * sd2
*/
ll pow(ll a, ll b) {
    if (b == 0) {
        return (ll)1;
    }
    ll c = pow(a, b / 2);
    c *= c;
    c %= MOD;
    if (b%2) {
        c *= a;
        c %= MOD;    
    }
    return c;
}

ll inv(ll a) {
    return pow(a, MOD - 2);
}

int bs(ll b) {
    int l = 0;
    int h = n;
    int m;

    while (l < h) {
        m = (l + h + 1) / 2;
        if (d[m] >= b) {
            h = m - 1;
        } else {
            l = m;
        }
    }

    return l;
}

void solve() {
    int c2 = bs(b);
    int c1 = n - c2;
    ll sd2 = ps[c2];
    ll sd1 = ps[n] - sd2;

    ll p1 = max((ll)0, (ll)(c1 - a)) * inv((ll)c1);
    p1 %= MOD;
    ll p2 = max((ll)0, (ll)(c1 - a + 1)) * inv((ll)(c1 + 1));
    p2 %= MOD;

    // ll ans = ((p1 * sd1) % MOD + (p2 * sd2) % MOD) % MOD;
    ll ans1 = p1 * sd1;
    ans1 %= MOD;
    ll ans2 = p2 * sd2;
    ans2 %= MOD;
    ll ans = ans1 + ans2;
    ans %= MOD;

    if (ans < 0) {
        ans += MOD;
    }

    cout << ans << "\n";
}


int main() {
    cin >> n >> m;
    d[0] = 0;
    for (int i=1; i<=n; i++) {
        cin >> d[i];
    }
    sort(d, d + n + 1);

    ps[0] = 0;
    for(int i=1; i<=n; i++) {
        ps[i] = d[i] + ps[i-1];
        ps[i] %= MOD;
    }

    while(m--) {
        cin >> a >> b;
        solve();
    }
}
