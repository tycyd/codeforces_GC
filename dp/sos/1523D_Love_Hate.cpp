// Problem: D. Love-Hate
// Contest: Codeforces - Deltix Round, Spring 2021 (open for everyone, rated, Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1523/problem/D
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// #pragma GCC optimize(2)
// #pragma GCC optimize("Ofast","inline","-ffast-math")
// #pragma GCC target("avx,sse2,sse3,sse4,mmx")
#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif
#include <random>
#include <numeric>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<stack>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#include<bitset>
#include<list>
#include<unordered_map>
#define lowbit(x) x&-x
using namespace std;
typedef long long LL;
typedef unsigned long long ull;
template<typename T>
inline void read(T &x)
{
	T f=1;x=0;
	char ch=getchar();
	while(0==isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(0!=isdigit(ch)) x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	x*=f;
}
template<typename T>
inline void write(T x)
{
	if(x<0){x=~(x-1);putchar('-');}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const int inf=0x3f3f3f3f;
const int N=1e6+100;
mt19937_64 eng(time(NULL));
LL s[N];
int cnt[(1<<15)+100];
int a[N];
int main()
{
#ifndef ONLINE_JUDGE
//	freopen("data.in.txt","r",stdin);
//	freopen("data.out.txt","w",stdout);
#endif
//	ios::sync_with_stdio(false);
	int n,m,p;
	read(n),read(m),read(p);
	for(int i=1;i<=n;i++) {
		string str;
		cin>>str;
		for(int j=0;j<m;j++) {
			if(str[j]=='1') {
				s[i]|=(1LL<<j);
			}
		}
	}
	iota(a+1,a+1+n,1);
	shuffle(a+1,a+1+n,eng);
	int ans=0;
	string res;
	for(int t=1;t<=min(50,n);t++) {
		memset(cnt,0,sizeof(cnt));
		int p=a[t];
		vector<int>bits;
		for(int j=0;j<m;j++) {
			if((s[p]>>j)&1) {
				bits.push_back(j);
			}
		}
		int sz=bits.size();
		for(int i=1;i<=n;i++) {//n*p
			int state=0;
			for(int j=0;j<sz;j++) {
				if((s[i]>>bits[j])&1) {
					state|=(1<<j);
				}
			}
			cnt[state]++;
		}
		for(int j=0;j<sz;j++) {//p*2^p
			for(int i=0;i<1<<sz;i++) {
				if(((i>>j)&1)==0) {
					cnt[i]+=cnt[i|(1<<j)];
				}
			}
		}
		for(int i=0;i<1<<sz;i++) {
			if((cnt[i]>=(n+1)/2)&&__popcnt(i)>ans) {
				ans=__popcnt(i);
				res=string(m,'0');
				for(int j=0;j<sz;j++) {
					if((i>>j)&1) {
						res[bits[j]]='1';
					}
				}
			}
		}
	}
	cout<<res<<endl;
	return 0;
}
