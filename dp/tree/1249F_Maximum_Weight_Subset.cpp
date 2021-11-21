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

int n, k, u, v, ans;
int a[100001], dp[202][202];
vector<int> vt[100001];

// dp[node][dep]
// maximum total weight of the subset in the subtree of node
// if the vertex with the minimum depth at least dep
void dfs(int node, int parent) {

    for(int next: vt[node]) {
        if (next == parent) continue;
        dfs(next, node);
    }

    dp[node][0] = a[node];
    for(int d=0; d<n; d++) {
        if(!d) {
            // dep = 0, take current node val + dp[next][k-1]
            for(int next: vt[node]) {
                if (next == parent) continue;
                dp[node][d] += dp[next][max(0, k-1)];
            }
        } else {
            // dep > 0, dp[next][dep-1] + dp[next2][max(dep-1, k-d-1)]
            //   1 
            // 2   3
            for(int next: vt[node]) {
                if (next == parent) continue;
                int sum = 0;
                for(int next2: vt[node]) {
                    if (next2 == parent || next2 == next) continue;
                    sum += dp[next2][max(d-1, k-d-1)];
                }
                dp[node][d] = max(dp[node][d], dp[next][d-1] + sum);
            }
        }
    }

    for(int d=n-2; d>=0; d--) {
        dp[node][d] = max(dp[node][d], dp[node][d+1]);
    }
}

int main() {
    cin >> n >> k;
    k++; //increase k to find the subset in which any pair of vertices had distance k or greater instead of k+1 greater
    for(int i=1; i<=n; i++) {
        cin >> a[i];
    }
    for(int i=0; i<n-1; i++) {
        cin >> u >> v;

        vt[u].push_back(v);
        vt[v].push_back(u);
    }
    memset(dp, 0, sizeof dp);
    dfs(1, 0);
    cout << dp[1][0] << "\n";
}
