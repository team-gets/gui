# Use preinstalled version (i.e. from package managers)
# TODO: should we limit versions?
if (NOT GR_LIBRARY)
	message("-- Searching for GR...")
	find_library(GR_LIBRARY NAMES GR gr)
endif()

# Just use FetchContent
if (NOT GR_FOUND)
	include(FetchContent)
	message("-- Did not find system-wide installation of GR in the standard locations. Will use FetchContent to install GR for this project.")
	FetchContent_Declare(
		GR
		GIT_REPOSITORY https://github.com/sciapp/gr.git
		GIT_TAG v0.73.24
	)

	FetchContent_MakeAvailable(GR)
endif()
