cmake_minimum_required(VERSION 3.5)

project(MyQtProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH /home/cbf/Qt/6.8.0/gcc_64)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets SvgWidgets)

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
    include/graphics/FoodItem.hpp
    include/graphics/NestItem.hpp
    include/graphics/PheromoneLayer.hpp
    include/graphics/SimulationVisualizer.hpp
    include/graphics/CustomView.hpp

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
    src/graphics/FoodItem.cpp
    src/graphics/NestItem.cpp
    src/graphics/PheromoneLayer.cpp
    src/graphics/SimulationVisualizer.cpp
    src/graphics/CustomView.cpp

    src/widgets/SettingsPanel.cpp

    src/model/Ant.cpp
    src/model/FoodStorage.cpp
    src/model/PheromoneMap.cpp
    src/model/AntColonyModel.cpp
)

qt_add_resources(RESOURCES "resources.qrc")

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${RESOURCES})

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Widgets Qt6::SvgWidgets)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
