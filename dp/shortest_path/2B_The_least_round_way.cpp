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

typedef long long LL;

int n, a[1000][1000], dp2[1000][1000], dp5[1000][1000];
int cnt2, cnt5;
char ans[2000];
/*
x = 0 => res = 0
prime number:
2,3,5,7
10 = 1*10 = 2*5
20 = 2*10
30 = 3*10
x0 = x*10

least min(cnt2, cnt5)
*/

void steps(int dp[][1000]) {
    int i = n - 1;
    int j = n - 1;
    int c = 2*n-3;

    while(i > 0 || j > 0) {
        if (i == 0) {
            ans[c--] = 'R';
            j--;
        } else if (j == 0) {
            ans[c--] = 'D';
            i--;
        } else {
            if (dp[i-1][j] < dp[i][j-1]) {
                ans[c--] = 'D';
                i--;
            } else {
                ans[c--] = 'R';
                j--;
            }
        }
    }

    for(int i=0; i<2*n-2; i++) {
        cout << ans[i];
    }
}

int main() {

    memset(dp2, 0, sizeof dp2);
    memset(dp5, 0, sizeof dp5);

    bool zero = false;
    int zi = -1;
    int zj = -1;
    cin >> n;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> a[i][j];

            cnt2 = 0;
            cnt5 = 0;

            if (a[i][j] == 0) {
                zero = true;
                zi = i;
                zj = j;
            }
            while(a[i][j] && (a[i][j]%2) == 0) {
                a[i][j]/=2;
                cnt2++;
            }
            while(a[i][j] && (a[i][j]%5) == 0) {
                a[i][j]/=5;
                cnt5++;
            }

            if (i == 0 && j == 0) {
                dp2[i][j] = cnt2;
                dp5[i][j] = cnt5;
            } else if (i == 0) {
                dp2[i][j] = dp2[i][j-1] + cnt2;
                dp5[i][j] = dp5[i][j-1] + cnt5;
            } else if (j == 0) {
                dp2[i][j] = dp2[i-1][j] + cnt2;
                dp5[i][j] = dp5[i-1][j] + cnt5;
            } else {
                dp2[i][j] = min(dp2[i-1][j], dp2[i][j-1]) + cnt2;
                dp5[i][j] = min(dp5[i-1][j], dp5[i][j-1]) + cnt5;
            }
        }
    }

    
    int res = min(dp2[n-1][n-1], dp5[n-1][n-1]);
    if (zero && res > 1) {
        cout << "1\n";
        for (int i=0; i<zi; i++) {
            cout << "D";
        }
        for (int j=0; j<zj; j++) {
            cout << "R";
        }
        for(int i=zi; i<n-1; i++) {
            cout << "D";
        }
        for(int j=zj; j<n-1; j++) {
            cout << "R";
        }
    } else {
        cout << res << "\n";
        if (dp2[n-1][n-1] <= dp5[n-1][n-1]) {
            steps(dp2);
        } else {
            steps(dp5);
        }
    }
}
