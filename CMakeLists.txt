cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(ApplicHoraire)

# Spécifier le standard C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Trouver les modules Qt nécessaires
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# Inclure le répertoire includes
include_directories(includes)

# Ajouter les fichiers sources automatiquement
file(GLOB SOURCES "sources/*.cpp")
file(GLOB HEADERS "includes/*.h" "includes/*.hpp" "includes/*.ipp")

# Ajouter l'exécutable dans le répertoire build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
add_executable(ApplicHoraire ${SOURCES} ${HEADERS})

# Lier les bibliothèques Qt nécessaires
target_link_libraries(ApplicHoraire Qt5::Core Qt5::Gui Qt5::Widgets)
