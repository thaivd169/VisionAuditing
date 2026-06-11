file(GLOB sources "*.cpp")

qt_add_executable(${CMAKE_PROJECT_NAME}
  MANUAL_FINALIZATION
  ${sources}
)

target_include_directories(${CMAKE_PROJECT_NAME} 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(${CMAKE_PROJECT_NAME} 
  PUBLIC 
  adapter
  infra
  domain
)
