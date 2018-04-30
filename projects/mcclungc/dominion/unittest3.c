/*
---------------------------------------------------------------------- -
*Connie McClung - Unit Test 3
* test gainCard()
*
* Tests basic requirements of gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
* 1. If supply count of card is empty or card is not in game, return -1 and do not change game state
* 2. Depending on toFlag value, adds available card to current player's hand, deck, or discard pile
* 3. When card is gained, supplyCount for card is decremented and currentPlayer's 
*    hand, deck or discard count is incremented
* 4. If card is gained, gainCard() return value is 0
* 4. Calling gainCard() does not change any other player's card counts
*
* Demonstration of how to write unit tests for dominion - base
* Include the following lines in your makefile :
*
* unittest3 : unittest3.c dominion.o rngs.o
*      gcc - o unittest3 - g  unittest3.c dominion.o rngs.o $(CFLAGS)
* ---------------------------------------------------------------------- -
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output, EXCEPT headers and assert results
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
	int testReturn = -99;

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
	int numPlayer = 2;
	int currentPlayer = 0;
	// sets of kingdom cards
	int k1[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	//int k2[10] = { minion, steward, tribute, ambassador, cutpurse, embargo
	//	, outpost, salvager, sea_hag, treasure_map };
	struct gameState G, testG; //probably not necessary to back up game state for this test

	printf("-------------------------------------------------------------------------\n");
	printf("----------------------TESTING gainCard():--------------------------------\n");
	printf("-------------------------------------------------------------------------\n");
	printf("\n");
	printf("-------------------------------------------------------------------------\n");
	printf("TEST 1 - TESTING correct return value/behavior if no card in supply pile:\n");
	printf("-------------------------------------------------------------------------\n");
	printf("\n");

	//Initialize game and test gainCard()
	//USING K1 SET OF KINGDOM CARDS BUT WILL FILL SUPPLYCOUNT WITH ALL CARDS FOR TESTING

	initializeGame(numPlayer, k1, seed, &testG);
	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG remains in original state


	 //test isGameOver on newly initialized game
#if(NOISY_TEST ==1)
	printf("Player %d is current player.\n", G.whoseTurn + 1);
#endif
	//set all cards in supplyCount to 30, for each card, call gainCard() for each player with each toFlag
	// toFlag = 0 : add to discard
	// toFlag = 1 : add to deck
	// toFlag = 2 : add to hand

	for (i = 0; i < 27; i++)
	{
		G.supplyCount[i] = 0;
		//printf("Card %s count is %d\n", cardNames[i], G.supplyCount[i]);
	}
	for (i = 0; i < 27; i++)
	{
		G.whoseTurn = 0;
		currentPlayer = G.whoseTurn;
		//check that current player's discard pile updates
		j = 0;	// toFlag = 0 : add to discard
		int preHand = G.handCount[G.whoseTurn];
		int preDeck = G.deckCount[G.whoseTurn];
		int preDiscard = G.discardCount[G.whoseTurn];
#if(NOISY_TEST ==1)
		printf("Before gainCard() for card %s with toFlag %d, player %d handcount = %d, deckCount = %d, discardCount = %d\n", cardNames[i], j, currentPlayer + 1, preHand, preDeck, preDiscard);
#endif
		//printf("supply count for card is %d\n", G.supplyCount[i]);
		testReturn = gainCard(i, &G, j, G.whoseTurn);
		printf(myAssert(testReturn == -1));
#if(NOISY_TEST ==1)
		printf("Return value is %d\n", testReturn);
		printf("After gainCard() with toFlag %d:\n", j);
		printf("Player %d handcount = %d, deckCount = %d, discardCount = %d\n", currentPlayer + 1, G.handCount[G.whoseTurn], G.deckCount[G.whoseTurn], G.discardCount[G.whoseTurn]);
		printf("Expected player %d handcount = %d, deckCount = %d, discardCount = %d\n", currentPlayer + 1, preHand, preDeck, preDiscard);
#endif
		printf(myAssert(G.handCount[G.whoseTurn] == preHand));
		printf(myAssert(G.deckCount[G.whoseTurn] == preDeck));
		printf(myAssert(G.discardCount[G.whoseTurn] == preDiscard));
#if(NOISY_TEST ==1)
		printf("\n");
#endif
	}
#if(NOISY_TEST ==1)
		printf("\n");
#endif
		

	printf("\n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("TEST 2 -TESTING toFlag 0 updates current player's discard pile, not other player card piles:\n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("\n");

	//Initialize game and test gainCard()
	//USING K1 SET OF KINGDOM CARDS BUT WILL FILL SUPPLYCOUNT WITH ALL CARDS FOR TESTING
	initializeGame(numPlayer, k1, seed, &testG);
	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG remains in original state


#if(NOISY_TEST ==1)
	printf("Player %d is current player.\n", G.whoseTurn + 1);
#endif
	//set all cards in supplyCount to 30, for each card, call gainCard() for each player with each toFlag
	// toFlag = 0 : add to discard
	// toFlag = 1 : add to deck
	// toFlag = 2 : add to hand

	for (i = 0; i < 27; i++)
	{
		G.supplyCount[i] = 30;
		//printf("Card %s count is %d\n", cardNames[i], G.supplyCount[i]);
	}
	for (i = 0; i < 27; i++)
	{
		G.whoseTurn = 0;
		currentPlayer = G.whoseTurn;
		//check that current player's discard pile updates
		j = 0;	// toFlag = 0 : add to discard
		int preHand = G.handCount[G.whoseTurn];
		int preDeck = G.deckCount[G.whoseTurn];
		int preDiscard = G.discardCount[G.whoseTurn];
#if(NOISY_TEST ==1)
		printf("Before gainCard() for card %s with toFlag %d, player %d handcount = %d, deckCount = %d, discardCount = %d\n", cardNames[i], j, currentPlayer + 1, preHand, preDeck, preDiscard);
#endif
		//printf("supply count for card is %d\n", G.supplyCount[i]);
		testReturn = gainCard(i, &G, j, G.whoseTurn);
		printf(myAssert(testReturn == 0));
#if(NOISY_TEST ==1)
		printf("Return value is %d\n", testReturn);
		printf("After gainCard() with toFlag %d:\n",j);
		printf("Player %d handcount = %d, deckCount = %d, discardCount = %d\n",  currentPlayer + 1, G.handCount[G.whoseTurn], G.deckCount[G.whoseTurn], G.discardCount[G.whoseTurn]);
		printf("Expected player %d handcount = %d, deckCount = %d, discardCount = %d\n",  currentPlayer + 1, preHand, preDeck, preDiscard + 1);
#endif
		printf(myAssert(G.handCount[G.whoseTurn] == preHand));
		printf(myAssert(G.deckCount[G.whoseTurn] == preDeck));
		printf(myAssert(G.discardCount[G.whoseTurn] == preDiscard + 1));

#if(NOISY_TEST ==1)
		printf("\n");
#endif
		//check that no other player's discard deck changes

		for (currentPlayer = 1; currentPlayer < numPlayer; currentPlayer++)
		{
			int preHand = G.handCount[currentPlayer];
			int preDeck = G.deckCount[currentPlayer];
			int preDiscard = G.discardCount[currentPlayer];
#if(NOISY_TEST ==1)
			printf("Before gainCard() for card %s with toFlag %d, player %d handcount = %d, deckCount = %d, discardCount = %d\n", cardNames[i], j, currentPlayer + 1, preHand, preDeck, preDiscard);
#endif
			testReturn = gainCard(i, &G, j, G.whoseTurn);
			printf(myAssert(testReturn == 0));
#if(NOISY_TEST ==1)
			printf("Return value is %d\n", testReturn);
			printf("After gainCard() with toFlag %d:\n",j);
			printf("Player %d handcount = %d, deckCount = %d, discardCount = %d\n", currentPlayer + 1, G.handCount[currentPlayer], G.deckCount[currentPlayer], G.discardCount[currentPlayer]);
			printf("Expected player %d handcount = %d, deckCount = %d, discardCount = %d\n",  currentPlayer + 1, preHand, preDeck, preDiscard);
#endif
			printf(myAssert(G.handCount[currentPlayer] == preHand));
			printf(myAssert(G.deckCount[currentPlayer] == preDeck));
			printf(myAssert(G.discardCount[currentPlayer] == preDiscard));
#if(NOISY_TEST ==1)
			printf("\n");
#endif
		}

	}

	printf("\n");
	printf("----------------------------------------------------------------------------------=-\n");
	printf("TEST 3 -TESTING toFlag 1 updates current player's deck, not other player card piles:\n");
	printf("-----------------------------------------------------------------------------------=\n");
	printf("\n");

	//Initialize game and test gainCard()
	//USING K1 SET OF KINGDOM CARDS BUT WILL FILL SUPPLYCOUNT WITH ALL CARDS FOR TESTING
	initializeGame(numPlayer, k1, seed, &testG);
	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG remains in original state


#if(NOISY_TEST ==1)
	printf("Player %d is current player.\n", G.whoseTurn + 1);
#endif
	//set all cards in supplyCount to 30, for each card, call gainCard() for each player with each toFlag
	// toFlag = 0 : add to discard
	// toFlag = 1 : add to deck
	// toFlag = 2 : add to hand

	for (i = 0; i < 27; i++)
	{
		G.supplyCount[i] = 30;
		//printf("Card %s count is %d\n", cardNames[i], G.supplyCount[i]);
	}
	for (i = 0; i < 27; i++)
	{
		G.whoseTurn = 0;
		currentPlayer = G.whoseTurn;
		//check that current player's discard pile updates
		j = 1;	// toFlag = 0 : add to discard
		int preHand = G.handCount[G.whoseTurn];
		int preDeck = G.deckCount[G.whoseTurn];
		int preDiscard = G.discardCount[G.whoseTurn];
#if(NOISY_TEST ==1)
		printf("Before gainCard() for card %s with toFlag %d, player %d handcount = %d, deckCount = %d, discardCount = %d\n", cardNames[i], j, currentPlayer + 1, preHand, preDeck, preDiscard);
#endif
		//printf("supply count for card is %d\n", G.supplyCount[i]);
		testReturn = gainCard(i, &G, j, G.whoseTurn);
		printf(myAssert(testReturn == 0));
#if(NOISY_TEST ==1)
		printf("Return value is %d\n", testReturn);
		printf("After gainCard() with toFlag %d:\n",j);
		printf("Player %d handcount = %d, deckCount = %d, discardCount = %d\n", currentPlayer + 1, G.handCount[G.whoseTurn], G.deckCount[G.whoseTurn], G.discardCount[G.whoseTurn]);
		printf("Expected player %d handcount = %d, deckCount = %d, discardCount = %d\n",  currentPlayer + 1, preHand, preDeck + 1, preDiscard);
#endif
		printf(myAssert(G.handCount[G.whoseTurn] == preHand));
		printf(myAssert(G.deckCount[G.whoseTurn] == preDeck + 1));
		printf(myAssert(G.discardCount[G.whoseTurn] == preDiscard));
#if(NOISY_TEST ==1)
		printf("\n");
#endif

		//check that no other player's discard deck changes

		for (currentPlayer = G.whoseTurn + 1; currentPlayer < numPlayer; currentPlayer++)
		{
			int preHand = G.handCount[currentPlayer];
			int preDeck = G.deckCount[currentPlayer];
			int preDiscard = G.discardCount[currentPlayer];
#if(NOISY_TEST ==1)
			printf("Before gainCard() with toFlag %d, player %d handcount = %d, deckCount = %d, discardCount = %d\n", j, currentPlayer + 1, preHand, preDeck, preDiscard);
#endif
			testReturn = gainCard(i, &G, j, G.whoseTurn);
			printf(myAssert(testReturn == 0));
#if(NOISY_TEST ==1)
			printf("Return value is %d\n", testReturn);
			printf("After gainCard() with toFlag %d:\n",j);
			printf("Player %d handcount = %d, deckCount = %d, discardCount = %d\n",  currentPlayer + 1, G.handCount[currentPlayer], G.deckCount[currentPlayer], G.discardCount[currentPlayer]);
			printf("Expected player %d handcount = %d, deckCount = %d, discardCount = %d\n",  currentPlayer + 1, preHand, preDeck, preDiscard);
#endif
			printf(myAssert(G.handCount[currentPlayer] == preHand));
			printf(myAssert(G.deckCount[currentPlayer] == preDeck));
			printf(myAssert(G.discardCount[currentPlayer] == preDiscard));
#if(NOISY_TEST ==1)
			printf("\n");
#endif
		}
	}
	printf("\n");
	printf("-------------------------------------------------------------------------------------\n");
	printf("TEST 4 - TESTING toFlag 2 updates current player's hand, not other player card piles:\n");
	printf("-------------------------------------------------------------------------------------\n");
	printf("\n");

	//Initialize game and test gainCard()
	//USING K1 SET OF KINGDOM CARDS BUT WILL FILL SUPPLYCOUNT WITH ALL CARDS FOR TESTING
	initializeGame(numPlayer, k1, seed, &testG);
	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG remains in original state


												  //test isGameOver on newly initialized game
#if(NOISY_TEST ==1)
	printf("Player %d is current player.\n", G.whoseTurn + 1);
#endif
	//set all cards in supplyCount to 30, for each card, call gainCard() for each player with each toFlag
	// toFlag = 0 : add to discard
	// toFlag = 1 : add to deck
	// toFlag = 2 : add to hand

	for (i = 0; i < 27; i++)
	{
		G.supplyCount[i] = 30;
		//printf("Card %s count is %d\n", cardNames[i], G.supplyCount[i]);
	}
	G.whoseTurn = 0;
	for (i = 0; i < 27; i++)
	{
		G.whoseTurn = 0;
		currentPlayer = G.whoseTurn;
		//check that current player's discard pile updates
		j = 2;	// toFlag = 0 : add to discard
		int preHand = G.handCount[G.whoseTurn];
		int preDeck = G.deckCount[G.whoseTurn];
		int preDiscard = G.discardCount[G.whoseTurn];
#if(NOISY_TEST ==1)
		printf("Before gainCard() for card %s with toFlag %d, player %d handcount = %d, deckCount = %d, discardCount = %d\n", cardNames[i], j, currentPlayer + 1, preHand, preDeck, preDiscard);
#endif
		//printf("supply count for card is %d\n", G.supplyCount[i]);
		testReturn = gainCard(i, &G, j, G.whoseTurn);
		printf(myAssert(testReturn == 0));
#if(NOISY_TEST ==1)
		printf("Return value is %d\n", testReturn);
		printf("After gainCard() with toFlag %d:\n",j);
		printf("Player %d handcount = %d, deckCount = %d, discardCount = %d\n",  currentPlayer + 1, G.handCount[G.whoseTurn], G.deckCount[G.whoseTurn], G.discardCount[G.whoseTurn]);
		printf("Expected player %d handcount = %d, deckCount = %d, discardCount = %d\n",  currentPlayer + 1, preHand, preDeck, preDiscard + 1);
#endif
		printf(myAssert(G.handCount[G.whoseTurn] == preHand + 1));
		printf(myAssert(G.deckCount[G.whoseTurn] == preDeck));
		printf(myAssert(G.discardCount[G.whoseTurn] == preDiscard));
#if(NOISY_TEST ==1)
		printf("\n");
#endif

		//check that no other player's discard deck changes

		for (currentPlayer = 1; currentPlayer < numPlayer; currentPlayer++)
		{
			int preHand = G.handCount[currentPlayer];
			int preDeck = G.deckCount[currentPlayer];
			int preDiscard = G.discardCount[currentPlayer];
#if(NOISY_TEST ==1)
			printf("Before gainCard() with toFlag %d, player %d handcount = %d, deckCount = %d, discardCount = %d\n", j, currentPlayer + 1, preHand, preDeck, preDiscard);
#endif
			testReturn = gainCard(i, &G, j, G.whoseTurn);
			printf(myAssert(testReturn == 0));
#if(NOISY_TEST ==1)
			printf("Return value is %d\n", testReturn);
			printf("After gainCard() with toFlag %d\n",j);
			printf("Player %d handcount = %d, deckCount = %d, discardCount = %d\n", currentPlayer + 1, G.handCount[currentPlayer], G.deckCount[currentPlayer], G.discardCount[currentPlayer]);
			printf("Expected player %d handcount = %d, deckCount = %d, discardCount = %d\n", currentPlayer + 1, preHand, preDeck, preDiscard);
#endif
			printf(myAssert(G.handCount[currentPlayer] == preHand));
			printf(myAssert(G.deckCount[currentPlayer] == preDeck));
			printf(myAssert(G.discardCount[currentPlayer] == preDiscard));
#if(NOISY_TEST ==1)
			printf("\n");
#endif
		}
	}
	

	printf("\nAll tests passed!\n");

	return 0;
}
