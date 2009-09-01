project( Game )

set(SOURCES 
  Camera.cpp
  main.cpp
  WindowMng.cpp
)

include_directories( 
  ../ProcCity
  ../ProcTerrain
  ../libs/freetype/include
  ../libs/ftgl/src
  ../libs/glew/include
  ../libs/glfw/include
  ../libs/pthreads
)

add_definitions( 
  -DWIN32
  -D_CONSOLE
  -D_DEBUG
)

add_executable( Game WIN32 ${SOURCES} )

target_link_libraries( Game glew glfw ftgl freetype pthread ProcCity opengl32 glu32 ws2_32 )
