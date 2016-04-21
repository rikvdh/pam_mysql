if (NOT BUILD_TESTING)
	message(STATUS "testing disabled")
	return()
endif()
message(STATUS "testing enabled")

set(TESTS
	load_unload
)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/Unity/src"
	"${CMAKE_CURRENT_SOURCE_DIR}/Unity/extras/fixture/src")

add_library(Unity STATIC Unity/src/unity.c Unity/extras/fixture/src/unity_fixture.c)

foreach(test ${TESTS})
	add_executable(${test} ${test}.c)
	add_dependencies(${test} ${PROJECT_NAME} Unity)
	target_link_libraries(${test} ${PROJECT_NAME} Unity)
	add_test(NAME "${test}" COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${test}")
endforeach()

