#include "CRingBuffer.h"
#include <Windows.h>

CRingBuffer::CRingBuffer(int iBufferSize) : _iReadPos(0), _iWritePos(0), _iSize(iBufferSize), _pBuffer((char*)malloc(sizeof(char) * (iBufferSize)))
{
	memset(_pBuffer, 0, iBufferSize);
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
	memset(_pBuffer, 0, _iSize);
}

int CRingBuffer::GetTotalSize()
{
	return _iSize;
}

int CRingBuffer::GetUseSize()
{
	if (_iReadPos > _iWritePos)
		return _iSize - _iReadPos + _iWritePos;

	return _iWritePos - _iReadPos;
}

int CRingBuffer::GetFreeSize()
{
	if (_iReadPos > _iWritePos)
		return _iReadPos - _iWritePos;

	return _iSize - _iWritePos + _iReadPos;
}

int CRingBuffer::GetUnbrokenEnqueueSize()
{
	return _iSize - _iWritePos;
}

int CRingBuffer::GetUnbrokenDequeueSize()
{
	return _iSize - _iReadPos;
}

int CRingBuffer::Enqueue(char * pInData, int iSize)
{
	// 여유 공간 크기 < 입력 데이터 크기
	if (GetFreeSize() < iSize)
	{
		/////////////////////////////////////////////////////////////////////////
		// TODO : Enqueue 문제 Solution 1. 버퍼 내 데이터 크기 만큼만 입력 
		/// → 데이터가 잘리는데 의미가 있나??????
		//
		/////////////////////////////////////////////////////////////////////////
		//iSize = GetFreeSize();
		//if (_iReadPos > _iWritePos)	// front가 rear보다 뒤에 있을 경우
		//{
		//	memcpy(_pBuffer + _iReadPos, pInData, iSize);
		//	_iWritePos += iSize;
		//}
		//else
		//{
		//	if (iSize < GetUnbrokenEnqueueSize())
		//	{
		//		memcpy(_pBuffer + _iReadPos, pInData, iSize);
		//		_iWritePos += iSize;
		//	}
		//	else
		//	{
		//		memcpy(_pBuffer + _iReadPos, pInData, _iSize - _iWritePos);
		//		memcpy(_pBuffer, pInData + (_iSize - _iWritePos), iSize - (_iSize - _iWritePos));
		//		_iWritePos = _iSize - _iWritePos;
		//	}
		//}
		//return iSize;
		
		/////////////////////////////////////////////////////////////////////////
		// TODO : Enqueue 문제 Solution 2. 입력 중단
		//
		/////////////////////////////////////////////////////////////////////////
		return 0;
	}

	// 남은 공간이 넉넉할 경우
	if (_iReadPos > _iWritePos)	// front가 rear보다 뒤에 있을 경우
	{
		memcpy(_pBuffer + _iWritePos, pInData, iSize);	// 데이터가 짤릴 일이 없으므로 크기 그대로 넣어준다
		_iWritePos += iSize;
	}
	else
	{
		if (iSize < GetUnbrokenEnqueueSize())	// 데이터 크기가 잘리지 않는 경우
		{
			memcpy(_pBuffer + _iWritePos, pInData, iSize);
			_iWritePos += iSize;
		}
		else
		{
			memcpy(_pBuffer + _iWritePos, pInData, _iSize - _iWritePos);
			memcpy(_pBuffer, pInData + (_iSize - _iWritePos), iSize - (_iSize - _iWritePos));
			_iWritePos = iSize - (_iSize - _iWritePos);
		}
	}

	return iSize;
}

int CRingBuffer::Dequeue(char * pOutData, int iSize)
{
	// 버퍼 내 데이터 크기 < 출력할 데이터 크기
	if (GetUseSize() < iSize)
	{
		/////////////////////////////////////////////////////////////////////////
		// TODO : Dequeue 문제 Solution 1. 버퍼 내 데이터 크기 만큼만 출력 
		/// → 데이터가 잘리는데 의미가 있나??????
		//
		/////////////////////////////////////////////////////////////////////////
		//iSize = GetUseSize();
		//if (_iWritePos > _iReadPos)		// WritePos가 ReadPos보다 주소 상에서 뒤에 있을 경우
		//{
		//	memcpy(pOutData, _pBuffer + _iReadPos, _iWritePos - _iReadPos);
		//	_iReadPos = _iWritePos;
		//}
		//else
		//{
		//	if (iSize < GetUnbrokenDequeueSize())	// 출력 데이터가 잘리지 않는 경우
		//	{
		//		memcpy(pOutData, _pBuffer + _iReadPos, _iSize - _iReadPos);
		//		_iReadPos = _iSize;
		//	}
		//	else
		//	{
		//		memcpy(pOutData, _pBuffer + _iReadPos, _iSize - _iReadPos);
		//		memcpy(pOutData + (_iSize - _iReadPos), _pBuffer, _iWritePos);
		//		_iReadPos = _iWritePos;
		//	}
		//}
		//return iSize;

		/////////////////////////////////////////////////////////////////////////
		// TODO : Dequeue 문제 Solution 2. 출력 중단
		//
		/////////////////////////////////////////////////////////////////////////
		return 0;
	}

	if (_iWritePos > _iReadPos)		// rear가 front보다 뒤에 있을 경우
	{
		memcpy(pOutData, _pBuffer + _iReadPos, iSize);
		_iReadPos += iSize;
	}
	else
	{
		if (iSize < GetUnbrokenDequeueSize())	// 데이터 크기가 잘리지 않는 경우
		{
			memcpy(pOutData, _pBuffer + _iReadPos, iSize);
			_iReadPos += iSize;
		}
		else
		{
			memcpy(pOutData, _pBuffer + _iReadPos, _iSize - _iReadPos);
			memcpy(pOutData + (_iSize - _iReadPos), _pBuffer, iSize - (_iSize - _iReadPos));
			_iReadPos = iSize - (_iSize - _iReadPos);
		}
	}
	return iSize;
}

int CRingBuffer::Peek(char * pOutData, int iSize)
{
	if (GetUseSize() < iSize)
	{
		//iSize = GetUseSize();
		//if (_iWritePos > _iReadPos)
		//{
		//	memcpy(pOutData, _pBuffer + _iReadPos, _iWritePos - _iReadPos);
		//}
		//else
		//{
		//	if (iSize < GetUnbrokenDequeueSize())
		//	{
		//		memcpy(pOutData, _pBuffer + _iReadPos, _iSize - _iReadPos);
		//	}
		//	else
		//	{
		//		memcpy(pOutData, _pBuffer + _iReadPos, _iSize - _iReadPos);
		//		memcpy(pOutData + (_iSize - _iReadPos), _pBuffer, _iWritePos);
		//	}
		//}
		//return iSize;

		return 0;
	}

	if (_iWritePos > _iReadPos)
	{
		memcpy(pOutData, _pBuffer + _iReadPos, iSize);
	}
	else
	{
		if (iSize < _iSize - _iReadPos)
		{
			memcpy(pOutData, _pBuffer + _iReadPos, iSize);
		}
		else
		{
			memcpy(pOutData, _pBuffer + _iReadPos, _iSize - _iReadPos);
			memcpy(pOutData + (_iSize - _iReadPos), _pBuffer, iSize - (_iSize - _iReadPos));
		}
	}
	return iSize;
}

void CRingBuffer::RemoveData(int iSize)
{
	if (GetUseSize() < iSize)
	{
		iSize = GetUseSize();
		if (_iWritePos > _iReadPos)
		{
			_iReadPos = _iWritePos;
		}
		else
		{
			if (iSize < GetUnbrokenDequeueSize())
			{
				_iReadPos = _iSize;
			}
			else
			{
				_iReadPos = _iWritePos;
			}
		}
		return;
	}

	if (_iWritePos > _iReadPos)
	{
		_iReadPos += iSize;
	}
	else
	{
		if (iSize < _iSize - _iReadPos)
		{
			_iReadPos += iSize;
		}
		else
		{
			_iReadPos = iSize - (_iSize - _iReadPos);
		}
	}
	return;
}

int CRingBuffer::MoveWritePos(int iSize)
{
	if (GetFreeSize() < iSize)
	{
		iSize = GetFreeSize();
		if (_iReadPos > _iWritePos)
		{
			_iWritePos += iSize;
		}
		else
		{
			if (iSize < GetUnbrokenEnqueueSize())
			{
				_iWritePos += iSize;
			}
			else
			{
				_iWritePos = _iSize - _iWritePos;
			}
		}
		return iSize;
	}

	if (_iReadPos > _iWritePos)
	{
		_iWritePos += iSize;
	}
	else
	{
		if (iSize < _iSize - _iWritePos)
		{
			_iWritePos += iSize;
		}
		else
		{
			_iWritePos = iSize - (_iSize - _iWritePos);
		}
	}
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