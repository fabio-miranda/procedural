; ..\LIB\GLU32.LIB PROTOTYPES
; ~~~~~~~~~~~~~~~~~~~~~~~~~~~

gluBeginCurve PROTO :DWORD
gluBeginPolygon PROTO :DWORD
gluBeginSurface PROTO :DWORD
gluBeginTrim PROTO :DWORD
gluBuild1DMipmaps PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
gluBuild2DMipmaps PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
gluCylinder PROTO :DWORD,:QWORD,:QWORD,:QWORD,:DWORD,:DWORD
gluDeleteNurbsRenderer PROTO :DWORD
gluDeleteQuadric PROTO :DWORD
gluDeleteTess PROTO :DWORD
gluDisk PROTO :DWORD,:QWORD,:QWORD,:DWORD,:DWORD
gluEndCurve PROTO :DWORD
gluEndPolygon PROTO :DWORD
gluEndSurface PROTO :DWORD
gluEndTrim PROTO :DWORD
gluErrorString PROTO :DWORD
gluErrorUnicodeStringEXT PROTO :DWORD
gluGetNurbsProperty PROTO :DWORD,:DWORD,:DWORD
gluGetString PROTO :DWORD
gluGetTessProperty PROTO :DWORD,:DWORD,:DWORD
gluLoadSamplingMatrices PROTO :DWORD,:DWORD,:DWORD,:DWORD
gluLookAt PROTO :QWORD,:QWORD,:QWORD,:QWORD,:QWORD,:QWORD,:QWORD,:QWORD,:QWORD
gluNewNurbsRenderer PROTO
gluNewQuadric PROTO
gluNewTess PROTO
gluNextContour PROTO :DWORD,:DWORD
gluNurbsCallback PROTO :DWORD,:DWORD,:DWORD
gluNurbsCurve PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
gluNurbsProperty PROTO :DWORD,:DWORD,:DWORD
gluNurbsSurface PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
gluOrtho2D PROTO :QWORD,:QWORD,:QWORD,:QWORD
gluPartialDisk PROTO :DWORD,:QWORD,:QWORD,:DWORD,:DWORD,:QWORD,:QWORD
gluPerspective PROTO :QWORD,:QWORD,:QWORD,:QWORD
gluPickMatrix PROTO :QWORD,:QWORD,:QWORD,:QWORD,:DWORD
gluProject PROTO :QWORD,:QWORD,:QWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
gluPwlCurve PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
gluQuadricCallback PROTO :DWORD,:DWORD,:DWORD
gluQuadricDrawStyle PROTO :DWORD,:DWORD
gluQuadricNormals PROTO :DWORD,:DWORD
gluQuadricOrientation PROTO :DWORD,:DWORD
gluQuadricTexture PROTO :DWORD,:DWORD
gluScaleImage PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
gluSphere PROTO :DWORD,:QWORD,:DWORD,:DWORD
gluTessBeginContour PROTO :DWORD
gluTessBeginPolygon PROTO :DWORD,:DWORD
gluTessCallback PROTO :DWORD,:DWORD,:DWORD
gluTessEndContour PROTO :DWORD
gluTessEndPolygon PROTO :DWORD
gluTessNormal PROTO :DWORD,:QWORD,:QWORD,:QWORD
gluTessProperty PROTO :DWORD,:DWORD,:QWORD
gluTessVertex PROTO :DWORD,:DWORD,:DWORD
gluUnProject PROTO :QWORD,:QWORD,:QWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
