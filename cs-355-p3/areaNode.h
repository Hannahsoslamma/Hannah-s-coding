#ifndef H_areanode
#define H_areanode

#include "Area.h"

struct areaNode
{
	Area info;
	int areaId;
	areaNode *u;
	areaNode *d;
	areaNode *l;
	areaNode *r;
};

#endif // H_areanode
