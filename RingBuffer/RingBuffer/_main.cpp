#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include "CRingBuffer.h"
#include <conio.h>

#include <Windows.h>
#define df_TEST_DEQUEUE

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
	printf("GetSize	%d \n", RingBuffer->GetSize());
	printf("GetUnbrokenDequeueSize	%d \n", RingBuffer->GetUnbrokenDequeueSize());
	printf("GetUnbrokenEnqueueSize	%d \n", RingBuffer->GetUnbrokenEnqueueSize());


	printf("\n");
	while (1)
	{
		size = rand() % 81 + 1;
		size2 = 81 - size;

		enqlen = RingBuffer->Enqueue(inbuff, sizeof(inbuff));
		////////////////////////////////////////////////////
		// 1 ������ ũ�� ��ŭ ���

		memset(outbuff, 0, sizeof(outbuff));
		memset(peekbuff, 0, sizeof(peekbuff));

		peeklen = RingBuffer->Peek(peekbuff, size);
		deqlen = RingBuffer->Dequeue(outbuff, size);

#ifdef df_TEST_DEQUEUE
		// peek�� dequeue ��� ��
		if (memcmp(peekbuff, outbuff, size) == 0)
			printf(outbuff);
		else
			break;
#endif



		////////////////////////////////////////////////////
		// 2 ���� ũ�� ���� ���

		memset(outbuff, 0, sizeof(outbuff));
		memset(peekbuff, 0, sizeof(peekbuff));

		peeklen = RingBuffer->Peek(peekbuff, size2 + 10);	// �Ϻη� �� ���� �̾ƺ���	
		deqlen = RingBuffer->Dequeue(outbuff, size2 + 10);

#ifdef df_TEST_DEQUEUE
		// peek�� dequeue ��� ��
		if (memcmp(peekbuff, outbuff, size2) == 0)
		{
			printf(outbuff);
		}
		else
			break;
#else
		// �ι�° ��� �����Ϳ� �ش� �κ��� �Է� ������ ������ ������ 
		if (memcmp(peekbuff, inbuff + size, size2) == 0)
			printf(peekbuff);
		else
		{
			printf(peekbuff);
			printf("\n");
			printf(inbuff + size);
			break;
		}
#endif

	}
	return;
}