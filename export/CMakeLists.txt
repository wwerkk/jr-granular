target_include_directories(
    ringmod
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/rnbo"
        "${CMAKE_CURRENT_SOURCE_DIR}/rnbo/common"
)

target_sources(
    ringmod
    PRIVATE
        ringmod-stereo-3.cpp
        rnbo/RNBO.cpp
)
