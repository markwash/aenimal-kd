#ifndef kdtree
#define kdtree

#include <vector>

using namespace std;

class kdnode {
	public:
	double x, y;
	const void *data;
	kdnode *lt, *gt, *par;
	kdnode *next;
};

class KDTree {

	public:
	KDTree();
	void add(double x, double y, const void *data);
	const void *get(double x, double y);
	bool has(double x, double y);
	void del(double x, double y);
	int size();
	void display();

	private:
	vector<kdnode> nodes;
	kdnode *root;

	int compare(double x, double y, kdnode *n, int depth);
	int search(double x, double y, kdnode **parent_r);
	void insert(kdnode *n);
	void node_display(kdnode *n, int depth);

	kdnode *get_free_node();
	void grow_nodes();
};

#endif
