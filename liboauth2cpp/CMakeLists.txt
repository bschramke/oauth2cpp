cmake_minimum_required(VERSION 3.1)
set(LIBNAME "oauth2cpp")

# We need C++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Sources
set(jsonxx_SRCS  externals/jsonxx/jsonxx.cc)
set(oauth2cpp_SRCS  src/Client.cpp src/ClientConfiguration.cpp src/BearerToken.cpp src/TokenFactory.cpp src/DefaultStorage.cpp)

include_directories(include externals/jsonxx)

add_library( "${LIBNAME}" SHARED ${oauth2cpp_SRCS} ${jsonxx_SRCS})