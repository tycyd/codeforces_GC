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

int n, m;
char sb, c;
int u, v, k, wu, wv;
map<int, map<int, char>> mp;
map<int, set<int>> ans1;
map<int, set<int>> ans2;

int main() {
    cin >> n >> m;
    
    for(int i=0; i<m; i++) {
        cin >> sb;
        if (sb == '?') {
            cin >> k;

            if (k % 2) {
                // odd
                if (ans1.size()) {
                    cout << "YES\n";
                } else {
                    cout << "NO\n";
                }
            } else {
                // even
                if (ans2.size()) {
                    cout << "YES\n";
                } else {
                    cout << "NO\n";
                }
            }

        } else {
            cin >> u >> v;
            wu = min(u, v);
            wv = max(u, v);
            if (sb == '+') {
                cin >> c;
                mp[u][v] = c;
                if (mp[v].find(u) != mp[v].end()) {
                    ans1[wu].insert(wv);
                    if (c == mp[v][u]) {
                        ans2[wu].insert(wv);
                    }
                }
            } else {
                mp[u].erase(v);
                if (ans1.find(wu) != ans1.end() &&
                    ans1[wu].find(wv) != ans1[wu].end()) {
                    ans1[wu].erase(wv);
                    if(!ans1[wu].size()) {
                        ans1.erase(wu);
                    }
                }

                if (ans2.find(wu) != ans2.end() &&
                    ans2[wu].find(wv) != ans2[wu].end()) {
                    ans2[wu].erase(wv);
                    if(!ans2[wu].size()) {
                        ans2.erase(wu);
                    }
                }
            }
        }
    }
}
