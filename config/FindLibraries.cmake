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


# GLUT library
find_package(GLUT REQUIRED)

if(GLUT_FOUND)

  message(STATUS "GLUT_INCLUDE_DIR = " ${GLUT_INCLUDE_DIR})
  include_directories(${GLUT_INCLUDE_DIR})
  
  message (STATUS "GLUT_LIBRARIES = " ${GLUT_LIBRARIES})
  set (EXT_LIBRARIES ${GLUT_LIBRARIES} ${EXT_LIBRARIES})
  
endif()

# OpenGL library
find_package(OpenGL REQUIRED)

if(OPENGL_FOUND)

  message(STATUS "OPENGL_INCLUDE_DIR = " ${OPENGL_INCLUDE_DIR})
  include_directories(${OPENGL_INCLUDE_DIR})
  
  message (STATUS "OPENGL_LIBRARIES = " ${OPENGL_LIBRARIES})
  set (EXT_LIBRARIES ${OPENGL_LIBRARIES} ${EXT_LIBRARIES})

endif()

# MathGL library
find_package(MathGL2 REQUIRED GLUT)

if(MATHGL2_FOUND)

  message(STATUS "MATHGL2_INCLUDE_DIRS = " ${MATHGL2_INCLUDE_DIRS})
  include_directories(${MATHGL2_INCLUDE_DIRS})
  
  message (STATUS "MATHGL2_LIBRARIES = " ${MATHGL2_LIBRARIES})
  set (EXT_LIBRARIES ${MATHGL2_LIBRARIES} ${EXT_LIBRARIES})

endif()