#!/usr/bin/python
import os
import os.path

env = Environment();

def enable_tcmalloc_heap_checker_if_possible(env):
    file_name = env['LIBPREFIX'] + "tcmalloc" + env['SHLIBSUFFIX'];
    os_name = os.uname()[0]
    if os_name != "Linux":
        return False
    libpath = ['/usr/lib',
               '/usr/lib64', 
               '/usr/local/lib', 
               '/usr/local/lib64'] 
    if env.has_key('LIBPATH'):
        libpath += env['LIBPATH']

    ld_preload_name = "LD_PRELOAD"
    for d in libpath:
        tcmalloc_full_path = os.path.join(d, file_name)
        if os.path.exists(tcmalloc_full_path):
            s = "%s=%s" % (ld_preload_name, tcmalloc_full_path)
            s += " HEAPCHECK=normal "
            env['heap_check_env'] = s;
            return True
    return False

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
    
    cmd = "/usr/bin/env ";
    if env.has_key('LIBPATH'):
        cmd += "%s=%s " % (ld_path_name, ":".join(env['LIBPATH']))
    if env.has_key('heap_check_env'):
        cmd += env['heap_check_env'] + " "

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
        a_cmd = "check_" + str(cmd);
        test = env.runUnitTest(t, cmd)
        env.Alias(a_cmd, test)
        env.Alias('check', a_cmd)
        ret.append(t);
    AlwaysBuild(ret);
    Default(targets);
    return ret
env.AddMethod(UnitTest, 'UnitTest');

env.PrependUnique(CCFLAGS=['-g', '-std=c++0x'])
env.PrependUnique(CCFLAGS=['-g', '-std=c++0x'])

if os.path.isdir('/Users/j'): ##just for my mac :)##
    env.AppendUnique(LIBPATH=['/Users/j/lib'])
    env.AppendUnique(CPPPATH=['/Users/j/include']); 

env['gmock_libs'] =['gtest_main', 'gmock', 'gtest', 'pthread']
enable_tcmalloc_heap_checker_if_possible(env)

Export('env')

SConscript('SConscript', variant_dir='build')


