#ifndef INCLUDES
#define INCLUDES
#include <stdio.h>
#include <math.h>

#endif // Includes

#ifndef DEFINES
#define DEFINES

void complexFIR(int dataLength, int filterLength, int ** data, int ** filter);
void computeComplexFIR(int datasetLength, int filterLength, int input, int ** filter, int ** output);


#endif // Defines
