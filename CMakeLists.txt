project(procimg)
include_directories("/usr/local/include")
find_package( OpenCV REQUIRED )

add_executable(procimg main.cpp)
target_link_libraries( procimg ${OpenCV_LIBS} )
install(TARGETS procimg RUNTIME DESTINATION bin)
