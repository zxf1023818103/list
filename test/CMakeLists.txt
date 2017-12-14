enable_testing()

if(MSVC)
  set(variables 
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
	CMAKE_CXX_FLAGS_RELWITHDEBINFO
	CMAKE_CXX_FLAGS_MINSIZEREL
  )
  foreach(variable ${variables})
	if(${variable} MATCHES "/MD")
	  string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
	endif()
  endforeach()
endif()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../src)

### create and release test
add_executable(CreateAndReleaseTest CreateAndReleaseTest.cpp)
target_link_libraries(CreateAndReleaseTest gtest gtest_main)
target_link_libraries(CreateAndReleaseTest list)
add_test(BasicTests CreateAndReleaseTest)

### read and write test
add_executable(ReadAndWriteTest ReadAndWriteTest.cpp)
target_link_libraries(ReadAndWriteTest gtest gtest_main)
target_link_libraries(ReadAndWriteTest list)
add_test(BasicTests ReadAndWriteTest)

### get length test
add_executable(GetLengthTest GetLengthTest.cpp)
target_link_libraries(GetLengthTest gtest gtest_main)
target_link_libraries(GetLengthTest list)
add_test(BasicTests GetLengthTest)
