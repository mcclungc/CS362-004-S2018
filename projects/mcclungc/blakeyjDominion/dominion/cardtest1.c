/* -----------------------------------------------------------------------
* Connie McClung - card Test 1
* cardtest1.c
*
* Tests basic operations of Adventurer card
* 1. Reveal cards from current player's deck until 2 treasure cards are revealed
* 2. Add 2 revealed treasure cards to hand, discard other revealed cards
* 3. If deck runs out of cards while digging for treasure, shuffle discard pile into deck (not including revealed cards)
* 4. If only 1 treasure card is revealed, only add 1 treasure card to hand
*
* -----------------------------------------------------------------------
*/
/*
* Include the following lines in your makefile:
*
* cardtest1: cardtest1.c dominion.o rngs.o
*      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Adventurer"

//helper function to count a treasure card type in player hand
int countTreasureCardInHand(int card, int player, struct gameState state) {
	int treasureCount = 0;
	int i;
	//get starting count of a treasure card in deck
	for (i = 0; i < state.handCount[player]; i++)
	{
		if (state.hand[player][i] == card) treasureCount++;
	}
	return treasureCount;
}

//helper function to count a treasure card type in player deck
int countTreasureCardInDeck(int card, int player, struct gameState state) {
	int treasureCount = 0;
	int i;
	//get starting count of a treasure card in deck
	for (i = 0; i < state.deckCount[player]; i++)
	{
		if (state.deck[player][i] == card) treasureCount++;
	}
	return treasureCount;
}

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
	int i;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayer = 4;
	int currentPlayer = 0;
	struct gameState G, testG; 
	int k1[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	//int k2[10] = { minion, steward, tribute, ambassador, cutpurse, embargo
	//	, outpost, salvager, sea_hag, treasure_map };

	int addedTreasure;
	//int startHandCount = 5;
	int startTreasureCount = 0;

	//TEST 1
	//testing in a game with k1 kingdom card set
	initializeGame(numPlayer, k1, seed, &testG);


	printf("----------------- TESTING: %s ----------------\n", TESTCARD);

	// TEST 1: with treasure cards in deck, 2 treasure cards are added, other revealed discarded
	printf("\n");
	printf("---------------------------------------------------------------------\n");
	printf("TEST 1: at least 2 copper treasure cards are in deck\n");
	printf("---------------------------------------------------------------------\n");

	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG stays unchanged

	addedTreasure = 2;
	startTreasureCount = countTreasureCardInHand(copper, currentPlayer, testG); //how many treasure in hand before
	printf("Starting treasure count is %d\n", startTreasureCount);
	printf("Calling cardEffect for Adventurer...\n");
	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

	//check that 2 cards were added to hand since we know there are at least 2 treasure cards in deck
	printf("Hand count = %d, expected = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer] + addedTreasure);
	printf(myAssert(G.handCount[currentPlayer] == testG.handCount[currentPlayer] + addedTreasure));
	int newTreasureCount = countTreasureCardInHand(copper, currentPlayer, G);
	printf("Treasure in hand count = %d, expected = %d\n", newTreasureCount , startTreasureCount + addedTreasure);
	printf(myAssert(newTreasureCount == startTreasureCount + addedTreasure));

	//check no other player hands were changed
	for (i = currentPlayer + 1; i < numPlayer; i++)
	{
		printf("Hand count player %d  = %d, expected = %d\n", i + 1, G.handCount[i], testG.handCount[i]);
		printf(myAssert(G.handCount[i] == testG.handCount[i]));
	}

	printf("\n");
	
	//TEST 2
	//testing in a game with k1 kingdom card set
	initializeGame(numPlayer, k1, seed, &testG);


	//printf("----------------- TESTING: %s ----------------\n", TESTCARD);

	// TEST 2: only 1 card in deck, reshuffle from discard pile required
	printf("\n");
	printf("---------------------------------------------------------------------\n");
	printf("TEST 2: only 1 copper card in deck, reshuffle from discard pile required\n");
	printf("---------------------------------------------------------------------\n");

	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG stays unchanged

	startTreasureCount = countTreasureCardInHand(copper, currentPlayer, testG);
	printf("Starting treasure count is %d\n", startTreasureCount); // we know only copper in hand, so this is valid count

	//decrement deck until only 1 card
	//printf("Starting player deck count is %d\n", G.deckCount[currentPlayer]);
	printf("Removing all but 1 card from player's deck...\n");
	for (i = 1; i < 5; i++) //move all but 1 card from player's deck to discard pile
	{
		G.discard[currentPlayer][G.discardCount[currentPlayer]] = G.deck[currentPlayer][G.deckCount[currentPlayer] - 1];
		G.discardCount[currentPlayer]++;
		G.deck[currentPlayer][G.deckCount[currentPlayer] - 1] = -1;
		//reduce number of cards in hand
		G.deckCount[currentPlayer]--;
	}

	printf("Player deck count is now %d\n", G.deckCount[currentPlayer]);
	printf("Calling cardEffect for Adventurer...\n");
	addedTreasure = 2;
	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

	//check that 2 cards were added to hand since we know there are at least 2 treasure cards in deck
	printf("Hand count = %d, expected = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer] + addedTreasure);
	printf(myAssert(G.handCount[currentPlayer] == testG.handCount[currentPlayer] + addedTreasure));
	newTreasureCount = countTreasureCardInHand(copper, currentPlayer, G);
	printf("Treasure in hand count = %d, expected = %d\n", newTreasureCount, startTreasureCount + addedTreasure);
	printf(myAssert(newTreasureCount == startTreasureCount + addedTreasure));

	//TEST 3
	//printf("TESTING  in a game with k1 kingdom card set:\n");
	initializeGame(numPlayer, k1, seed, &testG);


	//printf("----------------- TESTING: %s ----------------\n", TESTCARD);

	// TEST 3: only 1 treasure card available in deck
	printf("\n");
	printf("---------------------------------------------------------------------\n");
	printf("TEST 3: only 1 copper treasure card available in any deck\n");
	printf("---------------------------------------------------------------------\n");


	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG stays unchanged

	int startTreasureCountHand = countTreasureCardInHand(copper, currentPlayer, testG);
	printf("Starting treasure count in player's hand is %d\n", startTreasureCountHand); // we know only copper in hand, so this is valid count

	int startTreasureCountDeck = countTreasureCardInDeck(copper, currentPlayer, testG);
	printf("Starting treasure count in deck is %d\n", startTreasureCountDeck); // we know only copper in hand, so this is valid count

	printf("Removing all but 1 treasure card from player's deck...\n");
	int allowedTreasure = 0;
	for (i = 0; i < 5; i++) //remove all but 1 card from player's deck to discard pile
	{
		if (G.deck[currentPlayer][i] == copper)
		{
			allowedTreasure++;
			if (allowedTreasure > 1)
			{
				G.deck[currentPlayer][i] = estate; //change copper to estate
			}
		}

	}
	int newTreasureCountDeck = countTreasureCardInDeck(copper, currentPlayer, G);
	printf("New treasure count in deck is %d\n", newTreasureCountDeck); 


	printf("Calling cardEffect for Adventurer...\n");

	addedTreasure = 1;
	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

	//check that only 1 card was added to hand since we know there is only 1 treasure card in deck
	printf("Hand count = %d, expected = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer] + addedTreasure);
	printf(myAssert(G.handCount[currentPlayer] == testG.handCount[currentPlayer] + addedTreasure));
	newTreasureCount = countTreasureCardInHand(copper, currentPlayer, G);
	printf("Treasure in hand count = %d, expected = %d\n", newTreasureCount, startTreasureCount + addedTreasure);
	printf(myAssert(newTreasureCount == startTreasureCount + addedTreasure));

	//TEST 4
	//testing in a game with k1 kingdom card set
	initializeGame(numPlayer, k1, seed, &testG);


	printf("----------------- TESTING: %s ----------------\n", TESTCARD);

	// TEST 4: Test for silver or gold cards in player deck
	printf("\n");
	printf("---------------------------------------------------------------------\n");
	printf("TEST 4: silver or gold treasure cards in player deck\n");
	printf("---------------------------------------------------------------------\n");

	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG stays unchanged
	for (i = 0; i < G.deckCount[currentPlayer]; i++)
	{
		G.deck[currentPlayer][i] = silver;
	}

	addedTreasure = 2;
	startTreasureCountHand = countTreasureCardInHand(silver, currentPlayer, G);
	printf("Starting silver treasure count in player's hand is %d\n", startTreasureCountHand); 

	startTreasureCountDeck = countTreasureCardInDeck(silver, currentPlayer, G);
	printf("Starting silver treasure count in deck is %d\n", startTreasureCountDeck);
	printf("Calling cardEffect for Adventurer...\n");
	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

	//check that 2 cards were added to hand since we know there are at least 2 treasure cards in deck
	printf("Hand count = %d, expected = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer] + addedTreasure);
	printf(myAssert(G.handCount[currentPlayer] == testG.handCount[currentPlayer] + addedTreasure));
	newTreasureCount = countTreasureCardInHand(silver, currentPlayer, G);
	printf("Treasure in hand count = %d, expected = %d\n", newTreasureCount, startTreasureCountHand + addedTreasure);
	printf(myAssert(newTreasureCount == startTreasureCountHand + addedTreasure));

	//check no other player hands were changed
	for (i = currentPlayer + 1; i < numPlayer; i++)
	{
		printf("Hand count player %d  = %d, expected = %d\n", i + 1, G.handCount[i], testG.handCount[i]);
		printf(myAssert(G.handCount[i] == testG.handCount[i]));
	}
	printf("\n");

	initializeGame(numPlayer, k1, seed, &testG);
	//copy gamestate to testG so you can compare before and after
	memcpy(&G, &testG, sizeof(struct gameState)); //testG stays unchanged

	for (i = 0; i < G.deckCount[currentPlayer]; i++)
	{
		G.deck[currentPlayer][i] = gold;
	}
	addedTreasure = 2;
	//startTreasureCount = countTreasureCardInHand(gold, currentPlayer, testG); //how many treasure in hand before
	//printf("Starting gold treasure count is %d\n", startTreasureCount);
	startTreasureCountHand = countTreasureCardInHand(gold, currentPlayer, G);
	printf("Starting gold treasure count in player's hand is %d\n", startTreasureCountHand); // we know only copper in hand, so this is valid count

	startTreasureCountDeck = countTreasureCardInDeck(gold, currentPlayer, G);
	printf("Starting gold treasure count in deck is %d\n", startTreasureCountDeck); // we know only copper in hand, so this is valid count
	printf("Calling cardEffect for Adventurer...\n");
	cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

	//check that 2 cards were added to hand since we know there are at least 2 treasure cards in deck
	printf("Hand count = %d, expected = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer] + addedTreasure);
	printf(myAssert(G.handCount[currentPlayer] == testG.handCount[currentPlayer] + addedTreasure));
	newTreasureCount = countTreasureCardInHand(gold, currentPlayer, G);
	printf("Treasure in hand count = %d, expected = %d\n", newTreasureCount, startTreasureCountHand + addedTreasure);
	printf(myAssert(newTreasureCount == startTreasureCountHand + addedTreasure));

	//check no other player hands were changed
	for (i = currentPlayer + 1; i < numPlayer; i++)
	{
		printf("Hand count player %d  = %d, expected = %d\n", i + 1, G.handCount[i], testG.handCount[i]);
		printf(myAssert(G.handCount[i] == testG.handCount[i]));
	}


	printf("\n");


	printf("\n >>>>> Testing complete for %s <<<<<\n\n", TESTCARD);


	return 0;
}
