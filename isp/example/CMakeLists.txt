project("isp-example")

set(EXE_SOURCES
    ${PROJECT_SOURCE_DIR}/example.cpp
)

set(EXE_HPP

)

add_executable(${PROJECT_NAME} ${EXE_SOURCES} ${EXE_HPP})
target_link_libraries(${PROJECT_NAME} isp)
