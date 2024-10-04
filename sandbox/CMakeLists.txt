cmake_minimum_required(VERSION 3.20)

project("suuri_sandbox")

set(SOURCES
	main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
						   PUBLIC ../src/
)

set_target_properties(${PROJECT_NAME}
					  PROPERTIES
					  CXX_STANDARD 20
					  CXX_STANDARD_REQUIRED YES
					  CXX_EXTENSIONS NO
)
