cmake_minimum_required(VERSION 2.8)

project(student_toolkit)
add_executable(${PROJECT_NAME} "main.cpp" "png_toolkit.cpp" "png_toolkit.h"
    "filters.cpp" "filters.h" "manager_filters.cpp" "manager_filters.h" 
	"rectangle_area.cpp" "rectangleArea.h" 
	"secondary_functions.cpp" "secondary_functions.h"
	"stb_image.h" "stb_image_write.h")
