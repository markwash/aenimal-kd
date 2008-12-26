#include "kdtree.h"

#include <iostream>

KDTree::KDTree() {
	root = 0;
}

void KDTree::add(double x, double y, const void * data) {
	kdnode next;
	next.x = x;
	next.y = y;
	next.data = data;
	nodes.push_back(next);
	insert(&nodes.back());
}

const void *KDTree::get(double x, double y) {
	
	kdnode *n;
	int cmp = search(x, y, &n);
	if (n == 0 || cmp != 0) {
		return 0;
	}
	return n->data;

}

bool KDTree::has(double x, double y) {
	
	kdnode *n;
	int cmp = search(x, y, &n);
	if (n == 0 || cmp != 0) {
		return false;
	}
	return true;

}

void KDTree::del(double x, double y) {
	
	kdnode *n;
	int cmp = search(x, y, &n);
	if (n == 0 || cmp != 0) {
		return;
	}

	if (n->par != 0) {
		if (n->par->lt == n) {
			n->par->lt = 0;
		} else {
			n->par->gt = 0;
		}
		n->par = 0;
	}
	
	kdnode *insert_list = 0;
	if (n->lt != 0) {
		n->lt->next = insert_list;
		insert_list = n->lt;
		n->lt = 0;
	}
	if (n->gt != 0) {
		n->gt->next = insert_list;
		insert_list = n->gt;
		n->gt = 0;
	}

	if (n == root) {
		root = 0;
	}
	*n = nodes.back();
	nodes.pop_back();
	
	while (insert_list != 0) {

		n = insert_list;
		insert_list = n->next;
		n->next = 0;
		if (n->lt != 0) {
			n->lt->next = insert_list;
			insert_list = n->lt;
			n->lt = 0;
		}
		if (n->gt != 0) {
			n->gt->next = insert_list;
			insert_list = n->gt;
			n->gt = 0;
		}
		insert(n);

	}

}

int KDTree::size() {
	return nodes.size();
}

void KDTree::display() {
	cout << endl;
	node_display(root, 0);
}

void KDTree::node_display(kdnode *n, int depth) {

	for (int i = 0; i < depth; i++) {
		cout << "  ";
	}
	if (n == 0) {
		cout << "N" << endl;
		return;
	}
	cout << n->x << ", " << n->y << endl;
	node_display(n->lt, depth + 1);
	node_display(n->gt, depth + 1);
}

int KDTree::compare(double x, double y, kdnode *n, int depth) {

	if (x == n->x && y == n->y) {
		return 0;
	}

	if (depth % 2 == 0) {
		if (x < n->x) {
			return -1;
		} else {
			return 1;
		}
	} else {
		if (y < n->y) {
			return -1;
		} else {
			return 1;
		}
	}
}

int KDTree::search(double x, double y, kdnode **parent_r) {

	*parent_r = 0;
	
	kdnode *cur = root;
	int cmp = 0;
	int depth = 0;
	while (cur != 0) {

		*parent_r = cur;
		cmp = compare(x, y, cur, depth);
		if (cmp < 0) {
			cur = cur->lt;
		} else if (cmp > 0) {
			cur = cur->gt;
		} else {
			break;
		}

	}

	return cmp;
}
		

void KDTree::insert(kdnode *n) {

	n->lt = 0;
	n->gt = 0;

	kdnode *parent;
	int cmp = search(n->x, n->y, &parent);
	n->par = parent;
	if (parent == 0) {
		root = n;
	} else if (cmp < 0) {
		parent->lt = n;
	} else {
		parent->gt = n;
	}
}



/*kdnode *KDTree::pop_freelist() {
	if (freelist == 0) {
		grow_freelist();
	}
	kdnode *next = freelist;
	freelist = freelist->next;
	next->next = 0;
	return next;
}

void KDTree::grow_freelist() {
	freelist = new kdnode[10];
	for (int i = 0; i < 9; i++) {
		freelist[i].next = &freelist[i + 1];
	}
	freelist[9].next = 0;
}*/


