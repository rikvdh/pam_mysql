if (NOT BUILD_TESTING)
	message(STATUS "testing disabled")
	return()
endif()
message(STATUS "testing enabled")

set(TESTS
	authenticate
	authenticate_args
)

include(ExternalProject)

externalproject_add(libpam_stubs
	DOWNLOAD_COMMAND ""
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libpam_stubs"
	CMAKE_ARGS
		-DCMAKE_BUILD_TYPE=Release
	INSTALL_COMMAND ""
	TEST_COMMAND ""
)
externalproject_get_property(libpam_stubs binary_dir)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/libpam_stubs/include"
	"${binary_dir}/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/Unity/src"
	"${CMAKE_CURRENT_SOURCE_DIR}/Unity/extras/fixture/src")

add_library(Unity STATIC Unity/src/unity.c Unity/extras/fixture/src/unity_fixture.c)

foreach(test ${TESTS})
	add_executable(${test} ${test}.c)
	set_source_files_properties(${test}.c PROPERTIES COMPILE_FLAGS -Wno-redundant-decls)
	add_dependencies(${test} ${PROJECT_NAME} Unity libpam_stubs)
	target_link_libraries(${test} ${PROJECT_NAME} Unity crypt ${binary_dir}/libpam_stubs.so)
	add_test(NAME "${test}" COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${test}")
endforeach()

