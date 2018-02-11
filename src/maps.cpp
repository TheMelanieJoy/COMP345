#include <string>
using namespace std;

struct mapLink
{
	//... payload ...
	region *region1, *region2;
	mapLink *prev_link_region1, *next_link_region1,
		*prev_link_region2, *next_link_region2;
};

struct region
{
	string owner;
	int tokens;

	mapLink *first_link, *last_link;

	region *prev_region, *next_region;
};

class map {
	region *first_region, *last_region;

	void addRegion(region *r) {
		if (!first_region) {
			first_region = r;
			last_region = r;
		}
		else {
			r->prev_region = last_region;
			last_region->next_region = r;
		}
	}

	void addLink(region *r1, region *r2) {
		mapLink l;
		l.region1 = r1;
		l.region2 = r2;

		if (r1->first_link) {
			r1->first_link = &l;
			r1->last_link = &l;
		}
		else {
			l.prev_link_region1 = r1->last_link;

			if (r1->last_link->region1 == r1)
				r1->last_link->next_link_region1 = &l;
			else
				r1->last_link->next_link_region2 = &l;

			r1->last_link = &l;
		}


		if (r2->first_link) {
			r2->first_link = &l;
			r2->last_link = &l;
		}
		else {
			l.prev_link_region2 = r2->last_link;

			if (r2->last_link->region2 == r2)
				r2->last_link->next_link_region2 = &l;
			else
				r2->last_link->next_link_region1 = &l;

			r2->last_link = &l;
		}
	}
};