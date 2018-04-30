/*---------------------------------------------------------------------- -
*Connie McClung - Unit Test 4
* test fullDeckCount()
*
* Tests basic requirements of fullDeckCount(int player, int card, struct gameState *state)
* 1. For the player and card passed in, returns the total count of card in all of player's card piles
* 2. If card passed in is not in player's pile, returns 0
* 3. Correctly counts and totals card count for player's hand, deck, and discard pile
* 4. Calling fullDeckCount does not change game state 
*
* Demonstration of how to write unit tests for dominion - base
* Include the following lines in your makefile :
*
* unittest4 : unittest4.c dominion.o rngs.o
*      gcc - o unittest4 - g  unittest4.c dominion.o rngs.o $(CFLAGS)
* ---------------------------------------------------------------------- -
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

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
	int testReturn = -1; //sentinel value

	const char* cardNames[] = {
		"curse",
		"estate",
		"duchy",
		"province",
		"copper",
		"silver",
		"gold",
		"adventurer",
		"council_room",
		"feast",
		"gardens",
		"mine",
		"remodel",
		"smithy",
		"village",
		"baron",
		"great_hall",
		"minion",
		"steward",
		"tribute",
		"ambassador",
		"cutpurse",
		"embargo",
		"outpost",
		"salvager",
		"sea_hag",
		"treasure_map"
	};



	// variables to set up a game for for players and initialze
	int seed = 1000;
	int numPlayer = MAX_PLAYERS;
	int currentPlayer = 0;
	// sets of kingdom cards
	int k1[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	int k2[10] = { minion, steward, tribute, ambassador, cutpurse, embargo
		, outpost, salvager, sea_hag, treasure_map };
	struct gameState G, testG, G2, testG2; //probably not necessary to back up game state for this test




	printf("-----------------------------------------------------------------------------\n");
	printf("---------------------TESTING fullDeckCount():--------------------------------\n");
	printf("-----------------------------------------------------------------------------\n");

	//Initialize game and test gainCard()
	//USING K1 SET OF KINGDOM CARDS

	initializeGame(numPlayer, k1, seed, &testG);
	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG remains in original state

	printf("\n");
	printf("-----------------------------------------------------------------------------\n");
	printf("TEST 1 - TESTING new game for correct count, no change in game state\n");
	printf("----------------------------------------------------------------------------\n");
#if(NOISY_TEST ==1)
	printf("TESTING fullDeckCount() in a game with k1 kingdom card set:\n\n");
#endif
#if(NOISY_TEST ==1)
	printf("TESTING fullDeckCount() on newly initialized game\n\n");
	printf("Player %d is current player.\n", G.whoseTurn + 1);

	//call fullDeckCount() for estate and coppers after game is initialized

	printf("\nTESTING fullDeckCount() for each player's estate and province after game initialized:\n");
	//printf("This tests card in/not in hand, card in/not in deck\n");
	printf("\n");
#endif
	int estate = 1;
	int copper = 4;
	int estateAtStart = 3;
	int copperAtStart = 7;

	for (currentPlayer=0; currentPlayer<numPlayer; currentPlayer++)
	{
		testReturn = fullDeckCount(currentPlayer, estate, &G);
#if(NOISY_TEST ==1)
		printf("Full deck count for player %d card %s is %d, expected %d\n", currentPlayer + 1, cardNames[estate], testReturn, estateAtStart);
#endif
		printf(myAssert(testReturn == estateAtStart));
		testReturn = fullDeckCount(currentPlayer, copper, &G);
#if(NOISY_TEST ==1)
		printf("Full deck count for player %d card %s is %d, expected %d\n", currentPlayer + 1, cardNames[copper], testReturn, copperAtStart);
#endif
		printf(myAssert(testReturn == copperAtStart));
		
	}
#if(NOISY_TEST ==1)
	printf("\n");
	printf("Testing that game state did not change just from calling fullDeckCount()\n");
#endif
	printf(myAssert(memcmp(&G, &testG, sizeof(struct gameState)) == 0));
#if(NOISY_TEST ==1)
	printf("Game state G is equal copy of game state TestG - no change in game state!\n");
	printf("\n");
	printf("Testing that player and supply deck counts did not change just from calling fullDeckCount() on new game\n");
#endif
	for (j = 0; j < numPlayer; j++)
	{
#if(NOISY_TEST ==1)
		printf("Player %d hand count is: %d, expected %d\n", j + 1, G.handCount[j], testG.handCount[j]);
#endif
		printf(myAssert(G.handCount[j] == testG.handCount[j]));
#if(NOISY_TEST ==1)
		printf("Player %d deck count is: %d, expected %d\n", j + 1, G.deckCount[j], testG.deckCount[j]);
#endif
		printf(myAssert(G.deckCount[j] == testG.deckCount[j]));
#if(NOISY_TEST ==1)
		printf("Player %d discard count is: %d, expected %d\n", j + 1, G.discardCount[j], testG.discardCount[j]);
#endif
		printf(myAssert(G.discardCount[j] == testG.discardCount[j]));
#if(NOISY_TEST ==1)
		printf("\n");
#endif
	}
	printf("\n");
	printf("-----------------------------------------------------------------------------\n");
	printf("TEST 2 - TESTING for correct count if none of card in any pile\n");
	printf("----------------------------------------------------------------------------\n");
	printf("\n");
#if(NOISY_TEST ==1)
	printf("TESTING fullDeckCount() for each player when all card counts are zero:\n");
#endif
	for (currentPlayer = 0; currentPlayer < numPlayer; currentPlayer++)
	{
		for (i = 0; i < 27; i++)
		{
			for (j = 0; j < 10; j++)
			{
				G.deck[currentPlayer][j] = -1;
				G.discard[currentPlayer][j] = -1;
				G.hand[currentPlayer][j] = -1;
			}

			int empty = 0;
			testReturn = fullDeckCount(currentPlayer, i, &G);
#if(NOISY_TEST ==1)
			printf("Full deck count for player %d card %s is %d, expected %d\n", currentPlayer + 1, cardNames[i], testReturn, empty);
#endif
			printf(myAssert(testReturn == empty));
		}
#if(NOISY_TEST ==1)
		printf("\n");
#endif

	}


	printf("\n");
	printf("----------------------------------------------------------------------------------------\n");
	printf("TEST 3 - TESTING for correct count, card in all piles, just deck, just discard, just hand\n");
	printf("----------------------------------------------------------------------------------------\n");
	printf("\n");
	
	//printf("TESTING fullDeckCount() in a game with k2 kingdom card set:\n\n");
	initializeGame(numPlayer, k2, seed, &testG2);
	//copy gamestate to testG so you can compare before and after
	memcpy(&G2, &testG2, sizeof(struct gameState)); //testG remains in original state

#if(NOISY_TEST ==1)
	printf("TESTING fullDeckCount() for each player when card is in all of player's piles:\n");
#endif
	for (currentPlayer = 0; currentPlayer < numPlayer; currentPlayer++)
	{
		G.deckCount[currentPlayer] = 0;
		G.discardCount[currentPlayer] = 0;
		G.handCount[currentPlayer] = 0;

		for (i = 0; i < 27; i++)
		{
			for (j = 0; j < 10; j++)
			{
				G.deck[currentPlayer][j] = i;
				//printf("card %s:\n", cardNames[G.deck[currentPlayer][j]]);
				G.deckCount[currentPlayer]++;
				G.discard[currentPlayer][j] = i;
				//printf("card %s:\n", cardNames[G.discard[currentPlayer][j]]);
				G.discardCount[currentPlayer]++;
				G.hand[currentPlayer][j] = i;
				//printf("card %s:\n", cardNames[G.hand[currentPlayer][j]]);
				G.handCount[currentPlayer]++;

			}

			int expected = 30;
			testReturn = fullDeckCount(currentPlayer, i, &G);
#if(NOISY_TEST ==1)
			printf("Full deck count for player %d card %s is %d, expected %d\n", currentPlayer + 1, cardNames[i], testReturn, expected);
#endif
			printf(myAssert(testReturn == expected));

		}

	}
#if(NOISY_TEST ==1)
	printf("\n");

	printf("TESTING fullDeckCount() for each player when card is in player's discard pile only:\n");
#endif
	for (currentPlayer = 0; currentPlayer < numPlayer; currentPlayer++)
	{
		G.deckCount[currentPlayer] = 0;
		G.discardCount[currentPlayer] = 0;
		G.handCount[currentPlayer] = 0;

		for (i = 0; i < 27; i++)
		{
			for (j = 0; j < 10 ; j++)
			{
				G.deck[currentPlayer][j] = -1;
				//printf("card %s:\n", cardNames[G.deck[currentPlayer][j]]);
				G.deckCount[currentPlayer]++;
				G.discard[currentPlayer][j] = i;
				//printf("card %s:\n", cardNames[G.discard[currentPlayer][j]]);
				G.discardCount[currentPlayer]++;
				G.hand[currentPlayer][j] = -1;
				//printf("card %s:\n", cardNames[G.hand[currentPlayer][j]]);
				G.handCount[currentPlayer]++;

			}
			
			int expected = 10;
			testReturn = fullDeckCount(currentPlayer, i, &G);
#if(NOISY_TEST ==1)
			printf("Full deck count for player %d card %s is %d, expected %d\n", currentPlayer + 1, cardNames[i], testReturn, expected);
#endif
			printf(myAssert(testReturn == expected));
			
		}

	}
#if(NOISY_TEST ==1)
	printf("\n");
	printf("TESTING fullDeckCount() for each player when card is in player's hand only:\n");
#endif
	for (currentPlayer = 0; currentPlayer < numPlayer; currentPlayer++)
	{
		G.deckCount[currentPlayer] = 0;
		G.discardCount[currentPlayer] = 0;
		G.handCount[currentPlayer] = 0;

		for (i = 0; i < 27; i++)
		{
			for (j = 0; j < 10; j++)
			{
				G.deck[currentPlayer][j] = -1;
				//printf("card %s:\n", cardNames[G.deck[currentPlayer][j]]);
				G.deckCount[currentPlayer]++;
				G.discard[currentPlayer][j] = -1;
				//printf("card %s:\n", cardNames[G.discard[currentPlayer][j]]);
				G.discardCount[currentPlayer]++;
				G.hand[currentPlayer][j] = i;
				//printf("card %s:\n", cardNames[G.hand[currentPlayer][j]]);
				G.handCount[currentPlayer]++;

			}

			int expected = 10;
			testReturn = fullDeckCount(currentPlayer, i, &G);
#if(NOISY_TEST ==1)
			printf("Full deck count for player %d card %s is %d, expected %d\n", currentPlayer + 1, cardNames[i], testReturn, expected);
#endif
			printf(myAssert(testReturn == expected));

		}

	}
#if(NOISY_TEST ==1)
	printf("\n");
	printf("TESTING fullDeckCount() for each player when card is in player's deck only:\n");
#endif
	for (currentPlayer = 0; currentPlayer < numPlayer; currentPlayer++)
	{
		G.deckCount[currentPlayer] = 0;
		G.discardCount[currentPlayer] = 0;
		G.handCount[currentPlayer] = 0;

		for (i = 0; i < 27; i++)
		{
			for (j = 0; j < 10; j++)
			{
				G.deck[currentPlayer][j] = i;
				//printf("card %s:\n", cardNames[G.deck[currentPlayer][j]]);
				G.deckCount[currentPlayer]++;
				G.discard[currentPlayer][j] = -1;
				//printf("card %s:\n", cardNames[G.discard[currentPlayer][j]]);
				G.discardCount[currentPlayer]++;
				G.hand[currentPlayer][j] = -1;
				//printf("card %s:\n", cardNames[G.hand[currentPlayer][j]]);
				G.handCount[currentPlayer]++;

			}

			int expected = 10;
			testReturn = fullDeckCount(currentPlayer, i, &G);
#if(NOISY_TEST ==1)
			printf("Full deck count for player %d card %s is %d, expected %d\n", currentPlayer + 1, cardNames[i], testReturn, expected);
#endif
			printf(myAssert(testReturn == expected));

		}

	}

	printf("\n");
	printf("All tests passed!\n");


	return 0;
}
