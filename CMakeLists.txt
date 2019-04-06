#------------------------------------------------------------------------------
# CMakeLists.txt
# for ModularGameEngine
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)

project(rtype)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
endif()

#------------------------------------------------------------------------------
# Packages
#------------------------------------------------------------------------------
# - gamekit
#------------------------------------------------------------------------------
find_package(GameKit REQUIRED)
if(NOT GAMEKIT_FOUND)
	message(FATAL_ERROR "gamekit is needed to build the project. Please install it correctly.")
endif()

include_directories(${GAMEKIT_INCLUDE_DIRS})
link_directories(${GAMEKIT_LIBRARY_DIRS})

#------------------------------------------------------------------------------
# - tinyxml2
#------------------------------------------------------------------------------
find_package(TinyXml2 REQUIRED)
if(NOT TINYXML2_FOUND)
	message(FATAL_ERROR "tinyxml2 is needed to build the project. Please install it correctly.")
endif()

include_directories(${TINYXML2_INCLUDE_DIRS})
link_directories(${TINYXML2_LIBRARY_DIRS})

#------------------------------------------------------------------------------
# - SFML
#------------------------------------------------------------------------------
find_package(SFML COMPONENTS audio graphics network system window REQUIRED)

if(NOT SFML_FOUND)
	message(FATAL_ERROR "SFML is needed to build the project. Please install it correctly.")
endif()

include_directories(${SFML_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# Subdirectories
#------------------------------------------------------------------------------
add_subdirectory(game)
add_subdirectory(client)
add_subdirectory(server)

