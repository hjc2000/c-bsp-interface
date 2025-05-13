# 编译目标
add_library(${ProjectName} STATIC)
target_import_src(${ProjectName})

# 添加测试程序
if(platform STREQUAL "msys")
	set(exe_name "test")
	add_executable(${exe_name} ${CMAKE_CURRENT_SOURCE_DIR}/exe/main.c)
	target_link_libraries(${exe_name} ${ProjectName})
	target_install(${exe_name})
endif()
