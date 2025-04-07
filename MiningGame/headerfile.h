//
// Created by Louis on 03/05/2024.
//

#ifndef VERSION5_HEADERFILE_H
#define VERSION5_HEADERFILE_H

//all structs
typedef struct coordinates{     // struct to represent coordinate data
    int x;
    int y;
}coordinates;

typedef struct itemData{        //struct to hold data on items the player can possess
    char name[50];
    double value;
    char rarity[20];
    int weight;
    char mapIcon;
    char type[10];
    int nutritionalValue;
}itemData;

typedef struct molehill{            //holding coordinates on mole hills (impassible objects)
    coordinates location;
    char mapIcon;
}moleHills;

typedef struct ores{            //struct representing data on ores
    coordinates location;
    itemData typeOfOre;
}ores;

typedef struct item{            //holding data on items
    coordinates location;
    itemData typeOfItem;
}item;

typedef struct backpack{        //struct to hold data on what the player is currently carrying
    int level;
    int maxWeight;
    int currentWeight;
    item items[20];

}Bag;

typedef struct player{          //struct to represent data on the player
    coordinates location;
    int energy;
    int maxenergy;
    double coins;

}playerInfo;




//prototypes for each function

int getDifficulty();
int gameSetup();

int theShop(Bag* playerbag, playerInfo * player);
int getStock(item *);
int shopBuy(item* ,Bag* ,playerInfo*);
int shopSell(item* ,Bag* ,playerInfo*);
int shopFirstVisitDialogue();
int generateNewLevel(playerInfo *, Bag* );

int createRandomNumber(int, int);
int movePlayer(int , int , int, ores * ,item * ,Bag* ,playerInfo *, moleHills *);
int outOfBounds(int, moleHills* , playerInfo *);

int generateMoleHill(int, moleHills*);
int generateOres(int, ores*);
int generateItem(int, int, item*, ores*);
int generateMap(int,int,int, playerInfo *,ores*,item*,moleHills *);
int oreTypeGenerator(int, ores*);
int itemTypeGenerator(int, item*);

int mining(int,playerInfo *, ores*);
int calculateEnergy(playerInfo* );

Bag setBag();
int upgradeBag(Bag* );
int addToBag(Bag *, ores*,int, item*,char);
int removeItem(item * , Bag *);

int inventory(Bag *, playerInfo *, char);
int inventoryOptions(Bag * , playerInfo * );
int pickUp(playerInfo *, item*, ores*, Bag*, int ,int);

int endGame(playerInfo* player);
int winGame(playerInfo* player);
int readToleaderBoard();
int writeToleaderBoard(playerInfo* player);

//end of prototype

#endif //VERSION5_HEADERFILE_H
