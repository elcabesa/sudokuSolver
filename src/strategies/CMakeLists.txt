target_sources(libSudoku PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/single.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/hiddenSingle.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/naked.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/hidden.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/pointingPair.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/boxLine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/xWing.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/yWing.cpp
	)

# Make sure the compiler can find include files for our libChess library
# when other libraries or executables link to libChess
target_include_directories (libSudoku PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

