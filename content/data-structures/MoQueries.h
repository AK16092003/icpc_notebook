/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * Description: Answer offline interval or tree path queries 
 * Usage: Create vector<query> and pass to the mo fn
 * Time: O(N \sqrt Q)
 * Status: stress-tested
 */
 
void remove(int idx){}
void add(int idx){}
ll get_answer(){}
ll BLOCK_SIZE = 700;
 
struct Query {
    ll l, r, idx;
    bool operator<(Query other) const
    {
    	    if (l / BLOCK_SIZE != other.l / BLOCK_SIZE)
	        return make_pair(l,r) < make_pair(other.l , other.r);
		    return (l / BLOCK_SIZE & 1) ? (r < other.r) : (r > other.r);
    }
};
 
vl mo_s_algorithm(vector<Query> queries) {
 
    vector<ll> answers(queries.size());
    sort(queries.begin(), queries.end());
 
    int cur_l = 0;
    int cur_r = -1;
 
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}


