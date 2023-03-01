
find_package(Threads REQUIRED)

add_library(USSP
	test/USSPMinimalFlow.cpp
	test/USSPMinimalFlow.h
	services/dispatcher.h
)

target_include_directories(USSP PUBLIC services test)

target_link_libraries(USSP
	Qt5::Core
	Qt5::Location
	Qt5::Widgets
	Threads::Threads

	qgc
)

target_include_directories(USSP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
