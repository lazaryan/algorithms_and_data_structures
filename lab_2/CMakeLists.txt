﻿cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME Lab_2)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add project files (personaly)
add_executable(${PROJECT_NAME} 
    "src/index.cpp"
	"src/CSV/CSVReader.h"
	"src/CSV/interfaces.h"
	"src/Databases/Movies.h"
	"src/Databases/Views.h"
	"src/Recomendation/UserRecomendation.h"
	"src/Recomendation/UserRecomendation.cpp"
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})


set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/database $<TARGET_FILE_DIR:${PROJECT_NAME}>/database
)