get_directory_property(_old_compile_opts COMPILE_OPTIONS)

if (MSVC)
        add_compile_options("/W0")
else()
        add_compile_options("-w")
endif()

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.9.0
)
FetchContent_MakeAvailable(yaml-cpp)

if (MSVC)
	target_compile_options(yaml-cpp PRIVATE /W0)
else()
	add_compile_options(yaml-cpp PRIVATE -w)
endif()
