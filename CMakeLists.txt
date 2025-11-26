cmake_minimum_required(VERSION 3.20)
project(MyCompiler)

set(CMAKE_CXX_STANDARD 17)

find_package(MLIR REQUIRED CONFIG)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/frontend)

include_directories(${MLIR_INCLUDE_DIRS})

include_directories(${SOURCE_DIR})

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

FLEX_TARGET(MyLexer ${SOURCE_DIR}/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.c)

set_source_files_properties(${FLEX_MyLexer_OUTPUTS} PROPERTIES LANGUAGE CXX)

BISON_TARGET(MyParser ${SOURCE_DIR}/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c)

set_source_files_properties(${BISON_MyParser_OUTPUTS} PROPERTIES LANGUAGE CXX)

add_executable(my_compiler
    ${SOURCE_DIR}/ast.cpp

    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyLexer_OUTPUTS}
)

target_link_libraries(my_compiler
    MLIRIR
    MLIRParser
    MLIRFuncDialect
    MLIRArithDialect
    MLIRSCFDialect
    MLIRMemRefDialect
    LLVMSupport
)

target_include_directories(my_compiler PUBLIC ${CMAKE_CURRENT_BINARY_DIR})