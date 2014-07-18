import os
# Set up build dir
AddOption(
    '--release',
    action='store_true',
    help='release build',
    default=False)

# Set up Construction Environment
env = Environment()
env.Append(CCFLAGS='-std=gnu++11')
env.Append(CPPPATH = [os.getcwd() + '/include'])
env.Append(LIBPATH = ['/usr/lib', '/usr/lib64'])

variant_dir = os.getcwd() + '/'

if GetOption('release'):
    variant_dir += 'build/release'
else:
    env.ParseFlags("-DDEBUG -g")
    variant_dir += 'build/debug'

env.Append(LIBPATH = [variant_dir + '/devices'])
    
SConscript('src/SConscript',
           variant_dir=variant_dir,
           duplicate=False,
           exports="env variant_dir")
