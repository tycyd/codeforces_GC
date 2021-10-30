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

const int N = 5e5 + 4;
int st[4 * N];

// bottom to up
/*
void build(int t[]) {  // build the tree
  for (int i = n - 1; i > 0; --i) {
    t[i] = max(t[i<<1], t[i<<1|1]);
  }
}

void modify(int t[], int p, int value) {  // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1) {
      t[p>>1] = max(t[p], t[p^1]);
  }
}

int query(int t[], int l, int r) {  // sum on interval [l, r)
  int res = -INF;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, t[l++]);
    if (r&1) res = max(res, t[--r]);
  }
  return res;
}
*/

// up to bottom
int update(int p , int l , int r , int pos , int v){
    if(pos < l || pos > r)
        return st[p];
    if(l == r)
        return st[p] = v;
    int mid = (l + r) / 2;
    return st[p] = max(update(p * 2 , l , mid , pos , v) , update(p * 2 + 1 , mid + 1 , r , pos , v));
}
 
int query(int p , int l , int r , int i , int j){
    if(l > j || r < i)
        return 0;
    if(l >= i && r <= j)
        return st[p];
    int mid = (l + r) / 2;
    return max(query(p * 2 , l , mid , i , j) , query(p * 2 + 1 , mid + 1 ,r , i , j));
}
 
vector<int> build_next(vector<int> &a , int n) {
    vector<int> nxt(n + 1);
    for (int i = n; i >= 1; i--) {
        nxt[i] = i + 1;
        while (nxt[i] <= n && a[nxt[i]] < a[i])
            nxt[i] = nxt[nxt[i]];
    }
    return nxt;
}

/*
min(b1, b2) < min(b2, b3)
dp[i]
t1 => 1. beginning of list 
t2 => max(dp[j]) + 1   (j < i, a[j] <= a[i])
t3 => max(dp[j]) + 2   (j < i-1, a[j] <= a[i])
*/
int main() {
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for(int i = 1 ; i <= n ; ++i)
            cin >> a[i];
        vector<int> nxt = build_next(a , n) , dp(n + 1 , 0);
 
        vector<vector<int>> adj(n + 1 , vector<int>());
        for(int i = 1 ; i <= n ; ++i){
            dp[i] = 1 + query(1 , 1 , n , 1 , a[i]);
            if(i > 1)
                dp[i] = max(dp[i] , 2);
            
            if(nxt[i] <= n)
                adj[nxt[i]].push_back(i);
            for(int x : adj[i])
                update(1 , 1 , n , a[x] , query(1 , 1 , n , a[x] , a[x]) + 1);
            update(1 , 1 , n , a[i] , dp[i]);
        }
 
        cout << st[1] << "\n";
        for(int i = 0 ; i <= 4 * n ; ++i)
            st[i] = 0;
    }
}