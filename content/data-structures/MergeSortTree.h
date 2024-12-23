/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Mergesort tree, sorted values in every node, use set for point updates.
 * Time: O(\log N)
 * Status: stress-tested
 */
 
// both [l,r] inclusive

#define N 200005
vll Tree[5*N];

// usage: build_tree(a , 0 , 0  , a.size()-1);
void build_tree(vll &a, int cur,int l,int r)  {
  if(l==r)  {
    Tree[cur].push_back(a[l]);
    return ;
  }
  int mid = l+(r-l)/2;
  build_tree(a,2*cur+1 , l , mid ); 
  build_tree(a,2*cur+2 , mid+1 ,r);
  //Merging the two sorted arrays
  merge(Tree[2*cur+1].begin(), Tree[2*cur+1].end(),Tree[2*cur+2].begin(),Tree[2*cur+2].end(),back_inserter(Tree[cur])); 
}


// usage: ll ans = query(0 , 0 , a.size()-1  , lx,  rx , z)
ll query(int cur,int l,int r,int x,int y,ll k) {
   if(r<x||l>y)
     return 0;
   if(x<=l && r<=y) {
    // count <= k
    ll ans = upper_bound(Tree[cur].begin(),Tree[cur].end(),k)-Tree[cur].begin();
    return ans;
   }
   int mid=l+(r-l)/2;
   return query(2*cur+1,l,mid,x,y,k)+query(2*cur+2,mid+1,r,x,y,k);
}

