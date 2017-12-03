//
// Created by zamit on 11/26/17.
//

#include "Colosseum.h"
#include "splayTree.h"
#include "trainer.h"
#include "Gladiator.h"

#define nullptr 0

//TODO: exceptions,findMax,assert,change h
namespace Colosseum {
    class Colosseum {
        SplayTree<Trainer *> trainers;
        SplayTree<Gladiator> gladById;
        SplayTree<Gladiator,levelKey> gladByLvl;
        int bestGladId;
    public:
        Colosseum() : bestGladId(-1) {};
        ~Colosseum() {};

        StatusType AddTrainer(int trainerID) {
            Trainer *trainer = new Trainer(trainerID);
            try {
                trainers.insert(trainerID, trainer);
            }
            catch (alreadyIn) {
                delete trainer;
                return FAILURE;
            }
            return SUCCESS;
        }

        StatusType BuyGladiator(int gladiatorID, int trainerID, int level) {
            try {
                Trainer *trainer = trainers.find(trainerID);
                Gladiator glad(gladiatorID, level, trainer);
                gladById.insert(gladiatorID, glad);
                gladByLvl.insert(levelKey(glad), glad);
                trainer->addGladiator(glad);
                bestGladId=gladByLvl.findMax().getId();///////////////////////
            }
            catch(ElementNotFound()) {///////////////////////////////////
                return FAILURE;
            }
            catch  (alreadyIn) {
                return FAILURE;
            }
            return SUCCESS;
        }

        StatusType FreeGladiator(int gladiatorID) {

            try {
                Gladiator glad = gladById.find(gladiatorID);
                glad.getTrainer()->removeGladiator(glad);
                gladById.remove(gladiatorID);
                gladByLvl.remove(glad);
                bestGladId = gladByLvl.findMax().getId();///////////////////////
            }
            catch(ElementNotFound){
                return FAILURE;
            }
            return SUCCESS;
        }

        StatusType LevelUp(int gladiatorID, int levelIncrease) {
            try {
                Gladiator glad = gladById.find(gladiatorID);///!!!!!!
                glad.getTrainer()->updateLvl(glad, levelIncrease);
                gladById.remove(glad.getId());
                gladByLvl.remove(glad);
                glad.setLevel(glad.getLevel() + levelIncrease);
                gladById.insert(glad.getId(),glad);
                gladByLvl.insert(glad,glad);
                bestGladId = gladByLvl.findMax().getId();
            }
            catch(ElementNotFound){
                return FAILURE;
            }
            return SUCCESS;
        }

        StatusType GetTopGladiator(int trainerID, int *gladiatorID) {
            if (trainerID < 0)
                return bestGladId;
            try{
                Trainer* trainer = trainers.find(trainerID);
                trainer->getTopGladId();
            }
            catch(ElementNotFound){
                return FAILURE;
            }
            return SUCCESS;
        }

        StatusType getAllGladiatorsByLevel(int trainerId, int** gladiators,
                                           int* numOfGladiators){

        }
    };

}//namespace colosseum