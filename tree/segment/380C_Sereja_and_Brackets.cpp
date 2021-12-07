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

string s;
int m, l, r;

struct TN {
    int res, rl, rr;
};

TN t[4*1000000];

/*
res — the maximum length of the bracket subsequence
rl — remaining left brackets
rr — remaining right brackets

combine:
res = res1 + res2 + min(rl1, rr2)
rl = rl1 + rl2 - min(rl1, rr2)
rr = rr1 + rr2 - min(rl1, rr2)
*/
void build(const string& s, int v, int tl, int tr) {
    if (tl == tr) {
        t[v].res = 0;
        if (s[tl] == '(') {
            t[v].rl = 1;
            t[v].rr = 0;
        } else {
            t[v].rl = 0;
            t[v].rr = 1;
        }
    } else {
        int tm = (tl + tr) / 2;
        build(s, v*2, tl, tm);
        build(s, v*2+1, tm+1, tr);
        int li = v*2;
        int ri = v*2 + 1;
        t[v].res = t[li].res + t[ri].res + min(t[li].rl, t[ri].rr)*2;
        t[v].rl = t[li].rl + t[ri].rl - min(t[li].rl, t[ri].rr);
        t[v].rr = t[li].rr + t[ri].rr - min(t[li].rl, t[ri].rr);
    }
}

TN query(int v, int tl, int tr, int l, int r) {
    TN ans;
    if (l > r) {
        ans.res = 0;
        ans.rl = 0;
        ans.rr = 0;
        return ans;
    }
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    TN ln = query(v*2, tl, tm, l, min(r, tm));
    TN rn = query(v*2+1, tm+1, tr, max(l, tm+1), r);
    ans.res = ln.res + rn.res + min(ln.rl, rn.rr)*2;
    ans.rl = ln.rl + rn.rl - min(ln.rl, rn.rr);
    ans.rr = ln.rr + rn.rr - min(ln.rl, rn.rr);
    return ans;
}

int main() {
    cin >> s >> m;
    int n = s.length();
    build(s, 1, 0, n-1);
    while(m--) {
        cin >> l >> r;
        TN res = query(1, 0, n-1, l-1, r-1);
        cout << res.res << "\n";
    }
}
