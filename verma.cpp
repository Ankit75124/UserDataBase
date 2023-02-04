#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
struct Tree {
  vector<vector<pair<int,int>>> a;
  vector<int> nm,sm,mx,su,cs;
  int n,ans1=2147483647,ans2=0;
  void init() {
    cin >> n;
    a.resize(n+1);cs.resize(n+1);
    nm.resize(n+1);sm.resize(n+1);
    mx.resize(n+1);su.resize(n+1);
    for(int i=0;i<=n;++i) {
      nm[i]=sm[i]=mx[i]=cs[i]=su[i]=0;
      a[i].clear();
    }
    int x,y,z;
    for(int i=1;i<n;++i) {
      cin >> x >> y >> z;
      a[x].push_back({y,z});
      a[y].push_back({x,z});
    }
  }
  void dfs1(int p,int fa) {
    su[p]=1;cs[p]=0;mx[p]=0;
    for(auto to:a[p]) {
      if(to.first==fa) continue;
      dfs1(to.first,p);
      su[p]+=su[to.first];
      mx[p]=max(mx[p],su[to.first]);
      cs[p]+=cs[to.first]+su[to.first]*to.second;
    }
    mx[p]=max(mx[p],n-su[p]);
  }
  void dfs2(int p,int fa) {
    for(auto to:a[p]) {
      if(to.first==fa) continue;
      dfs2(to.first,p);
      int T=(sm[to.first]+nm[to.first]*to.second)%mod;
      ans2+=(T*nm[p]%mod+sm[p]*nm[to.first]%mod)%mod;
      nm[p]+=nm[to.first];
      sm[p]=(sm[p]+T)%MOD;
    }
    nm[p]++;
  }
  void solve() {
    init();
    dfs1(1,0);
    int um=n,x=0;
    for(int i=1;i<=n;++i)
      if(mx[i]<um) {
        um=mx[i];x=i;
      }
    dfs1(x,0);
    ans1=cs[x]%mod;
    dfs2(1,0);
    for(int i=1;i<=n;++i) ans2=(ans2+sm[i])%mod;
  }
};
Tree T[10001];
int n,a[10001],answer,sum;
vector<int> e,q;
signed main() {
  cin >> n;
  for(int i=1;i<=n;++i) {
    T[i].solve();
    sum+=T[i].n;
    q.push_back(T[i].n);
  }
  for(int i=1,x;i<n;++i) {
    cin >> x;
    e.push_back(x);
  }
  sort(e.begin(),e.end());
  sort(q.begin(),q.end());
  reverse(e.begin(),e.end());
  for(int i=1;i<=n;++i)
    answer=(answer+T[i].ans2+T[i].ans1*(sum-T[i].n)%mod)%mod;
  for(int i=0;i<n-1;++i)
    answer=(answer+q[i]*(sum-q[i])%mod*e[i])%mod;
  cout << answer << endl;
}