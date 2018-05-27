/* -----------------------------------------------------------------------
* Connie McClung - Random Card Test 1
* randomtestcard1.c
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
* randomtestcard1: randomtestcard1.c dominion.o rngs.o
*      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

static int failCounter = 0;
static int passCounter = 0;

char* myAssert(int testValue)
{
	if (testValue == 0)
	{
		failCounter++;
		char* msg = "TEST FAILED!\n";
		//getchar();
		return msg;
	}
	else
	{
		passCounter++;
		char* msg = "Test passed!\n";
		return msg;
	}
}


void randomTestSmithy(int p, int player, struct gameState *randomStatePost) {
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int handPos = 0;
	struct gameState randomStatePre;
	randomStatePost->whoseTurn = player;
	char* returnmsg;

	int i;

	//copy game state so there is a previous state for comparision
	memcpy(&randomStatePre, randomStatePost, sizeof(struct gameState));

	//UNCOMMENT NEXT 3 LINES FOR MORE VERBOSE OUTPUT
	//printf("PRE Smithy card effect player %d: handcount %d, deckcount %d, discardcount %d\n"
	//	, player + 1, randomStatePre.handCount[player], randomStatePre.deckCount[player],
	//	randomStatePre.discardCount[player]);

	int returnValue;
	returnValue = cardEffect(smithy, choice1, choice2, choice3, randomStatePost, handPos, &bonus);

	returnmsg = myAssert(returnValue == 0);
	if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
	{
		printf("Return value for smithy card effect, player %d: ", player + 1);
		printf(returnmsg);

	}

	//UNCOMMENT NEXT 3 LINES FOR MORE VERBOSE OUTPUT
	//printf("POST adventurer card effect player %d: handcount %d, deckcount %d, discardcount %d\n"
	//	, player + 1, randomStatePost->handCount[player], randomStatePost->deckCount[player],
	//	randomStatePost->discardCount[player]);
	//update pre to reflect change from card effect
	
	randomStatePre.handCount[player] += 2;

	returnmsg = myAssert(randomStatePost->handCount[player] == (randomStatePre.handCount[player]));
	if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
	{
		printf("Hand count for player who played Smithy increased by correct # of cards: ");
		printf(returnmsg);
	}
	for (i = 0; i < p; i++)
	{
		if (i != player) 
		{
			returnmsg = myAssert(randomStatePost->handCount[i] == (randomStatePre.handCount[i]));
			if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
			{
				printf("Hand count for player %d in same game did not change : ", i + 1);
				printf(returnmsg);
			}
		}
	
	}
	//printf("\n");
}



int main() {
	srand((unsigned int)time(NULL));
	int i, j, m, n, p;

	int seed = 999;
	//int maxPlayers = 4;

	int k[10] = { adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall };

	struct gameState G;

	printf("\nTesting Smithy card.\n");

	printf("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	int numIterations = 500;
	for (n = 0; n < numIterations; n++) {
		//UNCOMMENT NEXT LINE TO SHOW WHICH ITERATION YOU ARE ON
		//printf("n = %d\n", n);

		p = (rand() % (MAX_PLAYERS - 1 + 1)) + 1;
		//printf("There are %d players in this game\n", p);
		initializeGame(MAX_PLAYERS, k, seed, &G);//initialize for max # of players to make sure no memory access errors
		int player;
		for (player = 0; player < p; player++)
		{
			int maxValue = 26;
			int minValue = 0;
			int addCardsDeck = (rand() % (MAX_DECK - 1 + 1)) + 1;
			int addCardsDiscard = (rand() % (MAX_DECK - 1 + 1)) + 1;
			int addCardsHand = (rand() % (MAX_HAND - 1 + 1)) + 1;
			for (i = G.deckCount[player]; i < addCardsDeck; i++)
			{
				int randomInt = (rand() % (maxValue - minValue + 1)) + minValue;
				G.deck[player][i] = randomInt; //number of cards in ENUM
				G.deckCount[player]++;
			}
			for (j = G.discardCount[player]; j < addCardsDiscard; j++)
			{
				int randomInt = (rand() % (maxValue - minValue + 1)) + minValue;
				G.discard[player][i] = randomInt; //number of cards in ENUM
				G.discardCount[player]++;
			}
			for (m = G.handCount[player]; m < addCardsHand; m++)
			{
				int randomInt = (rand() % (maxValue - minValue + 1)) + minValue;
				G.hand[player][i] = randomInt; //number of cards in ENUM
				G.handCount[player]++;
			}

			randomTestSmithy(p, player, &G);
		}

	}

	printf("\nRANDOM TESTS COMPLETE\n");
	printf("Seed: %d\n", seed);
	printf("Number of iterations: %d\n", numIterations);
	printf("Tests passed: %d\n", passCounter);
	printf("Tests failed: %d\n", failCounter);

	return 0;
}
