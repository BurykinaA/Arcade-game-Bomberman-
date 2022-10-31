cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(BomberMan)

file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.cpp
)
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp
)
file(GLOB_RECURSE IMAGES_FILES
	${CMAKE_SOURCE_DIR}/images/*)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SFML REQUIRED system window graphics)
install(TARGETS BomberMan DESTINATION lib DESTINATION images DESTINATION bin)
install(FILES ${SOURCE_FILES} ${HEADER_FILES} DESTINATION lib)
install(FILES ${IMAGES_FILES} DESTINATION images)
file(GLOB_RECURSE DLL ${SFML_DIR}/../../../bin/*)
install(FILES ${DLL} DESTINATION bin)


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(WIN32)
    set(LIBS  sfml-graphics sfml-system sfml-window)
else()
    set(LIBS sfml-graphics sfml-system sfml-window)
endif()

include_directories(
 "${CMAKE_SOURCE_DIR}"
)

target_link_libraries(${PROJECT_NAME} ${LIBS} ${CMAKE_DL_LIBS})

find_package(Doxygen)

if (DOXYGEN_FOUND)
    set(DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/src)

    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/)

    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target( docs ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating docs"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("doxygen need to be installed")
endif(DOXYGEN_FOUND)