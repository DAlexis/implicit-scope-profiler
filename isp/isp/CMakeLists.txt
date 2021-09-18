project("isp")

find_package(Boost COMPONENTS thread system REQUIRED)

set(LIB_SOURCE
    ${PROJECT_SOURCE_DIR}/src/host.cpp
)

set(LIB_HPP
    ${PROJECT_SOURCE_DIR}/isp/isp.hpp
)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCE} ${LIB_HPP})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR} ${RapidJSON_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} Boost::thread)
