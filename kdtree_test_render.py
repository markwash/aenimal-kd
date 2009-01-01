import unittest
import kdtree
import numpy as N

class TestKDTreeRender(unittest.TestCase):

	def setUp(self):
		self.k = kdtree.KDTree()
		self.color = N.array((255, 128, 0))
		self.arr = N.zeros((100, 100, 3))
	
	def test_render_simple(self):
		self.k.render_simple(self.arr)
	

if __name__ == '__main__':
	unittest.main()
