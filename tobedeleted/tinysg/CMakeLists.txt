# Process plugins first
set( TSG_ODE_TARGET "tsgode" )
set( TSG_LC_TARGET "tsglc" )
add_subdirectory( plugins )

if ( Log4cxx_FOUND )
	include_directories( ${Log4cxx_INCLUDE_DIRS} )
	link_libraries( ${Log4cxx_LIBRARIES} )
endif ( Log4cxx_FOUND )

include_directories( 
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/api
	plugins
	${Boost_INCLUDE_DIRS}
)

link_directories( 
	${Boost_LIBRARY_DIRS}
	${PROJECT_BINARY_DIR}/api
	${PROJECT_BINARY_DIR}/math
)

# Link against static plugins
if ( Ode_FOUND )
	link_directories( ${PROJECT_BINARY_DIR}/tinysg/plugins/ode )
	link_libraries( ${TSG_ODE_TARGET} )
endif ( Ode_FOUND )

link_directories( ${PROJECT_BINARY_DIR}/tinysg/plugins/lincanny )
link_libraries( ${TSG_LC_TARGET} )
			  
# Gather all *.cpp and *.h files into their respective variables
file(GLOB TSG_SRCS "*.cpp")
file(GLOB TSG_HEADERS "*.h")

add_definitions(-DTIXML_USE_STL=1)
add_definitions("-DTINYSG_VERSION_MAJOR=${TINYSG_VERSION_MAJOR}")
add_definitions("-DTINYSG_VERSION_MINOR=${TINYSG_VERSION_MINOR}")
add_definitions("-DTINYSG_VERSION_PATCH=${TINYSG_VERSION_PATCH}")

add_library( ${TSG_TARGET} SHARED ${TSG_SRCS})
target_link_libraries(${TSG_TARGET} boost_thread-mt ${TSG_PF_TARGET} ${TSG_PF_TARGET} ${TSG_MATH_TARGET})

install( TARGETS ${TSG_TARGET} DESTINATION tinysg/lib )
install( FILES ${TSG_HEADERS} DESTINATION tinysg/include/tinysg )

message( STATUS "Will build shared library: ${TSG_TARGET}" )