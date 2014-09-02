#!/usr/bin/python
import os

env = Environment();
def run_test(env, target, source):
    os_name = os.uname()[0]
    ld_path_name = "LD_LIBRARY_PATH";
    if os_name == "Linux":
        ld_path_name = "LD_LIBRARY_PATH";
    elif os_name == "Darwin":
        ld_path_name = "DYLD_LIBRARY_PATH"
    elif os_name == "Windows":
        ld_path_name = "PATH"
        raise  "Sorry! Not Implemented for Windows Yet!"
    cmd = "/usr/bin/env %s=%s " % (ld_path_name, env['ENV']['LIB'])
    cmd += str(source[0].abspath)
    print cmd
    ret =  os.system(cmd);
    if ret == 0:
        os.system("echo Success! > " + target[0].abspath)
    else:
        os.system("echo Failed! > " + target[0].abspath)
    return ret
bld = Builder(action = run_test)
env.Append(BUILDERS = {'runUnitTest' : bld})
def UnitTest(env, *nargs, **kwargs): 
    targets = env.Program(*nargs, **kwargs);

    ret = [];
    for cmd in targets:
        t = str(cmd) + ".report";
        test = env.runUnitTest(t, cmd)
        env.Alias('check', test)
        ret.append(t);
    AlwaysBuild(ret);
    Default(targets);
    return ret
env.AddMethod(UnitTest, 'UnitTest');

env.PrependUnique(CCFLAGS=['-g', '-I/Users/j/include']);
env.AppendENVPath('LIB', '/Users/j/lib')
env.UnitTest(target = 'binarySearchTest', 
             source = 'binarySearchTest.cpp',
             LIBS=['gtest_main', 'gtest'], 
             LIBPATH=["/Users/j/lib"])

