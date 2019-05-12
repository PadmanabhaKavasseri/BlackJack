//*******************************************************************************
// * Twenty-One (Blackjack) PA
// * Name: Padmanabha Kavasseri
// ******************************************************************************/
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

//Global arrays to be used as tables
const char suit[4] = {'H','S','D','C'};
const char* type[13] =
        {"2","3","4","5","6","7",
         "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

//Shuffling the cards using the Fisher-Yates / Durstenfeld shuffle algorithm
void shuffle(int cards[]){
    //initializing the deck    
    for(int i =0; i<52; i++){
        cards[i]=i;
    }
    Fisher-Yates / Durstenfeld shuffle algorithm
    for(int i=51; i>0; i--) {
        int j = rand() % (i+1);
        int x = cards[i];
        cards[i] = cards[j];
        cards[j] = x;
    }
}


//Prints the card in a "pretty" format:   "type-suit" 
void printCard(int id)
{
    cout << type[id%13] << "-" << suit[id/13];
}

/*
 *  Returns the numeric value of the card.
 *  Should return 11 for an ACE or 1 depending on the sum of the score
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

//Prints out each hand in the card using printCard()
void printHand(int hand[9], int numCards)
{

    for (int i =0; i<numCards; i++){
        printCard(hand[i]);
        cout << " ";
    }
    cout << endl;

}

/*
 * Should return the total score of the provided hand.
 * ACES should be treated as 11s to make the highest possible hand
 * and only being reduced to 1s as needed to avoid busting.
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
    return score;
}

//the main program for Blackjack
int main(int argc, char* argv[])
{
    if(argc < 2){
        cout << "Error - Please provide the seed value." << endl;
        return 1;
    }
    int seed = atoi(argv[1]);
    srand(seed);

    int cards[52];
    int dhand[9];
    int phand[9];
        
    //variables required
    char response;
    char again;
    bool play = true;
    int pscore = 0;
    int dscore = 0;

    //while a game is being played    
    while (play == true) {
        int cardnumber=3;
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
