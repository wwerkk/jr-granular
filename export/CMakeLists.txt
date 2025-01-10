target_include_directories(
    rm-pretty
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/rnbo"
        "${CMAKE_CURRENT_SOURCE_DIR}/rnbo/common"
)

target_sources(
    rm-pretty
    PRIVATE
        ringmod-stereo-3.cpp
        rnbo/RNBO.cpp
)
