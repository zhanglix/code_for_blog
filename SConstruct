#!/usr/bin/python
env = Environment();
env.PrependUnique(CCFLAGS=['-g', '-I/Users/j/include', '-I/usr/include/c++/4.2.1']);

env.Program(target = 'bianrySearchTest', source = 'binarySearchTest.cpp', LIBS=['gtest_main', 'gtest'], LIBPATH=["/Users/j/lib"])
