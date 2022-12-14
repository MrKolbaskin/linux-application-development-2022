cmake_minimum_required(VERSION 3.22)
project(guess-number C)
set(CMAKE_C_STANDARD 17)

find_package(Doxygen REQUIRED dot)

add_definitions(-DLOCALE_PATH="${PROJECT_SOURCE_DIR}/po")

add_executable(main main.c)


add_custom_target(translate DEPENDS main
        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/po/ru/LC_MESSAGES
        COMMAND msgfmt -o ${CMAKE_CURRENT_BINARY_DIR}/po/ru/LC_MESSAGES/main.mo ${CMAKE_SOURCE_DIR}/po/ru.po
        )

add_custom_target(update-translation DEPENDS translate
        COMMAND xgettext --keyword=_ --add-comments ${CMAKE_SOURCE_DIR}/main.c -o ${CMAKE_CURRENT_BINARY_DIR}/po/main.pot
        COMMAND msgmerge -U ${CMAKE_SOURCE_DIR}/po/ru.po ${CMAKE_CURRENT_BINARY_DIR}/po/main.pot
        COMMAND msgfmt -o ${CMAKE_CURRENT_BINARY_DIR}/po/ru/LC_MESSAGES/main.mo ${CMAKE_SOURCE_DIR}/po/ru.po
        COMMAND rm ${CMAKE_CURRENT_BINARY_DIR}/main.pot
        )

add_custom_target(main-ru DEPENDS main translate
        COMMAND LANGUAGE=ru_RU ${CMAKE_CURRENT_BINARY_DIR}/main
        )

add_custom_target(main-en DEPENDS main
        COMMAND LANGUAGE=en_EN ${CMAKE_CURRENT_BINARY_DIR}/main
        )

configure_file(${CMAKE_SOURCE_DIR}/Doxygen.in ${CMAKE_CURRENT_BINARY_DIR}/Doxygen.in)
add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxygen.in
        )

add_custom_target(man DEPENDS main
        COMMAND help2man --no-info --output=${CMAKE_BINARY_DIR}/main.l --name=${CMAKE_BINARY_DIR}/main ${CMAKE_BINARY_DIR}/main
        )

add_custom_target(clean COMMAND git clean -fd ${CMAKE_SOURCE_DIR})
