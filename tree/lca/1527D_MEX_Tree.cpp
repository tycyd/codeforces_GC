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

int t, n, u, v;
vector<int> vct[200000];
int dep_a[200000];
int jmp_a[200000][20];
int cnt_a[200000];
long long res[200001];

int dfs(int r, int p, int d) {

    dep_a[r] = d;
    jmp_a[r][0] = p;
    for (int i=1; i<20; i++) {
        jmp_a[r][i] = jmp_a[jmp_a[r][i-1]][i-1];
    }

    int cnt = 1;
    for (auto it = begin(vct[r]); it != end(vct[r]); ++it) {
        if (*it == p) {
            continue;
        }
        cnt += dfs(*it, r, d+1);
    }
    cnt_a[r] = cnt;
    return cnt;
}

int get_node(int node, int d) {
    for(int i=19; i>=0; i--) {
        if((d >> i) & 1) {
            node = jmp_a[node][i];
        }
    }
    return node;
}

int lca(int node1, int node2) {
    if(dep_a[node1] > dep_a[node2]) {
        node1 = get_node(node1, dep_a[node1] - dep_a[node2]);
    } else if(dep_a[node1] < dep_a[node2]) {
        node2 = get_node(node2, dep_a[node2] - dep_a[node1]);
    }

    int l=0;
    int h=dep_a[node1];

    while(l < h) {
        int m = (l+h) / 2;
        int ck1 = get_node(node1, m);
        int ck2 = get_node(node2, m);

        if (ck1 == ck2) {
            h = m;
        } else {
            l = m+1;
        }
    }
    return get_node(node1, h);
}

void solve() {
    dfs(0, 0, 0);

    int end1 = 0;
    int end2 = 1;
    int zeroc = 0;

    // 0, mex(0), all - {0}
    long long pair1 = (long long)n*(long long)(n-1)/(long long)2;
    long long pair2 = 0;
    int zerocnt = cnt_a[0] - 1;
    for (auto it = begin(vct[0]); it != end(vct[0]); ++it) {
        zerocnt -= cnt_a[*it]; 
        pair2 += (long long)cnt_a[*it] * (long long)zerocnt;
        // printf("pair2 zerocnt %d %d\n", pair2, zerocnt);
    }
    pair2 += (long long)(cnt_a[0] - 1);
    res[0] = pair1 - pair2;

    // 1, mex(1), {0} - {0,1}
    pair1 = pair2;
    int node = get_node(1, dep_a[1] - dep_a[0] - 1);
    zeroc = cnt_a[0] - cnt_a[node];
    pair2 = (long long)zeroc * (long long)cnt_a[1];
    res[1] =  pair1 - pair2;

    for(int i=2; i<n; i++) {
        // 2, mex(2), {0,1} - {0,1,2}
        pair1 = pair2;
        pair2 = 0;
        int ck1 = lca(end1, i);
        int ck2 = lca(end2, i);

        if (end1 == 0) {
            if(ck1 == 0 && ck2 == 0) {
                pair2 = (long long)cnt_a[i] * (long long)cnt_a[end2];
                end1 = i;
            } else if(ck2 == end2) {
                pair2 = (long long)cnt_a[i] * (long long)zeroc;
                end2 = i;
            } else if(ck2 == i) {
                pair2 = (long long)zeroc * (long long)cnt_a[end2];
            } else {
                res[i] = pair1;
                pair2 = 0;
                break;
            }
        } else {
            if (ck1 == end1) {
                pair2 = (long long)cnt_a[i] * (long long)cnt_a[end2];
                end1 = i;
            } else if(ck2 == end2) {
                pair2 = (long long)cnt_a[i] * (long long)cnt_a[end1];
                end2 = i;
            } else if(ck1 == i || ck2 == i) {
                pair2 = (long long)cnt_a[end1] * (long long)cnt_a[end2];
            } else {
                res[i] = pair1;
                pair2 = 0;
                break;
            }
        }
        res[i] = pair1 - pair2;
    }

    if (pair2) {
        res[n] = 1;
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        
        for (int i=0; i<n; i++) {
            vct[i].clear();
            dep_a[i] = 0;
            for (int j=0; j<20; j++) {
                jmp_a[i][j] = 0;
            }
            cnt_a[i] = 0;
            res[i] = 0;
        }
        res[n] = 0;

        for (int i=0; i<n-1; i++) {
            scanf("%d%d", &u, &v);
            vct[u].push_back(v);
            vct[v].push_back(u);
        }

        solve();

        for (int i=0; i<=n; i++) {
            printf("%lld ", res[i]);
        }
        printf("\n");
    }
}