import Options
from os import unlink, symlink, popen
from os.path import exists

srcdir = '.'
blddir = 'build'
VERSION = '0.0.1'

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')

  mecab_config = conf.find_program('mecab-config', var = 'MECAB_CONFIG', mandatory = True)
  mecab_libdir = popen("%s --libs-only-L" % mecab_config).readline().strip()
  conf.env.append_value('LIBPATH_MECAB', mecab_libdir)
  conf.env.append_value('LIB_MECAB', 'mecab')
  mecab_includedir = popen("%s --inc-dir" % mecab_config).readline().strip()
  conf.env.append_value('CPPPATH_MECAB', '-I' + mecab_includedir)

def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.target = 'binding'
  obj.source = 'src/mecab_node.cc src/tagger.cc src/binding.cc'
  obj.uselib = 'MECAB'

def shutdown():
  t = 'binding.node'
  if exists('build/default' + t) and not exists(t):
    symlink('build/default/' + t, t)
