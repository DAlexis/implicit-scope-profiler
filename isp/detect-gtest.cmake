if(GTEST_INCLUDE_DIR)
	message(STATUS "Googletest seems already avaliable (maybe from parent projects)")
	set(GTEST_FOUND YES)
else()
	if(EXISTS ${PROJECT_SOURCE_DIR}/3rdparty/googletest/googletest/CMakeLists.txt)
		message(STATUS "Googletest repository found at 3rdparty/googletest/")
		add_subdirectory(3rdparty/googletest)
		set(GTEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/3rdparty/googletest/googletest/include)
		set(GTEST_LIBRARY_NO_MAIN gtest)
		set(GTEST_LIBRARIES ${GTEST_LIBRARY_NO_MAIN} gtest_main)
		set(GTEST_FOUND YES)
	else()
		message(WARNING "Googletest repository NOT found at 3rdparty/googletest/, if you need to build unit tests run 'git submodule init && git submodule update'")
		set(GTEST_FOUND NO)
	endif()
endif()
