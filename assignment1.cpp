/*********************************************************************
** Program Filename:assignment1.cpp
** Author: Hayden Henderson
** Date: 10/9/22
** Description: This program is designed to simulate a game of bowling. The program correctly calculates every frame a a bowling match
** Input: The user input for the program would be the users name and if they would like to play again or not. Additionally, the user has to press enter when they want to roll the ball
** Output: The output of this program is each frame of the game. The program will show what the user rolled and the impact that roll had on there score. Additionally, the program will
 output the type of roll the user rolled.
*********************************************************************/


#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;



string greetings(int frameNum);
int randomizeRoll1();
int randomizeRoll2(int roll1);
void outputCalc(int score[], int totalScore[], int outputTracker[], int index, int totalScoreIndex);
void playGame(int score[], int totalScore[], string name);
void frameTracker(int rollNum, int &frameNum);
void firstRoll(int &rollNum, int roll1, int frameNum, bool &extraRoll);
void secondRoll(int &rollNum, int roll2, int roll1, int frameNum, bool &extraRoll);
void pinsKnocked(int roll1, int roll2, int index, int rollNum, int score[]);
void totalScoreTracker(int score[], int totalScore[], int roll1, int roll2, int &totalScoreIndex, int rollNum, int &tempScore, int frameNum, int index, bool spare);
void fillArray(int score[], int totalScore);
void outPut(int score[], int totalScore[], string name, int index, int totalScoreIndex);
void calculationsOne(int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name);
void calculationsTwo(int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name);
void calculationsThree(int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name);
void leftSide(int score[], int i);
void rightSide(int score[], int i);
void trackerConditionOne(int score[], int totalScore[], int roll1, int roll2, int &totalScoreIndex, int rollNum, int &tempScore, int frameNum, int index, bool spare);
void trackerConditionTwo(int score[], int totalScore[], int roll1, int roll2, int &totalScoreIndex, int rollNum, int &tempScore, int frameNum, int index, bool spare);
void trackerConditionThree(int score[], int totalScore[], int roll1, int roll2, int &totalScoreIndex, int rollNum, int &tempScore, int frameNum, int index, bool spare);
void frameTenStrike(int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name);
void frameTenSpare(int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name);



/*********************************************************************
** Function: greeting function
** Description: this function is designed to greet the user and ask the for their name.
** Parameters: int frameNum
** Pre-Conditions: there are no pre conditions to this function
** Post-Conditions: there are no post conditions to this function
*********************************************************************/
string greetings(int frameNum) {
    bool goodName = false;
    string strName = "";
    cout << "Welcome the Bowling!" << endl;
    cout << "What is your name? ";
    while (goodName == false){
        cin >> strName;
        if (strName.size() <= 10){
            goodName = true;
        }
        else {
            cout << "Sorry please have name of 10 characters or less." << endl;
            cout << "Try again!";
        }
    }
    
    cout << "Hello " << strName << endl;
    
    return strName;
}


/*********************************************************************
** Function: playGame function
** Description: This is the central function that directs the program to make sure the game runs. This program calls a lot of functions to keep things organized
** Parameters: int score[], int totalScore [], string name
** Pre-Conditions: there are no pre conditions to this function
** Post-Conditions: the post conditions to this function are that frameNum has to reach 11
*********************************************************************/
void playGame(int score[], int totalScore [], string name) {
    int randomPin;
    int roll1, roll2;
    int rollNum;
    int index = 0;
    int totalScoreIndex = 0;
    int frameNum = 1;
    int tempScore = 0;
    bool extraRoll = false;
    bool spare = false;
    
    while (frameNum < 11){
        for (rollNum = 0; rollNum < 2; rollNum++) {
            if (rollNum == 0) {
                calculationsOne(randomPin, roll1, roll2, rollNum, index, totalScoreIndex, frameNum, tempScore, score, totalScore, extraRoll, spare, name);
            }
            if (rollNum == 1) {
                calculationsTwo(randomPin, roll1, roll2, rollNum, index, totalScoreIndex, frameNum, tempScore, score, totalScore, extraRoll, spare, name);
            }
            if (extraRoll == true) {
                calculationsThree(randomPin, roll1, roll2, rollNum, index, totalScoreIndex, frameNum, tempScore, score, totalScore, extraRoll, spare, name);
            }
        }
    }
}
/*********************************************************************
** Function: calculationsOne
** Description: this function is used to calculate the first roll of a frame. This function calls all the necessary functions that aid that goal
** Parameters: int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name){
 frameTracker(rollNum, frameNum
** Pre-Conditions: the conditions before entering this function are that rollNum has to be equal to zero
** Post-Conditions: the conditions to exit the funciton are that the output must done and rollNum has to increase
*********************************************************************/
void calculationsOne(int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name){
    frameTracker(rollNum, frameNum);
    roll1 = randomizeRoll1();
    firstRoll(rollNum, roll1, frameNum, extraRoll);
    pinsKnocked(roll1, roll2, index, rollNum, score);
    totalScoreTracker(score, totalScore, roll1, roll2, totalScoreIndex, rollNum, tempScore, frameNum, index, spare);
    outPut(score, totalScore, name, index, totalScoreIndex);
    if (roll1 == 10){
        index = index + 2;
    }
    else {
        index ++;
    }

}
/*********************************************************************
 ** Function: calculationsTwo
 ** Description: this function is used to calculate the second roll of a frame. This function calls all the necessary functions that aid that goal
 ** Parameters: int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name){
  frameTracker(rollNum, frameNum
 ** Pre-Conditions: the conditions before entering this function are that rollNum has to be equal to 1
 ** Post-Conditions: the conditions to exit the funciton are that the output must done and rollNum has to change
*********************************************************************/
void calculationsTwo(int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name){
    frameTracker(rollNum, frameNum);
    roll2 = randomizeRoll2(roll1);
    secondRoll(rollNum, roll2, roll1, frameNum, extraRoll);
    pinsKnocked(roll1, roll2, index, rollNum, score);
    totalScoreTracker(score, totalScore, roll1, roll2, totalScoreIndex, rollNum, tempScore, frameNum, index, spare);
    outPut(score, totalScore, name, index, totalScoreIndex);
    index ++;
}
/*********************************************************************
 ** Function: calculationsThree
 ** Description: this function is used to calculate the final frame of the game. This function calls all the necessary functions that aid that goal
 ** Parameters: int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name
 ** Pre-Conditions: the conditions before entering this function are that there was a spare or a strike on the 10 frame
 ** Post-Conditions: the conditions to exit the funciton are that the output must done and rollNum has to increase
*********************************************************************/
void calculationsThree(int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name){
    rollNum = 0;
    if (roll1 == 10){ // strike
        frameTenStrike(randomPin, roll1, roll2, rollNum, index, totalScoreIndex, frameNum, tempScore, score, totalScore, extraRoll, spare, name);
    }
    else { // spare
        frameTenSpare(randomPin, roll1, roll2, rollNum, index, totalScoreIndex, frameNum, tempScore, score, totalScore, extraRoll, spare, name);
    }
    rollNum = 2;
    
}
/*********************************************************************
** Function: frame ten strike
** Description: this function is used to calculate what would happen if there was a strike on frame 10. More specifically it is used to calculate the extra rolls that come with that
** Parameters:int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name
** Pre-Conditions: the pre conditions to this function are that the program has to roll a strike on the tenth fram
** Post-Conditions: the post conditions to this program are the arrays have to be full outputed
*********************************************************************/
void frameTenStrike(int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name){
    for (int i = 0; i < 2; i++){
        frameNum ++;
        frameTracker(rollNum, frameNum);
        roll1 = randomizeRoll1();
        firstRoll(rollNum, roll1, frameNum, extraRoll);
        pinsKnocked(roll1, roll2, index, rollNum, score);
        totalScoreTracker(score, totalScore, roll1, roll2, totalScoreIndex, rollNum, tempScore, frameNum, index, spare);
        outPut(score, totalScore, name, index, totalScoreIndex);
        if (roll1 == 10){
            index = index + 2;
        }
        else {
            index ++;
        }
        if (roll1 < 10 && rollNum != -2){
            rollNum = 1;
            frameNum ++;
            frameTracker(rollNum, frameNum);
            roll2 = randomizeRoll2(roll1);
            secondRoll(rollNum, roll2, roll1, frameNum, extraRoll);
            pinsKnocked(roll1, roll2, index, rollNum, score);
            totalScoreTracker(score, totalScore, roll1, roll2, totalScoreIndex, rollNum, tempScore, frameNum, index, spare);
            outPut(score, totalScore, name, index, totalScoreIndex);
            i++;
        }
    }
}
/*********************************************************************
 ** Function: frame ten spare
 ** Description: this function is used to calculate what would happen if there was a spare on frame 10. More specifically it is used to calculate the extra rolls that come with that
 ** Parameters:int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name
 ** Pre-Conditions: the pre conditions to this function are that the program has to roll a spare on the tenth fram
 ** Post-Conditions: the post conditions to this program are the arrays have to be full outputed
*********************************************************************/
void frameTenSpare(int &randomPin, int &roll1, int &roll2, int &rollNum, int &index, int &totalScoreIndex, int &frameNum, int &tempScore, int score[], int totalScore [], bool &extraRoll, bool spare, string name){
    spare = true;
    frameNum ++;
    frameTracker(rollNum, frameNum);
    roll1 = randomizeRoll1();
    firstRoll(rollNum, roll1, frameNum, extraRoll);
    pinsKnocked(roll1, roll2, index, rollNum, score);
    totalScoreTracker(score, totalScore, roll1, roll2, totalScoreIndex, rollNum, tempScore, frameNum, index, spare);
    outPut(score, totalScore, name, index, totalScoreIndex);
}


/*********************************************************************
** Function: firstroll
** Description: this function outputs what type of roll the user had
** Parameters: int &rollNum, int roll1, int frameNum, bool &extraRoll
** Pre-Conditions: rollnum has to be equal to 0
** Post-Conditions: there are no post conditions
*********************************************************************/
void firstRoll(int &rollNum, int roll1, int frameNum, bool &extraRoll) {
    if (roll1 == 0) {
        cout << "Awe, you got a gutter ball, 0 pins!" << endl << endl;
    }
    else if (roll1 < 10) {
        if (roll1 == 1) {
            cout << "You knocked down " << roll1 << " pin!" << endl << endl;
        }
        else {
            cout << "You knocked down " << roll1 << " pins!" << endl << endl;
        }
    }
    else {
        cout << "You got a STRIKE! 10 pins" << endl << endl;
        if (frameNum == 11){
            extraRoll = true;
        }
        rollNum = -2;
    }
}


/*********************************************************************
 ** Function: secondroll
 ** Description: this function outputs what type of roll the user had on their second roll
 ** Parameters:int &rollNum, int roll2, int roll1, int frameNum, bool &extraRoll
 ** Pre-Conditions: rollnum has to be equal to 1
 ** Post-Conditions: there are no post conditions
*********************************************************************/
void secondRoll(int &rollNum, int roll2, int roll1, int frameNum, bool &extraRoll) {
    if (roll2 == 0) {
        cout << "Awe, you got a gutter ball, 0 pins!" << endl << endl;
    }
    else if (roll2 + roll1 != 10) {
        if (roll2 == 1) {
            cout << "You knocked down " << roll2 << " pin!" << endl << endl;
        }
        else {
            cout << "You knocked down " << roll2 << " pins!" << endl << endl;
        }
    }
    else {
        cout << "You got a spare! " << roll2 << " pins!" << endl << endl;
        if (frameNum == 11){
            extraRoll = true;
        }
    }
}


/*********************************************************************
** Function:randomize roll1
** Description: this funciton randomizes roll1
** Parameters:
** Pre-Conditions: rollnum has to be equal to 0
** Post-Conditions: there are no post conditions
*********************************************************************/
int randomizeRoll1() {
    int randomPin = rand() % 11;

    return randomPin;
}

/*********************************************************************
 ** Function:randomize roll2
 ** Description: this funciton randomizes roll1
 ** Parameters:
 ** Pre-Conditions: rollnum has to be equal to 1
 ** Post-Conditions: there are no post conditions
*********************************************************************/
int randomizeRoll2(int roll1) {
    int randomPin = rand() % (11 - roll1);
    return randomPin;
}

/*********************************************************************
** Function: frametracker
** Description: this funciton tracks what frame the user is on
** Parameters:int rollNum, int &frameNum
** Pre-Conditions: this fucntion is used on every roll so the only condition is that the user is playing
** Post-Conditions: this funciton needs to increase framenum
*********************************************************************/
void frameTracker(int rollNum, int &frameNum) {
    string temp = "";
    if ((rollNum == 0) && (frameNum < 11)) {
        cout << endl << endl << endl;
        cout << "Frame " << frameNum << " ... " << endl;
        cout << "Press enter to roll!";
        getline(cin, temp);
        frameNum++;
    }
    else if (rollNum == 1 || frameNum >= 11) {
        cout << "Press enter to roll!";
        getline(cin, temp);
    }
}


/*********************************************************************
** Function: pins Knocked
** Description: this function assigns the number of pins knocked to an array
** Parameters:int roll1, int roll2, int index, int rollNum, int score[]
** Pre-Conditions: roll1 has to be randomized
** Post-Conditions: index has to increase
*********************************************************************/
void pinsKnocked(int roll1, int roll2, int index, int rollNum, int score[]) {
    if (rollNum == 0 || rollNum == -2){
        score[index] = roll1;
        if (score[index - 1] == 10){
            index ++;
        }
    }
    else if (rollNum == 1){
        score[index] = roll2;
    }
}

/*********************************************************************
** Function: output
** Description: this funciton outputs all the information that the program calculates in a neat and understandable fashion
** Parameters:int score[], int totalScore[], string name, int index, int totalScoreIndex
** Pre-Conditions: there are no pre conditions to this funciton
** Post-Conditions: there are no post conditions
*********************************************************************/
void outPut(int score[], int totalScore[], string name, int index, int totalScoreIndex){
    int i = 0;
    int outputTracker [11];
    
    cout << "Name      |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |      10       |  Total" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(10) <<  name <<  "|";

    for (i = 0; i <= 22; i++){ // rolls
        if ((i + 1) % 2 != 0){
            leftSide(score, i);
        }
        else {
            rightSide(score, i);
        }
    }
    cout << "|";
    
    if (totalScore[totalScoreIndex] == 0){
        cout << totalScore[totalScoreIndex - 1];
    }
    else {
        cout << totalScore[totalScoreIndex];
    }
    cout << endl;
    cout << left << setw(10) << " ";
    outputCalc(score, totalScore, outputTracker, index, totalScoreIndex);
    
    cout << "          |";
    cout << endl << endl;
}

/*********************************************************************
** Function: output calc
** Description: this function assist with the output function by organizeds the score bar
** Parameters:int score[], int totalScore[], int outputTracker[], int index, int totalScoreIndex
 ** Pre-Conditions: there are no pre conditions to this function
 ** Post-Conditions: there are no post conditions
*********************************************************************/
void outputCalc(int score[], int totalScore[], int outputTracker[], int index, int totalScoreIndex){
    for (int c = 0; c < 10; c++){ // total
        if (totalScore[c] == 0){
            cout << "|     ";
        }
        else if (totalScore[c] < 10){
            cout << "|  " << totalScore[c] << "  ";
        }
        else if(totalScore[c] < 100){
            cout << "|  " << totalScore[c] << " ";
        }
        else{
            cout << "| " << totalScore[c] << " ";
        }
    }
}

// ------------------------------------------------------------- //
/*********************************************************************
** Function: left side
** Description: this function organizes the left side of the frame
** Parameters:int score[], int i
** Pre-Conditions: the index has to be at an odd value
** Post-Conditions: there are no post conditions
*********************************************************************/
void leftSide(int score[], int i){
    if (score[i] == -1){
        cout << "   ";
    }
    else {
        if (score[i] == 10){
            cout << " X ";
        }
        else if (score[i] == 0){
            cout << " - ";
        }
        else{
            cout << " " << score[i] << " ";
        }
    }
}
// ------------------------------------------------------------- //
/*********************************************************************
 ** Function: right side
 ** Description: this function organizes the right side of the frame
 ** Parameters:int score[], int i
 ** Pre-Conditions: the index has to be at an even value
 ** Post-Conditions: there are no post conditions
*********************************************************************/

void rightSide(int score[], int i){
    if (score[i] == -1){
        cout << "  |";
    }
    else{
        if (score[i] + score[i - 1] == 10){
            cout << "/ |";
        }
        else if (score[i] == 0){
            cout <<"- |";
        }
        else if (score[i] < 10){
            cout << score[i] << " |";
        }
    }
}

// ----------------- Total Score Function -------------------- //
/*********************************************************************
** Function: total score tracker
** Description:this funciton is the central hub for scoring the game
** Parameters:int score[], int totalScore[], int roll1, int roll2, int &totalScoreIndex, int rollNum, int &tempScore, int frameNum, int index, bool spare
** Pre-Conditions: each rolls has to be  randomized
** Post-Conditions: there are no post conditions
*********************************************************************/
void totalScoreTracker(int score[], int totalScore[], int roll1, int roll2, int &totalScoreIndex, int rollNum, int &tempScore, int frameNum, int index, bool spare) {
    trackerConditionOne(score, totalScore, roll1, roll2, totalScoreIndex, rollNum, tempScore, frameNum, index, spare);
    trackerConditionTwo(score, totalScore, roll1, roll2, totalScoreIndex, rollNum, tempScore, frameNum, index, spare);
    trackerConditionThree(score, totalScore, roll1, roll2, totalScoreIndex, rollNum, tempScore, frameNum, index, spare);

}
/*********************************************************************
 ** Function: tracker condition one
 ** Description: this function calculates the score of the roll based off conditions such as what roll it is previous rolls etc
 ** Parameters:int score[], int totalScore[], int roll1, int roll2, int &totalScoreIndex, int rollNum, int &tempScore, int frameNum, int index, bool spare
 ** Pre-Conditions:the pre conditions are that fucntiononly works if rullnum is 0 and framenum is at a certain point
 ** Post-Conditions: there are no post conditions to this function
*********************************************************************/
void trackerConditionOne(int score[], int totalScore[], int roll1, int roll2, int &totalScoreIndex, int rollNum, int &tempScore, int frameNum, int index, bool spare){
    // strike total is outputed after the next two ROLLS not frames
    // spare total is outputed on the next ROLL not frame
        if ((rollNum == 0 || rollNum == -2) && frameNum <= 11) {
            totalScore[totalScoreIndex] = totalScore[totalScoreIndex - 1] + roll1;
            if (score[index - 2] == 10){
                totalScore[totalScoreIndex - 1] = totalScore[totalScoreIndex - 1] + roll1;
                totalScore[totalScoreIndex] = totalScore[totalScoreIndex] + roll1;
            }
            if (score[index - 3] == 10 ){
                totalScore[totalScoreIndex - 2] = totalScore[totalScoreIndex - 2] + roll1;
                totalScore[totalScoreIndex] = totalScore[totalScoreIndex - 1] + roll1;
            }
            if (score[index - 4] == 10 && score[index - 1] == -1){
                totalScore[totalScoreIndex - 2] = totalScore[totalScoreIndex - 2] + roll1;
                totalScore[totalScoreIndex - 1] = totalScore[totalScoreIndex - 1] + roll1;
                totalScore[totalScoreIndex] = totalScore[totalScoreIndex] + roll1;
            }
            if (score[index - 1] + score[index - 2] == 10){
                totalScore[totalScoreIndex - 1] = totalScore[totalScoreIndex - 1] + roll1;
            }
        }
}
/*********************************************************************
 ** Function: tracker condition two
 ** Description: this function calculates the score of the roll based off conditions such as what roll it is previous rolls etc
 ** Parameters:int score[], int totalScore[], int roll1, int roll2, int &totalScoreIndex, int rollNum, int &tempScore, int frameNum, int index, bool spare
 ** Pre-Conditions:the pre conditions are that fucntiononly works if rullnum is 0  and framenum is at a certain point also spare has to be true
 ** Post-Conditions: there are no post conditions to this function
*********************************************************************/
void trackerConditionTwo(int score[], int totalScore[], int roll1, int roll2, int &totalScoreIndex, int rollNum, int &tempScore, int frameNum, int index, bool spare){
    if (frameNum >= 12 && rollNum != 1 && spare != true) {
        totalScore[totalScoreIndex] = totalScore[totalScoreIndex] + roll1;
        if (score[index - 4] == 10 && frameNum == 12){
            totalScore[totalScoreIndex - 1] = totalScore[totalScoreIndex - 1] + roll1;
            totalScore[totalScoreIndex] = totalScore[totalScoreIndex] + roll1;
        }
        if (score[index - 1] + score[index - 2] == 10){
            totalScore[totalScoreIndex] = totalScore[totalScoreIndex - 1] + roll1;
        }
    }
    if (spare == true){
        totalScore[totalScoreIndex] = totalScore[totalScoreIndex] + roll1;
    }
    
    if (roll1 == 10 && frameNum < 12) {
        totalScore[totalScoreIndex] = totalScore[totalScoreIndex - 1] + roll1;
        if (frameNum < 11) {
            totalScoreIndex ++;
        }
    }
}
/*********************************************************************
** Function: tracker condition three
** Description: this function calculates the score of the roll based off conditions such as what roll it is previous rolls etc
** Parameters:int score[], int totalScore[], int roll1, int roll2, int &totalScoreIndex, int rollNum, int &tempScore, int frameNum, int index, bool spare
** Pre-Conditions:the pre conditions are that fucntiononly works if rullnum is 1 and framenum is at a certain point
** Post-Conditions: there are no post conditions to this function
*********************************************************************/
void trackerConditionThree(int score[], int totalScore[], int roll1, int roll2, int &totalScoreIndex, int rollNum, int &tempScore, int frameNum, int index, bool spare){
    if (rollNum == 1 && frameNum == 13){
        totalScore[totalScoreIndex] = totalScore[totalScoreIndex] + roll2;
    }
    else if (rollNum == 1){
        totalScore[totalScoreIndex] = totalScore[totalScoreIndex - 1] + roll2 + roll1;
        if (frameNum < 11){
            totalScoreIndex ++;
        }
        if (score[index - 3] == 10 && frameNum < 11){
            totalScore[totalScoreIndex - 2] = totalScore[totalScoreIndex - 2] + roll2;
            totalScore[totalScoreIndex - 1] = totalScore[totalScoreIndex - 1] + roll2;
        }
        if (score[index - 3] == 10 && frameNum == 11){
            totalScore[totalScoreIndex - 1] = totalScore[totalScoreIndex - 1] + roll2;
            totalScore[totalScoreIndex] = totalScore[totalScoreIndex] + roll2;
        }
    }
}



// ----------------- fill array Function -------------------- //
/*********************************************************************
** Function: fillArray function
** Description: this function fills arrays so they can be used effectively
** Parameters: int score[], int totalScore[]
** Pre-Conditions: there are no pre conditions to this function
** Post-Conditions: there are no post conditions to this function
*********************************************************************/
void fillArray(int score[], int totalScore[]){
    for (int i = 0; i <= 22; i++){
        score[i] = -1;
    }
    for (int c = 0; c < 11; c++){
        totalScore[c] = 0;
    }
    
}

// ------------------ Main Function ------------------- //
/*********************************************************************
** Function: Main function
** Description: This function starts the program off and ends it by asking if the user wants to play again
** Parameters:
** Pre-Conditions: there are no pre conditions to this function
** Post-Conditions: to exit this function the user must enter n to exit the program
*********************************************************************/
int main() {
    bool playAgain = true;
    char userChoice = ' ';
    
    srand(time(NULL));
    
    do{
        int randomPin;
        int frameNum = 1;
        int score [21];
        int totalScore [11];
        
        
        fillArray(score, totalScore);
        string name = greetings(frameNum);
        playGame(score, totalScore, name);
        
        cout << "Thank you for playing!" << endl;
        cout << "Would you like to play again {'y' for yes or 'n' for no}?:";
        cin >> userChoice;
        while (userChoice != 'y' && userChoice != 'n'){
            cout << "ERROR! please enter 'y' or 'n' if you want to play again!" << endl;
            cin >> userChoice;
        }
    }while (userChoice == 'y');

    return 0;
}
