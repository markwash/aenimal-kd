from distutils.core import setup, Extension
setup(name="kdtree", version="1.0",
      ext_modules=[Extension("kdtree", ["kdtree_module.c"], extra_objects=["kdtree.o", "simple_vector.o"])])
