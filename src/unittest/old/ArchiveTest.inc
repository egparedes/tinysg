set( build_test TRUE )

add_definitions(-DTIXML_USE_STL=1 )

# Required source files for this test
set( test_srcs ${PROJECT_SOURCE_DIR}/src/Exception.cpp
			   ${PROJECT_SOURCE_DIR}/src/PropertyCollection.cpp
			   ${PROJECT_SOURCE_DIR}/src/Archive.cpp
			   ${PROJECT_SOURCE_DIR}/src/tinyxml.cpp
			   ${PROJECT_SOURCE_DIR}/src/tinyxmlerror.cpp
			   ${PROJECT_SOURCE_DIR}/src/tinyxmlparser.cpp)