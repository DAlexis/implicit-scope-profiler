project("isp")

set(LIB_SOURCE
    ${PROJECT_SOURCE_DIR}/src/host.cpp
)

set(LIB_HPP
    ${PROJECT_SOURCE_DIR}/isp/isp.hpp
    
    
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/prettywriter.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/rapidjson.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/document.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/ostreamwrapper.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/cursorstreamwrapper.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/encodings.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/filewritestream.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/schema.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/filereadstream.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/reader.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/memorybuffer.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/stringbuffer.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/memorystream.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/pointer.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/error/error.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/error/en.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/istreamwrapper.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/msinttypes/stdint.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/msinttypes/inttypes.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/writer.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/allocators.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/fwd.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/encodedstream.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/stream.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/swap.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/biginteger.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/ieee754.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/regex.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/itoa.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/pow10.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/meta.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/clzll.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/diyfp.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/strfunc.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/stack.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/strtod.h
    ${PROJECT_SOURCE_DIR}/isp/rapidjson/internal/dtoa.h
)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCE} ${LIB_HPP})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

