from distutils.core import setup, Extension

extmod = Extension('pycsv',
                   include_dirs = ['../extras/libcsv-3.0.0/'],
                   libraries = ['csv'],
                   library_dirs = ['../extras/libcsv-3.0.0/'],
                   sources = ['pycsv/pycsvmodule.c'])

setup (name = 'pycsv',
       version = '1.0',
       description = 'A C wrapper for libcsv',
       ext_modules = [extmod])
