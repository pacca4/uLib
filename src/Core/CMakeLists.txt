
set(HEADERS Options.h
            StaticInterface.h)

set(SOURCES Options.cpp)

set(LIBRARIES ${Boost_PROGRAM_OPTIONS_LIBRARY})

set(libname ${PACKAGE_LIBPREFIX}Core)
set(ULIB_SHARED_LIBRARIES ${ULIB_SHARED_LIBRARIES} ${libname} PARENT_SCOPE)
set(ULIB_SELECTED_MODULES ${ULIB_SELECTED_MODULES} Core PARENT_SCOPE)

add_library(${libname} SHARED ${SOURCES})
set_target_properties(${libname} PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION ${PROJECT_SOVERSION})
target_link_libraries(${libname} ${LIBRARIES})

install(TARGETS ${libname}
        EXPORT "${PROJECT_NAME}Targets"
        RUNTIME DESTINATION ${PACKAGE_INSTALL_BIN_DIR} COMPONENT bin
        LIBRARY DESTINATION ${PACKAGE_INSTALL_LIB_DIR} COMPONENT lib)

install(FILES ${HEADERS} DESTINATION ${PACKAGE_INSTALL_INC_DIR}/Core)



