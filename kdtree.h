#ifndef kdtree
#define kdtree

#include <vector>

using namespace std;

class kdnode {
	public:
	int x, y;
	const void *data;
	kdnode *lt, *gt, *par;
	kdnode *next;
};

class KDTree {

	public:
	KDTree();
	void add(int x, int y, const void *data);
	const void *get(int x, int y);
	bool has(int x, int y);
	void del(int x, int y);
	int size();
	void display();

	private:
	vector<kdnode> nodes;
	kdnode *root;

	int compare(int x, int y, kdnode *n, int depth);
	int search(int x, int y, kdnode **parent_r);
	void insert(kdnode *n);
	void node_display(kdnode *n, int depth);

	kdnode *get_free_node();
	void grow_nodes();
};

#endif
