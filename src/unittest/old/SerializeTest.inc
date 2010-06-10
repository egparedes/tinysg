add_definitions(-DTIXML_USE_STL=1 )

# Required source files for this test
set( test_srcs	${PROJECT_SOURCE_DIR}/src/Exception.cpp
				${PROJECT_SOURCE_DIR}/src/tinyxml/tinyxmlerror.cpp
				${PROJECT_SOURCE_DIR}/src/tinyxml/tinyxmlparser.cpp
				${PROJECT_SOURCE_DIR}/src/tinyxml/tinyxml.cpp
				${PROJECT_SOURCE_DIR}/src/PropertyCollection.cpp )