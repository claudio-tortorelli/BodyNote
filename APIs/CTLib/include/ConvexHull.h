#pragma once

#include <algorithm>
#include <vector>

#include <stack>
#include <stdlib.h>

using namespace std;

typedef int coord_t;         // coordinate type
typedef long long coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2
 
struct CHPoint {
	coord_t x, y;
 
	bool operator <(const CHPoint &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

vector<CHPoint> MonotoneChain(vector<CHPoint> P);
stack<CHPoint> GrahamScan(vector<CHPoint> points);
