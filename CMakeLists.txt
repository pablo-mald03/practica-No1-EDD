cmake_minimum_required(VERSION 3.19)
project(PracticaNo1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(PracticaNo1
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    recursos.qrc
    pantallainicio.h pantallainicio.cpp pantallainicio.ui
    pantallaseleccion.h pantallaseleccion.cpp pantallaseleccion.ui
    pantallamodalidad.h pantallamodalidad.cpp pantallamodalidad.ui
    pantallaconfiguraciones.h pantallaconfiguraciones.cpp pantallaconfiguraciones.ui
    pantallajuego.h pantallajuego.cpp pantallajuego.ui
    modelo.h modelo.cpp
    colorcarta.h colorcarta.cpp
    numerica.h numerica.cpp
    multicolorsuma.h multicolorsuma.cpp
    coloreterno.h coloreterno.cpp
    sumacantidad.h sumacantidad.cpp
    cambiodireccion.h cambiodireccion.cpp
    comodincolor.h comodincolor.cpp
    bloqueo.h bloqueo.cpp
    espia.h espia.cpp
    eclipse.h eclipse.cpp
    reversa.h reversa.cpp
    nodo.h nodo.tpp
    listaenlazada.h listaenlazada.tpp
    jugador.h jugador.cpp
    configuracionpartida.h configuracionpartida.cpp
    partida.h partida.cpp



)

target_link_libraries(PracticaNo1
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS PracticaNo1
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET PracticaNo1
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
