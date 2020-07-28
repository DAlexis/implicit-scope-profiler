project("isp-unit-tests")

set(EXE_SOURCES
    ${PROJECT_SOURCE_DIR}/tests.cpp
)

set(EXE_HPP

)

add_executable(${PROJECT_NAME} ${EXE_SOURCES} ${EXE_HPP})

target_link_libraries (${PROJECT_NAME}
    gtest
    gtest_main
    isp
)

add_test(NAME stmod-testing COMMAND ${PROJECT_NAME})
