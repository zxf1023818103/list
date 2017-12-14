cmake_minimum_required(VERSION 3.0.0)

project(list-lib)

aux_source_directory(. SOURCES)
add_library(list STATIC ${SOURCES})

