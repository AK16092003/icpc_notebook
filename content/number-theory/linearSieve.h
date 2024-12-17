/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds all primes in O(N), computes any multiplicative function
 */
#pragma once

#define maxsz 10000005
int lp[maxsz];
vi pr;

void sieve()
{
	for(int i = 0 ; i < maxsz ; i ++) lp[i] = i;
	lp[0] = 0;
	lp[1] = 0;
	for(int i = 2 ; i < maxsz ; i ++)
	{
		if(lp[i] == i) {	
			pr.pb(i);	
		}
		for(int j = 0 ; (i*pr[j] < maxsz) ; j ++)
		{
			lp[i*pr[j]] = pr[j];
			if((i%pr[j]) == 0)	{
				break;
			}
		}
	}
}



