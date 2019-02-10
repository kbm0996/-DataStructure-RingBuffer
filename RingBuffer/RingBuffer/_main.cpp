#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include "CRingBuffer.h"

#include <conio.h>


void main()
{
	srand((unsigned int)time(NULL));
	CRingBuffer* RingBuffer = new CRingBuffer(83);
	char* inbuff = "1234567890 abcdefghijklmnopqrstuvwxyz 1234567890 abcdefghijklmnopqrstuvwxyz 1234q";
	char* inbuff2 = "54321 zyxwvutsrqponmlkjihgfedcba 0987654321 zyxwvutsrqponmlkjihgfedcba 0987654321";

	char peekbuff[82];
	char outbuff[82];

	int size;
	int size2;
	int len;

	while (1)
	{
		size = rand() % 81 + 1;
		size2 = 81 - size;

		RingBuffer->Enqueue(inbuff, 81);

		////////////////////////////////////////////////////
		// 1 임의의 크기 만큼 출력

		memset(outbuff, 0, sizeof(outbuff));
		memset(peekbuff, 0, sizeof(peekbuff));
		
		RingBuffer->Peek(peekbuff, size);
		RingBuffer->Dequeue(outbuff, size);

		// peek과 dequeue 결과 비교
		//if (memcmp(peekbuff, outbuff, size) == 0)
		//	printf(outbuff);
		//else
		//	break;

		

		////////////////////////////////////////////////////
		// 2 남은 크기 마저 출력

		memset(outbuff, 0, sizeof(outbuff));
		memset(peekbuff, 0, sizeof(peekbuff));
		
		RingBuffer->Peek(peekbuff, size2);
		RingBuffer->Dequeue(outbuff, size2);

		// peek과 dequeue 결과 비교
		//if (memcmp(peekbuff, outbuff, size2) == 0)
		//	printf(outbuff);
		//else
		//	break;

		// 두번째 출력 데이터와 해당 부분인 입력 데이터 지점이 같은지 
		if (memcmp(peekbuff, inbuff+size, size2) == 0)
			printf(peekbuff);
		else
			break;

	}
	return;
}