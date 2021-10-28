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
typedef pair<int, int> pii;

int n, m, u, v, w, q, l;
int INF = 0x3f3f3f3f;
ll dis[601][601];
ll edg[601][601];
ll ma[601];
vector<pii> g[601];

int main() {
    cin >> n >> m;

    memset(dis, INF, sizeof dis);
    for(int i=1; i<=n; i++) {
        dis[i][i] = 0;
    }

    for(int i=0; i<m; i++) {
        cin >> u >> v >> w;
        dis[u][v] = dis[v][u] = w;
        edg[u][v] = edg[v][u] = w;
    }

    for(int k=1; k<=n; k++) {
        for(int i=1; i<=n; i++) {
            for(int j=1; j<=n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }

    /*
    dis[u][i] + e[i][j] + dis[j][v] <= l​
    e[i][j] + dis[j][v] <= l - dis[u][i]
    */
    cin >> q;
    while(q--) {
        cin >> u >> v >> l;
        g[u].push_back({v, l});
        g[v].push_back({u, l});
    }

    int ans = 0;
    for(int i=1; i<=n; i++) {
        memset(ma, -INF, sizeof ma);
        for(int v=1; v<=n; v++) {
            for(auto it: g[v]) {
                ma[v] = max(ma[v], it.second - dis[it.first][i]);
            }
        }

        for(int j=i+1; j<=n; j++) {
            if (!edg[i][j]) {
                continue;
            }

            for(int v=1; v<=n; v++) {
                if(edg[i][j] + dis[j][v]<=ma[v]) {
                    ans++;
                    break;
                }
            }
        }
    }
    cout << ans << "\n";
}