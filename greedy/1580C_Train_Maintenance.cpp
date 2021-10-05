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

int n, m, op, k, ans;
int x[200001];
int y[200001];
int ps[200001];
int last_a[200001];
int cnt_a[450][450];    //x+y, x
/*
t: train
i: day
x+y=z
if z > sqr(z), then 
    op = 1
        ps[(i+x) * n*z] += 1, ps[(i+x) * n*z + y+1] -= 1    // O(sqr(z)), n: i->m
        last[t] = i
    op = 2
        j=last[t]
        ps[(j+x) * n*z] -= 1, ps[(j+x) * n*z + y+1] += 1    // O(sqr(z)), n: i->m

if z <= sqr(z), then
    op = 1
        l = (x + i) % z
        r = (i - 1) % z
        j: l->r => cnt[z][j] += 1
    op = 1
        l = (x + last[t]) % z
        r = (last[t] - 1) % z
        j: l->r => cnt[z][j] -= 1
*/

void block_modify(int tm, int k, int v) {
    int z = x[k] + y[k];
    int l = (tm + x[k]) % z, r = (tm - 1);
    if (r < 0) {
        r += z;
    }
    r %= z;
    if (l <= r) for (int i = l; i <= r; i ++) cnt_a[z][i] += v;
    else {
        for (int i = 0; i <= r; i ++) cnt_a[z][i] += v;
        for (int i = l; i < z; i ++) cnt_a[z][i] += v;
    }
}

int block_query(int tm) {
    int res = 0;
    for (int i=2; i<450; i++) {
        res += cnt_a[i][tm%i];
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    int sqrm = sqrt(m);
    ans = 0;

    for(int i=0; i<m; i++) {
        scanf("%d %d", &op, &k);
        k--;

        // if ((x[i] + y[i])*(x[i] + y[i]) > m2) {
        if (x[k] + y[k] > sqrm) {
            if(op == 1) {
                // x:2, y:3 => 0 1 2 3 4
                //             
                // add 
                for(int j= i + x[k]; j <= m; j += x[k] + y[k]) {
                    ps[j] += 1;
                    if (j + y[k] <= m) {
                        ps[j + y[k]] -= 1;
                    }
                }

                last_a[k] = i;
            } else {
                // remove
                for(int j= last_a[k] + x[k]; j <= m; j += x[k] + y[k]) {
                    ps[j] -= 1;
                    if (j + y[k] <= m) {
                        ps[j + y[k]] += 1;
                    }
                    // overlap
                    // +1   |   -1
                    if (j < i && j + y[k] >= i) ans --;
                }
            }
        } else {
            if(op == 1) {
                block_modify(i, k, 1);
                last_a[k] = i;
            } else {
                block_modify(last_a[k], k, -1);
            }
        }

        ans += ps[i];
        std::printf("%d\n", ans + block_query(i));
    }
}