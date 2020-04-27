cmake_minimum_required(VERSION 3.0.0)
project(cage VERSION 0.1.0)

include(CTest)
enable_testing()

message("**********************************")
message("          CAGE v" ${PROJECT_VERSION})
message("**********************************")
#message(INFO " ** Make sure SOCI is installed for C++17 (-DCMAKE_CXX_STANDARD=17 -DSOCI_CXX11=ON) **")

# set CXX standard
set(CMAKE_CXX_STANDARD 17)


###################################
# FIND PACKAGES

# Boost Package
include(FindBoost)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )

# Postgres Package
find_package(PostgreSQL REQUIRED)

# sqlpp11 Package
find_package(Sqlpp11 REQUIRED)

# sqlpp11-connector-postgresql Package
set(Sqlpp-connector-postgresql_LIBRARIES sqlpp11-connector-postgresql sqlpp11-connector-postgresql-dynamic)

# spdlog Package
find_package(spdlog REQUIRED)

# glog Package
find_package(glog REQUIRED)

# evpp Package
message(** "Make sure evpp is installed" **)

###################################
# EXECUTABLE / LIBRARY

add_executable(cage ./src/main.cpp)

###################################
# INCLUDE DIRECTORIES AND LIBRARIES

# SOURCE
set(PUBLIC_INCLUDE "./include/")
set(PRIVATE_SRC "./src/")

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INCLUDE})
target_include_directories(${PROJECT_NAME} PRIVATE ${PRIVATE_SRC} ${PostgreSQL_INCLUDE_DIRS} ${Sqlpp11_INCLUDE_DIRS} ${glog_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PostgreSQL_LIBRARIES} ${Sqlpp11_LIBRARIES} ${Sqlpp-connector-postgresql_LIBRARIES} evpp_static)
target_link_libraries(${PROJECT_NAME} PUBLIC pthread pq spdlog event_core glog::glog)

###################################

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
