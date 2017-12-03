#ifndef WET1_TRAINER_H
#define WET1_TRAINER_H
#include "splayTree.h"
#include "Gladiator.h"


//TODO:


class Trainer {
private:
    int id;
    SplayTree<Gladiator> gladById;
    SplayTree<Gladiator,levelKey> gladByLvl;
    int topGladId;
public:
    Trainer(int id) : id(id), topGladId(-1){};
    void addGladiator(Gladiator glad) {
        if (gladById.find(glad.getId()) != nullptr) {
           // to complete
        }
        gladById.insert(glad.getId(),glad);
        gladByLvl.insert(levelKey(glad.getId(),glad.getLevel()),glad);
        topGladId=gladByLvl.findMax().getId();
    }

    void removeGladiator(Gladiator glad){
        if (gladById.find(glad.getId()) == nullptr) {
            //to complete
        }
        gladById.remove(glad.getId());
        gladByLvl.remove(levelKey(glad.getId(),glad.getLevel()));
        topGladId=gladByLvl.findMax().getId();
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
        if(topGladId == glad.getId())
            topGladId = glad.getId();
        glad.setId(newId);
        gladById.insert(glad.getId(),glad);
        gladByLvl.insert(glad,glad);
    }

    int getId()const{
        return id;
    }
    int getTopGladId()const{
        return topGladId;
    }
    bool operator==(const Trainer& trainer){
        return (id==trainer.getId());
    }
};
#endif //WET1_TRAINER_H
