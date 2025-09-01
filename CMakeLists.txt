cmake_minimum_required(VERSION 3.10)

# Project name
project(Interpreter)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    Interpreter/Interpreter/BlockStatement.cpp
    Interpreter/Interpreter/Boolean.cpp
    Interpreter/Interpreter/CallExpression.cpp
    Interpreter/Interpreter/Expression.cpp
    Interpreter/Interpreter/FunctionLiteral.cpp
    Interpreter/Interpreter/Helper.cpp
    Interpreter/Interpreter/Identifier.cpp
    Interpreter/Interpreter/IfExpression.cpp
    Interpreter/Interpreter/InfixExpression.cpp
    Interpreter/Interpreter/IntegerLiteral.cpp
    Interpreter/Interpreter/LetStatement.cpp
    Interpreter/Interpreter/Lexer.cpp
    Interpreter/Interpreter/main.cpp
    Interpreter/Interpreter/Node.cpp
    Interpreter/Interpreter/Parser.cpp
    Interpreter/Interpreter/PrefixExpression.cpp
    Interpreter/Interpreter/Program.cpp
    Interpreter/Interpreter/Statement.cpp
    Interpreter/Interpreter/token.cpp
)

# Header files
set(HEADERS
    Interpreter/Interpreter/BlockStatement.h
    Interpreter/Interpreter/Boolean.h
    Interpreter/Interpreter/CallExpression.h
    Interpreter/Interpreter/Expression.h
    Interpreter/Interpreter/FunctionLiteral.h
    Interpreter/Interpreter/Helper.h
    Interpreter/Interpreter/Identifier.h
    Interpreter/Interpreter/IfExpression.h
    Interpreter/Interpreter/InfixExpression.h
    Interpreter/Interpreter/IntegerLiteral.h
    Interpreter/Interpreter/LetStatement.h
    Interpreter/Interpreter/Lexer.h
    Interpreter/Interpreter/main.h
    Interpreter/Interpreter/Node.h
    Interpreter/Interpreter/Parser.h
    Interpreter/Interpreter/PrefixExpression.h
    Interpreter/Interpreter/Program.h
    Interpreter/Interpreter/Statement.h
    Interpreter/Interpreter/token.h
)

# Create executable
add_executable(interpreter ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(interpreter PRIVATE Interpreter/Interpreter)

# Set output directories
set_target_properties(interpreter
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Enable warnings
if(MSVC)
    target_compile_options(interpreter PRIVATE /W4)
else()
    target_compile_options(interpreter PRIVATE -Wall -Wextra)
endif()
