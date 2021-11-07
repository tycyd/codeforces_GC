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

struct Point {
    int x;
    int y;
    int i;
};

int n, x, y;
int ofx, ofy;
Point p00[1000], p01[1000], p10[1000], p11[1000];
int l00, l01, l10, l11;

/*
(0,0) - p00
(0,1) - p01
(1,0) - p10
(1,1) - p11

pre process:
set first point as orign (0,0), offset all other points. (gurantee p00 exists)
if all p00, => p00 / 2  until  p00, p11 or p10 or p01

1. if there is p01 or p10
    (p00,p11) (p01,p10)  => E(p00,p01),E(p00,p10),E(p11,p01),E(p11,p10) are odd.
2. if there is p00 and p11
    (p00) (p11) => 
        E(p00) E(p11) => sqr( (2x)^2 + (2y)^2 )     =>  sqr ( 4(x^2+y^2) )   
        E(p00,p11)    => sqr( (2x+1)^2 + (2y+1)^2 ) =>  sqr ( 2(2(x^2 + y^2 + x + y) + 1) )
        => E(p00) E(p11) != E(p00,p11)
    prove:
        (2x+1)^2 + (2y+1)^2
        4x^2 + 4x + 1   +   4y^2 + 4y + 1
        4(x^2 + y^2) + 4(x + y) + 2
        4(x^2 + y^2 + x + y) + 2
        2(2(x^2 + y^2 + x + y) + 1)   !=   4(x^2+y^2)
*/

void count(int x, int y, int i) {
    if(x%2 && y%2) {
        // 1, 1
        p11[l11].x = x;
        p11[l11].y = y;
        p11[l11].i = i;
        l11++;
    } else if(x%2) {
        // 1, 0
        p10[l10].x = x;
        p10[l10].y = y;
        p10[l10].i = i;
        l10++;
    } else if(y%2) {
        // 0, 1
        p01[l01].x = x;
        p01[l01].y = y;
        p01[l01].i = i;
        l01++;
    } else {
        // 0 0
        p00[l00].x = x;
        p00[l00].y = y;
        p00[l00].i = i;
        l00++;
    }
}

void solve() {
    // 1. if there is p01 or p10
    // (p00,p11) (p01,p10)  => E(p00,p01),E(p00,p10),E(p11,p01),E(p11,p10) are odd.
    if (l01 || l10) {
        cout << l00 + l11 << "\n";
        for(int i=0; i<l00; i++) {
            cout << p00[i].i << " ";
        }
        for(int i=0; i<l11; i++) {
            cout << p11[i].i << " ";
        }
        return;
    }

    /* if there is p00 and p11, (p00) (p11)
    (p00) (p11) => 
        E(p00) E(p11) => sqr( (2x)^2 + (2y)^2 )     =>  sqr ( 4(x^2+y^2) )   
        E(p00,p11)    => sqr( (2x+1)^2 + (2y+1)^2 ) =>  sqr ( 2(2(x^2 + y^2 + x + y) + 1) )
        => E(p00) E(p11) != E(p00,p11)
    */
   if (l11) {
       cout << l00 << "\n";
        for(int i=0; i<l00; i++) {
            cout << p00[i].i << " ";
        }
        return;
   }
}

void debug_t(Point a[], int l) {
    for(int i=0; i<l; i++) {
        cout << a[i].i << " ";
    }
    cout << "\n";
}

int main() {
    l00 = l01 = l10 = l11 = 0;

    // set first point as orign (0,0), offset all other points. (gurantee p00 exists)
    cin >> n;
    cin >> ofx >> ofy;
    p00[0].x = p00[0].y = 0;
    p00[0].i = 1;
    l00 = 1;

    for(int i=1; i<n; i++) {
        cin >> x >> y;
        x -= ofx;
        y -= ofy;

        count(x, y, i+1);
    }

    // if all p00, => p00 / 2  until  p00, p11 or p10 or p01
    if(l01 == 0 && l10 == 0 && l11 == 0) {
        bool scale = true;
        while(scale) {
            for(int i=0; i<l00; i++) {
                p00[i].x /= 2;
                p00[i].y /= 2;

                if(p00[i].x % 2 || p00[i].y % 2) {
                    scale = false;
                }
            }
        }
        
        int _l00 = l00;
        l00 = 0;
        for(int i=0; i<_l00; i++) {
            count(p00[i].x, p00[i].y, p00[i].i);
        }
    }

    /*
    cout << "l00:" << l00 << "\n";
    debug_t(p00, l00);
    cout << "l01:" << l01 << "\n";
    debug_t(p01, l01);
    cout << "l10:" << l10 << "\n";
    debug_t(p10, l10);
    cout << "l11:" << l11 << "\n";
    debug_t(p11, l11);
    */

    solve();
}