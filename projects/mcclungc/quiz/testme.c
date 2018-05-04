#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function

	//characters needed to match conditions are in ASCII range 32 - 125
	int maxValue = 125; 
	int minValue = 32;
	int randomInt = (rand() % (maxValue - minValue + 1)) + minValue;
	return (char)(randomInt);
}

char *inputString()
{
    // TODO: rewrite this function

	//initialize string of correct length	
	char randomString[6];
	memset(randomString, '\0', 6);

	//lowercase alphabet from e to t is in ASCII range 101 - 116	
	int maxValue = 116;
	int minValue = 101;

	int i;
	for (i = 0; i < 5; i++)
	{
		// assign random lowercase char at index i
		randomString[i]= (char)((rand() % (maxValue - minValue + 1)) + minValue);
	}
	char *ptrRandomString = randomString;
	return ptrRandomString;

}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;

  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
   	printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }

}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
