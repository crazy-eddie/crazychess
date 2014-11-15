find_package(Boost)
find_package(Boost COMPONENTS unit_test_framework iostreams filesystem system)

add_custom_target(fcheck COMMAND ${CMAKE_CTEST_COMMAND})
add_custom_target(ftests)

configure_file(config.hpp.in config.hpp)

include_directories(${Boost_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}) 

function(add_boost_ftest name)
  add_executable(${name} EXCLUDE_FROM_ALL ${ARGN})

  target_link_libraries(${name} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                                ${Boost_IOSTREAMS_LIBRARY}
                                ${Boost_FILESYSTEM_LIBRARY}
                                ${Boost_SYSTEM_LIBRARY})
  
  add_test(${name} ./${name})
  
  add_dependencies(fcheck ${name})
  add_dependencies(ftests ${name})
endfunction()

add_boost_ftest(board_positions positions.cpp process.cpp)
