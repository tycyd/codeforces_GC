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

int n;
int r;

/*
sx: guess orignal value of x
sum: sum of total guess value
r: returned x/n

c = n - (sum + sx) % n

r  = (sum + x + n - (sum + sx) % n) / n
r2 = (sum + sx + n - (sum + sx) % n) / n

if r==r2, x >= sx
else x < sx
*/
int main() {
    cin >> n;

    int l = 1;
    int h = n - 1;
    int sum = 0;
    
    while(l < h) {
        int sx = (l + h + 1) / 2;
        int c = n - (sum + sx) % n;

        cout << "+ " << c << "\n"; 
        fflush(stdout);
        cin >> r;

        if (r == (sum + sx + c) / n) {
            l = sx;
        } else {
            h = sx - 1;
        }

        sum += c;
    }

    cout << "! " << sum + l << "\n";
    fflush(stdout);
}