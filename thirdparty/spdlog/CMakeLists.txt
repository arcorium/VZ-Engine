
add_library(spdlog STATIC 
	async.cpp
	cfg.cpp
	color_sinks.cpp
	file_sinks.cpp
	fmt.cpp
	spdlog.cpp
	stdout_sinks.cpp
	)

target_compile_definitions(spdlog
	PUBLIC SPDLOG_COMPILED_LIB
)
target_include_directories(spdlog
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
	)
