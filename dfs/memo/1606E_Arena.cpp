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

const ll MOD = 998244353;
int n, x;
ll memo[501][501];
ll P[501][501];
ll C[501][501];

/*
i: number of heros remaining
j: max health equal or less than j
k: after one round, number of heros remaining
*/
ll dfs(int i, int j) {
    if (i == 1) {
        return 0;
    }
    if (i == 0) {
        return 1;
    }
    if (j <= i-1) {
        return P[j][i];
    }

    if(memo[i][j] != -1) {
        return memo[i][j];
    }

    ll r = 0;
    for(int k=0; k<=i; k++) {
        ll r2= dfs(k, max(0, j-i+1));

        r2 *= P[min(x, i-1)][i-k];
        r2 %= MOD;
        r2 *= C[i][k];
        r2 %= MOD;

        r += r2;
        r %= MOD;
    }

    memo[i][j] = r;
    return r;
}

void build() {
    for(int i=0; i<=max(n,x); i++) {
        for(int j=0; j<=max(n,x); j++) {
            if (j > 0) {
                P[i][j] = P[i][j-1] * i;
                P[i][j] %= MOD;
            } else {
                P[i][j] = (i==0 ? 0:1);
            }
        }
    }

    //      1
    //    1   1
    //  1   2   1
    //1   3   3   1
    for(int i=0; i<=n; i++) {
        C[i][0] = 1;
        for(int j=1; j<i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
            C[i][j] %= MOD;
        }
        C[i][i] = 1;
    }
}

int main() {
    cin >> n >> x;
    memset(memo, -1, sizeof memo);

    build();

    ll ans = dfs(n, x);
    cout << ans << "\n";
}
