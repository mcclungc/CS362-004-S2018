/* -----------------------------------------------------------------------
* Connie McClung - Card Test 4
* cardtest4.c
*
* Tests basic operations of Great Hall card
* 1. Allows current player to draw 1 card
* 2. Increments game state variable numActions by 1
* 3. Current player's hand before playing additional actions should equal handCount +  1 - 1(for Great Hall move to played card pile)
* 4. Other players' hand count  should not change
* 5. Successful Great Hall cardEffect returns 0
*
* -----------------------------------------------------------------------
*/
/*
* Include the following lines in your makefile:
*
* cardtest4: cardtest4.c dominion.o rngs.o
*      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Great Hall"


//user defined assert function  so that fails will not abort program
char* myAssert(int testValue)
{
	if (testValue == 0)
	{
		char* msg = "TEST FAILED!\n";
		return msg;
	}
	else
	{
		char* msg = "Test passed!\n";
		return msg;
	}
}



int main() {


	int i, j;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayer = 4;
	int currentPlayer = 0;
	struct gameState G, testG;
	int k1[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	//int k2[10] = { minion, steward, tribute, ambassador, cutpurse, embargo
	//	, outpost, salvager, sea_hag, treasure_map };

	int addedActions;
	//int startHandCount;
	//int startActions;
	int addedCards;
	int discarded;
	int successReturn;
	int initialHand;

	//TEST 1
	//testing with game using k1 kingdom card set
	initializeGame(numPlayer, k1, seed, &testG);


	printf("----------------- TESTING: %s ----------------\n", TESTCARD);

	// TEST 1: Great Hall card called by first player in newly initialized game
	printf("\n---------------------------------------------------------------------\n");
	printf("TEST 1: Great Hall card called by first player in newly initialized game\n");
	printf("---------------------------------------------------------------------\n");

	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG stays unchanged

	printf("Starting hand count for first player = %d\n", G.handCount[currentPlayer]);
	printf("Starting number of actions for first player = %d\n", G.numActions);
	printf("Calling cardEffect for Great Hall to add 1 card, 1 action, discard Great Hall card...\n");
	int testReturn = cardEffect(great_hall, choice1, choice2, choice3, &G, handpos, &bonus);

	addedCards = 1;
	addedActions = 1;
	discarded = 1;
	successReturn = 0;

	printf("Hand count first player = %d, expected = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer] + addedCards - discarded);
	printf(myAssert(G.handCount[currentPlayer] == testG.handCount[currentPlayer] + addedCards - discarded));

	printf("Actions count (global for game state) = %d, expected = %d\n", G.numActions, testG.numActions + addedActions);
	printf(myAssert(G.numActions == testG.numActions + addedActions));

	printf("Return value for successful cardEffect for Great Hall = %d, expected = %d\n", testReturn, successReturn);
	printf(myAssert(testReturn == successReturn));

	for (i = currentPlayer + 1; i < numPlayer; i++)
	{
		printf("Hand count player %d  = %d, expected = %d\n", i + 1, G.handCount[i], testG.handCount[i]);
		printf(myAssert(G.handCount[i] == testG.handCount[i]));
	}
	printf("\n");


	//TEST 2
	//testing with game using k1 kingdom card set
	initializeGame(numPlayer, k1, seed, &testG);


	//printf("----------------- TESTING: %s ----------------\n", TESTCARD);

	// TEST 2: Great Hall card called by other players 
	printf("\n---------------------------------------------------------------------\n");
	printf("TEST 2: Testing Great Hall card effect works same for all players in game\n");
	printf("---------------------------------------------------------------------\n");

	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG stays unchanged

	for (i = 1; i < numPlayer; i++)
	{
		G.numActions = 1; //reset to correct number for start of hand
		G.whoseTurn = i;
		currentPlayer = G.whoseTurn;
		printf("Drawing initial hand for player %d...\n", currentPlayer + 1);
		for (j = 0;j < 5;j++)
		{
			drawCard(currentPlayer, &G);
		}

		printf("Starting hand count for player %d = %d\n", currentPlayer + 1, G.handCount[currentPlayer]);
		printf("Starting number of actions (reset to 1 for new turn) for player %d = %d\n", currentPlayer + 1, G.numActions);
		printf("Calling cardEffect for Great Hall to add 1 card, 1 action, discard Great Hall card...\n");
		int testReturn = cardEffect(great_hall, choice1, choice2, choice3, &G, handpos, &bonus);

		addedCards = 1;
		discarded = 1;
		addedActions = 1;
		successReturn = 0;
		initialHand = 5;

		printf("Hand count = %d, expected = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer] + initialHand + addedCards - discarded);
		printf(myAssert(G.handCount[currentPlayer] == testG.handCount[currentPlayer] + initialHand + addedCards - discarded));

		printf("Actions count (global for game state) = %d, expected = %d\n", G.numActions, testG.numActions + addedActions);
		printf(myAssert(G.numActions == testG.numActions + addedActions));

		printf("Return value for successful cardEffect for Great Hall = %d, expected = %d\n", testReturn, successReturn);
		printf(myAssert(testReturn == successReturn));

		printf("\n");
	}


	printf("\n >>>>> Testing complete for %s <<<<<\n\n", TESTCARD);


	return 0;
}
