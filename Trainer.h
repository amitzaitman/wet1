#ifndef WET1_TRAINER_H
#define WET1_TRAINER_H
#include "splayTree.h"
#include "Gladiator.h"

template <class T>
bool alwaysTrue(T t){
    return true;
}

class Trainer {
private:
    int id;
    SplayTree<Gladiator> gladById;
    SplayTree<Gladiator,levelKey> gladByLvl;
    int topGladId;
public:
    Trainer(int id) : id(id), topGladId(-1){};
    void addGladiator(Gladiator glad) {
        gladById.insert(glad.getId(),glad);
        gladByLvl.insert(levelKey(glad.getId(),glad.getLevel()),glad);
        topGladId=gladByLvl.findMax().getId();
    }

    void removeGladiator(Gladiator glad){
        gladById.remove(glad.getId());
        gladByLvl.remove(levelKey(glad.getId(),glad.getLevel()));
        if (!gladByLvl.getSize()) topGladId = -1;
        else topGladId=gladByLvl.findMax().getId();
    }

    void updateLvl(Gladiator glad,int lvlIncrease){
        gladById.remove(glad.getId());
        gladByLvl.remove(glad);
        glad.setLevel(glad.getLevel()+lvlIncrease);
        gladById.insert(glad.getId(),glad);
        gladByLvl.insert(glad,glad);
        topGladId = gladByLvl.findMax().getId();
    }

    void updateId(Gladiator glad,int newId){
        gladById.remove(glad.getId());
        gladByLvl.remove(glad);
        glad.setId(newId);
        gladById.insert(glad.getId(),glad);
        gladByLvl.insert(glad,glad);
        topGladId = gladByLvl.findMax().getId();
    }
    void  updateLevels(int stimulantCode,int stimulantFactor){
        UpdateIdTree(&gladById,stimulantCode,stimulantFactor);
        UpdateLevelTree(&gladByLvl,stimulantCode,stimulantFactor);
    }

    int getId()const{
        return id;
    }
    int getTopGladId()const{
        return topGladId;
    }
    int getGladiatorsNum(){
        return gladById.getSize();
    }
    Gladiator* getGladiatorsByLevel(){
        int a = 0;
        return gladByLvl.getDataByPred(alwaysTrue<Gladiator>, &a);
    }
    bool operator==(const Trainer& trainer){
        return (id==trainer.getId());
    }
};
#endif //WET1_TRAINER_H
