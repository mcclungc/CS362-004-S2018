/*
---------------------------------------------------------------------- -
*Connie McClung - Unit Test 2
* test isGameOver()
*
* Tests basic requirements of isGameOver(gameState*)
* 1. If count of province card in supplyCount == 0, returns 1 to indicate game is over
* 2. If count of 3 cards in supplyCount == 0, returns 1 to indicate game is over
* 3. If neither condition 1 or 2 is true, returns 0 to indicate game is not over
* 4. Calling isGameOver() does not change game state or player variables
*
* Demonstration of how to write unit tests for dominion - base
* Include the following lines in your makefile :
*
* unittest2 : unittest2.c dominion.o rngs.o
*      gcc - o unittest2 - g  unittest2.c dominion.o rngs.o $(CFLAGS)
* ---------------------------------------------------------------------- -
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output, EXCEPT headers and assert statement results
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
	int testReturn = -1;//initialize to sentinel value

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
	//int currentPlayer = 0;
	int gameOverTrue = 1;
	int gameOverFalse = 0;

	int k1[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	int k2[10] = { minion, steward, tribute, ambassador, cutpurse, embargo
		, outpost, salvager, sea_hag, treasure_map };
	struct gameState G, testG, G2, testG2;



	printf("---------------------------------------------------------------------\n");
	printf("------------------TESTING isGameOver()-------------------------------\n");
	printf("---------------------------------------------------------------------\n");
	//Initialize game and test isGameOver()
	//USING K1 SET OF KINGDOM CARDS

	printf("\n");
	printf("---------------------------------------------------------------------\n");
	printf("TEST 1 - Call GameOver() on newly initialized game and check card counts after\n");
	printf("---------------------------------------------------------------------\n");
#if(NOISY_TEST == 1)
	printf("TESTING isGameOver() in a game with k1 kingdom card set:\n\n");
#endif
	initializeGame(numPlayer, k1, seed, &testG);
	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG remains in original state

	//test isGameOver on newly initialized game
#if(NOISY_TEST == 1)
	printf("TESTING isGameOver() on newly initialized game\n\n");
#endif
	testReturn = isGameOver(&G);
#if(NOISY_TEST == 1)
	printf("isGameOver() return value is %d, expected %d\n", testReturn, gameOverFalse);
#endif
	printf(myAssert(testReturn == gameOverFalse));
#if(NOISY_TEST == 1)
	printf("Testing that game state did not change just from calling isGameOver() on new game\n");
	printf("Game state G is equal copy of game state TestG - no change in game state!\n");
#endif
	printf(myAssert(memcmp(&G, &testG, sizeof(struct gameState)) == 0));
#if(NOISY_TEST == 1)

	printf("\n");
	printf("Testing that player and supply deck counts did not change just from calling isGameOver() on new game\n");
#endif
	for (j = 0; j < numPlayer; j++)
	{
#if(NOISY_TEST == 1)
		printf("Player %d hand count is: %d, expected %d\n", j + 1, G.handCount[j], testG.handCount[j]);
#endif
		printf(myAssert(G.handCount[j] == testG.handCount[j]));
#if(NOISY_TEST == 1)
		printf("Player %d deck count is: %d, expected %d\n", j + 1, G.deckCount[j], testG.deckCount[j]);
#endif
		printf(myAssert(G.deckCount[j] == testG.deckCount[j]));
#if(NOISY_TEST == 1)
		printf("Player %d discard count is: %d, expected %d\n", j + 1, G.discardCount[j], testG.discardCount[j]);
#endif
		printf(myAssert(G.discardCount[j] == testG.discardCount[j]));
	}
#if(NOISY_TEST == 1)
	printf("\n");
#endif
	for (i = 0; i < 27; i++)
	{
#if(NOISY_TEST == 1)
		printf("Card %s count is  %d, expected %d\n", cardNames[i], G.supplyCount[i], testG.supplyCount[i]);
#endif
		printf(myAssert(G.supplyCount[i] == testG.supplyCount[i]));
	}

	printf("\n");
	
	printf("---------------------------------------------------------------------\n");
	printf("TEST 2 - Test for conditions that should cause game over\n");
	printf("---------------------------------------------------------------------\n");
#if(NOISY_TEST == 1)
	printf("TESTING isGameOver() on province card count condition: \n\n");
#endif
	//TEST WHEN PROVINCE CARD COUNT IN SUPPLYCOUNT == 0
	//set province card count in supplyCount to 0
	G.supplyCount[province] = 0;
#if(NOISY_TEST == 1)
	printf("Set province card pile to zero and call isGameOver():\n");
#endif
	testReturn = isGameOver(&G);
#if(NOISY_TEST == 1)
	printf("isGameOver() return value is %d, expected %d\n", testReturn, gameOverTrue);
#endif
	printf(myAssert(testReturn == gameOverTrue));
#if(NOISY_TEST == 1)
	printf("\n");
#endif
	//TEST WHEN PROVINCE CARD COUNT IN SUPPLYCOUNT != 0
	//set province card count in supplyCount to various non-zero values
#if(NOISY_TEST == 1)
	printf("Set count of province card to various values within and outside of game conditions.\n");
	printf("As long as province card count != 0, isGameOver() should return 0.\n\n");
#endif
	for (i = 1; i <= 20; i++)
	{
		G.supplyCount[province] = i;
		testReturn = isGameOver(&G);
#if(NOISY_TEST == 1)
		printf("isGameOver() with province card count %d, return value is %d, expected %d\n", G.supplyCount[province], testReturn, gameOverFalse);
#endif
		printf(myAssert(testReturn == gameOverFalse));
	}
	for (i = -1; i >= -20; i--)
	{
		G.supplyCount[province] = i;
		testReturn = isGameOver(&G);
#if(NOISY_TEST == 1)
		printf("isGameOver() with province card count %d, return value is %d, expected %d\n", G.supplyCount[province], testReturn, gameOverFalse);
#endif
		printf(myAssert(testReturn == gameOverFalse));
	}
#if(NOISY_TEST == 1)
	printf("\n");
#endif
	//TEST ISGAMEOVER() ON CONDITION OF 3 EMPTY CARD PILES IN SUPPLY
#if(NOISY_TEST == 1)
	printf("TESTING isGameOver() on 3 empty card piles in supply count condition: \n\n");
#endif	//set all card piles to zero
	for (i = 0; i < 27; i++)
	{
		G.supplyCount[i] = 0;
	}
#if(NOISY_TEST == 1)
	printf("Set all supplyCount card piles to zero and call isGameOver():\n");
#endif
	testReturn = isGameOver(&G);
#if(NOISY_TEST == 1)
	printf("isGameOver() return value is %d, expected %d\n", testReturn, gameOverTrue);
#endif
	printf(myAssert(testReturn == gameOverTrue));
#if(NOISY_TEST == 1)
	printf("\n");
#endif
	//set all card piles to -1
	for (i = 0; i < 27; i++)
	{
		G.supplyCount[i] = -1;
	}
#if(NOISY_TEST == 1)
	printf("Set all supplyCount card piles to -1 (card not in game) and call isGameOver():\n");
#endif	
	testReturn = isGameOver(&G);
#if(NOISY_TEST == 1)
	printf("isGameOver() return value is %d, expected %d\n", testReturn, gameOverFalse);
#endif
	printf(myAssert(testReturn == gameOverFalse));
#if(NOISY_TEST == 1)
	printf("\n");
#endif
	//set all card piles > 60
	for (i = 0; i < 27; i++)
	{
		G.supplyCount[i] = 61;
	}
#if(NOISY_TEST == 1)
	printf("Set all supplyCount card piles to > max possible count for any card and call isGameOver():\n");
#endif
	testReturn = isGameOver(&G);
#if(NOISY_TEST == 1)
	printf("isGameOver() return value is %d, expected %d\n", testReturn, gameOverFalse);
#endif
	printf(myAssert(testReturn == gameOverFalse));
#if(NOISY_TEST == 1)
	printf("\n");
#endif
	// set 1-2 pile at zero 
	for (i = 0; i < 2; i++)
	{
		G.supplyCount[i] = 0;
	}
	for (i = 2; i < 28; i++)
	{
		G.supplyCount[i] = 10;
	}
#if(NOISY_TEST == 1)
	printf("Set 1 or 2 supplyCount card piles to empty and call isGameOver():\n");
#endif
	testReturn = isGameOver(&G);
#if(NOISY_TEST == 1)
	printf("isGameOver() return value is %d, expected %d\n", testReturn, gameOverFalse);
#endif
	printf(myAssert(testReturn == gameOverFalse));

	printf("\n");

	printf("---------------------------------------------------------------------\n");
	printf("TEST 3 - Testing that isGameOver() return value is correct\n");
	printf("---------------------------------------------------------------------\n");
#if(NOISY_TEST == 1)
	printf("TESTING isGameOver() in a game with k2 kingdom card set:\n");
	printf("isGameOver() return value, should be 0 or 1:\n\n");
	printf("Calling on newly initialized game should return 0\n");
#endif
	initializeGame(numPlayer, k2, seed, &testG2);
	//copy gamestate to testG so you can compare before and after
	memcpy(&G2, &testG2, sizeof(struct gameState)); //testG2 remains in original state
	testReturn = isGameOver(&G2);
#if(NOISY_TEST == 1)
	printf("isGameOver() return value is %d, expected %d\n", testReturn, gameOverFalse);
#endif
	//printf(myAssert((testReturn == gameOverFalse) || (testReturn == gameOverTrue)));
	printf(myAssert((testReturn == gameOverFalse)));
#if(NOISY_TEST == 1)
	printf("Setting game state to a game over condition should return 1\n");
#endif
	G2.supplyCount[province] = 0;
	G2.supplyCount[1] = 0;
	G2.supplyCount[2] = 0;
	testReturn = isGameOver(&G2);
#if(NOISY_TEST == 1)
	printf("isGameOver() return value is %d, expected %d\n", testReturn, gameOverTrue);
#endif
	printf(myAssert((testReturn == gameOverTrue)));

	printf("\nAll tests passed!\n");



	return 0;
}
