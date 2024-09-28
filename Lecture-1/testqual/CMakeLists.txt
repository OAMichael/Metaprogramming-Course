set(TESTQUAL_EXEC "testqual")

set(TESTQUAL_SOURCES
    Lexer.h
    Lexer.cpp
    TestQual.h
    TestQual.cpp
    main.cpp
)

add_executable(${TESTQUAL_EXEC} ${TESTQUAL_SOURCES})
