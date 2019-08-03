#include <stdio.h>
#include <stdlib.h>

int NUM_ITERATIONS 		= 10000; // define number of iteratios to average over
int NUM_ELEMENTS 		= 100; // define number of elements to randomly place in the array
int MIN_RND_VALUE 		= 1000; // minimum salary
int MAX_RND_VALUE 		= 5000; // maximum salary

int main()
{
	/*
		Create "job offers" with varying salaries into nOffersArray.
		Then use the 37% rule to solve choosing the best possible offer on the spot (optimal stopping)

		Do this over n iterations and average out the scores. This will result in a 37% chance of
		picking the best possible job offer no matter how many offers are presented in the current set,
		while the chance of picking the correct one randomly would end up with the following propabilities:

		1 offer = 100%
		2 offers = 50%
		3 offers = 33.3333%
		10 offers = 10%
		...
		100 offers = 1%
	*/

	static const double s_flMagic = 0.37; // amount of items to iterate before selecting the next best option

	int* nOffersArray = malloc(sizeof(int) * NUM_ELEMENTS); // allocate NUM_ELEMENTS integers

	int nTimesFound = 0; // how many times was the best offer found
	for (int i = 0; i < NUM_ITERATIONS; ++i) // iterate over n times
	{
		srand((i + 1) * NUM_ITERATIONS + (i + 1) + 4); // set random seed to something reproducable

		// randomize items to the array
		for (int j = 0; j < NUM_ELEMENTS; ++j)
			nOffersArray[j] = (rand() % (MAX_RND_VALUE - MIN_RND_VALUE)) + MIN_RND_VALUE;

		int nHighestSeen = -1; // highest offer seen so far
		int nSelectedOffer = -1; // selected offer
		for (int j = 0; j < NUM_ELEMENTS; ++j) // iterate over each item
		{
			double flPercentageIterated = (double)(j + 1) / (double)NUM_ELEMENTS; // percentage iterated

			if (flPercentageIterated > s_flMagic && nOffersArray[j] > nHighestSeen)
			{
				// optimal stopping point reached
				nSelectedOffer = j;
				break; // stop now! we are taking this one.
			}
			else
			{
				// store the best value seen so far
				if (nHighestSeen < nOffersArray[j])
					nHighestSeen = nOffersArray[j];
			}
		}

		// check if we found the highest offer
		if (nSelectedOffer != -1)
		{
			// we selected an offer, check it
			int nVerifiedHighestValue = -1;
			int nVerifiedHighestIndex = -1;
			for (int j = 0; j < NUM_ELEMENTS; ++j)
			{
				if (nOffersArray[j] > nVerifiedHighestValue)
				{
					nVerifiedHighestValue = nOffersArray[j];
					nVerifiedHighestIndex = j;
				}
			}

			if(nVerifiedHighestIndex == nSelectedOffer) // was the best one found?
				++nTimesFound; // increment times found
		}

		printf("It. %i (success rate=%.4f)\n", i, (float)nTimesFound / (float)NUM_ITERATIONS);
	}

	float flSuccessAvg = (float)nTimesFound / (float)NUM_ITERATIONS; // average success percentage
	printf("Success percentage = %.4f (%i out of %i)\n", flSuccessAvg, nTimesFound, NUM_ITERATIONS);

	free(nOffersArray); // free allocated memory
	return 0;
}
