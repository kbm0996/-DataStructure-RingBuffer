#include "CRingBuffer.h"
#include <Windows.h>

CRingBuffer::CRingBuffer(int iSize) : _iReadPos(0), _iWritePos(0), _iSize(iSize), _pBuffer(new char[iSize])
{
}

CRingBuffer::~CRingBuffer()
{
	if(_pBuffer != nullptr)
		delete[] _pBuffer;
	_pBuffer = nullptr;
}

void CRingBuffer::Clear()
{
	_iReadPos = 0;
	_iWritePos = 0;
}

int CRingBuffer::GetSize()
{
	return _iSize - en_BUFFER_BLANK;
}

int CRingBuffer::GetUseSize()
{
	if (_iReadPos > _iWritePos)
		return _iSize - _iReadPos + _iWritePos;
	else 
		return _iWritePos - _iReadPos;
}

int CRingBuffer::GetFreeSize()
{
	if (_iReadPos > _iWritePos)
		return _iReadPos - (_iWritePos + en_BUFFER_BLANK);
	else
		return _iSize - (_iWritePos + en_BUFFER_BLANK) + _iReadPos;
}

int CRingBuffer::GetUnbrokenEnqueueSize()
{
	if (_iReadPos > _iWritePos)
		return _iReadPos - (_iWritePos + en_BUFFER_BLANK);
	else
	{
		if (_iReadPos < en_BUFFER_BLANK)
		{
			int iRetval = _iSize - _iWritePos - (en_BUFFER_BLANK - _iReadPos);
			if (iRetval < 0) 
				return 0;

			return iRetval;
		}

		return _iSize - _iWritePos;
	}
}

int CRingBuffer::GetUnbrokenDequeueSize()
{
	if (_iReadPos > _iWritePos)
		return _iSize - _iReadPos;

	return _iWritePos - _iReadPos;
}

int CRingBuffer::Enqueue(char * pInData, int iSize)
{
	if (iSize <= 0)
		return 0;

	if (GetFreeSize() < iSize)
		iSize = GetFreeSize();

	int iEnqueueSize = GetUnbrokenEnqueueSize();
	if (iSize <= iEnqueueSize)
	{
		memcpy(_pBuffer + _iWritePos, pInData, iSize);
	}
	else
	{
		memcpy(_pBuffer + _iWritePos, pInData, iEnqueueSize);
		memcpy(_pBuffer, pInData + iEnqueueSize, iSize - iEnqueueSize);
	}

	_iWritePos = (iSize + _iWritePos) % _iSize;

	return iSize;
}

int CRingBuffer::Dequeue(char * pOutData, int iSize)
{
	if (iSize <= 0)
		return 0;

	if (GetUseSize() < iSize)
		iSize = GetUseSize();

	int iDequeueSize = GetUnbrokenDequeueSize();
	if (iSize <= iDequeueSize)
	{
		memcpy(pOutData, _pBuffer + _iReadPos, iSize);
	}
	else
	{
		memcpy(pOutData, _pBuffer + _iReadPos, iDequeueSize);
		memcpy(pOutData + iDequeueSize, _pBuffer, iSize - iDequeueSize);
	}

	_iReadPos = (iSize + _iReadPos) % _iSize;

	return iSize;
}

int CRingBuffer::Peek(char * pOutData, int iSize)
{
	if (iSize <= 0)
		return 0;

	if (GetUseSize() < iSize)
		iSize = GetUseSize();

	int iDequeueSize = GetUnbrokenDequeueSize();
	if (iSize <= iDequeueSize)
	{
		memcpy(pOutData, _pBuffer + _iReadPos, iSize);
	}
	else
	{
		memcpy(pOutData, _pBuffer + _iReadPos, iDequeueSize);
		memcpy(pOutData + iDequeueSize, _pBuffer, iSize - iDequeueSize);
	}

	return iSize;
}

void CRingBuffer::RemoveData(int iSize)
{
	_iReadPos = (iSize + _iReadPos) % _iSize;
}

int CRingBuffer::MoveWritePos(int iSize)
{
	_iWritePos = (iSize + _iWritePos) % _iSize;

	return iSize;
}

char * CRingBuffer::GetBufferPtr()
{
	return _pBuffer;
}

char * CRingBuffer::GetReadBufferPtr()
{
	return _pBuffer + _iReadPos;
}

char * CRingBuffer::GetWriteBufferPtr()
{
	return _pBuffer + _iWritePos;
}