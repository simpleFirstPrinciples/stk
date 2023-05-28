cmake_minimum_required(VERSION 3.10)

SET(PROJECT_NAME stk)
project(${PROJECT_NAME})  
set(CMAKE_INCLUDE_CURRENT_DIR ON)  
set(CMAKE_CXX_STANDARD 14)


#mitk
find_package(MITK REQUIRED)

# Check that MITK has been build with Qt support
#if(NOT MITK_USE_QT5)
 # message(SEND_ERROR "MITK needs to be built with MITK_USE_QT set to ON")
#endif()




include(mitkFunctionCheckCompilerFlags)
mitk_create_executable(
  ${PROJECT_NAME} DEPENDS MitkQtWidgetsExt
  PACKAGE_DEPENDS ITK|ITKCurvatureFlow+ITKRegionGrowing
  )
