target_sources(robodetect
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/robodetectMainWindow.h
        ${CMAKE_CURRENT_LIST_DIR}/pointScene.h
        ${CMAKE_CURRENT_LIST_DIR}/localHistogram.h
        ${CMAKE_CURRENT_LIST_DIR}/widgets/robodetectImageWidget.h
        ${CMAKE_CURRENT_LIST_DIR}/gapFiller.h
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/robodetectMainWindow.cpp
        ${CMAKE_CURRENT_LIST_DIR}/main_robodetect.cpp
        ${CMAKE_CURRENT_LIST_DIR}/pointScene.cpp
        ${CMAKE_CURRENT_LIST_DIR}/localHistogram.cpp
        ${CMAKE_CURRENT_LIST_DIR}/widgets/robodetectImageWidget.cpp
)