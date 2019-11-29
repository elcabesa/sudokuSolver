target_sources(libSudoku PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/single.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/hiddenSingle.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/naked.cpp 
	)

# Make sure the compiler can find include files for our libChess library
# when other libraries or executables link to libChess
target_include_directories (libSudoku PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

