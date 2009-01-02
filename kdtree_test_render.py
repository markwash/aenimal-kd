import unittest
import kdtree
import numpy as N

class TestKDTreeRender(unittest.TestCase):

	def setUp(self):
		self.k = kdtree.KDTree()
		self.color = N.array((255, 128, 0), dtype=N.uint8)
		self.k[0, 0] = self.color
		self.arr = N.zeros((10, 10, 3), dtype=N.uint8)
	
	def test_render_simple(self):
		self.k.render_simple(self.arr)
		for x in xrange(10):
			for y in xrange(10):
				for i in xrange(3):
					self.assertEquals(self.arr[x, y, i], self.color[i])
	

if __name__ == '__main__':
	unittest.main()
