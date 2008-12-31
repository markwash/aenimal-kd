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

	def test_set_nonseq(self):
		d = {}
		# self.k[d] = 'error'
		self.assertRaises(KeyError, self.k.__setitem__, d, 'error')

	def test_set_nonduo(self):
		# self.k[(5.0)] = 'error'
		self.assertRaises(KeyError, self.k.__setitem__, (5.0), 'error')

	def test_set_nonnum(self):
		# self.k['left', 'right'] = 'error'
		self.assertRaises(KeyError, self.k.__setitem__, ('left', 'right'), 'error')
		# self.k[1.0, 'right'] = 'error'
		self.assertRaises(KeyError, self.k.__setitem__, (1.0, 'right'), 'error')
		# self.k['left', 1.0] = 'error'
		self.assertRaises(KeyError, self.k.__setitem__, ('left', 1.0), 'error')

	def test_set_int_and_get_int(self):
		self.k[0, 0] = 'bottomleft'
		val = self.k[0, 0]
		self.assertEquals(val, 'bottomleft')

	def test_set_int_and_get(self):
		self.k[0, 0] = 'bottomleft'
		val = self.k[0.0, 0.0]
		self.assertEquals(val, 'bottomleft')

	def test_set_and_get_int(self):
		self.k[0.0, 0.0] = 'bottomleft'
		val = self.k[0, 0]
		self.assertEquals(val, 'bottomleft')

	def test_get_nonexist(self):
		# self.k[1.0, 1.0]
		self.assertRaises(KeyError, self.k.__getitem__, (1.0, 1.0))

	def test_add_and_del(self):
		self.k[5.0, 5.0] = 'center'
		del self.k[5.0, 5.0]


if __name__ == '__main__':
	unittest.main()
