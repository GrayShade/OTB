MESSAGE(STATUS "Importing Qt...")

IF(WRAP_QT)
  FIND_PACKAGE(Qt4 REQUIRED)
  SET(QT_USE_QTXML 1)
  INCLUDE(${QT_USE_FILE})
ENDIF(WRAP_QT)

