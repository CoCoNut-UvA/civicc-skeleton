cmake_minimum_required(VERSION 3.13)

project(civicc VERSION 1.0 LANGUAGES C)


find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

bison_target(CivicParser src/scanparse/parser.y "${CMAKE_CURRENT_BINARY_DIR}/parser.c"
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/parser.h")

flex_target(CivicLexer src/scanparse/lexer.l "${CMAKE_CURRENT_BINARY_DIR}/lexer.c"
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/lexer.h")
ADD_FLEX_BISON_DEPENDENCY(CivicLexer CivicParser)


include(./coconut/coconut.cmake)

# Whenever you add a file, add it here too.
add_executable(civicc ${FLEX_CivicLexer_OUTPUTS} ${BISON_CivicParser_OUTPUTS}
    src/main.c src/print/print.c src/scanparse/scanParse.c
    src/global/globals.c src/global/globals.h
    src/demo/opt_sub.c src/demo/sum_ints.c src/demo/rename_identifiers.c
)

target_compile_options(civicc PRIVATE
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Wno-unused-function>
)

coconut_target_generate(civicc "${CMAKE_CURRENT_LIST_DIR}/src/main.ccn" dynamic)
target_include_directories(civicc 
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/src" 
)

add_custom_target(dot 
    dot -Tpng ccngen/ast.dot > ast.png
    COMMENT "Generate a png of your ast based on the generated dot diagram."
)
