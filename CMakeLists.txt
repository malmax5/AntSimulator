cmake_minimum_required(VERSION 3.5)

project(MyQtProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH /home/cbf/Qt/6.8.0/gcc_64)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(HEADERS
    include/MainWindow.hpp
    include/AntField.hpp
    include/AntSimulator.hpp
    include/CoordinateSystem.hpp

    include/graphics/AntItem.hpp

    include/widgets/SettingsPanel.hpp

    include/model/Ant.hpp
    include/model/FoodStorage.hpp
    include/model/PheromoneMap.hpp
    include/model/AntColonyModel.hpp
)

set(SOURCES
    main.cpp

    src/MainWindow.cpp
    src/AntField.cpp
    src/AntSimulator.cpp
    src/CoordinateSystem.cpp

    src/graphics/AntItem.cpp

    src/widgets/SettingsPanel.cpp

    src/model/Ant.cpp
    src/model/FoodStorage.cpp
    src/model/PheromoneMap.cpp
    src/model/AntColonyModel.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Widgets)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
