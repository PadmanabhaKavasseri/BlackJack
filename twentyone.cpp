//*******************************************************************************
// * CS 103 Twenty-One (Blackjack) PA
// * Name: Padmanabha Kavasseri
// * USC email: kavasser@usc.edu
// * Comments (you want us to know):
//*
//*
// ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;
int aceCount = 0;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] =
        {"2","3","4","5","6","7",
         "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
    for(int i =0; i<52; i++){
        cards[i]=i;
    }

    for(int i=51; i>0; i--) {
        int j = rand() % (i+1);
        int x = cards[i];
        cards[i] = cards[j];
        cards[j] = x;
    }
    //for(int i =0; i<52; i++){
    //    cout << cards[i] << " ";
    //}
    //cout << endl;
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
    cout << type[id%13] << "-" << suit[id/13];
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then.
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
    int num = id % 13;

    if (num <= 8){
        return num+2;
    }
    else if (num >8 && num<=11){
        num = 10;
        return num;
    }
    else {
        num = 11;
        aceCount++;
        return num;
    }
}
//reactnative
//no310withhalfond
/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.
 * Should use printCard() to print out each card.
 */
void printHand(int hand[9], int numCards)
{

    for (int i =0; i<numCards; i++){
        printCard(hand[i]);
        cout << " ";
    }
    cout << endl;

}

/**
 * Should return the total score of the provided hand.
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
    int score = 0;
    int ace_counter = 0;
    for (int i = 0; i < numCards; i++) {
        int cval = cardValue(hand[i]);
        if (cval == 11) {
            ace_counter++;
        }
        score += cval;

    }

    if((score>21) && (ace_counter != 0)){
        score -= 10;
        ace_counter--;
    }
    //cout << score << endl;
    return score;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
    //---------------------------------------
    // Do not change this code -- Begin
    //---------------------------------------
    if(argc < 2){
        cout << "Error - Please provide the seed value." << endl;
        return 1;
    }
    int seed = atoi(argv[1]);
    srand(seed);

    int cards[52];
    int dhand[9];
    int phand[9];
    //---------------------------------------
    // Do not change this code -- End
    //---------------------------------------

    /******** You complete ****************/
    //variables required
    char response;
    char again;
    bool play = true;
    int pscore = 0;
    int dscore = 0;

    //cout << cardValue(2) << " " << cardValue(6) << endl;
    while (play == true) {

        int cardnumber=3;// remember to reset after a game
        int phandcnt = 1;
        int dhandcnt = 1;
        bool win = false;
        bool pturn = true;
        bool pdone = false;
        bool ddone = false;

        //shuffle and dealing the cards
        shuffle(cards);
        phand[0] = cards[0];
        dhand[0] = cards[1];
        phand[1] = cards[2];
        dhand[1] = cards[3];

        //print the hand
        cout << "Dealer: ";
        cout << "? ";
        printCard(dhand[1]);
        cout << endl;
        cout << "Player: ";
        printHand(phand, 2);
        phandcnt++;
        dhandcnt++;
        cardnumber++;
        pscore = (getBestScore(phand, phandcnt));
        dscore = (getBestScore(dhand, dhandcnt));

        //player
        while (pturn == true)
        {
            if (pscore == 21) {
                pturn = false;
                pdone = true;
            }
            //cout << "1st while" << endl;
            while (pscore < 21)
            {
                //cout << "2st while" << endl;
                cout << "Type 'h' to hit and 's' to stay:" << endl;
                cin >> response;
                if ((response == 'h') || (response == 's')) {
                    if (response == 'h') {
                        phand[phandcnt++] = cards[cardnumber++];
                        cout << "Player: ";
                        printHand(phand, phandcnt);
                        pscore = (getBestScore(phand, phandcnt));
                        if (pscore == 21) {
                            pturn = false;
                            pdone = true;
                        }
                        if (pscore > 21){
                            pdone = true;
                            ddone = false;
                            pturn = false;
                        }
                    } else { //if resp = s;
                        pdone = true;
                        pturn = false;
                        break;
                    }
                }
            }
            if (pscore > 21) {
                ddone = true;
                pdone = true;
                pturn = false;
            }
        }
        //dealer
        while (ddone == false) {
            //cout << "bib" << endl;
            //dealer black jack automatically wins
            if (dscore == 21) {
                ddone = true;
                pdone = true;
            }
            // dealer cannot draw another card
            if ((dscore >= 17) && (dscore < 21)) {
                ddone = true;
                pturn = true;
            }
            //dealer needs to draw a card
            if (dscore < 17) {
                dhand[dhandcnt++] = cards[cardnumber++];
                dscore = (getBestScore(dhand, dhandcnt));
                if (dscore> 21) {
                    ddone = true;
                    pdone = true;
                }

            }
            if (dscore> 21) {
                ddone = true;
                pdone = true;
            }
            
        }
        //checks scores
        if ((ddone == true) && (pdone == true)){
            if (dscore == 21){
                printHand(dhand, dhandcnt);
                cout << "Lose " << pscore << " " << dscore << endl;
            }
            else if (dscore > 21){
                cout << "Dealer Busts" << endl;
                cout << "Win " << pscore << " " << dscore << endl;
            }
            else if (pscore == dscore) {
                cout << "Dealer: ";
                printHand(dhand, dhandcnt);
                cout << "Tie " << pscore << " " << dscore << endl;
            }
            else if (pscore > 21){
                cout << "Player Busts" << endl;
                cout << "Lose " << pscore << " " << dscore << endl;
            }
            else if ((pscore > dscore)){
                cout << "Dealer: ";
                printHand(dhand, dhandcnt);
                cout << "Win " << pscore << " " << dscore << endl;
            }
            else if (pscore < dscore){
                cout << "Dealer: ";
                printHand(dhand, dhandcnt);
                cout << "Lose " << pscore << " " << dscore << endl;
            }
        }



        //play again?
        cout << "Play again?  [y/n]" << endl;
        cin >> again;
        if ( again == 'y' || again == 'n'){
            if(again == 'n'){
                play = false;
            }
        }
    }

    return 0;
}