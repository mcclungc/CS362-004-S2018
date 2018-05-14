/* -----------------------------------------------------------------------
* Connie McClung - Random Adventurer Card Test 
* randomtestadventurer.c
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
* randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
*      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
* -----------------------------------------------------------------------
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
	//	getchar();
		return msg;
	}
	else
	{
		passCounter++;
		char* msg = "Test passed!\n";
		return msg;
	}
}

void randomTestAdventurer(int player, struct gameState *randomStatePost) {
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int handPos = 0;
	struct gameState randomStatePre;
	randomStatePost->whoseTurn = player;
	char* returnmsg;
	
	int preDeckTreasure = 0;
	int preHandTreasure = 0;
	int preDiscardTreasure = 0;
	int i,j,k;

	//copy game state so there is a previous state for comparision
	memcpy(&randomStatePre, randomStatePost, sizeof(struct gameState));

	//printf("PRE Adventurer card effect player %d: handcount %d, deckcount %d, discardcount %d\n"
	//	, player + 1, randomStatePre.handCount[player], randomStatePre.deckCount[player], 
		//randomStatePre.discardCount[player]);
	
	//count treasure cards in player's hand and deck before running card effect
	//so you can tell correct treasure amount was added to hand 
	for (i = 0; i < randomStatePost->handCount[player];i++)
	{
		if (randomStatePost->hand[player][i] == silver || randomStatePost->hand[player][i] == gold ||
			randomStatePost->hand[player][i] == copper)
		{
			preHandTreasure++;
		}
	}
	for (j = 0; j < randomStatePost->deckCount[player];j++)
	{
		if (randomStatePost->deck[player][j] == silver || randomStatePost->deck[player][j] == gold ||
			randomStatePost->deck[player][j] == copper)
		{
			preDeckTreasure++;
		}
	}
	for (k = 0; k < randomStatePost->deckCount[player];k++)
	{
		if (randomStatePost->discard[player][k] == silver || randomStatePost->discard[player][k] == gold ||
			randomStatePost->discard[player][k] == copper)
		{
			preDiscardTreasure++;
		}
	}

	//printf("Before call to adventurer card effect, player has %d treasure cards in hand\n", preHandTreasure);
	//printf("Before call to adventurer card effect, player has %d treasure cards in deck\n", preDeckTreasure);
	//printf("Before call to adventurer card effect, player has %d treasure cards in discard pile\n", preDiscardTreasure);

	int returnValue;
	returnValue = cardEffect(adventurer, choice1, choice2, choice3, randomStatePost, handPos, &bonus);

	returnmsg = myAssert(returnValue == 0);
	if (strcmp(returnmsg,"TEST FAILED!\n" )==0)
	{
		printf("Return value for adventurer card effect, player %d: ", player + 1);
		printf(returnmsg);
	}

	if ((preDeckTreasure + preDiscardTreasure) == 1) { //if only one treasure card available, only add 1
		returnmsg = myAssert(randomStatePost->handCount[player] == (randomStatePre.handCount[player] + 1));
		if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
		{
			printf("Hand count increased by correct # of treasure cards: ");
			printf(returnmsg);
		}
		int postOtherDeck = randomStatePost->deckCount[player] + randomStatePost->discardCount[player];
		int preOtherDeck = (randomStatePre.deckCount[player] + randomStatePre.discardCount[player]) -1;
		returnmsg = myAssert(postOtherDeck == preOtherDeck);
		if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
		{
			printf("Deck + discard pile total count decreased by correct # (1 treasure card in deck or discard pile): ");
			printf(returnmsg);
		}
		
	}
	else if ((preDeckTreasure >=2) || ((preDeckTreasure + preDiscardTreasure) >=2)) //if 2+ treasure cards available, add 2
	{
		returnmsg = myAssert(randomStatePost->handCount[player] == (randomStatePre.handCount[player] + 2));
		if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
		{
			printf("Hand count increased by correct # of treasure cards: ");
			printf(returnmsg);
		}
		//check to be sure total of other piles decreases by correct amount
		int postOtherDeck = randomStatePost->deckCount[player] + randomStatePost->discardCount[player];
		int preOtherDeck = (randomStatePre.deckCount[player] + randomStatePre.discardCount[player]) - 2;
		returnmsg = myAssert(postOtherDeck == preOtherDeck);
		if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
		{
			printf("Deck + discard pile total count decreased by correct # (2+ treasure cards in deck or discard pile): ");
			printf(returnmsg);
		}
	}
	else if ((preDeckTreasure + preDiscardTreasure) < 1)//this would never happen in real game but possibly in random test there could be 0 treasure cards in player deck
	{
		returnmsg = myAssert(randomStatePost->handCount[player] == randomStatePre.handCount[player]);
		if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
		{
			printf("Hand count increased by correct # of treasure cards: ");
			printf(returnmsg);
		}
		//check to be sure total of other piles decreases by correct amount
		int postOtherDeck = randomStatePost->deckCount[player] + randomStatePost->discardCount[player];
		int preOtherDeck = randomStatePre.deckCount[player] + randomStatePre.discardCount[player];
		returnmsg = myAssert(postOtherDeck == preOtherDeck);
		if (strcmp(returnmsg, "TEST FAILED!\n") == 0)
		{
			printf("Deck + discard pile total count decreased by correct # (0 treasure cards in deck or discard pile): ");
			printf(returnmsg);
		}
	}
	//printf("POST adventurer card effect player %d: handcount %d, deckcount %d, discardcount %d\n"
		//, player + 1, randomStatePost->handCount[player], randomStatePost->deckCount[player],
		//randomStatePost->discardCount[player]);
	//printf("\n");
}



int main() {
	srand((unsigned int)time(NULL));
	int i,j, m, n, p;

	int seed = 999;

	int k[10] = { adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall };

	struct gameState G;

	printf("Testing Adventurer card.\n");

	printf("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);
	int numIterations = 5000;

	for (n = 0; n < numIterations; n++) {
		//printf("n = %d\n", n);
		p = (rand() % (MAX_PLAYERS - 1 + 1)) + 1;

		//printf("There are %d players in this game.\n", p);
		initializeGame(MAX_PLAYERS, k, seed, &G);
		int player;
		for (player = 0; player < p; player++)
		{
			int maxValue = 26;
			int minValue = 0;
			//random numbers for number of cards to draw for each player's hand and decks
			int addCardsDeck = (rand() % (MAX_DECK- 1 + 1)) + 1;
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
				G.discard[player][j] = randomInt; //number of cards in ENUM
				G.discardCount[player]++;
			}
			for (m = G.handCount[player]; m < addCardsHand; m++)
			{
				int randomInt = (rand() % (maxValue - minValue + 1)) + minValue;
				G.hand[player][m] = randomInt; //number of cards in ENUM
				G.handCount[player]++;
			}
				randomTestAdventurer(player, &G);
		}
	}

	printf("\nRANDOM TESTS COMPLETE\n");
	printf("Seed: %d\n", seed);
	printf("Number of iterations: %d\n", numIterations);
	printf("Tests passed: %d\n", passCounter);
	printf("Tests failed: %d\n", failCounter);

	return 0;
}
