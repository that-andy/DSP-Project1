#include "processing.h"
#include "iir.h"
#include <math.h>

#define FLT 32768

void calculateShelvingCoeff(float alpha, Int16* output)
{
	Int16 a;

	a = FLT * alpha;

	output[0] = a;
	output[1] = -1 * FLT;
	output[2] = 1*FLT - 1;
	output[3] = -a;

}

void calculatePeekCoeff(float alpha, float beta, Int16* output)
{
	Int16 a;
	Int16 b;

	a = FLT * alpha;
	b = FLT * alpha;

	output[0] = a;
	output[1] = -b * (1 + a);
	output[2] = 1 * FLT;
	output[3] = 1 * FLT;
	output[4] = -b * (1 + a);
	output[5] = a;

}

void shelvingHP(Int16* input, Int16* coeff, Int16* z_x, Int16* z_y, Int16 n, Int16 k, Int16* output)
{
	/* Your code here */
	int i;
	Int16 tmp;

	if( (k - 1) < 0)
	{
		for(i = 0; i < n; i++)
		{
			tmp = first_order_IIR(input, coeff, z_x, z_y);
			output = (( input[i] - tmp) >> 1) + (( input[i] + tmp) >> (k-1));

		}
	} else {

		for(i = 0; i < n; i++)
		{
			tmp = first_order_IIR(input, coeff, z_x, z_y);
			output = (( input[i] - tmp) >> 1) + (( input[i] + tmp) << (k-1));
		}
	}

}

void shelvingLP(Int16* input, Int16* coeff, Int16* z_x, Int16* z_y, Int16 n, Int16 k, Int16* output)
{
	int i;
	Int16 tmp;

	if( (k -1) < 0 )
	{
		for(i = 0; i < n; i++)
		{
			tmp = first_order_IIR(input, coeff, z_x, z_y);
			output =  (( input[i] - tmp) >> (k - 1)) + (( input[i] + tmp) >> 1);
		}

	} else {
		for(i = 0; i < n; i++)
		{
			tmp = first_order_IIR(input, coeff, z_x, z_y);
			output = (( input[i] - tmp) << (k - 1)) + (( input[i] +tmp) >> 1);
		}
	}

}

void shelvingPeek(Int16* input, Int16* coeff, Int z_x16*, Int16* z_y, Int16 n, Int16 k, Int16* output)
{
	/* Your code here */
}
