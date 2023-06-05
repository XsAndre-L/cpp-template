cmake_minimum_required(VERSION 3.26.0)
project(
  CppProjectTemplate 
  VERSION 1.0.0 
  LANGUAGES C CXX
)

# include(CTest)
# enable_testing()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_subdirectory(App)

include(App/CMakeLists.txt)

add_executable(CppProjectTemplate ${ALL_CODE})

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
