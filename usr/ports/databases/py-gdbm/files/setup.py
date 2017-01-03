#!/usr/bin/env python
# To use:
#       python setup.py install
#

__version__ = "$FreeBSD: tags/RELEASE_10_3_0/databases/py-gdbm/files/setup.py 340872 2014-01-24 00:14:07Z mat $"

try:
    import distutils
    from distutils import sysconfig
    from distutils.command.install import install
    from distutils.core import setup, Extension
except:
    raise SystemExit, "Distutils problem"

install.sub_commands = filter(lambda (cmd, avl): 'egg' not in cmd,
                              install.sub_commands)

prefix = sysconfig.PREFIX
inc_dirs = [prefix + "/include"]
lib_dirs = [prefix + "/lib"]
libs = ["gdbm"]

setup(name = "gdbm",
      description = "GDBM Extension to Python",

      ext_modules = [Extension('gdbm', ['gdbmmodule.c'],
                               include_dirs = inc_dirs,
                               libraries = libs,
                               library_dirs = lib_dirs)]
      )
