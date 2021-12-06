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

int n, MAX;
int a[1000000];
LL dp[5000001], cnt[5000001];

/*
 dp[i] = the maximum answer if we can pick from the whole array, and every element of the resulting array is divisible by i.
 Initially, dp[i]=cnt[i]*i, where cnt[i] is the number of elements in a that is divisible by i.
 
 j%i = 0, 
 dp[i] = max(dp[i], dp[j] + i*(cnt[i]-cnt[j]))
*/
int main() {

    MAX = 0;
    memset(cnt, 0, sizeof cnt);

    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
        MAX = max(MAX, a[i]);
    }

    for (int i=1; i<=MAX; i++) {
        for (int j=2*i; j<=MAX; j+=i) {
            cnt[i] += cnt[j];
        }
    }

    for (int i=MAX; i>=1; i--) {
        dp[i] = i*cnt[i];
        for (int j=i*2; j<=MAX; j+=i) {
            dp[i] = max(dp[i], dp[j] + i*(cnt[i]-cnt[j]));
        }
    }

    cout << dp[1];
}