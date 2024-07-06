# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\chiken_invaders_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\chiken_invaders_autogen.dir\\ParseCache.txt"
  "chiken_invaders_autogen"
  )
endif()
