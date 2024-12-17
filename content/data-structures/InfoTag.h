/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Info and Tag structures used for segment tree. Sample for min segment tree.
 */
struct Tag {
  int add = 0;
  void apply(const Tag &t) & {
  }
  bool operator==(const Tag &t) const {
    return add == t.add;
  }
};
struct Info {
  int mn = 1e9;
  void apply(const Tag &t) & {
  }
};
 
Info operator+(const Info &l, const Info &r) { 
  return {min(l.mn, r.mn)};
}

// pred (find first function)
auto predicate = [&](const Info &info) {
	if(info.val >= k) return true;
	k -= info.val;
	return false;
};

