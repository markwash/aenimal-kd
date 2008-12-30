import unittest
import kdtree

class TestKDTree(unittest.TestCase):

	def setUp(self):
		self.k = kdtree.KDTree()
	
	def test_create(self):
		k2 = kdtree.KDTree()
		k3 = kdtree.KDTree(0)
		k4 = kdtree.KDTree(100)

	def test_add(self):
		self.k[5.0, 5.0] = "center"

	def test_add_and_get(self):
		self.k[5.0, 5.0] = "center"
		val = self.k[5.0, 5.0]
		self.assertEqual(val, "center")

if __name__ == '__main__':
	unittest.main()
