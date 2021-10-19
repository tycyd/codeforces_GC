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

int t, n, A, B;
string x;
char ans[50];
int memo[41][41][41][41];
int EMPTY = 50;
int INF = 60;

/*
memo i,red mod, red count, black mod
40 40 40 40
*/

int dfs(int idx, int rm, int rc, int bm) {
    if (idx == n) {
        if(rm == 0 && bm == 0 && rc > 0 && rc < n) {
            // cout << "found " << rc << "\n";
            int res = abs(rc - (n - rc));
            memo[idx][rm][rc][bm] = res;
            return abs(rc - (n - rc));
        } else {
            return INF;
        }
    }

    if (memo[idx][rm][rc][bm] != EMPTY) {
        return memo[idx][rm][rc][bm];
    }

    int d = x[idx] - '0';
    int rm2 = (rm * 10 + d) % A;
    int a = dfs(idx + 1, rm2, rc + 1, bm);
    int bm2 = (bm * 10 + d) % B;
    int b = dfs(idx + 1, rm, rc, bm2);

    memo[idx][rm][rc][bm] = min(a, b);
    return memo[idx][rm][rc][bm];
}

void solve() {
    int best = dfs(0, 0, 0, 0);
    if (best >= EMPTY) {
        cout << -1 << '\n';
        return;
    }

    // cout << best << "best\n";

    int acnt = 0;
    int amod = 0;
    int bmod = 0;
    for(int i=0; i<n; i++) {
        int d = x[i] - '0';
        int rm = (amod * 10 + d) % A;
        int bm = (bmod * 10 + d) % B;

        int r1 = memo[i+1][rm][acnt+1][bmod];
        int r2 = memo[i+1][amod][acnt][bm];

        if (r1 == best) {
            ans[i] = 'R';
            acnt++;
            amod = rm;
        } else if (r2 == best) {
            ans[i] = 'B';
            bmod = bm;
        } else {
            cout << "shoud not happen.\n";
        }
    }
    ans[n] = '\0';
    cout << ans << '\n';
}

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        cin >> A;
        cin >> B;
        cin >> x;

        for (int i=0; i<41; i++)
            for (int j=0; j<41; j++)
                for (int k=0; k<41; k++)
                    for (int l=0; l<41; l++)
                        memo[i][j][k][l] = EMPTY;
        for (int i=0; i<n; i++) {
            ans[i] = '\0';
        }
        solve();
    }
}