find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(OpenSSL REQUIRED)

if(CONFIG_UTM_ADAPTER)

    add_definitions(-DCONFIG_UTM_ADAPTER)
    add_definitions(-DQT_DEBUG)

    set(CMAKE_BUILD_TYPE Debug)
    set(QGC_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
    set(NLOHMANN_JSON_SOURCE_DIR "${QGC_ROOT_DIR}/libs/libevents/libevents/libs/cpp/parse/nlohmann_json")
    set(NLOHMANN_JSON_BINARY_DIR "${CMAKE_BINARY_DIR}/nlohmann_json")

    add_subdirectory(${NLOHMANN_JSON_SOURCE_DIR} ${NLOHMANN_JSON_BINARY_DIR})

    message(STATUS "UTMSP: UTMSP is Initialized")

    add_library(UTMSP
        UTMSPRestInterface.h
        UTMSPBlenderRestInterface.h
        UTMSPAuthorization.h
        UTMSPNetworkRemoteIDManager.h
        UTMSPAircraft.h
        UTMSPOperator.h
        UTMSPFlightPlanManager.h
        UTMSPServiceController.h
        UTMSPVehicle.h
        UTMSPManager.h
        UTMSPFlightDetails.h
        UTMSPRestInterface.cpp
        UTMSPBlenderRestInterface.cpp
        UTMSPAuthorization.cpp
        UTMSPNetworkRemoteIDManager.cpp
        UTMSPAircraft.cpp
        UTMSPOperator.cpp
        UTMSPFlightPlanManager.cpp
        UTMSPServiceController.cpp
        UTMSPVehicle.cpp
        UTMSPManager.cpp
        UTMSPFlightDetails.cpp
    )

    add_custom_target(UTMSPQml
        SOURCES
        UTMSPAdapterEditor.qml
        UTMSPMapVisuals.qml
        UTMSPActivationStatusBar.qml
        UTMSPStateStorage.qml
        )

    target_include_directories(UTMSP PUBLIC
        services
        ${QGC_ROOT_DIR}/libs/libevents/libevents/libs/cpp/parse/nlohmann_json/include
    )

    target_link_libraries(UTMSP

    PRIVATE
            libevents_parser
    PUBLIC
            Boost::system
            Boost::thread
            OpenSSL::SSL
            OpenSSL::Crypto
            nlohmann_json::nlohmann_json
            Qt6::Core
            Qt6::Location
            Qt6::Widgets
            Threads::Threads
            qgc
    )

else()
    # If CONFIG_UTM_ADAPTER is not set, use utmsp_dummy.qrc
    message(STATUS "UTMSP: Dummy is Initialized")

    add_library(UTMSP
            dummy/utmsp_dummy.qrc
    )

    target_include_directories(UTMSP PUBLIC dummy)

    target_link_libraries(UTMSP

    PRIVATE
            libevents_parser
    PUBLIC
            Qt6::Core
            Qt6::Location
            Qt6::Widgets
            Threads::Threads
            qgc
    )

endif()

target_include_directories(UTMSP INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
