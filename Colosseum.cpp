

#include "splayTree.h"
#include "Colosseum.h"
#include "Trainer.h"

#define nullptr 0


Colosseum::Colosseum() : bestGladId(-1) {};
Colosseum::~Colosseum() {};

StatusType Colosseum::AddTrainer(int trainerID) {
    Trainer *trainer = new Trainer(trainerID);
    try {
        trainers.insert(trainerID, trainer);
    }
    catch (alreadyIn) {
        delete trainer;
        return FAILURE;
    }
    catch(std::bad_alloc){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Colosseum::BuyGladiator(int gladiatorID, int trainerID, int level) {
    try {
        Trainer *trainer = trainers.findData(trainerID);
        Gladiator glad(gladiatorID, level, trainer);
        gladById.insert(gladiatorID, glad);
        gladByLvl.insert(levelKey(glad), glad);
        trainer->addGladiator(glad);
        bestGladId=gladByLvl.findMax().getId();///////////////////////
    }
    catch(ElementNotFound) {///////////////////////////////////
        return FAILURE;
    }
    catch  (alreadyIn) {
        return FAILURE;
    }
    catch(std::bad_alloc){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Colosseum::FreeGladiator(int gladiatorID) {
    try {
        Gladiator glad = gladById.findData(gladiatorID);///////////////
        glad.getTrainer()->removeGladiator(glad);
        gladById.remove(gladiatorID);
        gladByLvl.remove(glad);
        bestGladId = gladByLvl.findMax().getId();
    }
    catch(ElementNotFound){
        return FAILURE;
    }
    catch(std::bad_alloc){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Colosseum::LevelUp(int gladiatorID, int levelIncrease) {
    try {
        Gladiator glad = gladById.findData(gladiatorID);///!!!!!!
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
    catch(std::bad_alloc){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Colosseum::GetTopGladiator(int trainerID, int *gladiatorID) {
    if (trainerID < 0){
         *gladiatorID = bestGladId;
        return SUCCESS;
    }
    try{
        Trainer* trainer = trainers.findData(trainerID);
        *gladiatorID = trainer->getTopGladId();
    }
    catch(ElementNotFound){
        return FAILURE;
    }
    catch(std::bad_alloc){
      return  ALLOCATION_ERROR;
    }
    return SUCCESS;
}

static void idArray(int** gladiators, Gladiator* gladiatorsData, int numOfGladiators){
    if(!gladiatorsData) {
        *gladiators = NULL;
        return;
    }

    *gladiators = new int [numOfGladiators*sizeof(int)];
    for (int i=0 ; i<numOfGladiators; i++){
        (*gladiators)[i] = gladiatorsData[numOfGladiators-1-i].getId();
    }
}

StatusType Colosseum::GetAllGladiatorsByLevel(int trainerId, int** gladiators,
                                   int* numOfGladiators){
    try {
        Gladiator* gladiatorsData;
        if (trainerId < 0) {
            int junk = 0;
            *numOfGladiators = gladByLvl.getSize();
            gladiatorsData = gladByLvl.getDataByPred(alwaysTrue<Gladiator>, &junk);
        } else {
            Trainer *trainer = trainers.findData(trainerId);
            *numOfGladiators = trainer->getGladiatorsNum();
            gladiatorsData = trainer->getGladiatorsByLevel();
        }
        idArray(gladiators, gladiatorsData, *numOfGladiators);
    }
    catch(ElementNotFound){
        return FAILURE;
    }
    catch(std::bad_alloc){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}



StatusType Colosseum::UpgradeGladiator(int gladiatorID, int upgradedId) {
    try {
        Gladiator glad = gladById.findData(gladiatorID);///!!!!!!
        Gladiator newGlad = Gladiator(upgradedId,glad.getLevel(),glad
                .getTrainer());
        gladById.insert(newGlad.getId(),newGlad);
        gladByLvl.insert(newGlad,newGlad);

        glad.getTrainer()->updateId(glad, upgradedId);
        gladById.remove(glad.getId());
        gladByLvl.remove(glad);
        bestGladId = gladByLvl.findMax().getId();
    }
    catch(ElementNotFound){
        return FAILURE;
    }
    catch(alreadyIn){
        return FAILURE;
    }
    catch(std::bad_alloc){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}
StatusType Colosseum::UpdateLevels(int stimulantCode, int stimulantFactor){

    try{
        UpdateIdTree(&gladById,stimulantCode,stimulantFactor);
        UpdateLevelTree(&gladByLvl,stimulantCode,stimulantFactor);
        int numOfTrainers = 0;
        Trainer** allTrainers = trainers.getAllData(alwaysTrue,&numOfTrainers);
        for(int i=0; i < numOfTrainers; i++){
            allTrainers[i]->updateLevels(stimulantCode,stimulantFactor);
        }
    }
    catch(std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}
//
