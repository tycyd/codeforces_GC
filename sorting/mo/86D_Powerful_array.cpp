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

/*
2*n*sqr(n)
*/
struct MO {
    int b, l, r, i;

    bool operator<(const MO& ot) const {
        if (b != ot.b) {
            return b < ot.b;
        }
        return r < ot.r;
    }
};

int n, t, B;
LL a[200000], ans[200000], cnt[1000001];
MO mo[200000];

int main() {
    memset(cnt, 0, sizeof cnt);

    cin >> n >> t;
    B = (int)ceil(sqrt(n));
    // B = 450;
    for(int i=0; i<n; i++) {
        cin >> a[i];
    }

    for(int i=0; i<t; i++) {
        cin >> mo[i].l;
        cin >> mo[i].r;
        mo[i].l--;
        mo[i].r--;
        mo[i].i = i;
        mo[i].b = mo[i].l / B;
    }

    sort(mo, mo + t);

    int l=0;
    int r=0;
    LL c=a[0];
    cnt[a[0]] = 1;

    for(int i=0; i<t; i++) {
        while(l > mo[i].l) {
            l--;
            cnt[a[l]]++;
            c += (2 * cnt[a[l]] - 1)*a[l];
        }

        while(l < mo[i].l) {
            c -= (2 * cnt[a[l]] - 1)*a[l];
            cnt[a[l]]--;
            l++;
        }

        while(r > mo[i].r) {
            c -= (2 * cnt[a[r]] - 1)*a[r];
            cnt[a[r]]--;
            r--;
        }

        while(r < mo[i].r) {
            r++;
            cnt[a[r]]++;
            c += (2 * cnt[a[r]] - 1)*a[r];
        }
        ans[mo[i].i]=c;
    }

    for(int i=0; i<t; i++) {
        cout << ans[i] << "\n";
    }
}