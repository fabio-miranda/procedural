project( ProcTerrain )

set(SOURCES 
  ProcTerrain/Util/FBO.cpp
  ProcTerrain/Shaders/GenerationShader.cpp
  ProcTerrain/Util/GUI.cpp
  ProcTerrain/HeightMap/HeightMap.cpp
  ProcTerrain/Shaders/RenderingShader.cpp
  ProcTerrain/Shaders/Shader.cpp
  ProcTerrain/Util/SimpleSquare.cpp
  ProcTerrain/Scene/SquareNode.cpp
  ProcTerrain/Util/textfile.cpp
  ProcTerrain/Util/VBO.cpp
  ProcTerrain/Util/VBOSquare.cpp
  ProcTerrain/TerrainMng.cpp
  ProcTerrain/Config.cpp
)

include_directories( 
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

add_library( ProcTerrain STATIC ${SOURCES} )

