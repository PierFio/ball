### list all filenames of the directory here ###
SET(GROUP VIEW/DIALOGS)

FILE(GLOB HEADERS_LIST "include/BALL/${GROUP}/*.h" "include/BALL/${GROUP}/*.iC")

IF(NOT BALL_PYTHON_SUPPORT)
	LIST(REMOVE_ITEM HEADERS_LIST "${CMAKE_CURRENT_SOURCE_DIR}/include/BALL/${GROUP}/pythonSettings.h")
ENDIF()

IF(NOT BALL_HAS_FFTW)
	LIST(REMOVE_ITEM HEADERS_LIST "${CMAKE_CURRENT_SOURCE_DIR}/include/BALL/${GROUP}/geometricFitDialog.h")
ENDIF()

IF(NOT BALL_HAS_QTWEBENGINE)
	LIST(REMOVE_ITEM HEADERS_LIST "${CMAKE_CURRENT_SOURCE_DIR}/include/BALL/${GROUP}/webEnginePreferences.h")
ENDIF()

ADD_VIEW_HEADERS("${GROUP}" "${HEADERS_LIST}")