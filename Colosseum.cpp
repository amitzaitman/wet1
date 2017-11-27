//
// Created by zamit on 11/26/17.
//

#include "Colosseum.h"
#include "splayTree.h"

struct trainer {
    int id;
    SplayTree<Gladiator> gladById;
    SplayTree<Gladiator> gladByLvl;
};

struct gladiator {
    int id;
    int lvl;
    Trainer* trainer;
};

class Colosseum{
    SplayTree<Trainer> trainers;
public:
    Colosseum();
    ~Colosseum();

};

