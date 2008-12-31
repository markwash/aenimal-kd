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
		x, y, dist, val = self.k.nn(5.0, 5.0)
		self.assertEquals(x, 5.0)
		self.assertEquals(y, 5.0)
		self.assertEquals(dist, 0.0)
		self.assertEquals(val, 'center')

	def test_near_center(self):
		x, y, dist, val = self.k.nn(4.0, 6.0)
		self.assertEquals(x, 5.0)
		self.assertEquals(y, 5.0)
		self.assertEquals(dist, 2.0)
		self.assertEquals(val, 'center')

	def test_near_bottomleft(self):
		x, y, dist, val = self.k.nn(1.0, 1.0)
		self.assertEquals(x, 0.0)
		self.assertEquals(y, 0.0)
		self.assertEquals(dist, 2.0)
		self.assertEquals(val, 'bottomleft')

	def test_near_left(self):
		x, y, dist, val = self.k.nn(1.0, 5.0)
		self.assertEquals(x, 0.0)
		self.assertEquals(y, 5.0)
		self.assertEquals(dist, 1.0)
		self.assertEquals(val, 'left')

	def test_near_topleft(self):
		x, y, dist, val = self.k.nn(1.0, 9.0)
		self.assertEquals(x, 0.0)
		self.assertEquals(y, 10.0)
		self.assertEquals(dist, 2.0)
		self.assertEquals(val, 'topleft')

	def test_near_top(self):
		x, y, dist, val = self.k.nn(5.0, 9.0)
		self.assertEquals(x, 5.0)
		self.assertEquals(y, 10.0)
		self.assertEquals(dist, 1.0)
		self.assertEquals(val, 'top')

	def test_near_topright(self):
		x, y, dist, val = self.k.nn(7.6, 7.6)
		self.assertEquals(x, 10.0)
		self.assertEquals(y, 10.0)
		self.assertAlmostEquals(dist, 11.52)
		self.assertEquals(val, 'topright')

	def test_near_right(self):
		x, y, dist, val = self.k.nn(15.0, 5.0)
		self.assertEquals(x, 10.0)
		self.assertEquals(y, 5.0)
		self.assertEquals(dist, 25.0)
		self.assertEquals(val, 'right')

	def test_near_bottomright(self):
		x, y, dist, val = self.k.nn(7.6, 2.4)
		self.assertEquals(x, 10.0)
		self.assertEquals(y, 0.0)
		self.assertAlmostEquals(dist, 11.52)
		self.assertEquals(val, 'bottomright')

	def test_near_bottom(self):
		x, y, dist, val = self.k.nn(5.0, 1.0)
		self.assertEquals(x, 5.0)
		self.assertEquals(y, 0.0)
		self.assertEquals(dist, 1.0)
		self.assertEquals(val, 'bottom')

if __name__ == '__main__':
	unittest.main()
