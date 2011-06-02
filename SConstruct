env = Environment()
conf = Configure(env)

LIBS = ['SDL','SDL_image','GL', 'GLU', 'glut']

for lib in LIBS:
    if not conf.CheckLib(lib):
        print 'Could not find lib ' + lib
        Exit(1)
env.Append(LIBS=LIBS)
env = conf.Finish()

#env.ParseConfig('sdl-config --cflags')
#env.ParseConfig('sdl-config --libs')
#env.ParseConfig('pkg-config glu --cflags')
#env.ParseConfig('pkg-config glu --libs')

env.Append(CCFLAGS = ['-Wall', '-g'])
env.Append(CPPPATH = ['#engine'])

#env.Replace(CXX = ['clang++'])

Export('env')

SConscript(['game/SConscript', 'engine/SConscript'])

