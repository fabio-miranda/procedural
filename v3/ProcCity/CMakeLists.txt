project( ProcCity )

set(SOURCES 
  ProcCity/Scene/CellNode.cpp
  ProcCity/CityMng.cpp
  ProcCity/Config.cpp
  ProcCity/Util/GUI.cpp
  ProcCity/Scene/Node.cpp
  ProcCity/Util/SimpleSquare.cpp
  ProcCity/Util/textfile.cpp
  ProcCity/Util/VBO.cpp
  ProcCity/Util/VBOSquare.cpp
)

include_directories( 
  "../libs/voro++/src"
  ../libs/freetype/include
  ../libs/ftgl/src
  ../libs/glew/include
  ../libs/glfw/include
  ../libs/pthreads
)

add_definitions( 
  -DGLEW_STATIC
  -DPTW32_STATIC_LIB
  -DWIN32
  -D_CONSOLE
  -D_DEBUG
)

add_library( ProcCity STATIC ${SOURCES} )

