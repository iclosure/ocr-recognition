
project(ocr_devinfo_app CXX)

find_package(Qt5 COMPONENTS Core Gui Widgets Concurrent REQUIRED)

set(OpenCV_DIR "$ENV{OPENCV_HOME}")
#set(Tesseract_DIR "C:/Program Files/Tesseract-OCR")
set(Tesseract_DIR "C:/Program Files/tesseract/cmake")

find_package(OpenCV CONFIG REQUIRED)
find_package(Tesseract CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

if(OpenCV_FOUND)
  include_directories(${OpenCV_INCLUDE_DIRS})
endif(OpenCV_FOUND)

if(Tesseract_FOUND)
  include_directories(${Tesseract_INCLUDE_DIRS})
endif(Tesseract_FOUND)

include_directories($ENV{Tesseract_DIR}/include)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Concurrent
)

if(OpenCV_FOUND)
  target_link_libraries(${PROJECT_NAME}
    PUBLIC ${OpenCV_LIBS}
  )
endif(OpenCV_FOUND)

if(Tesseract_FOUND)
  target_link_libraries(${PROJECT_NAME}
    PUBLIC ${Tesseract_LIBRARIES}
  )
endif(Tesseract_FOUND)
