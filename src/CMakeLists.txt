add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_sources(${PROJECT_NAME} PRIVATE rendering/RenderWindow.cpp)
target_sources(${PROJECT_NAME} PRIVATE RigidSprite.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE vendor)
