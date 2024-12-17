/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
#pragma once

#define point complex<lld>
#define X real()
#define Y imag()
#define PI 3.141592653589793238462

lld dot(point x, point y){ // accurate
   return (conj(x) * y).X ;
}

lld cross(point x, point y){ // accurate
   return (conj(x) * y).Y  ;
}

point rotate(point x, lld angle, point p = point(0, 0)){ // precision
   // rotate point x w.r.t. point p with 'angle' Rad. similar scaling
   // default rotation is done w.r.t. origin (0, 0) counterclockwise
   return (x - p) * polar((lld)1.0, angle) + p ;
}

lld angle(point v, point w) { // precision
   lld cosTheta = dot(v,w) / abs(v) / abs(w);
   return acos(max((lld)-1.0, min((lld)1.0, cosTheta)));
}

lld orient(point a, point b, point c){ // accurate
   // orient(a, b, c) = ab X ac
   // positive if C is on left side of ab (counterclockwise of ab)
   return cross(b-a, c-a);
}

bool isConvex(vector<point> p) { // accurate
   // check if polygon is convex, points in the order of indices
   bool hasPos=false, hasNeg=false;
   for (int i=0, n=p.size(); i<n; i++) {
      lld o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
      if (o > 0) hasPos = true;
      if (o < 0) hasNeg = true;
   }
   return !(hasPos && hasNeg);
}

bool half(point p) { // true if angle is in [0, PI) false if [PI, 2*PI)
   assert(p.X != 0 || p.Y != 0); // the argument of (0,0) is undefined
   return p.Y > 0 || (p.Y == 0 && p.X > 0);
}

void polarSort(vector<point> &v) { // accurate
// sorts point in increasing order of their angle from X axis counter clockwise
   sort(v.begin(), v.end(), [&](point x, point y){
      return make_tuple(!half(x), 0) < make_tuple(!half(y), cross(x, y));
  });
}

point intersectionLine(point a, point b, point p, point q) { // precision
   // finds intersection of infinite lines AB and PQ
   lld c1 = cross(p - a, b - a), c2 = cross(q - a, b - a);
   return (c1 * q - c2 * p) / (c1 - c2); // undefined if parallel
}

point project(point p, point v){ // precision
   // Project p onto vector v (line ov)
   return v * dot(p, v) / norm(v);
}

point reflect(point p, point a, point b){ // precision
   // reflect point p across line passing through ab
   return a + conj((p - a) / (b - a)) * (b - a);
}
