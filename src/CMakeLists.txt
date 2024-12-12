cmake_minimum_required(VERSION 3.16)

# Définir le projet
project(MyProject)

# Ajouter le chemin d'inclusion
include_directories(${CMAKE_SOURCE_DIR}/include)

# Spécifier les fichiers sources
add_executable(MyProject src/main.c src/geometry.c)