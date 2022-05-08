
project ("SuuriSandbox")

set(SOURCES
	"main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ../src/
)

target_link_directories(${PROJECT_NAME}
	PRIVATE ../src/
)
 
target_link_libraries(${PROJECT_NAME}
	suuri
)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)