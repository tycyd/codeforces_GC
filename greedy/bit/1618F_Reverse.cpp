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
#include <bitset>

using namespace std;

typedef long long LL;

LL x, y, x1, x2, x3, x4;
LL len, len1, len2, len3, len4;
/*
2,  8

10
1
*/
LL get(LL v, int l, int r, int ln) {

    LL mk = 0;
    for(int i=0; i<l; i++) {
        mk <<= 1;
        mk += 1;
    }
    if (l > 0 && (mk << ln) >= 0) {
        v += (mk << ln);
    }
    for(int i=0; i<r && v >= 0 && mk >= 0; i++) {
        v <<= 1;
        v += 1;
    }
    return v;
}

bool solve() {

    x1 = x;
    x2 = 0;
    x3 = 1;
    x4 = (x << 1) + 1;
    
    len2 = 0;
    len3 = 1;

    LL tmp = x;
    while(tmp > 0) {
        x2 *= 2;
        x2 += tmp & 1;

        x3 *= 2;
        x3 += tmp & 1;

        tmp /= 2;

        len++;
        if (x2 > 0) {
            len2++;
        }
        len3++;
    }

    len1 = len;
    len4 = len3;
    while(x1 > 0 && (x1 & 1) == 0) {
        x1 >>= 1;
        len1--;
    }

    for(int l=0; l<64; l++) {
        for(int r=0; r<64; r++) {
            if (get(x1, l, r, len1) == y) return true;
            if (x2 != x && get(x2, l, r, len2) == y) return true;
            if (get(x3, l, r, len3) == y) return true;
            if (get(x4, l, r, len4) == y) return true;
        }
    }

    return false;
}

int main() {
    cin >> x >> y;

    if (x == y || solve()) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}

