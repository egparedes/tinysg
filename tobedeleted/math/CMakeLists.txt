if ( ${PERFORM_UNIT_TESTS} AND ${Log4cxx_FOUND} )
	sub_directory( tests )
endif ( ${PERFORM_UNIT_TESTS} AND ${Log4cxx_FOUND} )

if ( MuParser_FOUND )
	include_directories( ${MuParser_INCLUDE_DIRS} )
	link_libraries( ${MuParser_LIBRARIES} )
endif ( MuParser_FOUND )
	
include_directories( ${PROJECT_SOURCE_DIR} )
			  			  
# Gather all *.cpp and *.h files into their respective variables
file(GLOB TSG_MATH_SRCS "*.cpp")
file(GLOB TSG_MATH_HEADERS "*.h")
 
add_library( ${TSG_MATH_TARGET} SHARED ${TSG_MATH_SRCS})

install( TARGETS ${TSG_MATH_TARGET} DESTINATION tinysg/lib )
install( FILES ${TSG_MATH_HEADERS} DESTINATION tinysg/include/math )

message( STATUS "Will build shared library: ${TSG_MATH_TARGET}" )