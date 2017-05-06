project(CTERMINAL)

add_library(cterminal STATIC ${CTERMINAL_SOURCE_DIR}/src/cterminal.c)
install(TARGETS cterminal DESTINATION lib)

target_include_directories(cterminal PRIVATE ${CTERMINAL_SOURCE_DIR})
