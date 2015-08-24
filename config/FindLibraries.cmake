# Module to find libraries

set (EXT_LIBRARIES "")

# Boost library
find_package (Boost 1.55.0 COMPONENTS unit_test_framework REQUIRED)

if (Boost_FOUND)

  message(STATUS "Boost_INCLUDE_DIRS = " ${Boost_INCLUDE_DIRS})
  include_directories (${Boost_INCLUDE_DIRS})
  
  message (STATUS "Boost_LIBRARIES = " ${Boost_LIBRARIES})
  set (EXT_LIBRARIES ${Boost_LIBRARIES} ${EXT_LIBRARIES})
  
endif ()

# SFML library
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

if(SFML_FOUND)

  message(STATUS "SFML_INCLUDE_DIR = " ${SFML_INCLUDE_DIR})
  include_directories(${SFML_INCLUDE_DIR})

  message (STATUS "SFML_LIBRARIES = " ${SFML_LIBRARIES})
  set (EXT_LIBRARIES ${SFML_LIBRARIES} ${EXT_LIBRARIES})
  
endif()