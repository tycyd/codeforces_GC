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

int n, u, v;
set<int> fib;
set<int> st[200001];
int cur, pre, cur_cnt, pre_cnt;
set<int> test;

void buildFib() {
    int f0 = 1;
    int f1 = 1;
    int f2 = 2;

    fib.insert(1);
    while (f2 <= 200001) {
        f2 = f0 + f1;
        fib.insert(f2);
        f0 = f1;
        f1 = f2;
    }
}

int dfs(int c, int p, int ttl) {
    int r = 1;
    for(int nxt : st[c]) {
        if (nxt != p) {
            int tmp = dfs(nxt, c, ttl);
            if (tmp == -1) {
                return -1;
            }
            r += tmp;
        }
    }

    if (fib.find(r) != fib.end() && fib.find(ttl - r) != fib.end()) {
        cur = c;
        pre = p;
        cur_cnt = r;
        pre_cnt = ttl - r;
        return -1;
    }

    return r;
}

bool fb(int nd, int ct) {
    if (ct == 1) {
        return true;
    }

    int r = dfs(nd, -1, ct);
    if (r == -1) {
        st[cur].erase(pre);
        st[pre].erase(cur);
        int lcur = cur;
        int lcnt = cur_cnt;
        int pcur = pre;
        int pcnt = pre_cnt;
        return fb(lcur, lcnt) && fb(pcur, pcnt);
    } else {
        return false;
    }
}

void solve() {
    if (fib.find(n) == fib.end()) {
        cout << "NO\n";
        return;
    }
    if(fb(1, n)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

}

int main() {
    cin >> n;
    for(int i=0; i<n-1; i++) {
        cin >> u >> v;
        st[u].insert(v);
        st[v].insert(u);
    }

    buildFib();
    solve();
}