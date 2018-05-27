/* -----------------------------------------------------------------------
* Connie McClung - Card Test 2
* cardtest2.c
*
* Tests basic operations of Smithy card
* 1. Allows current player to draw 3 cards
* 2. Current player's hand before turn change should equal handCount +  3 - 1(for Smithy move to played card pile)
* 3. Other players' hand count  should not increase
* 4. Successful Smithy cardEffect returns 0
*
* -----------------------------------------------------------------------
*/
/*
* Include the following lines in your makefile:
*
* cardtest2: cardtest2.c dominion.o rngs.o
*      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Smithy"



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

	//int startHandCount;
	//int startTreasureCount;
	int addedCards;
	int discarded ;
	int successReturn;
	int initialHand;
	int testReturn;

	//TEST 1
	//testing in a game with k1 card set
	initializeGame(numPlayer, k1, seed, &testG);


	printf("----------------- TESTING: %s ----------------\n", TESTCARD);

	// TEST 1: Smithy card called by first player in newly initialized game
	printf("\n");
	printf("---------------------------------------------------------------------\n");
	printf("TEST 1: Smithy card called by first player in newly initialized game\n");
	printf("---------------------------------------------------------------------\n");

	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG stays unchanged

	printf("Starting hand count for first player = %d\n", G.handCount[currentPlayer]);
	printf("Calling cardEffect for Smithy to add 3 cards, discard Smithy card...\n");
	testReturn = cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);

	addedCards = 3;
	discarded = 1;
	successReturn = 0;

	printf("Hand count first player = %d, expected = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer] + addedCards - discarded);
	printf(myAssert(G.handCount[currentPlayer] == testG.handCount[currentPlayer] + addedCards - discarded));
	
	printf("Return value for successful cardEffect for Smithy = %d, expected = %d\n", testReturn, successReturn);
	printf(myAssert(testReturn == successReturn));
	
	for (i = currentPlayer + 1; i < numPlayer; i++)
	{
		printf("Hand count player %d  = %d, expected = %d\n", i + 1, G.handCount[i], testG.handCount[i]);
		printf(myAssert(G.handCount[i] == testG.handCount[i]));
	}
	printf("\n");


	//TEST 2
	//testing in a game with k1 card set
	initializeGame(numPlayer, k1, seed, &testG);


	//printf("----------------- TESTING: %s ----------------\n", TESTCARD);

	// TEST 2: Smithy card effect tested on other players in game-doesn't matter which player is current player

	printf("\n");
	printf("---------------------------------------------------------------------\n");
	printf("TEST 2: Testing Smithy card effect works same for all players in game\n");
	printf("---------------------------------------------------------------------\n");

	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG stays unchanged

	for (i = 1; i < numPlayer; i++)
	{
		G.whoseTurn = i;
		currentPlayer = G.whoseTurn;
		printf("Drawing initial hand for player %d...\n", currentPlayer +1);
		for (j = 0;j < 5;j++)
		{
			drawCard(currentPlayer, &G);
		}

		printf("Starting hand count for player %d = %d\n", currentPlayer + 1, G.handCount[currentPlayer]);
		printf("Calling cardEffect for Smithy to add 3 cards, discard Smithy card...\n");
		int testReturn = cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);

		addedCards = 3;
		discarded = 1;
		successReturn = 0;
		initialHand = 5;

		printf("Hand count = %d, expected = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]+ initialHand + addedCards - discarded);
		printf(myAssert(G.handCount[currentPlayer] == testG.handCount[currentPlayer] +initialHand+ addedCards - discarded));

		printf("Return value for successful cardEffect for Smithy = %d, expected = %d\n", testReturn, successReturn);
		printf(myAssert(testReturn == successReturn));

		printf("\n");
	}

	
	printf("\n >>>>> Testing complete for %s <<<<<\n\n", TESTCARD);


	return 0;
}
