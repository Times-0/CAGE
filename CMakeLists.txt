cmake_minimum_required(VERSION 3.0.0)
project(cage VERSION 0.1.0)

include(CTest)
enable_testing()

message("**********************************")
message("          CAGE v" ${PROJECT_VERSION})
message("**********************************")
message(INFO " ** Make sure SOCI is installed for C++17 (-DCMAKE_CXX_STANDARD=17 -DSOCI_CXX11=ON) **")

# set CXX standard
set(CMAKE_CXX_STANDARD 17)

# SOCI
set(SOCI_LIB_PATH /usr/local/lib64)
set(SOCI_LIBS ${SOCI_LIB_PATH}/libsoci_core.so ${SOCI_LIB_PATH}/libsoci_postgresql.so)

###################################
# FIND PACKAGES

# Boost Package
include(FindBoost)
find_package(Boost COMPONENTS system filesystem program_options REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} ${SOCI_INCLUDE_DIR} )

# Postgres Package
find_package(PostgreSQL REQUIRED)

###################################
# EXECUTABLE / LIBRARY

add_executable(cage ./src/main.cpp)

###################################
# INCLUDE DIRECTORIES AND LIBRARIES

# SOURCE
set(PUBLIC_INCLUDE "./include/")
set(PRIVATE_SRC "./src/")

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INCLUDE})
target_include_directories(${PROJECT_NAME} PRIVATE ${PRIVATE_SRC} ${PostgreSQL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PostgreSQL_LIBRARIES})

#link_directories(${SOCI_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SOCI_LIBS})
target_link_libraries(${PROJECT_NAME} PUBLIC pthread)

###################################

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
