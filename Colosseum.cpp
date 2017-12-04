

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
                ALLOCATION_ERROR;
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
                ALLOCATION_ERROR;
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
                ALLOCATION_ERROR;
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
                ALLOCATION_ERROR;
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
            *gladiators = (int*) malloc(numOfGladiators*sizeof(int));
            if (!*gladiators) throw std::bad_alloc();
            for (int i=0 ; i<numOfGladiators; i++){
                (*gladiators)[i] = gladiatorsData[numOfGladiators-1-i].getId();
            }
        }

        StatusType Colosseum::GetAllGladiatorsByLevel(int trainerId, int** gladiators,
                                           int* numOfGladiators){
            try {
                Gladiator* gladiatorsData;
                if (trainerId < 0) {
                    *numOfGladiators = gladByLvl.getSize();
                    gladiatorsData = gladByLvl.getAllData();
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
                ALLOCATION_ERROR;
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

void stimulateGladiatorsByLvl(Gladiator* allGladiatorsByLvl,
                              int numOfGladiators, int stimulantCode, int stimulantFactor){
    int numOfStimulantGlad = 0;
    Gladiator* stimulantGlads =(Gladiator*) malloc(sizeof(Gladiator)
                                                   *numOfGladiators);
    if(stimulantGlads == NULL) {
        throw std::bad_alloc();
    }
    for (int i = 0; i < numOfGladiators; ++i) {
        Gladiator &glad = allGladiatorsByLvl[i];
        if(glad.getId()%stimulantCode == 0){
            stimulantGlads[numOfStimulantGlad] = Gladiator
                    (glad.getId(),glad.getLevel()*stimulantFactor,
                     glad.getTrainer());
            numOfStimulantGlad++;
            glad.setId(0);
        }
    }
    int counter1=0;
    int counter2=0;
    int counter=0;
    Gladiator* newGlads =(Gladiator*) malloc(sizeof(Gladiator)
                                             *numOfGladiators);
    while(counter1 < numOfStimulantGlad && counter2 < numOfGladiators){
        if (allGladiatorsByLvl[counter2].getId() == 0)
            counter2++;
        else
        {
            if(levelKey(allGladiatorsByLvl[counter2]) > levelKey
                    (stimulantGlads[counter1]))
            {
                newGlads[counter]=allGladiatorsByLvl[counter2];
                counter2++;
                counter++;
            }
            else{
                newGlads[counter]=stimulantGlads[counter1];
                counter1++;
                counter++;
            }
        }
    }

    while(counter1 < numOfStimulantGlad){
        newGlads[counter]=stimulantGlads[counter1];
        counter1++;
        counter++;
    }
    while(counter2 < numOfGladiators){
        if(allGladiatorsByLvl[counter2].getId()==0)
            counter2++;
        else {
            newGlads[counter] = allGladiatorsByLvl[counter2];
            counter2++;
            counter++;
        }
    }
    for (int i = 0; i <numOfGladiators ; ++i) {
        allGladiatorsByLvl[i]=newGlads[i];
    }
    free(stimulantGlads);
    free(newGlads);
}

void stimulateGladiatorsById(Gladiator* allGladiatorsById,
                             int numOfGladiators, int stimulantCode,
                             int stimulantFactor){
    for (int i = 0; i <numOfGladiators ; ++i) {
        if(allGladiatorsById[i].getId()%stimulantCode){
            allGladiatorsById[i].setLevel(allGladiatorsById[i].getId()
                                          *stimulantCode);
        }
    }
}

StatusType Colosseum::UpdateLevels(int stimulantCode, int stimulantFactor){

    Gladiator* allGladiatorsById;
    Gladiator *allGladiatorsByLvl;
    int numOfGladiators = gladByLvl.getSize();
    try {

        allGladiatorsByLvl = gladByLvl.getAllData();
    }
    catch(std::bad_alloc){
        return ALLOCATION_ERROR;
    }
    try{
        allGladiatorsById = gladById.getAllData();
    }
    catch(std::bad_alloc) {
        free(allGladiatorsByLvl);
        return ALLOCATION_ERROR;
    }
    try{
        stimulateGladiatorsById(allGladiatorsById,numOfGladiators,
                                stimulantCode,
                                stimulantFactor);
        stimulateGladiatorsByLvl(allGladiatorsByLvl,numOfGladiators,
                                 stimulantCode,
                                 stimulantFactor);
        gladById.destroyTree();
        gladByLvl.destroyTree();
        gladByLvl = SplayTree<Gladiator, levelKey>();
        gladById = SplayTree<Gladiator>();
        for (int i = 0; i < numOfGladiators; ++i) {
            gladByLvl.insert(allGladiatorsByLvl[0],
                             allGladiatorsByLvl[0]);
            gladById.insert(allGladiatorsById[0].getId(),
                            allGladiatorsById[0]);
        }
        int numOfTrainers = trainers.getSize();
        Trainer **allTrainer = trainers.getAllData();
        for (int i = 0; i < numOfTrainers; ++i) {//!!!!!!!!!!!!!!!!!!!1
            //       allTrainer[i]->stimulate(stimulnteCode, stimulantFactor);
        }//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }catch(std::bad_alloc){
        free(allGladiatorsById);
        free(allGladiatorsByLvl);
        return ALLOCATION_ERROR;
    }

    free(allGladiatorsById);
    free(allGladiatorsByLvl);
    return SUCCESS;
}



