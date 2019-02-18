#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include "CRingBuffer.h"
#include <conio.h>
#include <Windows.h>
using namespace mylib;

#define df_TEST_DEQUEUE

#define _iSize 10
#define en_BUFFER_BLANK 4

void main()
{

	srand((unsigned int)time(NULL));
	CRingBuffer* RingBuffer = new CRingBuffer(83);
	char inbuff[] = "1234567890 abcdefghijklmnopqrstuvwxyz 1234567890 abcdefghijklmnopqrstuvwxyz 1234q";

	char peekbuff[82];
	char outbuff[82];

	int size;
	int size2;

	int enqlen;
	int peeklen;
	int deqlen;

	printf("GetFreeSize	%d \n", RingBuffer->GetFreeSize());
	printf("GetUseSize	%d \n", RingBuffer->GetUseSize());
	printf("GetSize	%d \n", RingBuffer->GetBufferSize());
	printf("GetUnbrokenDequeueSize	%d \n", RingBuffer->GetUnbrokenDequeueSize());
	printf("GetUnbrokenEnqueueSize	%d \n", RingBuffer->GetUnbrokenEnqueueSize());




	//printf("\n\nBlank %d, Size %d \n", en_BUFFER_BLANK, _iSize);
	//printf("Write	Read	result	result2\n");
	//
	//int result, result2;
	//for (int ir = 0; ir < _iSize; ++ir)
	//{
	//	for (int iw = 0; iw < _iSize; ++iw)
	//	{
	//		if (ir > iw)
	//		{
	//			result = ir - (iw + en_BUFFER_BLANK);
	//			if (result < 0)
	//				result = 0;
	//		}
	//		else
	//		{
	//			if (ir < en_BUFFER_BLANK)
	//			{
	//				result = _iSize - iw - (en_BUFFER_BLANK - ir);
	//				if (result < 0)
	//					result = 0;
	//			}
	//			else
	//				result =  _iSize - iw;
	//		}


	//		/////////////////
	//		if ((iw + en_BUFFER_BLANK) % _iSize == ir)
	//		{
	//			result2 = 0;
	//			printf("!");
	//		}
	//		else if (iw <= ((ir + _iSize - en_BUFFER_BLANK) % _iSize))
	//		{
	//			result2 = ((ir + _iSize - en_BUFFER_BLANK) % _iSize) - iw;
	//			printf("@");
	//		}
	//		else if (iw >= ir)
	//		{
	//			result2 = _iSize - iw;
	//			printf("#");
	//		}
	//		else
	//		{
	//			result2 = 0;
	//			printf("$");
	//		}


	//		if (result != result2)
	//		{
	//			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	//			printf("%d	%d	%d	%d\n", iw , ir, result, result2);
	//			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//		}
	//		else
	//			printf("%d	%d	%d	%d\n", iw, ir, result, result2);
	//	}
	//}
	//printf("끝\n\n");


	printf("\n");
	while (1)
	{
		size = rand() % 81 + 1;
		size2 = 81 - size;

		enqlen = RingBuffer->Enqueue(inbuff, sizeof(inbuff));
		enqlen = RingBuffer->Enqueue(inbuff, sizeof(inbuff));
		////////////////////////////////////////////////////
		// 1 임의의 크기 만큼 출력

		memset(outbuff, 0, sizeof(outbuff));
		memset(peekbuff, 0, sizeof(peekbuff));
		
		peeklen = RingBuffer->Peek(peekbuff, size);
		deqlen = RingBuffer->Dequeue(outbuff, size);

#ifdef df_TEST_DEQUEUE
		// peek과 dequeue 결과 비교
		if (memcmp(peekbuff, outbuff, size) == 0)
			printf(outbuff);
		else
			break;
#endif

		

		////////////////////////////////////////////////////
		// 2 남은 크기 마저 출력

		memset(outbuff, 0, sizeof(outbuff));
		memset(peekbuff, 0, sizeof(peekbuff));
		
		peeklen = RingBuffer->Peek(peekbuff, size2+10);	// 일부러 더 많이 뽑아보기	
		deqlen = RingBuffer->Dequeue(outbuff, size2+10);

#ifdef df_TEST_DEQUEUE
		// peek과 dequeue 결과 비교
		if (memcmp(peekbuff, outbuff, size2) == 0)
		{
			printf(outbuff);
		}
		else
			break;
#elif
		// 두번째 출력 데이터와 해당 부분인 입력 데이터 지점이 같은지 
		if (memcmp(peekbuff, inbuff+size, size2) == 0)
			printf(peekbuff);
		else
			break;
#endif

	}
	return;
}