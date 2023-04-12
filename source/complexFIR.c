
#include <stdio.h>
#include <math.h>
#include <complex.h>

/**
 * @brief 
 * 
 * @param datasetLength 
 * @param filterLength 
 * @param data 
 * @param filter 
 */

void complexFIR(int dataLength, int filterLength, int ** data, int ** filter)
{
//	int ** filterCoeffs = (int**)malloc(filterLength * sizeof(int*)); //!< Filter coefficent storage space. Avoids needing connection to "filter" all the time
	int ** filterCoeffs;
	int ** rawOutput; //!< Single element output of the filter

	//Load complex coefficients
	for(int i = 0; i < filterLength; i++)
	{
		for(int j = 0; j < filterLength; j++)
		{
			filterCoeffs[i][j] = filter[i][j];
		}
	}

	//Run the FIR filter
	for(int k = 0; k < dataLength; k++)
	{
		for(int j = 0; j < dataLength; j++)
		{
			computeComplexFIR(dataLength, filterLength, data[i][j], filter, rawOutput);
			data[k][j] = **rawOutput;
//			printf("Re = %d, Im = %d", rawOutpu
		}
	}

	free(filterCoeffs); //Free the filterCoeffs to avoid a memory leakage
}


/**
 * @brief 
 * 
 * @param datasetLength 
 * @param filterLength 
 * @param input 
 * @param filter 
 * @param output 
 */
void computeComplexFIR(int datasetLength, int filterLength, int input, int ** filter, int ** output)
{
    static int ** delayLine;
    int ** result; // = 0, technically.

    for(int i = filterLength; i > 0; i--)
    {
        for(int j = filterLength; i > 0; i--)
        {
            delayLine[i][j] = delayLine[i - 1][j - 1];
        }   
    }
    delayLine[0][0] = input;

    for(int k = 0; k < filterLength; k++)
    {
        for(int j = 0; j < filterLength; j++)
        {
            result[0][0] += delayLine[k][j] * filter[k][j];
        }
    }

    **output = **result;
}
