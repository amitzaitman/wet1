cmake_minimum_required(VERSION 3.7)
project(wet1)

set(g++ –DNDEBUG –Wall)

set(SOURCE_FILES
        library1.h
        main1.cpp
        splayTree.h
        splayTree.cpp
        libary1.cpp
        Colosseum.cpp
        Colosseum.h
        Trainer.h
        test1.cpp)

add_executable(wet1 ${SOURCE_FILES})