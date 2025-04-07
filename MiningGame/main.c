/* FileName: PFECW - gardianAngel
 * Description: PFE CourseWork : Mining Game
 * Author: Louis Robinson @UWE 2024
 * Date: 02/05/2024
 * Version 5
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "headerfile.h"

int difficulty; //global variable for the difficulty


int main() {
    //readToleaderBoard();    //print out the previous games results
    getDifficulty();        //get the desired games difficulty
    gameSetup();            //start up the game

}

int getDifficulty(){
    //getting the desired games difficulty and setting it to the global variable
    printf("\n* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * WELCOME * * * * * * * * * * *\n");
    printf("* * * * * * * * * * TO * * * * * * * * * * * * \n");
    printf("* * * * * * * * *OREOPOLIS * * * * * * * * * * \n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    sleep(1);
    printf("\n\nPlease select your game difficulty!\n\n[1]Easy [2]Medium [3]Hard\n");
    scanf("%d", &difficulty);
    sleep(1);
    printf("Thank you....\n");
    sleep(2);

    return 0;
}

int gameSetup(){
    //generating the games values based on the selected difficulty
    int amount, amountItem, amountMoleHill;

    //creating an amount of ores to be present on the map
    amount = (createRandomNumber(60,10)/difficulty);
    ores Ores[amount];  //creating the struct array
    generateOres(amount, Ores); //generating data to put into the struct array about the ores

    //same thing but for the items
    amountItem = createRandomNumber(10,1)/difficulty;
    item Items[amountItem];
    generateItem(amountItem,amount,Items,Ores);

    //creating coords for moleHills
    amountMoleHill = createRandomNumber(10,1)*difficulty;
    moleHills MoleHill[amountMoleHill];
    generateMoleHill(amountMoleHill,MoleHill);

    //Creating the players bag
    Bag playerBag = setBag();

    //declaring the players initial data values
    playerInfo P1= {0,0,100,100};

    //Starting the game
    movePlayer(amount, amountItem,amountMoleHill, Ores, Items, &playerBag, &P1,MoleHill);

    return 0;
}

int generateNewLevel(playerInfo * P1, Bag* playerBag){
    //generating the new level values based on the selected difficulty
    int amount, amountItem, amountMoleHill;

    //creating an amount of ores to be present on the map
    amount = (createRandomNumber(60,1)/ difficulty);
    ores Ores[amount];
    generateOres(amount, Ores);

    //creating an amount of items
    amountItem = (createRandomNumber(10,1)/ difficulty);
    item Items[amountItem];
    generateItem(amountItem,amount,Items,Ores);

    //creating coords for moleHills
    amountMoleHill = createRandomNumber(10,1)*difficulty;
    moleHills MoleHill[amountMoleHill];
    generateMoleHill(amountMoleHill,MoleHill);

    //Starting the level
    movePlayer(amount, amountItem,amountMoleHill, Ores, Items, playerBag, P1,MoleHill);

    return 0;
}

int theShop(Bag* playerbag, playerInfo * player){

    int loop =0; char selection;

    shopFirstVisitDialogue();   //giving an introduction to the shop

    item shopstock[5];  //creating the shop stock
    getStock(shopstock);   //adding to the shop stock

    while(loop == 0) {  //while the player wishes to make a selection

        printf("[B]Buy [C]Sell [X]Exit [L]Elevator [I]Inventory [U]Upgrade Bag\n");    //options
        scanf(" %c", &selection);
        selection = toupper(selection); //turn them to upper so the map doesnt get involved

        switch (selection) {
            case 'B':
                shopBuy(shopstock, playerbag, player);  //commence shop buy function
                break;
            case 'C':
                shopSell(shopstock, playerbag, player); //commence shop buy function
                break;
            case 'L':

                printf("That would be 50 coins please\n!");
                if(player->coins >= 50){ //if player has enough money
                    player->coins = player->coins - 50;  //take away the price from the players coins
                    generateNewLevel(player, playerbag);    //use the elevator

                }else{  //if the player does not have enough money
                    printf("\nYou dont have enough money for that!\n");
                }
                break;
            case 'I':
                inventory(playerbag, player, 's'); //display inventory (without inventoryOptions)
                break;
            case 'U':

                printf("That will be 350 coins please!\n");
                if(player->coins >= 350){ //if player has enough money
                    player->coins = player->coins - 350;  //take away the price from the players coins
                    upgradeBag(playerbag);  //upgrading the players bag, giving them more weight
                    printf("Was a pleasure doing business with ya!\n ");
                    sleep(2);
                }else{  //if the player does not have enough money
                    printf("\nYou dont have enough money for that!\n");
                }
                break;
            case 'X':
                sleep(1);   //saying goodbye and ending the loop, allowing the player to access the map again
                printf("See you later!\n\n");
                sleep(1);
                printf("(Press [W][A][S][D] to leave the shop)");
                loop = 1;   //exit the loop
                break;
        }
    }

    return 0;
}

int shopFirstVisitDialogue(){
    static int interactions =0; //used to turn on and off the introduction to the shop
    if(interactions == 0){
        printf("\nHello! Welcome to my shop!\n");
        sleep(2);
        printf("Here you can do actions such as selling an item, buying an item, or even using the elevator!\n");
        sleep(5);
        printf("Whats the elevator you say?....\n");
        sleep(3);
        printf("The elevator allows you to go down to new floors once you have fully mined this one!\n");
        sleep(5);
        printf("But dont worry, theres a shop on every floor and they are all the same!\n");
        sleep(5);
        printf("Make sure you use the elevator to earn some extra bucks once your done with this level!\n");
        sleep(5);
        printf("Yes it will cost you, but nothing much...\n");
        sleep(4);
        printf("Out with the old, in with the new..... Thats what they say right?\n");
        sleep(4);
        printf("Anyway.... Ill be here if you need me. Bye for now. \n\n");
        sleep(3);
        printf("OH! One last thing! \n");
        sleep(2);
        printf("The only way to get out of here is if you earn 1,000 Coins... \n");
        sleep(4);
        printf("Look... I dont make the rules so dont be mad at me ok! \n");
        sleep(4);
        printf("Thats just the price of the elevator to get to the surface again... \n");
        sleep(4);
        printf("Goodluck! \n\n");
        sleep(4);
    }else{
        printf("\nWelcome back! What can I do for you!\n");
        sleep(3);
    }
    interactions +=1;   //once player has experienced this once, they wont have to again
    return 0;
}

int getStock(item* shopstock){
    //creating energy food for the player to purchase to not lose the game
    itemData largeRations = {"A breakfast bar", 10, "Mighty", 5, '!', "Item", 50};
    itemData water = {"A flask of water", 4, "prevents headaches", 4, '!', "Item", 10};
    itemData rations = {"A small bag of Rations", 6, "mhm mhm mhmmmm", 5, '!', "Item", 30};


    //adding them to the shopStock struct array
    shopstock[0].typeOfItem= largeRations;
    shopstock[1].typeOfItem = water;
    shopstock[2].typeOfItem= rations;

    printf("**********Welcome to the shop!**********\n\n");

    for (int i = 0; i < 3; ++i) {  //for each cell in the stock struct array

        //print data on the item
        printf("********** SLOT %d **********\n",i);
        printf("Name: %s\n", shopstock[i].typeOfItem.name);
        printf("Type: %s\n", shopstock[i].typeOfItem.type);
        printf("Rarity: %s\n", shopstock[i].typeOfItem.rarity);
        printf("Value: %.2f\n", shopstock[i].typeOfItem.value);
        printf("Weight: %d\n", shopstock[i].typeOfItem.weight);
        printf("Nutritional Value: %d\n", shopstock[i].typeOfItem.nutritionalValue);
    }

    return 0;
}

int shopBuy(item* shopstock,Bag* playerbag, playerInfo * player ){
    int itemNum;    //selected item
    printf("Please enter the item you would like to purchase");
    scanf(" %d",&itemNum);
    printf("You would like to buy: %s\nThat will be %2f coins please\n", shopstock[itemNum].typeOfItem.name, shopstock[itemNum].typeOfItem.value);

    if(player->coins >= shopstock[itemNum].typeOfItem.value){ //if player has enough money
        ores Ores;// addtobag needs an ores struct so i give it an empty one (it wont be used)
        player->coins = player->coins - shopstock[itemNum].typeOfItem.value;  //take away the price from the players coins

        addToBag(playerbag, &Ores, itemNum, &shopstock[itemNum], 'i');  //add the item to the players bag
    }else{  //if the player does not have enough money
        printf("\nYou dont have enough money for that!\n");
    }
    return 0;
}

int shopSell(item * shopstock,Bag* playerbag, playerInfo * player ){
    int itemNum;    //selected item
    inventory(playerbag,player,'s');    //displaying inventory without pulling in inventoryOptions
    printf("Your coins: %f\n",player->coins);    //displaying the users available coins

    printf("Please enter the item you would like to sell\n");
    scanf("%d",&itemNum);

    player->coins +=playerbag->items[itemNum].typeOfItem.value;  //adding the value to the players coins
    printf("Your coins: %f\n",player->coins);    //displaying the new value for the players coins

    removeItem(&playerbag->items[itemNum],playerbag);   //removing the item from the players bag

    if(player->coins >= 1000){  //player has won the game
        winGame(player);
    }else{
        printf("Getting that ever bit closer to freedom aye?\n\n");
    }

    return 0;
}

int removeItem(item * itemRemoved, Bag * playerBag){    //removing items from the inventory
    printf("Item Removed: %s",itemRemoved->typeOfItem.name);    //informing the player of the removed item

    playerBag->currentWeight -= itemRemoved->typeOfItem.weight; //readjusting the bag weight
    printf("Current Weight = %d\n", playerBag->currentWeight);  //informing player of new weight

    itemData Null = {"Empty",0,"Empty",0,'!',"Empty",0};
    itemRemoved->typeOfItem = Null; //setting the items slot to be empty


    return 0;
}

int movePlayer(int amount, int amountItem,int amountMoleHill, ores * Ores,item * Items,Bag* playerBag, playerInfo* P1, moleHills * moleHill){
    //taking user inputs and turning them into actions

    int moveLoop = 0, arrivedAtMoleHill;
    char input;

    generateMap(amount,amountItem,amountMoleHill,P1,Ores,Items,moleHill);   //displaying the map

    //monitoring player movement and interaction
    while(moveLoop == 0){       //while loop to constantly monitor player input
        scanf("%c", &input);    //taking in player input
        switch (input){             //determining what key was pressed
            case 'w':

                if(P1->location.y -1 < 0){   //if players coords exceed map boundaries
                    printf("You cannot exceed the boundaries of the Map\n");    //error message prompt
                }else{  //if they are still in the map
                    P1->location.y -=1;//move player up
                }

                arrivedAtMoleHill=outOfBounds( amountMoleHill, moleHill, P1); //checking if players on a molehill
                if(arrivedAtMoleHill == 1){ //if they are
                    P1->location.y +=1;//move player back
                }
                generateMap(amount,amountItem,amountMoleHill,P1,Ores,Items,moleHill);//update players movement
                break;
            case 'a':
                if(P1->location.x -1 < 0){
                    printf("You cannot exceed the boundaries of the Map\n");
                }else{
                    P1->location.x -=1;//move player left

                }

                arrivedAtMoleHill=outOfBounds( amountMoleHill, moleHill, P1); //checking if players on a molehill
                if(arrivedAtMoleHill == 1){ //if they are
                    P1->location.x +=1;//move player back
                }
                generateMap(amount,amountItem,amountMoleHill,P1,Ores,Items,moleHill);//update players movement
                break;
            case 's':
                if(P1->location.y +1 >= 12){
                    printf("You cannot exceed the boundaries of the Map\n");
                }else {
                    P1->location.y += 1;//move player down

                }

                arrivedAtMoleHill=outOfBounds( amountMoleHill, moleHill, P1); //checking if players on a molehill
                if(arrivedAtMoleHill == 1){ //if they are
                    P1->location.y -=1;//move player back
                }
                generateMap(amount,amountItem,amountMoleHill,P1,Ores,Items,moleHill);//update players movement
                break;
            case 'd':
                if(P1->location.x +1 >=24){
                    printf("You cannot exceed the boundaries of the Map\n");
                }else {
                    P1->location.x += 1;//move player right

                }
                arrivedAtMoleHill=outOfBounds( amountMoleHill, moleHill, P1); //checking if players on a molehill
                if(arrivedAtMoleHill == 1){ //if they are
                    P1->location.x -=1;//move player back
                }
                generateMap(amount,amountItem,amountMoleHill,P1,Ores,Items,moleHill);//update players movement
                break;
            case 'm':
                moveLoop = mining(amount,P1,Ores);  //perform the mining, if it returns 1 symbolising the player has died, the loop is ended.
                generateMap(amount,amountItem,amountMoleHill,P1,Ores,Items,moleHill);//update players movement
                break;
            case 'e':
                pickUp(P1,Items,Ores,playerBag,amount,amountItem);
                break;
            case 'i':
                inventory(playerBag,P1,'m');    //open inventory from the map
                generateMap(amount,amountItem,amountMoleHill,P1,Ores,Items,moleHill);//update players movement
                break;

        }

    }

    return 0;
}

int outOfBounds(int amountOfMolehills, moleHills* moleHill, playerInfo * player){//determining if players coords match a molehill
    int arrivedAtMoleHill;
    for (int i = 0; i < amountOfMolehills; ++i) {   //sifting through all the molehills coords
        if(player->location.x == moleHill[i].location.x && player->location.y == moleHill[i].location.y){   //if player is at a molehill
            printf("Thats one biiiiig molehill, guess I have to go around\n\n");    //giving reason for the blockage
            arrivedAtMoleHill =1;   //returning the result (true)
        }
    }
    return arrivedAtMoleHill;
}

int createRandomNumber(int max, int min){// creating random numbers
    int amount;
    //GENERATING THE AMOUNTS OF ORES
    srand(time(NULL));//seeding random number generator
    amount = (rand() %(max - min + 1)) + min; //Generating random number between min and max

    return amount;
}

int mining(int amount,playerInfo * player, ores *Ores){ //performing the mining action
    int mineable = 0, endTask =0; //if the current block contains an ore
    for (int k = 0; k < amount; ++k) {  //running through all the ores
        if(player->location.y == Ores[k].location.y && player->location.x == Ores[k].location.x && Ores[k].typeOfOre.mapIcon == '?') { //if current cell in array = ores coords
            mineable = 1; //the coordinate was an ore
            if(player->energy >0){  //if the player has enough energy to mine
                printf("Mining...");    //perform GUI animation, showing mining is taking place...
                sleep(1);
                printf("Mining...");
                sleep(1);
                printf("Mining...");
                sleep(1);
                printf("Mined!\n");
                sleep(2);
                printf("You have found: %s\n",Ores[k].typeOfOre.name);    //displaying the ore the user has found
                sleep(1);

                Ores[k].typeOfOre.mapIcon = '!';    //changing ore icon to show it has been interacted with

                endTask = calculateEnergy(player);    //calculating the players energy levels

            }else{
                printf("You need to get that energy up if you want to keep going!\n");
            }
            break; //exiting the for loop as there is no need to keep searching for a match if an ore has been found
        }

    }
    if (mineable == 0){ //having a true / false, allows me to keep the condition outside the for loop
        printf("Nothing here but some stones!\n");
        printf("You drop them because rocks are cooler\n");
    }
    return endTask; //returning the result of end task to kill the loop in movePlayer
}

int calculateEnergy(playerInfo* player){    //recalculating the players energy levels
    int endTask = 0;
    player->energy -=10;    //reducing the players energy as they mine
    printf("Energy Left: %d\n", player->energy);    //informing them of their energy levels decline
    sleep(2);

    if(player->energy <= 0){    //the player has runout of energy

        endTask = endGame(player);  //perform the end credits and end the game

    }else{

    }
    return endTask; //returning the result of end task to kill the loop in movePlayer
}

int endGame(playerInfo* player){    //when the player has died, end the game
    int endTask = 1;
    printf("You collapse to the ground, staring at the dimly lit cave ceiling....\n");
    sleep(3);
    printf("Is this the price I paid for not eating my vegetables...\n");
    sleep(3);
    printf("Goodbye cruel world...\n\n\n\n");
    sleep(3);
    printf("\n* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * GAME OVER * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    writeToleaderBoard(player); //update last game info
    readToleaderBoard();    //read out the players score for this game
    return endTask; //returns an indicator that the game has ended
}

int winGame(playerInfo* player){    //if player wins, end game
    printf("Wait!....\n");
    sleep(2);
    printf("Thi- this- THIS CANT BE....\n");
    sleep(3);
    printf("YOUVE DONE IT!.... \n");
    sleep(2);
    printf("I CANT BELIEVE SOMEONE HAS ACTUALLY MADE IT OUT OF THE MINE!....\n");
    sleep(4);
    printf("GO! GO NOW! BE FREE! HERE IS YOUR TICKET!\n");
    sleep(3);
    printf("(Elevator surface ticked acquired)");
    sleep(4);
    printf("Well... It was a please doing business with ya...\n");
    sleep(4);
    printf("Farewell...\n\n\n");
    sleep(3);

    printf("\n* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * YOU * WIN * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");

    writeToleaderBoard(player); //save game data to previous game result
    readToleaderBoard();//read the games score

    exit(0);    //terminates the script
}

int writeToleaderBoard(playerInfo* player){ //writing the players score to a text file

    char playername[50];
    printf("Please enter your name");
    scanf(" %s", playername);

    FILE * leaderboard; //pointer to a file
    leaderboard = fopen("leaderboard.txt", "w+");   //opening leaderboard.txt in readable and writable mode

    fprintf(leaderboard, "\n%s %s      %s %2f\n", "PlayerName:",playername,"Score:",player->coins); //printing in the players score and name

    fclose(leaderboard);    //closing the file


    return 0;
}

int readToleaderBoard(){    //reading the previous games score
    printf("****************PREVIOUS GAME SCORE***************");
    int display;
    FILE * leaderboard; //pointer to a file
    leaderboard = fopen("leaderboard.txt","r"); //opening leaderboard txt in readable mode

    while(1){
        display = fgetc(leaderboard);   //locating the char position in the file
        if( feof(leaderboard)){ //determining if it has reached the end of the string
            break;
        }
        printf("%c", display);  //printing out each char at a time
    }
    fclose(leaderboard);    //closing the file
    printf("\n");
    return 0;
}

int pickUp(playerInfo * player,item* item, ores* Ores, Bag* bag,int amount,int itemAmount){ //picking up items or ores
    int valid = 0; //to check if the player is trying to collect a pickupable item

    for (int i = 0; i < amount; ++i) {

        if(player->location.y == Ores[i].location.y && player->location.x == Ores[i].location.x) { //if current cell in array = ores coords
            sleep(1);
            if(Ores[i].typeOfOre.mapIcon == '!'){   // checking to make sure the ore has been mined
                if(Ores[i].typeOfOre.weight + bag->currentWeight <= bag->maxWeight){ //if there is enough room to pick up the ore
                    printf("You have got: %s\n",Ores[i].typeOfOre.name);    //displaying the ore the user has found
                    addToBag(bag, Ores,i, item, 'o');
                    Ores[i].location.y = -1 ;Ores[i].location.x = -1; //once it has been picked up, removing it from the map
                    valid = 1;
                }else{
                    printf("You need to drop some stuff if you want to pick that up!\n"); //if there is not enough room for the new ore
                    valid = 1;
                }
            }else{
                valid = 1;
                printf("Errr... maybe try mining it or something?\n"); //if the ore has not been mined
            }
        }
    }
    for (int i = 0; i < itemAmount; ++i) {

        if(player->location.y == item[i].location.y && player->location.x == item[i].location.x) { //if current cell in array = items coords
            sleep(1);
            if(item[i].typeOfItem.weight + bag->currentWeight <= bag->maxWeight){ //if there is enough room to pick up the item
                printf("You have got: %s\n",item[i].typeOfItem.name);    //displaying the item the user has found
                addToBag(bag, Ores,i,item, 'i');
                item[i].location.y = -1 ;item[i].location.x = -1; //once it has been picked up, removing it from the map
                valid = 1;
            }else{
                printf("You have found %s\n",item[i].typeOfItem.name);
                printf("You need to drop some stuff if you want to pick that up!\n"); //if there is not enough room for the new item
                valid = 1;
            }
        }
    }

    if(player->location.y == 0 && player->location.x == 0 ){    //if the player is at the shop
        valid = 1;  //its a valid time to press e, so dont error message
        theShop(bag,player);    //open shop
    }


    if(valid == 0){ //if player presses e at an invalid cell
        printf("You can only pick up items indicated as '!'\n");
    }

    return 0;
}

int addToBag(Bag * playerBag, ores* Ores,int i , item* items, char itemType){  //used to add picked up items to bag
    static int itemArrayPos = 0;    //holds the local value of itemArrayPos eternally during the run time of the script.

    char emptyName[50] = "Empty";
    int wasEmpty;

    if (itemArrayPos <= 20){ // if backpack has not reached the max amount of carriable items

        switch(itemType){
            case 'o':

                wasEmpty =0;
                for (int j = 0; j < itemArrayPos; ++j) {    //sifting through all the items in the backpack

                    int isEmpty = strcmp(playerBag->items[j].typeOfItem.name, emptyName);   //comparing to see if the cell is empty (been used up / sold)

                    if(isEmpty == 0){   //if it has been emptied
                        playerBag->items[j].typeOfItem = Ores[i].typeOfOre; //set ore to fill current item slot
                        playerBag->currentWeight = playerBag->currentWeight + playerBag->items[j].typeOfItem.weight; //update the current weight of the backpack
                        printf("Current weight : %d\n", playerBag->currentWeight);    //output the current weight to user, warning them of it growing
                        wasEmpty =1;
                        itemArrayPos -=1; //preventing the index from increasing
                        break;  //break out of for loop
                    }else{
                        //skipping to next in line
                    }
                }

                if(wasEmpty == 0){  //new cell (no data currently inside)

                    playerBag->items[itemArrayPos].typeOfItem = Ores[i].typeOfOre; //set ore to current item slot
                    playerBag->currentWeight = playerBag->currentWeight + playerBag->items[itemArrayPos].typeOfItem.weight; //update the current weight of the backpack

                    printf("Current weight : %d\n", playerBag->currentWeight);    //output the current weight to user, warning them of it growing
                }

                break;



            case 'i':
                wasEmpty =0;

                for (int j = 0; j < itemArrayPos; ++j) {    //sifting through all the items in the backpack

                    int isEmpty = strcmp(playerBag->items[j].typeOfItem.name, emptyName);   //comparing to see if the cell is empty (been used up / sold)

                    if(isEmpty == 0){
                        if(i>1){    //if player has bought it from the shop, it cant be in a struct array... so to seperate it...
                            playerBag->items[j].typeOfItem = items[i].typeOfItem; //set item to current item slot
                        }else{
                            playerBag->items[j].typeOfItem = items->typeOfItem; //set item to current item slot
                        }

                        playerBag->currentWeight = playerBag->currentWeight + playerBag->items[j].typeOfItem.weight; //update the current weight of the backpack
                        printf("New weight : %d\n", playerBag->currentWeight);    //output the current weight to user, warning them of it growing
                        itemArrayPos -=1; //preventing the index from increasing
                        wasEmpty =1;
                        break;
                    }else{
                        //skipping to next in line
                    }
                }

                if(wasEmpty == 0){  //new cell (no data currently inside)
                    if(i>1){    //if player has bought it from the shop, it cant be in a struct array... so to separate it...
                        playerBag->items[itemArrayPos].typeOfItem = items[i].typeOfItem; //set item to current item slot
                    }else{
                        playerBag->items[itemArrayPos].typeOfItem = items->typeOfItem; //set item to current item slot
                    }

                    playerBag->currentWeight = playerBag->currentWeight + playerBag->items[itemArrayPos].typeOfItem.weight; //update the current weight of the backpack
                    printf("New weight : %d\n", playerBag->currentWeight);    //output the current weight to user, warning them of it growing
                }
                break;

            default:
                printf("Error: Invalid Item Type\n");
                break;
        }
    }

    itemArrayPos +=1;//update index
    return 0;
}

Bag setBag(){
    Bag playerBag;  //creating a new bag struct
    playerBag.level = 1;    //setting initial starting values
    playerBag.currentWeight = 0;
    playerBag.maxWeight = 100;
    return playerBag;   //return the bag back to main, allowing it to be used for the game
}

int upgradeBag(Bag* playerBag){ //upgrading the players bag, giving more maximum weight
    playerBag->level +=1;   //upgrading the level
    playerBag->maxWeight += 150;    //upgrading the max weight
    return 0;
}

int inventory(Bag * playerbag, playerInfo * player, char location){ //printing the players inventory
    printf("**************** INVENTORY ****************\n");
    int empty = 1;
    for (int i = 0; i < 20; ++i) {  //for each cell in the items struct array
        if(playerbag->items[i].typeOfItem.mapIcon== '!' ){    //if the cell contains an item
            //print data on the item
            printf("********** SLOT %d **********\n",i);
            printf("Name: %s\n", playerbag->items[i].typeOfItem.name);
            printf("Type: %s\n", playerbag->items[i].typeOfItem.type);
            printf("Rarity: %s\n", playerbag->items[i].typeOfItem.rarity);
            printf("Value: %.2f\n", playerbag->items[i].typeOfItem.value);
            printf("Weight: %d\n", playerbag->items[i].typeOfItem.weight);
            empty = 0;

        }else{
            //if the next cell also does not contain anything

            if(i==0){   //if theres nothing in the bag
                printf("Theres nothing to show you yet!\n");
                empty =1;
            }



        }
    }
    if (empty == 0 && location == 'm'){ //if the player is accessing the inventory from the map, not the shop
        inventoryOptions(playerbag,player); //give them the option to perform actions
    }
    return 0;
}

int inventoryOptions(Bag * playerbag, playerInfo * player){ //if the player wants to consume an item or exit the inventory
    char input;
    int itemNumber;

    printf("\nPlease enter the slot number you would like to access\nFollowed by the action you would like to take\n"); //instructions for the user
    printf("[C] Consume [X] Exit\n");   //options for inputs
    scanf("%d %c",&itemNumber, &input); //saving the desired action for the desired slot
    input = toupper(input); //converting to upper case to prevent map interference

    switch(input){
        case 'C':   //consuming an item to replenish energy

            if(playerbag->items[itemNumber].typeOfItem.nutritionalValue > 0){   //if the item is edible
                if(player->maxenergy < player->energy + playerbag->items[itemNumber].typeOfItem.nutritionalValue){  //if adding the energy will exceed the max amount of energy
                    player->energy = player->maxenergy;

                }else{
                    player->energy += playerbag->items[itemNumber].typeOfItem.nutritionalValue; //otherwise just add the energy
                }
                printf("Your Energy: %d\n",player->energy); //output the new energy to the player
                removeItem(&playerbag->items[itemNumber], playerbag);   //remove the item from the inventory
            }else{
                printf("You cant eat that!!!!!\n");
                sleep(2);
            }
            break;
        case 'X':
            printf("Exiting Inventory\n");
            sleep(1);
            break;
    }

    return 0;
}

int generateMoleHill(int amountMoleHills, moleHills* moleHill){ //generating mole hill coords for the map
    //generating data on the moleHills
    int randx ,randy;


    srand(time(NULL));//seeding random number generator

    for (int i = 0; i < amountMoleHills; ++i) { // sifting through each hill

        randx = (rand() %(24-1+1))+1;//generating random coord for  x axis
        randy = (rand() %(12-1+1))+1;//generating random coord for  y axis

        moleHill[i].location.x = randx;//setting it to current  struct
        moleHill[i].location.y = randy;//setting it to current  struct
        moleHill[i].mapIcon = '^';  //setting map icon to a "hill"

        //coordinate matching
        int clash = 0; // paramter to break / continue to while loop

        for (int j = 0; j < i; ++j) {  //sifting through the struct array to see if any molehills have the same coords

            clash = 0; //entering the while loop

            while(clash < 1){ //used for infinitely checking the coordinates for matches, until coords are unique

                if(randx == moleHill[j].location.x && randy == moleHill[j].location.y){ // if their coords match
                    //debugging output to see where clashes are and if values change
                    //printf("CLASH! MoleHill[%d] X: %d, Y: %d with MoleHill[%d] X: %d, Y: %d\n",i,moleHill[i].location.x, moleHill[i].location.y,j,moleHill[j].location.x, moleHill[j].location.y);

                    randx = (rand() %(24-1+1))+1;//generating random coord for  x axis
                    randy = (rand() %(12-1+1))+1;//generating random coord for  y axis
                    moleHill[i].location.x = randx;//setting it to current  struct
                    moleHill[i].location.y = randy;//setting it to current  struct

                }
                else{
                    clash = 1; // exit while loop

                }
            }
        }
    }

    //debugging, making sure all hills are unique
    //for (int i = 0; i < amountMoleHills; ++i) {
    //printf("MoleHill[%d] X: %d, Y: %d\n",i,moleHill[i].location.x, moleHill[i].location.y);
    //}
    return 0;
}

int generateOres(int amount, ores *Ores){   //generating data for each ore in the struct array
    //generating data on the ores
    int randx ,randy,typeNumber;


    srand(time(NULL));//seeding random number generator

    for (int i = 0; i < amount; ++i) { // sifting through each ore

        randx = (rand() %(24-1+1))+1;//generating random coord for ore x axis
        randy = (rand() %(12-1+1))+1;//generating random coord for ore y axis

        Ores[i].location.x = randx;//setting it to current ores struct
        Ores[i].location.y = randy;//setting it to current ores struct

        //generating type of ore
        typeNumber = (rand() %(1000-1+1))+1; //random number 1-100 representing a %
        oreTypeGenerator(typeNumber,&Ores[i]);

        //coordinate matching
        int clash = 0; // paramter to break / continue to while loop

        for (int j = 0; j < i; ++j) {  //sifting through the Ores struct array to see if any ores have the same coords

            clash = 0; //entering the while loop

            while(clash < 1){ //used for infinitely checking the coordinates for matches, until coords are unique

                if(randx == Ores[j].location.x && randy == Ores[j].location.y){ // if their coords match
                    //debugging output to see where clashes are and if values change
                    //printf("CLASH! Ore[%d] X: %d, Y: %d with Ore[%d] X: %d, Y: %d\n",i,Ores[i].location.x, Ores[i].location.y,j,Ores[j].location.x, Ores[j].location.y);

                    randx = (rand() %(24-1+1))+1;//generating random coord for ore x axis
                    randy = (rand() %(12-1+1))+1;//generating random coord for ore y axis
                    Ores[i].location.x = randx;//setting it to current ores struct
                    Ores[i].location.y = randy;//setting it to current ores struct

                }
                else{
                    clash = 1; // exit while loop

                }
            }
        }
    }

    //debugging, making sure all ores are unique
    //for (int i = 0; i < amount; ++i) {
    //   printf("Ore[%d] X: %d, Y: %d\n",i,Ores[i].location.x, Ores[i].location.y);
    //}

    return 0;
}

int generateItem(int amount,int amountOres, item *items, ores * Ores){  //generating data on each item in the item struct array

    //generating data on the items
    int randx ,randy,typeNumber;
    srand(time(NULL));//seeding random number generator

    for (int i = 0; i < amount; ++i) { // sifting through each item

        randx = (rand() %(24-1+1))+1;//generating random coord for  x axis
        randy = (rand() %(12-1+1))+1;//generating random coord for  y axis

        items[i].location.x = randx;//setting it to current item struct
        items[i].location.y = randy;//setting it to current item struct

        //generating type of ore
        typeNumber = (rand() %(1000-1+1))+1; //random number 1-100 representing a %
        itemTypeGenerator(typeNumber,&items[i]);

        //coordinate matching
        int clash = 0; // paramter to break / continue to while loop

        for (int j = 0; j < i; ++j) {  //sifting through the items struct array to see if any items have the same coords

            clash = 0; //entering the while loop

            while(clash < 1){ //used for infinitely checking the coordinates for matches, until coords are unique

                if(randx == items[j].location.x && randy == items[j].location.y){ // if their coords match
                    //debugging output to see where clashes are and if values change
                    // printf("CLASH! Item[%d] X: %d, Y: %d with item[%d] X: %d, Y: %d\n",j,items[j].location.x, items[j].location.y,i,items[i].location.x, items[i].location.y);

                    randx = (rand() %(24-1+1))+1;//generating random coord for  x axis
                    randy = (rand() %(12-1+1))+1;//generating random coord for  y axis

                    items[i].location.x = randx;//setting it to current item struct
                    items[i].location.y = randy;//setting it to current item struct
                    j=0;    //resets the for loop
                }
                else{
                    clash = 1; // exit while loop
                }
            }
        }
    }

    //checking the ores and items locations dont match
    int clash = 0; // paramter to break / continue to while loop
    for (int j = 0; j < amount; ++j) {
        for (int i = 0; i < amountOres; ++i) {
            clash =0;
            while(clash < 1) { //used for infinitely checking the coordinates for matches, until coords are unique
                if (Ores[i].location.x == items[j].location.x && Ores[i].location.y == items[j].location.y) { // if their coords match debugging output to see where clashes are and if values change

                    //printf("CLASH! Item[%d] X: %d, Y: %d with Ore[%d] X: %d, Y: %d\n", j, items[j].location.x,items[j].location.y, i, Ores[i].location.x, Ores[i].location.y);

                    randx = (rand() %(24-1+1))+1;//generating random coord for  x axis
                    randy = (rand() %(12-1+1))+1;//generating random coord for  y axis

                    items[j].location.x = randx;//setting it to current item struct
                    items[j].location.y = randy;//setting it to current item
                    i = 0;  //resets the for loop

                }else{
                    clash = 1;
                }
            }
        }
    }

    //debugging, making sure all ores are unique
    //for (int i = 0; i < amount; ++i) {
    //    printf("Item[%d] X: %d, Y: %d\n",i,items[i].location.x, items[i].location.y);
    //}

    return 0;
}

int oreTypeGenerator(int typeNumber , ores* Ores){  //used to generate the type of ore found, collecting data on rarity, name, value, ect
    itemData GodOre ={"GodOre", 10000,"yippee",500, '?', "Ore"};
    itemData Spectrinite = {"Spectrinite", 550, "Mighty", 240, '?',"Ore"};
    itemData Loridium = {"Loridium",150,"Kinda rare?",175, '?',"Ore"};
    itemData Cominium ={"Cominium",25,"In the name",50, '?',"Ore"};
    itemData Bruhdine = {"Bruhdine",5, "Sick of it", 20, '?',"Ore"};
    itemData Rock ={"A rock! :)",1, "rock.",10, '?',"Ore"};


    if(typeNumber == 1){    //the rarest type of ore GodOre 0.1% chance
        Ores->typeOfOre= GodOre;
    }
    else if(typeNumber%20 == 0){    //the second-rarest type of ore Spectrinite
        Ores->typeOfOre= Spectrinite;

    }else if(typeNumber%10 == 0){    //the third-rarest type of ore Loridium
        Ores->typeOfOre= Loridium;

    }else if (typeNumber %5 == 0){
        Ores->typeOfOre= Bruhdine;  // the second most common ore Bruhdine
    }
    else if(typeNumber%3 == 0){    // the most common type of Cominium
        Ores->typeOfOre= Cominium;
    }else{
        Ores->typeOfOre= Rock;
    }
    return 0;
}

int itemTypeGenerator(int typeNumber,  item* items){    //generating data on the items
    itemData largeCoins ={"Spoils of War", 1000,"yippee",33, '!', "Item",0};
    itemData mediumCoins = {"A Decent Bag of Coins",300,"Wow!",5, '!',"Item",0};
    itemData largeRations = {"A breakfast bar", 50, "Mighty", 5, '!',"Item",50};
    itemData water ={"A flask of water",2,"prevents headaches",4, '!',"Item",40};
    itemData rations = {"A small bag of Rations",6, "mhm mhm mhmmmm", 5, '!',"Item",30};
    itemData smallCoins ={"A Small Bag of Coins",30, "Lucky me",1, '!',"Item",0};


    if(typeNumber == 1){    //the rarest item 0.1% chance
        items->typeOfItem = largeCoins;
    }
    else if(typeNumber%20 == 0){    //the second-rarest item
        items->typeOfItem = mediumCoins;

    }else if(typeNumber%10 == 0){    //the third-rarest item
        items->typeOfItem = largeRations;

    }else if (typeNumber %5 == 0){
        items->typeOfItem = water;// the second most common item
    }
    else if(typeNumber%3 == 0){    // the most common item
        items->typeOfItem = rations;
    }else{
        items->typeOfItem = smallCoins;
    }

    return 0;
}

int generateMap( int amount,int amountItem,int amountMoleHill,playerInfo* player, ores *Ores, item* items, moleHills * moleHill){   //printing out the map

    //generating the map
    char map[12][24];

    for (int i = 0; i < 12; ++i) {  //Y of matrix
        for (int j = 0; j < 24; ++j) {  //X of matrix


            if(i == player->location.y && j == player->location.x){   //if current coord equals player coord
                map[player->location.y][player->location.x] = '8';    //current coord = '8' to represent player on the screen
            }else{
                map[i][j] ='_'; //'_' to represent empty coords on the grid

                for (int k = 0; k < amountItem; ++k) {  //running through all the items
                    if(i == items[k].location.y && j == items[k].location.x){ //if current cell in array = items coords
                        map[items[k].location.y][items[k].location.x] = items[k].typeOfItem.mapIcon;  //current cell = icon of the items

                    }
                }
                for (int k = 0; k < amount; ++k) {  //running through all the ores
                    if(i == Ores[k].location.y && j == Ores[k].location.x){ //if current cell in array = ores coords
                        map[Ores[k].location.y][Ores[k].location.x] = Ores[k].typeOfOre.mapIcon;  //current cell = icon of the ore

                    }
                }
                for (int k = 0; k < amountMoleHill; ++k) {  //running through all the moleHills
                    if(i == moleHill[k].location.y && j == moleHill[k].location.x){ //if current cell in array = molehill coords
                        map[moleHill[k].location.y][moleHill[k].location.x] = moleHill[k].mapIcon;  //current cell = icon of the molehill

                    }
                }

                if(i ==0 && j==0){  //setting the shops coords
                    map[i][j] = 'S';    //shops mapicon
                }
            }
            printf("%c ",map[i][j]);    //print the grid

        }
        printf("\n"); //formatting the grid
    }

    return 0;
}

