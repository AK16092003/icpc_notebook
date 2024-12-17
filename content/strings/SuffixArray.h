/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

struct sufar {
	string s;
	vector<int>lcp,order,rank;
	int n;
	sufar(string _s) {
	    s=_s +'$';
	    n=s.length();
	}
	void build() {
	    order.resize(n);
	    rank.resize(n);
	    {
		    vector<pair<int,int>>temp;
		    for(int i=0;i<n;i++){
		        temp.push_back({s[i]-'a',i});
		    }
		    sort(temp.begin(),temp.end());
		    for(int i =0;i<n;i++){
		        order[i]=temp[i].second;
		    }
		    rank[order[0]]=0;
		    for(int i=1;i<n;i++){
		        rank[order[i]]=rank[order[i-1]]+(temp[i].first!=temp[i-1].first);
		    }
	    }
 
		int k=0;
		vector<int>order_t(n,0),rank_t(n,0);
		while((1<<k)<n) {
		   for(int i =0;i<n;i++){
		      (order[i]-=(1<<k)-n)%=n;
		   }
		   vector<int>cnt(n,0),pos(n,0);
		   for(auto &c:rank)
			    cnt[c]++;
		   for(int i=1;i<n;i++)
			    pos[i]=pos[i-1]+cnt[i-1];
		   for(int i=0;i<n;i++)
			    order_t[pos[rank[order[i]]]++]=order[i];
			    order=order_t;
		   for(int i=1;i<n;i++){
			    pair<int,int>old_val={rank[order[i-1]],rank[(order[i-1]+(1<<k))%n]};
			    pair<int,int>new_val={rank[order[i]],rank[(order[i]+(1<<k))%n]};
			    rank_t[order[i]]=rank_t[order[i-1]]+(old_val!=new_val);
		   }
		   rank=rank_t;
		   k++;
		}
 	}
 
 
	void build_lcp(){
	   lcp.resize(n,0);
	   int k=0;
	   for(int i=0;i<n-1;i++){
	      int pos=rank[i];
	      int j=order[pos-1];
	      while(s[i+k]==s[j+k]) k++;
	      lcp[pos]=k;
		  k=max(k-1,(int)0);
		}
	   }
};


