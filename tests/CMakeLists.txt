file( GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Test* )
foreach( testsourcefile ${SOURCES} )
    string( REPLACE ".cpp" "" testname ${testsourcefile} )
    get_filename_component(file ${testsourcefile} NAME_WE)
    add_executable( ${file} EXCLUDE_FROM_ALL ${testsourcefile} )
    target_link_libraries( ${file} srcsaxeventdispatch srcsax_static srcml ${LIBXML2_LIBRARIES} )
endforeach( testsourcefile ${SOURCES} )