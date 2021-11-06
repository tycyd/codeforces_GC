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

int T;
ll ans;
string s;
int wsa[200000], ada[200000], wsl, adl;

/*
DSAWWAW


WS
AD


 -1  1  1  1
 -1  0 1  2

  (1) 0 1 2 3
-1 0 1 (0) 1

-1(W): min(ps)..  min(ps)..  I, max(ps)  max(ps)
  1(S):  max(ps)..  max(ps)..  I, min(ps) min(ps)
 Between last min and first max
 Between last max and first min

Min(ps) + Max(ps)
Add 1 or -1 

 -1. 1. 1
 -1. 0. 1
*/
bool check(int ps[], int l) {
    int mn, mx;
    int last_min_idx, last_max_idx, first_min_idx, first_max_idx;

    // mn = mx = ps[0];
    mn = mx = 0;
    // last_min_idx = last_max_idx = first_min_idx = first_max_idx = 0;
    last_min_idx = last_max_idx = first_min_idx = first_max_idx = -1;
    // for(int i=1; i<l; i++) {
    for(int i=0; i<l; i++) {
        if(ps[i] < mn) {
            first_min_idx = last_min_idx = i;
            mn = ps[i];
        } else if(ps[i] == mn) {
            last_min_idx = i;
        }
        if (ps[i] > mx) {
            first_max_idx = last_max_idx = i;
            mx = ps[i];
        } else if (ps[i] == mx) {
            last_max_idx = i;
        }
    }

    if (last_min_idx + 1 < first_max_idx || last_max_idx + 1 < first_min_idx) {
        return true;
    } else {
        return false;
    }
}

void solve() {
    
    wsl = adl = ans = 0;
    for(int i=0; i<s.size(); i++) {
        switch (s[i]) {
            case 'W':
                wsa[wsl++] = 1;
                break;
            case 'S':
                wsa[wsl++] = -1;
                break;
            case 'A':
                ada[adl++] = 1;
                break;
            case 'D':
                ada[adl++] = -1;
                break;
        }
    }

    int wmx = wsa[0] > 0 ? wsa[0] : 0;
    int wmn = wsa[0] < 0 ? wsa[0] : 0;
    for(int i=1; i<wsl; i++) {
        wsa[i] += wsa[i-1];
        wmx = max(wmx, wsa[i]);
        wmn = min(wmn, wsa[i]);
    }
    int wlen = wmx - wmn + 1;
    if (wsl == 0) {
        wlen = 1;
    }

    int amx = ada[0] > 0 ? ada[0] : 0;
    int amn = ada[0] < 0 ? ada[0] : 0;
    for(int i=1; i<adl; i++) {
        ada[i] += ada[i-1];
        amx = max(amx, ada[i]);
        amn = min(amn, ada[i]);
    }
    int alen = amx - amn + 1;
    if (adl == 0) {
        alen = 1;
    }

    ll ans1 = (ll)wlen * (ll)alen;
    ll ans2 = (ll)wlen * (ll)alen;
    if(wsl > 1 && check(wsa, wsl)) {
        ans1 = (ll)(wlen-1)*(ll)alen;
    }
    if(adl > 1 && check(ada, adl)) {
        ans2 = (ll)wlen*(ll)(alen-1);
    }
    ans = min(ans1, ans2);
}

int main() {
    cin >> T;
    while(T--) {
        cin >> s;
        solve();
        cout << ans << "\n";
    }
}