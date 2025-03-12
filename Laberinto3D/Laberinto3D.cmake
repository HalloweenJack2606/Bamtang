set(SOURCE_BASE_DIR ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE CSources Laberinto3D/src/**.cpp)
file(GLOB_RECURSE HSources Laberinto3D/src/**.h)

add_executable(Laberinto3D
        ${CSources}
        ${HSources}
)

find_package(GLEW 2.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)
target_include_directories(Laberinto3D PRIVATE
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(Laberinto3D
        ${OPENGL_gl_LIBRARY}
        ${GLEW_LIBRARIES}
        glfw
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework IOKit"
        "-framework CoreVideo"
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set_target_properties("Laberinto3D" PROPERTIES
            OUTPUT_NAME "Laberinto3D"
            ARCHIVE_OUTPUT_DIRECTORY "bin/Debug-macosx-arm64/Laberinto3D"
            LIBRARY_OUTPUT_DIRECTORY "bin/Debug-macosx-arm64/Laberinto3D"
            RUNTIME_OUTPUT_DIRECTORY "bin/Debug-macosx-arm64/Laberinto3D"
    )
    target_include_directories("Laberinto3D" PRIVATE
            "${SOURCE_BASE_DIR}/src"
            "${SOURCE_BASE_DIR}/vendor/glm"
            "${SOURCE_BASE_DIR}/vendor/stb_image"
    )
    target_compile_definitions("Laberinto3D" PRIVATE
            "_CRT_SECURE_NO_WARNINGS"
            "FD_DEBUG"
    )

    target_compile_options("Laberinto3D" PRIVATE
            $<$<COMPILE_LANGUAGE:C>:-m64>
            $<$<COMPILE_LANGUAGE:C>:-g>
            $<$<COMPILE_LANGUAGE:CXX>:-m64>
            $<$<COMPILE_LANGUAGE:CXX>:-g>
            $<$<COMPILE_LANGUAGE:CXX>:-std=c++20>
    )
    set_target_properties("Laberinto3D" PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
            POSITION_INDEPENDENT_CODE False
            INTERPROCEDURAL_OPTIMIZATION False
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
    set_target_properties("Laberinto3D" PROPERTIES
            OUTPUT_NAME "Laberinto3D"
            ARCHIVE_OUTPUT_DIRECTORY "bin/Release-macosx-arm64/Laberinto3D"
            LIBRARY_OUTPUT_DIRECTORY "bin/Release-macosx-arm64/Laberinto3D"
            RUNTIME_OUTPUT_DIRECTORY "bin/Release-macosx-arm64/Laberinto3D"
    )
    target_include_directories("Laberinto3D" PRIVATE
            "${SOURCE_BASE_DIR}/src"
            "${SOURCE_BASE_DIR}/vendor/glm"
    )
    target_compile_definitions("Laberinto3D" PRIVATE
            "_CRT_SECURE_NO_WARNINGS"
            "FD_RELEASE"
    )
    target_link_libraries("Laberinto3D")
    target_compile_options("Laberinto3D" PRIVATE
            $<$<COMPILE_LANGUAGE:C>:-m64>
            $<$<COMPILE_LANGUAGE:C>:-O2>
            $<$<COMPILE_LANGUAGE:CXX>:-m64>
            $<$<COMPILE_LANGUAGE:CXX>:-O2>
            $<$<COMPILE_LANGUAGE:CXX>:-std=c++20>
    )
    set_target_properties("Laberinto3D" PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
            POSITION_INDEPENDENT_CODE False
            INTERPROCEDURAL_OPTIMIZATION False
    )
endif()
