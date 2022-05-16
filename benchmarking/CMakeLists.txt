
project ("Benchmarking")

add_compile_definitions("BENCHMARK_ENABLED")

set(SOURCES
	"main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ../src/
	PUBLIC ../vendor/benchmarker/
)

target_link_directories(${PROJECT_NAME}
	PRIVATE ../src/
    PRIVATE ../vendor/benchmarker/
)
 
target_link_libraries(${PROJECT_NAME}
	suuri
	benchmarker
)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)