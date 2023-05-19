#include_directories(${PROJECT_SOURCE_DIR}/Engine/External/Glad/include)
include_directories(include)

add_library(glad STATIC src/glad.c)