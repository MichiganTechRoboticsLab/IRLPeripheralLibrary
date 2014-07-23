import sys
import os
from util import *

# Set up build dir
AddOption(
    '--release',
    action='store_true',
    help='release build',
    default=False)

AddOption(
    '--verbose',
    action='store_true',
    help='Display verbose build',
    default=True
    )



colors = {}
colors['cyan']   = '\033[96m'
colors['purple'] = '\033[95m'
colors['blue']   = '\033[94m'
colors['green']  = '\033[92m'
colors['yellow'] = '\033[93m'
colors['red']    = '\033[91m'
colors['end']    = '\033[0m'

#If the output is not a terminal, remove the colors
if not sys.stdout.isatty():
   for key, value in colors.iteritems():
      colors[key] = ''

compile_source_message = '%sCompiling %s==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])

compile_shared_source_message = '%sCompiling shared %s==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])

link_program_message = '%sLinking Program %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

link_library_message = '%sLinking Static Library %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

ranlib_library_message = '%sRanlib Library %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

link_shared_library_message = '%sLinking Shared Library %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

java_library_message = '%sCreating Java Archive %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

if not GetOption('verbose'):
    env = Environment(
    CXXCOMSTR = compile_source_message,
    CCCOMSTR = compile_source_message,
    SHCCCOMSTR = compile_shared_source_message,
    SHCXXCOMSTR = compile_shared_source_message,
    ARCOMSTR = link_library_message,
    RANLIBCOMSTR = ranlib_library_message,
    SHLINKCOMSTR = link_shared_library_message,
    LINKCOMSTR = link_program_message,
    JARCOMSTR = java_library_message,
    JAVACCOMSTR = compile_source_message
    )
else:
    env = Environment()

# Set up Construction Environment

env.Append(CCFLAGS=['-std=gnu++11','-Wall'])
env.Append(CPPPATH = ['#/include','#/include/thirdparty/vectornav'])
env.Append(LIBPATH = ['/usr/lib', '/usr/lib64'])

variant_dir = '#/'

if GetOption('release'):
    variant_dir += 'build/release'
else:
    env.Append(CCFLAGS = ["-DDEBUG","-g"])
    variant_dir += 'build/debug'


    
bin_dir = '#/bin'    
lib_dir = '#/lib'    

env.Append(LIBPATH = [lib_dir])
    
SConscript('src/SConscript',
           variant_dir=variant_dir,
           duplicate=False,
           exports="env variant_dir bin_dir lib_dir")
