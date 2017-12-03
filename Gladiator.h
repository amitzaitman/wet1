//
// Created by גל on 29/11/2017.
//

#ifndef WET1_MASTER_GLADIATOR_H
#define WET1_MASTER_GLADIATOR_H


class Gladiator {
    int id;
    int lvl;
    Trainer* trainer;
public:
    Gladiator(int id,int lvl, Trainer* trainer) : id(id), lvl(lvl), trainer
            (trainer){};
    ~Gladiator(){};
    void setLevel(int newLevel){
        level=newLevel;
    }

    void setId(int newId){
        id=newId;
    }

    void setTrainer(int newTrainer){
        trainer=newTrainer;
    }

    int getId()const{
        return id;
    }
    int getLevel()const{
        return level;
    }
    Trainer* getTrainer()const{
        return trainer;
    }

};



class levelKey{
private:
    int level;
    int id;
public:
    levelKey(int id, int level): level(level), id(id){};
    levelKey(Gladiator glad): level(glad.getLevel()), id(glad.getId()){};
    ~levelKey(){};

    bool operator>(const levelKey& key)const {
        if (level > key.level || (level == key.level && id < key.id))
            return true;
        return false;
    }
    bool operator==(const levelKey& key)const{
        if(level==key.level && id==key.id)
            return true;
        return false;
    }

    bool operator<(const levelKey& key)const{
        if(*this == key || *this>key )
            return false;
        return true;
    }
};





#endif //WET1_MASTER_GLADIATOR_H
