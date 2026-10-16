if(ANDROID)
    file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/JNI/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/JNI/**/*.cpp"
    )

    file(GLOB_RECURSE INCLUDEDIR LIST_DIRECTORIES true
        "${CMAKE_CURRENT_SOURCE_DIR}/src/JNI/*"
    )

elseif(WIN32)
    file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/WIN/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/WIN/**/*.cpp"
    )

    file(GLOB_RECURSE INCLUDEDIR LIST_DIRECTORIES true
        "${CMAKE_CURRENT_SOURCE_DIR}/src/WIN/*"
    )
endif()

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SRCFILES}
    ${COMMSRCFILES}
)

foreach(_DIR ${INCLUDEDIR})
    if(IS_DIRECTORY ${_DIR})
        target_include_directories(${PROJECT_NAME} PUBLIC ${_DIR})
    endif()
endforeach()
