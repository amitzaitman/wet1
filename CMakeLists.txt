cmake_minimum_required(VERSION 3.7)
project(wet1)

set(g++ –DNDEBUG –Wall)

set(SOURCE_FILES
        library1.h
        library1_tests.cpp
#        main1.cpp
        splayTree.h
        libary1.cpp
        Colosseum.cpp
        Colosseum.h
        Gladiator.h
        Trainer.h)

add_executable(wet1 ${SOURCE_FILES})