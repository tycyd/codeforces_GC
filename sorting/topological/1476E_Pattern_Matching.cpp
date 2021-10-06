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
#include <unordered_map>

using namespace std;

int n, m, k, mt;
char wk[5];
string ptn[100001];
unordered_map<string, int> mp;
vector<int> vc[100001];
bool visited[100001];
bool tmp[100001];
int res[100001];
string str;

bool dfs(char* wk, int i) {
    if (i == k) {
        std::unordered_map<string,int>::const_iterator got = mp.find(wk);
        if ( got == mp.end() ) {
            // cout << "not found";
            return false;
        } else {
            if (mt != got->second) {
                vc[mt].push_back(got->second);
            }
            return true;
            // cout << got->first << " : " << got->second << "\n";
        }
    }

    wk[i] = str[i];
    bool r1 = dfs(wk, i+1);
    wk[i] = '_';
    bool r2 = dfs(wk, i+1);
    return r1 || r2;
}

bool topological_sort(int i, stack<int>* st) {
    if (tmp[i]) {
        // cout << " ts " << i << "\n";
        return false;
    }
    if (visited[i]) {
        return true;
    }
    tmp[i] = true;
    visited[i] = true;

    bool r = true;
    for(vector<int>::iterator it = vc[i].begin(); it != vc[i].end(); ++it) {
        r &= topological_sort(*it, st);
    }

    tmp[i] = false;
    st->push(i);
    return r;
}

bool solve() {

    stack<int> st;
    for (int i=1; i<=n; i++) {
        if (!visited[i]) {
            if(!topological_sort(i, &st)) {
                return false;
            }
            // cout << " ------------------ \n";
        }   
    }

    int idx = 0;
    while (!st.empty()) {
        // cout << " stack " << st.top() << "\n";
        res[idx++] = st.top();
        st.pop();
    }
    return true;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i=1; i<=n; i++) {
        cin >> ptn[i];
        // scanf("%s", &ptn[i]);
        mp.insert(make_pair(ptn[i], i));
    }
    for (int i=1; i<=m; i++) {
        cin >> str;
        cin >> mt;

        for(int j=0; j<k; j++) {
            if (str[j] == ptn[mt][j] || ptn[mt][j] == '_') {
                continue;
            } else {
                cout << "NO\n";
                return 0;
            }
        }

        // scanf("%s", str);
        if(!dfs(wk, 0)) {
            cout << "NO\n";
            return 0;
        }
    }

    if (solve()) {
        cout << "YES\n";
        for(int i=0; i<n; i++) {
            cout << res[i] << " ";
        }
    } else {
        cout << "NO\n";
    }
}
