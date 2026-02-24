#PracticaNo1-EDD

##Descripcion

Esta es mi primera practica de EDD :)
En la cual se me pidio hacer el juego de UNO. Este mismo fue realizado 
en el Framework QT Creator que me permitio desarrollar una interfaz grafica. QT es un Framework DE de C++ que posee la caracteristica de ser multiplataforma, sin embargo tambien para futuros programadores de este proyecto se debe de saber como poder compilar este archivo.

Por lo tanto aca les dejo las instrucciones para poder generar el ejecutable de mi practica. Que fue muy divertida de programar :) 

##Requisitos

- Qt 6.5 o superior
- CMake 3.19 o superior
- Compilador C++ (GCC / MinGW / MSVC)


##Instrucciones de compilacion

Aca les dejo un Scriptcito para que puedan generar el ejecutable en linux.

###Script build.sh

Crear un archivo llamado `build.sh` en la raíz del proyecto con el siguiente contenido:

```bash
#!/bin/bash

echo "===================================="
echo " Compilando PracticaNo1 :) (Qt6 + CMake)"
echo "===================================="

if [ ! -f "CMakeLists.txt" ]; then
    echo "Error: No se encontró CMakeLists.txt en esta carpeta."
    exit 1
fi

rm -rf build
mkdir build
cd build

echo "Generando proyecto con CMake..."

cmake -DCMAKE_PREFIX_PATH=$HOME/Qt/6.10.2/gcc_64 ..

if [ $? -ne 0 ]; then
    echo "Error en configuración CMake."
    exit 1
fi

echo "Compilando..."
cmake --build .

if [ $? -ne 0 ]; then
    echo "Error en compilación."
    exit 1
fi

echo "------------------------------------"
echo " Compilación exitosa."
echo " $(pwd)/PracticaNo1"
echo "------------------------------------"

```
##==========================================

##Luego de copiar el script:

Abre tu terminal en el directorio donde clonaste mi repositorio 
y ejecuta:

```
chmod +x build.sh

./build.sh
```

##Si no tienes QT en tu pc sigue los pasos:

Debido a que mi proyecto esta en QT este pide que este instalado entonces sigue los siguientes pasos:

##Compilacion en linux:

```
sudo apt update

sudo apt install qt6-base-dev qt6-base-dev-tools cmake build-essential

qmake6 --version 

cmake --version

```

## Compilación en Windows

### Opcion 1: Recomendada

1. Instalar Qt desde:
   https://www.qt.io/download

2. Abrir Qt Creator.
3. Abrir el proyecto. Dar click en (CMakeLists.txt).
4. Seleccionar el Kit adecuado.
5. Presionar Build.

---

### Opción 2 (Terminal Qt)

Instalar Qt con MinGW.

Abrir Qt Command Prompt (MinGW) (No usar PowerShell normal.)


Qt Command Prompt (MinGW)

Luego ejecutar:

mkdir build
cd build
cmake ..
cmake --build .

