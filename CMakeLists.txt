cmake_minimum_required(VERSION 3.7)
project(wet1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        library1.h
        main1.cpp splayTree.h splayTree.cpp Trainer.cpp Trainer.h libary1.cpp Colosseum.cpp Colosseum.h)

add_executable(wet1 ${SOURCE_FILES})