import unittest
import kdtree

class TestKDTree(unittest.TestCase):

	def setUp(self):
		self.k = kdtree.KDTree()
	
	def test_create(self):
		k2 = kdtree.KDTree()
		k3 = kdtree.KDTree(0)
		k4 = kdtree.KDTree(100)

if __name__ == '__main__':
	unittest.main()
