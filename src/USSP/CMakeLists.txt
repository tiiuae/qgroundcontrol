find_package(Threads REQUIRED)

add_library(USSP
	services/dispatcher.h
	flightBlender/telemetry.h
	flightBlender/telemetry.cc
	flightBlender/flightID.h
	flightBlender/flightID.cc
	USSPManager.h
	USSPManager.cc
	USSPVehicle.h
	USSPVehicle.cc
	USSPTelemetry.h
	USSPTelemetry.cc
)

target_include_directories(USSP PUBLIC services )

target_link_libraries(USSP

PRIVATE
	libevents_parser
PUBLIC
	Qt5::Core
	Qt5::Location
	Qt5::Widgets
	Threads::Threads
	qgc
)

target_include_directories(USSP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
