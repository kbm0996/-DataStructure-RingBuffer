#include "CRingBuffer.h"

using namespace mylib;


CRingBuffer::CRingBuffer(int iBufferSize)
{
	_iBufferSize = iBufferSize;
	_pBuffer = new char[iBufferSize];
	_iRead = 0;
	_iWrite = 0;

	InitializeSRWLock(&_srwLock);
}

CRingBuffer::~CRingBuffer()
{
	if (_pBuffer != nullptr)
		delete[] _pBuffer;
	_pBuffer = nullptr;
}

void CRingBuffer::Lock()
{
	AcquireSRWLockExclusive(&_srwLock);
}

void CRingBuffer::Unlock()
{
	ReleaseSRWLockExclusive(&_srwLock);
}

int CRingBuffer::GetUseSize()
{
	if (_iWrite >= _iRead)
		return _iWrite - _iRead;
	else
		return (_iBufferSize - _iRead) + _iWrite;
}

int CRingBuffer::GetFreeSize()
{
	return _iBufferSize - GetUseSize() - 1;
}

int CRingBuffer::GetUnbrokenDequeueSize()
{
	if (_iWrite >= _iRead)
		return _iWrite - _iRead;
	else
		return _iBufferSize - _iRead;
}

int CRingBuffer::GetUnbrokenEnqueueSize()
{
	if ((_iWrite + 1) % _iBufferSize == _iRead)
		return 0;

	if (_iWrite <= ((_iRead + _iBufferSize - 1) % _iBufferSize))
		return ((_iRead + _iBufferSize - 1) % _iBufferSize) - _iWrite;
	else if (_iWrite >= _iRead)
		return _iBufferSize - _iWrite;

	return 0;
}

int CRingBuffer::Enqueue(char * chpData, int iSize)
{
	if ((_iWrite + 1) % _iBufferSize == _iRead)
		return 0;

	if (GetFreeSize() <= iSize)
		iSize = GetFreeSize();

	if (GetUnbrokenEnqueueSize() >= iSize)
		memcpy((_pBuffer + _iWrite), chpData, iSize);
	else
	{
		int PutSize = GetUnbrokenEnqueueSize();
		memcpy((_pBuffer + _iWrite), chpData, PutSize);
		memcpy(_pBuffer, (chpData + PutSize), iSize - PutSize);
	}

	_iWrite = (_iWrite + iSize) % _iBufferSize;

	return iSize;
}

int CRingBuffer::Dequeue(char * pDest, int iSize)
{
	if (_iRead == _iWrite)
		return 0;

	if (GetUseSize() <= iSize)
		iSize = GetUseSize();

	if (GetUnbrokenDequeueSize() >= iSize)
		memcpy(pDest, (_pBuffer + _iRead), iSize);
	else
	{
		int GetSize = GetUnbrokenDequeueSize();
		memcpy(pDest, (_pBuffer + _iRead), GetSize);
		memcpy((pDest + GetSize), _pBuffer, iSize - GetSize);
	}

	_iRead = (_iRead + iSize) % _iBufferSize;

	return iSize;
}

int CRingBuffer::Peek(char * pDest, int iSize)
{
	if (_iRead == _iWrite)
		return 0;

	if (GetUseSize() <= iSize)
		iSize = GetUseSize();


	if (GetUnbrokenDequeueSize() >= iSize)
		memcpy(pDest, (_pBuffer + _iRead), iSize);
	else
	{
		int GetSize = GetUnbrokenDequeueSize();
		memcpy(pDest, (_pBuffer + _iRead), GetSize);
		memcpy((pDest + GetSize), _pBuffer, iSize - GetSize);
	}

	return iSize;
}

void CRingBuffer::MoveReadPos(int iSize)
{
	_iRead = (_iRead + iSize) % _iBufferSize;
}

int CRingBuffer::MoveWritePos(int iSize)
{
	_iWrite = (_iWrite + iSize) % _iBufferSize;
	return iSize;
}

void CRingBuffer::Clear()
{
	_iRead = _iWrite = 0;
}

char * CRingBuffer::GetBufferPtr()
{
	return _pBuffer;
}

char * CRingBuffer::GetReadBufferPtr()
{
	return &_pBuffer[_iRead];
}

char * CRingBuffer::GetWriteBufferPtr()
{
	return &_pBuffer[_iWrite];
}