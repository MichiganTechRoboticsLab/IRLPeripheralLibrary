# Set up build dir
AddOption(
  '--release',
  action-'store_true',
  help='release build',
  default=False)

# Set up Construction Environment
env = Environment()

env.ParseFlags()
if GetOption('release'):
    variant_dir = 'build/release'
else:
    env.ParseFlags('-DDEBUG -g')
    variant_dir = 'build/debug'
    
SConscript(dirs='src/SConscript',
           variant_dir=variant_dir,
           duplicate=False,
           exports="env")