set(SOURCE_FILES
    main.cpp
)

set(HEADER_FILES
)


add_executable(cb
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_include_directories(cb 
    PUBLIC
        ${CMAKE_SOURCE_DIR}/clip
)

target_link_libraries(cb
    PUBLIC
        clip
        MyLib
        ${CONAN_LIBS}
)