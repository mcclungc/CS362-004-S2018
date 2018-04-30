/* -----------------------------------------------------------------------
* Connie McClung - Unit Test 1
* test getCost()
*
* Tests basic requirements of getCost(int)
* 1. When passed int value corresponding to card in enum CARD, returns correct cost as int
* 2. When passed an int value not corresponding to card in enum CARD, returns -1
* 3. Calling getCost() does not change makeup of player decks or supplyCount in a game
*
* Demonstration of how to write unit tests for dominion-base
* Include the following lines in your makefile:
*
* unittest1: unittest1.c dominion.o rngs.o
*      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output , EXCEPT HEADERS AND ASSERT RESULTS
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

	int j;
	int testReturn;
	int supplyPos;

	// variables to set up a game and call getCost for all cards in hand and deck
	int seed = 1000;
	int numPlayer = MAX_PLAYERS;
	int currentPlayer = 0;

	int k1[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	//int k2[10] = { minion, steward, tribute, ambassador, cutpurse, embargo
	//	, outpost, salvager, sea_hag, treasure_map };
	struct gameState G, testG; 
	//int maxHandCount = 5;


	int  correctCosts[27] = { 0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4 };



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

	printf("---------------------------------------------------------------------\n");
	printf("----------------------- TESTING: %s -------------------------\n", "getCost()");
	printf("---------------------------------------------------------------------\n");
	printf("TESTING getCost() using game with first 10 kingdom cards:\n\n");
	//test all card costs
	printf("---------------------------------------------------------------------\n");
	printf("TEST 1 - Testing getCost() on existing and non-existent cards:\n\n");
	printf("---------------------------------------------------------------------\n");

	printf("TESTING getCost() with existing cards:\n");
	for (supplyPos = 0; supplyPos < 27; supplyPos++)
	{
		#if (NOISY_TEST ==1)
			printf("Testing card %s:\n", cardNames[supplyPos]);
		#endif
		testReturn = getCost(supplyPos);
		#if (NOISY_TEST ==1)
			printf("Card %s cost = %d, expected %d\n", cardNames[supplyPos], testReturn, correctCosts[supplyPos]);
		#endif
		printf(myAssert(testReturn == correctCosts[supplyPos]));
	}
	#if (NOISY_TEST ==1)
	printf("\n");
	#endif
	//test when int passed to getCost() does not reference a card in game - card < curse
	printf("TESTING getCost() with non-existent cards < curse:\n");
	for (supplyPos = curse - 1; supplyPos >= curse - 10; supplyPos--)
	{
		#if (NOISY_TEST ==1)
			printf("Testing non-existent card cost:\n");fflush(stdout);
		#endif
		testReturn = getCost(supplyPos);
		#if (NOISY_TEST ==1)
			printf("Card with int value %d cost = %d, expected %d\n", supplyPos, testReturn, -1);fflush(stdout);
		#endif
		printf(myAssert(testReturn ==  -1));
	}
#if (NOISY_TEST ==1)
	printf("\n");
#endif

	//test when int passed to getCost() does not reference a card in game - card > curse
	printf("TESTING getCost() with non-existent cards > treasure map:\n");
	for (supplyPos = treasure_map + 1; supplyPos < treasure_map + 10; supplyPos++)
	{
		#if (NOISY_TEST ==1)
			printf("Testing non-existent card > treasure_map:\n");
		#endif
		testReturn = getCost(supplyPos);
		#if (NOISY_TEST ==1)
			printf("Card with int value %d cost = %d, expected %d\n", supplyPos, testReturn, -1);
		#endif
			printf(myAssert(testReturn == -1));
	}
#if (NOISY_TEST ==1)
	printf("\n");
#endif


	//test game state before and after calling getCost() on all cards in a game
	//USING K1 SET OF KINGDOM CARDS
	printf("---------------------------------------------------------------------\n");
	printf("\nTEST 2 - Testing that calling getCost() did not change any card counts in game:\n\n");
	printf("---------------------------------------------------------------------\n");
	printf("TESTING getCost() in a game with k1 kingdom card set:\n");
	initializeGame(numPlayer, k1, seed, &testG);
	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState));

	//call getCost() on all cards in player decks and supply
	printf("TESTING getCost() returns correct values for player decks:\n");
	for (currentPlayer = 0; currentPlayer < numPlayer; currentPlayer++)
	{
		for (j = 0; j < G.handCount[currentPlayer]; j++)
		{
			#if (NOISY_TEST ==1)
				printf("Testing %s card in player %d hand:\n", cardNames[G.hand[currentPlayer][j]], currentPlayer +1);fflush(stdout);
			#endif
			testReturn = getCost(G.hand[currentPlayer][j]);
			#if (NOISY_TEST ==1)
				printf("Card %s cost = %d, expected %d\n", cardNames[G.hand[currentPlayer][j]], testReturn, correctCosts[G.hand[currentPlayer][j]]);fflush(stdout);
			#endif
				printf(myAssert(testReturn == correctCosts[G.hand[currentPlayer][j]]));
		}
#if (NOISY_TEST ==1)
		printf("\n");
#endif
		for (j = 0; j < G.deckCount[currentPlayer]; j++)
		{
			#if (NOISY_TEST ==1)
				printf("Testing %s card in player %d deck:\n", cardNames[G.deck[currentPlayer][j]], currentPlayer +1);fflush(stdout);
			#endif
			testReturn = getCost(G.deck[currentPlayer][j]);
			#if (NOISY_TEST ==1)
				printf("Card %s cost = %d, expected %d\n", cardNames[G.deck[currentPlayer][j]], testReturn, correctCosts[G.deck[currentPlayer][j]]);fflush(stdout);
			#endif
			printf(myAssert(testReturn == correctCosts[G.deck[currentPlayer][j]]));
		}
#if (NOISY_TEST ==1)
		printf("\n");
#endif
	}
	printf("TESTING getCost() returns correct values for supply deck:\n");
	for (j = 0; j < treasure_map + 1; j++)
	{
		if (G.supplyCount[j] > -1)
		{
			#if (NOISY_TEST ==1)			
				printf("Testing %s card in supply deck :\n", cardNames[j]);fflush(stdout);
				printf("There are %d copies of  %s card in supply deck:\n", G.supplyCount[j], cardNames[j]);fflush(stdout);
			#endif	
			testReturn = getCost(j);
			#if (NOISY_TEST ==1)
				printf("Card %s cost = %d, expected %d\n", cardNames[j], testReturn, correctCosts[j]);fflush(stdout);
			#endif			
			printf(myAssert(testReturn == correctCosts[j]));
		}
	}
	
	//check that all cards in player hand and deck are same, and supplyCount has not changed for any cards
	printf("\n");
	printf("TESTING  that getCost() did not change supply card counts or makeup of player decks:\n");
	printf("TESTING getCost() did not change player decks:\n");
	for (currentPlayer = 0; currentPlayer < numPlayer; currentPlayer++)
	{
		for (j = 0; j < G.handCount[currentPlayer]; j++)
		{
			#if (NOISY_TEST ==1)
			printf("Testing that %s card in player %d hand did not change:\n", cardNames[G.hand[currentPlayer][j]], currentPlayer +1);fflush(stdout);
			printf("Card %s, expected %s\n", cardNames[G.hand[currentPlayer][j]], cardNames[testG.hand[currentPlayer][j]]);fflush(stdout);
			#endif
			printf(myAssert(G.hand[currentPlayer][j] == testG.hand[currentPlayer][j]));
		}
#if (NOISY_TEST ==1)
		printf("\n");
#endif
		for (j = 0; j < G.deckCount[currentPlayer]; j++)
		{
			#if (NOISY_TEST ==1)
			printf("Testing that %s card in player %d deck did not change:\n", cardNames[G.deck[currentPlayer][j]], currentPlayer + 1);fflush(stdout);
			printf("Card %s, expected %s\n", cardNames[G.deck[currentPlayer][j]], cardNames[testG.deck[currentPlayer][j]]);fflush(stdout);
			#endif
			printf(myAssert(G.deck[currentPlayer][j] == testG.deck[currentPlayer][j]));
		}
#if (NOISY_TEST ==1)
		printf("\n");
#endif
	}
	printf("TESTING getCost() did not change supply count:\n");
	for (j = 0; j < treasure_map + 1; j++)
	{
		if (G.supplyCount[j] > -1)
		{
			#if (NOISY_TEST ==1)
			printf("Checking that %s card in supply deck in game state did not change:\n", cardNames[j]);fflush(stdout);
			printf("Card %s count = %d, expected %d\n", cardNames[j], G.supplyCount[j], testG.supplyCount[j]);fflush(stdout);
			#endif
			printf(myAssert(G.supplyCount[j] == testG.supplyCount[j]));		}
	}
	

	//SAME TESTS USING K2 SET OF KINGDOM CARDS
	//USING K2 SET OF KINGDOM CARDS
	
	printf("----------------------------------------------------------\n\n");
	printf("TESTING getCost() using game with second 10 kingdom cards:\n\n");
	//test all card costs
	printf("---------------------------------------------------------------------\n");
	printf("TEST 1 - Testing getCost() on existing and non-existent cards:\n\n");
	printf("---------------------------------------------------------------------\n");
	printf("TESTING getCost() with existing cards:\n");
	for (supplyPos = 0; supplyPos < 27; supplyPos++)
	{
#if (NOISY_TEST ==1)
		printf("Testing card %s:\n", cardNames[supplyPos]);
#endif
		testReturn = getCost(supplyPos);
#if (NOISY_TEST ==1)
		printf("Card %s cost = %d, expected %d\n", cardNames[supplyPos], testReturn, correctCosts[supplyPos]);
#endif
		printf(myAssert(testReturn == correctCosts[supplyPos]));
	}
#if (NOISY_TEST ==1)
	printf("\n");
#endif
	//test when int passed to getCost() does not reference a card in game - card < curse
	printf("TESTING getCost() with non-existent cards < curse:\n");
	for (supplyPos = curse - 1; supplyPos >= curse - 10; supplyPos--)
	{
#if (NOISY_TEST ==1)
		printf("Testing non-existent card cost:\n");fflush(stdout);
#endif
		testReturn = getCost(supplyPos);
#if (NOISY_TEST ==1)
		printf("Card with int value %d cost = %d, expected %d\n", supplyPos, testReturn, -1);fflush(stdout);
#endif
		printf(myAssert(testReturn == -1));
	}
#if (NOISY_TEST ==1)
	printf("\n");
#endif

	//test when int passed to getCost() does not reference a card in game - card > curse
	printf("TESTING getCost() with non-existent cards > treasure map:\n");
	for (supplyPos = treasure_map + 1; supplyPos < treasure_map + 10; supplyPos++)
	{
#if (NOISY_TEST ==1)
		printf("Testing non-existent card > treasure_map:\n");
#endif
		testReturn = getCost(supplyPos);
#if (NOISY_TEST ==1)
		printf("Card with int value %d cost = %d, expected %d\n", supplyPos, testReturn, -1);
#endif
		printf(myAssert(testReturn == -1));
	}
#if (NOISY_TEST ==1)
	printf("\n");
#endif



	printf("\n");
	printf("All tests passed!\n");



	return 0;
}
