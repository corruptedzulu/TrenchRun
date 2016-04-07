#include "stdafx.h"
#include <stdint.h>
#include "utils.h"


//int log2(uint64_t query)
//{
//	static const int MultiplyDeBruijnBitPosition2[32] =
//	{
//		0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
//		31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
//	};
//
//	return MultiplyDeBruijnBitPosition2[(uint64_t)(query * 0x077CB531U) >> 27];
//}



int log2_64(uint64_t value)
{
	/*value |= value >> 1;
	value |= value >> 2;
	value |= value >> 4;
	value |= value >> 8;
	value |= value >> 16;
	value |= value >> 32;*/

	return tab64[((uint64_t)((value - (value >> 1)) * 0x07EDD5E59A4E28C2)) >> 58];
	//return tab64[(uint64_t)(value * 0x07EDD5E59A4E28C2) >> 58];
}