/* -----------------------------------------------------------------------
* Connie McClung - Random Card Test 2
* randomcardtest2.c
*
* Tests basic operations of Village card
* 1. Allows current player to draw 1 cards
* 2. Increments global game state variable numActions by 2
* 3. Current player's hand before playing additional actions should equal handCount +  1 - 1(for Village move to played card pile)
* 4. Other players' hand count  should not change
* 5. Successful Village cardEffect returns 0
*
* -----------------------------------------------------------------------
*/
/*
* Include the following lines in your makefile:
*
* randomtestcard2: randomtestcard2.c dominion.o rngs.o
*      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
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


void randomTestVillage(int p, int player, struct gameState *randomStatePost) {
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int handPos = 0;
	struct gameState randomStatePre;
	randomStatePost->whoseTurn = player;
	randomStatePost->numActions = 1; //at start of turn always 1
	char* returnmsg;

	int i;

	//copy game state so there is a previous state for comparision
	memcpy(&randomStatePre, randomStatePost, sizeof(struct gameState));

	//printf("PRE Village card effect player %d: handcount %d, deckcount %d, discardcount %d\n"
		//, player + 1, randomStatePre.handCount[player], randomStatePre.deckCount[player],
		//randomStatePre.discardCount[player]);
	//printf("PRE Village card effect global variable numActions is: %d\n", randomStatePre.numActions);

	int returnValue;
	returnValue = cardEffect(village, choice1, choice2, choice3, randomStatePost, handPos, &bonus);


	returnmsg = myAssert(returnValue == 0);
	if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
	{

		printf("Return value for village card effect, player %d: ", player + 1);
		//printf(myAssert(returnValue == 0));
		printf(returnmsg);
	}
	//printf("POST adventurer card effect player %d: handcount %d, deckcount %d, discardcount %d\n"
	//	, player + 1, randomStatePost->handCount[player], randomStatePost->deckCount[player],
	//	randomStatePost->discardCount[player]);
	//printf("POST Village card effect global variable numActions is: %d\n", randomStatePost->numActions);

	//update pre to reflect change from card effect - handcount does not change, but numActions does
	randomStatePre.numActions += 2;
	returnmsg = myAssert(randomStatePost->handCount[player] == (randomStatePre.handCount[player]));
	if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
	{
		printf("Hand count increased by correct # of cards: ");
		//printf(myAssert(randomStatePost->handCount[player] == (randomStatePre.handCount[player])));
		printf(returnmsg);
	}
	returnmsg = myAssert(randomStatePost->numActions == (randomStatePre.numActions));
	if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
	{
		printf("Global variable numActions increased by 2: ");
		//printf(myAssert(randomStatePost->numActions == (randomStatePre.numActions)));
		printf(returnmsg);
	}
	//check that other player handcounts did not change
	for (i = 0; i < p; i++)
	{
		if (i != player)
		{
			returnmsg = myAssert(randomStatePost->handCount[i] == (randomStatePre.handCount[i]));
			if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
			{
				printf("Hand count for player %d in same game did not change : ", i + 1);
				//printf(myAssert(randomStatePost->handCount[i] == (randomStatePre.handCount[i])));
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

	int k[10] = { adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall };

	struct gameState G;

	printf("Testing Village card.\n");

	printf("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);
	int numIterations = 5000;

	for (n = 0; n < numIterations; n++) {
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
			int addCardsHand = (rand() % (MAX_HAND - 1 + 1)) + 1;
			for (i = G.deckCount[player]; i < addCardsDeck; i++)
			{
				int randomInt = (rand() % (maxValue - minValue + 1)) + minValue;
				G.deck[player][i] = randomInt; //number of cards in ENUM
				G.deckCount[player]++;
			}
			for (j = G.discardCount[player]; j < addCardsDeck; j++)
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

			randomTestVillage(p, player, &G);
		}

	}

	printf("\nRANDOM TESTS COMPLETE\n");
	printf("Seed: %d\n", seed);
	printf("Number of iterations: %d\n", numIterations);
	printf("Tests passed: %d\n", passCounter);
	printf("Tests failed: %d\n", failCounter);

	return 0;
}
