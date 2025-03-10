set(SOURCE_BASE_DIR ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE CSources Laberinto/src/**.cpp)
file(GLOB_RECURSE HSources Laberinto/src/**.h)

add_executable(Laberinto
        ${CSources}
        ${HSources}
)

find_package(GLEW 2.2 REQUIRED)
find_package(glfw3 3.4 REQUIRED)
target_include_directories(Laberinto PRIVATE
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("Laberinto" PROPERTIES
          OUTPUT_NAME "Laberinto"
          ARCHIVE_OUTPUT_DIRECTORY "bin/Debug-macosx-arm/Laberinto"
          LIBRARY_OUTPUT_DIRECTORY "bin/Debug-macosx-arm/Laberinto"
          RUNTIME_OUTPUT_DIRECTORY "bin/Debug-macosx-arm/Laberinto"
  )
  target_include_directories("Laberinto" PRIVATE
          "${SOURCE_BASE_DIR}/src"
          "${SOURCE_BASE_DIR}/vendor/glm"
  )
  target_compile_definitions("Laberinto" PRIVATE
          "_CRT_SECURE_NO_WARNINGS"
          "FD_DEBUG"
  )
  target_link_libraries("Laberinto"
          ${OPENGL_gl_LIBRARY}
          ${GLEW_LIBRARIES}
  )

  target_compile_options("Laberinto" PRIVATE
          $<$<COMPILE_LANGUAGE:C>:-m64>
          $<$<COMPILE_LANGUAGE:C>:-g>
          $<$<COMPILE_LANGUAGE:CXX>:-m64>
          $<$<COMPILE_LANGUAGE:CXX>:-g>
          $<$<COMPILE_LANGUAGE:CXX>:-std=c++20>
  )
  set_target_properties("Laberinto" PROPERTIES
          CXX_STANDARD 20
          CXX_STANDARD_REQUIRED YES
          CXX_EXTENSIONS NO
          POSITION_INDEPENDENT_CODE False
          INTERPROCEDURAL_OPTIMIZATION False
  )
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_dependencies("Laberinto")
  set_target_properties("Laberinto" PROPERTIES
          OUTPUT_NAME "Laberinto"
          ARCHIVE_OUTPUT_DIRECTORY "bin/Release-macosx-arm/Laberinto"
          LIBRARY_OUTPUT_DIRECTORY "bin/Release-macosx-arm/Laberinto"
          RUNTIME_OUTPUT_DIRECTORY "bin/Release-macosx-arm/Laberinto"
  )
  target_include_directories("Laberinto" PRIVATE
          "${SOURCE_BASE_DIR}/src"
          "${SOURCE_BASE_DIR}/vendor/glm"
  )
  target_compile_definitions("Laberinto" PRIVATE
          "_CRT_SECURE_NO_WARNINGS"
          "FD_RELEASE"
  )
  target_link_libraries("Laberinto")
  if (MSVC)
    target_compile_options("Laberinto" PRIVATE
            $<$<COMPILE_LANGUAGE:C>:/MP>
            $<$<COMPILE_LANGUAGE:C>:/Ot>
            $<$<COMPILE_LANGUAGE:C>:/MT>
            $<$<COMPILE_LANGUAGE:CXX>:/MP>
            $<$<COMPILE_LANGUAGE:CXX>:/Ot>
            $<$<COMPILE_LANGUAGE:CXX>:/MT>
            $<$<COMPILE_LANGUAGE:CXX>:/EHsc>
    )
  else()
    target_compile_options("Laberinto" PRIVATE
            $<$<COMPILE_LANGUAGE:C>:-m64>
            $<$<COMPILE_LANGUAGE:C>:-O2>
            $<$<COMPILE_LANGUAGE:CXX>:-m64>
            $<$<COMPILE_LANGUAGE:CXX>:-O2>
            $<$<COMPILE_LANGUAGE:CXX>:-std=c++20>
    )
  endif()
  set_target_properties("Laberinto" PROPERTIES
          CXX_STANDARD 20
          CXX_STANDARD_REQUIRED YES
          CXX_EXTENSIONS NO
          POSITION_INDEPENDENT_CODE False
          INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
