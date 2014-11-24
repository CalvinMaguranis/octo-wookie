cmake_minimum_required(VERSION 2.8)
project(octo-wookie)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(BIN_DIR ${CMAKE_PRJ_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

# Locate SDL2 related dependencies
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(include)

# SDL2_image
find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

# SDL2_ttf
find_package(SDL2_TTF REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

# SDL2_mixer
find_package(SDL2_MIXER REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIR})

# Setup actual executable
add_executable(${PROJECT_NAME}  main.cpp 
                                game.cpp 
                                ow_texture.cpp
                                #ow_text_stream.cpp
                                ow_error.cpp
								primitives.cpp)

target_link_libraries(${PROJECT_NAME}  ${SDL2_LIBRARY} 
                                       ${SDL2_IMAGE_LIBRARY}
                                       ${SDL2_MIXER_LIBRARY}
                                       ${SDL2_TTF_LIBRARY})

install(TARGETS ${PROJECT_NAME}  RUNTIME DESTINATION ${BIN_DIR})
