cmake_minimum_required(VERSION 3.17)

set(PROJECT "ClustersFromPointsPlugin")

PROJECT(${PROJECT})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /DWIN32 /EHsc /MP /permissive- /Zc:__cplusplus")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
endif(MSVC)

# Check if the directory to the ManiVault installation has been provided
if(NOT DEFINED MV_INSTALL_DIR)
    set(MV_INSTALL_DIR "" CACHE PATH "Directory where ManiVault is installed")
    message(FATAL_ERROR "Please set MV_INSTALL_DIR to the directory where ManiVault is installed")
endif()
file(TO_CMAKE_PATH ${MV_INSTALL_DIR} MV_INSTALL_DIR)

find_package(Qt6 COMPONENTS Widgets WebEngineWidgets REQUIRED)

find_package(OpenMP)

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(Plugin
    src/ClustersFromPointsPlugin.h
    src/ClustersFromPointsPlugin.cpp
)

set(Extractor
    src/Extractor.h
    src/Extractor.cpp
    src/IdentifierExtractor.h
    src/IdentifierExtractor.cpp
    src/IndexExtractor.h
    src/IndexExtractor.cpp
    src/StratificationExtractor.h
    src/StratificationExtractor.cpp
    src/IntervalExtractor.h
    src/IntervalExtractor.cpp
)

set(Actions
    src/SettingsAction.h
    src/SettingsAction.cpp
    src/AlgorithmAction.h
    src/AlgorithmAction.cpp
    src/IdentifierExtractorSettingsAction.h
    src/IdentifierExtractorSettingsAction.cpp
    src/IndexExtractorSettingsAction.h
    src/IndexExtractorSettingsAction.cpp
    src/StratificationExtractorSettingsAction.h
    src/StratificationExtractorSettingsAction.cpp
    src/IntervalExtractorSettingsAction.h
    src/IntervalExtractorSettingsAction.cpp
)

set(AUX
    src/ClustersFromPointsPlugin.json
)

set(SOURCES ${Plugin} ${Extractor} ${Actions} ${UI})

source_group(Plugin FILES ${Plugin})
source_group(Extractor FILES ${Extractor})
source_group(Actions FILES ${Actions})
source_group(Aux FILES ${AUX})

add_library(${PROJECT} SHARED ${SOURCES} ${AUX})

target_include_directories(${PROJECT} PRIVATE "${MV_INSTALL_DIR}/$<CONFIGURATION>/include/")

target_compile_features(${PROJECT} PRIVATE cxx_std_17)

set(HDPS_LINK_PATH "${MV_INSTALL_DIR}/$<CONFIGURATION>/lib")
set(PLUGIN_LINK_PATH "${MV_INSTALL_DIR}/$<CONFIGURATION>/$<IF:$<CXX_COMPILER_ID:MSVC>,lib,Plugins>")
set(HDPS_LINK_SUFFIX $<IF:$<CXX_COMPILER_ID:MSVC>,${CMAKE_LINK_LIBRARY_SUFFIX},${CMAKE_SHARED_LIBRARY_SUFFIX}>)

set(HDPS_LINK_LIBRARY "${HDPS_LINK_PATH}/${CMAKE_SHARED_LIBRARY_PREFIX}HDPS_Public${HDPS_LINK_SUFFIX}")
set(POINTDATA_LINK_LIBRARY "${PLUGIN_LINK_PATH}/${CMAKE_SHARED_LIBRARY_PREFIX}PointData${HDPS_LINK_SUFFIX}") 
set(CLUSTERDATA_LINK_LIBRARY "${PLUGIN_LINK_PATH}/${CMAKE_SHARED_LIBRARY_PREFIX}ClusterData${HDPS_LINK_SUFFIX}") 

target_link_libraries(${PROJECT} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT} PRIVATE Qt6::WebEngineWidgets)
target_link_libraries(${PROJECT} PRIVATE "${HDPS_LINK_LIBRARY}")
target_link_libraries(${PROJECT} PRIVATE "${POINTDATA_LINK_LIBRARY}")
target_link_libraries(${PROJECT} PRIVATE "${CLUSTERDATA_LINK_LIBRARY}")

install(TARGETS ${PROJECT}
    RUNTIME DESTINATION Plugins COMPONENT PLUGINS # Windows .dll
    LIBRARY DESTINATION Plugins COMPONENT PLUGINS # Linux/Mac .so
)

add_custom_command(TARGET ${PROJECT} POST_BUILD
    COMMAND "${CMAKE_COMMAND}"
        --install ${CMAKE_CURRENT_BINARY_DIR}
        --config $<CONFIGURATION>
        --prefix ${MV_INSTALL_DIR}/$<CONFIGURATION>
)

# Automatically set the debug environment (command + working directory) for MSVC
if(MSVC)
    set_property(TARGET ${PROJECT} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY  $<IF:$<CONFIG:DEBUG>,${MV_INSTALL_DIR}/debug,${MV_INSTALL_DIR}/release>)
    set_property(TARGET ${PROJECT} PROPERTY VS_DEBUGGER_COMMAND $<IF:$<CONFIG:DEBUG>,${MV_INSTALL_DIR}/debug/HDPS.exe,${MV_INSTALL_DIR}/release/HDPS.exe>)
endif()
