cmake_minimum_required (VERSION 2.6)
project (Swarmers)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(GLU REQUIRED)

set (SOURCES
  "engine/main.cpp"
	"engine/timing.cpp"
	"engine/error.cpp"
	"engine/defines.cpp"
	"game/swarmer.cpp"
	"game/events.cpp"
	"game/projection.cpp"
	"game/gl_setup.cpp"
	"game/game.cpp"
)


add_executable (
  Swarmers
  WIN32
  MACOSX_BUNDLE
  ${SOURCES}
  swarmers.rc
)

target_link_libraries (
  Swarmers
  ${SDL_LIBRARY}
  ${SDLMAIN_LIBRARY}
  ${OPENGL_LIBRARY}
)

include_directories (
  ${SDL_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIR}
)
