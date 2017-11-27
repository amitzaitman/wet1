//
// Created by zamit on 11/26/17.
//

#ifndef WET1_COLOSSEUM_H
#define WET1_COLOSSEUM_H

/* Return Values
* ----------------------------------- */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;

typedef struct gladiator Gladiator;
typedef struct trainer Trainer;


class Colosseum {
public:
    Colosseum(){

    }
    /* Description:   Adds a new trainer.
	* Input:         trainerID - The ID of the trainer to add.
	* Output:        None.
	* Return Values: ALLOCATION_ERROR - In case of an allocation error.
	*                INVALID_INPUT - If DS==NULL or if trainerID <= 0.
	*                FAILURE - If trainerID is already in the DS.
	*                SUCCESS - Otherwise.
	*/
    StatusType AddTrainer(int trainerID);

    /* Description:   Adds a new gladiator to the system.
    * Input:         gladiatorID - ID of the gladiator to add.
    *                trainerID - The ID of the gladiator's trainer
    *                level - The gladiator's level
    * Output:        None.
    * Return Values: ALLOCATION_ERROR - In case of an allocation error.
    *                INVALID_INPUT - If DS==NULL, or if gladiatorID <=0, or if trainerID <=0, or if level <= 0
    *                FAILURE - If gladiatorID is already in the DS, or trainerID isn't in the DS.
    *                SUCCESS - Otherwise.
    */
    StatusType BuyGladiator(int gladiatorID, int trainerID, int level);

    /* Description:   Removes an existing gladiator.
    * Input:         gladiatorID - The ID of the gladiator to remove.
    * Output:        None.
    * Return Values: ALLOCATION_ERROR - In case of an allocation error.
    *                INVALID_INPUT - If DS==NULL or if gladiatorID <= 0.
    *                FAILURE - If gladiatorID isn't in the DS.
    *                SUCCESS - Otherwise.
    */
    StatusType FreeGladiator(int gladiatorID);

    /* Description:   Increases the level of a gladiator.
    * Input:         gladiatorID - The ID of the gladiator.
    *		            levelIncrease - The increase in level.
    * Output:        None.
    * Return Values: ALLOCATION_ERROR - In case of an allocation error.
    *                INVALID_INPUT - If DS==NULL, or if gladiatorID<=0, or if levelIncrease<=0
    *                FAILURE - If gladiatorID isn't in the DS.
    *                SUCCESS - Otherwise.
    */
    StatusType LevelUp(int gladiatorID, int levelIncrease);

    /* Description:   Upgrades a gladiator, updating his ID, while maintaining his level.
    * Input:         gladiatorID - The original ID of the gladiator.
    *                upgradedID - The new ID of the gladiator.
    * Output:        None.
    * Return Values: ALLOCATION_ERROR - In case of an allocation error.
    *                INVALID_INPUT - If DS==NULL, or if gladiatorID<=0, or if upgradedID<=0.
    *                FAILURE - If gladiatorID isn't in the DS, or upgradedID is in the DS.
    *                SUCCESS - Otherwise.
    */
    StatusType UpgradeGladiator(int gladiatorID, int upgradedID);

    /* Description:   Returns the gladiator with the highest level from trainerID
    * 			If trainerID < 0, returns the top gladiator in the entire DS.
    * Input:         trainerID - The trainer that we'd like to get the data for.
    * Output:        gladiatorID - A pointer to a variable that should be updated to the ID of the top gladiator.
    * Return Values: ALLOCATION_ERROR - In case of an allocation error.
    *                INVALID_INPUT - If DS==NULL, or if gladiatorID == NULL, or if trainerID == 0.
    *                SUCCESS - Otherwise.
    */
    StatusType GetTopGladiator(int trainerID, int *gladiatorID);

    /* Description:   Returns all the gladiators from trainerID sorted by their level.
    *           			If trainerID < 0, returns all the gladiators in the entire DS sorted by their level.
    * Input:         trainerID - The trainer that we'd like to get the data for.
    * Output:        gladiators - A pointer to a to an array that you should update with the gladiators' IDs sorted by their level,
    *			          in case two gladiators have same level they should be sorted by their ID.
    *                numOfGladiator - A pointer to a variable that should be updated to the number of gladiators.
    * Return Values: ALLOCATION_ERROR - In case of an allocation error.
    *                INVALID_INPUT - If any of the arguments is NULL or if trainerID == 0.
    *                SUCCESS - Otherwise.
    */
    StatusType GetAllGladiatorsByLevel(int trainerID, int **gladiators, int *numOfGladiator);

    /* Description:   Updates the level of the gladiators where gladiatorID % stimulantCode == 0.
    * 			          For each matching gladiator, multiplies its level by stimulantFactor.
    * Input:         stimulantCode - The basis that the stimulant works on
    *          		  stimulantFactor - The multiply factor of the level
    * Output:        None.
    * Return Values: ALLOCATION_ERROR - In case of an allocation error.
    *                INVALID_INPUT - If DS==NULL or if stimulantCode < 1 or if stimulantFactor <1
    *                SUCCESS - Otherwise.
    */
    StatusType UpdateLevels(int stimulantCode, int stimulantFactor);


    /* Description:   Quits and deletes the database.
    * Input:         None
    * Output:        None.
    * Return Values: None.
    */
    void Quit();

};


#endif //WET1_COLOSSEUM_H
