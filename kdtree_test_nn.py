import unittest
import kdtree

class TestKDTreeNN(unittest.TestCase):

	def setUp(self):
		self.k = kdtree.KDTree()
		self.k[5.0, 5.0] = 'center'
		self.k[0.0, 0.0] = 'bottomleft'
		self.k[0.0, 5.0] = 'left'
		self.k[0.0, 10.0] = 'topleft'
		self.k[5.0, 10.0] = 'top'
		self.k[10.0, 10.0] = 'topright'
		self.k[10.0, 5.0] = 'right'
		self.k[10.0, 0.0] = 'bottomright'
		self.k[5.0, 0.0] = 'bottom'

	def test_exact_center(self):
		n = self.k.nn(5.0, 5.0)

if __name__ == '__main__':
	unittest.main()
