if(ANDROID)
    file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/JNI/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/JNI/**/*.cpp"
    )

    file(GLOB INCLUDEDIR
        "${CMAKE_CURRENT_SOURCE_DIR}/src/JNI/*/"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/JNI/**/*/"
    )

elseif(WIN32)
    file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/WIN/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/WIN/**/*.cpp"
    )

    file(GLOB INCLUDEDIR
        "${CMAKE_CURRENT_SOURCE_DIR}/src/WIN/*/"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/WIN/**/*/"
    )
endif()

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SRCFILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${INCLUDEDIR}
)
