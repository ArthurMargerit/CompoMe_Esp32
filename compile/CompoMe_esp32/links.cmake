set(_links_lib "")
include("${CMAKE_CURRENT_LIST_DIR}/Ext_links.cmake" OPTIONAL)

list(APPEND _links_dir "-L/home/ruhtra/compo/CompoMe/lib")
list(APPEND _links_lib "CompoMe")
include("/home/ruhtra/compo/CompoMe/compile/CompoMe/Ext_links.cmake" OPTIONAL)


