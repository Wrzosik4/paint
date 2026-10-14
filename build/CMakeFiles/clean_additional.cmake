# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/paint_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/paint_autogen.dir/ParseCache.txt"
  "paint_autogen"
  )
endif()
