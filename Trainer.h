#ifndef WET1_TRAINER_H
#define WET1_TRAINER_H
#include "splayTree.h"

class Trainer {
    int id;
    splayTree<gladiator> gladById;
    splayTree<gladiator> gladByLvl;
};


#endif //WET1_TRAINER_H
