if(GETTEXT_FOUND)
    set(POT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/tplotter.pot)
    set(PO_FILES ru.po)
    
    add_custom_command(
        OUTPUT ${POT_FILE}
        COMMAND xgettext --keyword=_ --language=C --add-comments --sort-output 
                -o ${POT_FILE} ${CMAKE_SOURCE_DIR}/src/main.c
        DEPENDS ${CMAKE_SOURCE_DIR}/src/main.c
        COMMENT "Extracting translatable strings"
    )
    
    foreach(PO_FILE ${PO_FILES})
        get_filename_component(LANG ${PO_FILE} NAME_WE)
        set(MO_FILE ${CMAKE_CURRENT_BINARY_DIR}/${LANG}.mo)
        
        add_custom_command(
            OUTPUT ${MO_FILE}
            COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} -o ${MO_FILE} 
                    ${CMAKE_CURRENT_SOURCE_DIR}/${PO_FILE}
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PO_FILE}
            COMMENT "Compiling ${LANG} translation"
        )
        
        install(FILES ${MO_FILE}
                DESTINATION ${CMAKE_INSTALL_LOCALEDIR}/${LANG}/LC_MESSAGES
                RENAME tplotter.mo)
        
        list(APPEND MO_FILES ${MO_FILE})
    endforeach()
    
    add_custom_target(translations ALL DEPENDS ${MO_FILES})
endif()
