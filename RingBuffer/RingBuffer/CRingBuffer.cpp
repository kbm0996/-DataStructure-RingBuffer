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
	// ���� ���� ũ�� < �Է� ������ ũ��
	if (GetFreeSize() < iSize)
	{
		/////////////////////////////////////////////////////////////////////////
		// TODO : Enqueue ���� Solution 1. ���� �� ������ ũ�� ��ŭ�� �Է� 
		/// �� �����Ͱ� �߸��µ� �ǹ̰� �ֳ�??????
		//
		/////////////////////////////////////////////////////////////////////////
		//iSize = GetFreeSize();
		//if (_iReadPos > _iWritePos)	// front�� rear���� �ڿ� ���� ���
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
		// TODO : Enqueue ���� Solution 2. �Է� �ߴ�
		//
		/////////////////////////////////////////////////////////////////////////
		return 0;
	}

	// ���� ������ �˳��� ���
	if (_iReadPos > _iWritePos)	// front�� rear���� �ڿ� ���� ���
	{
		memcpy(_pBuffer + _iWritePos, pInData, iSize);	// �����Ͱ� ©�� ���� �����Ƿ� ũ�� �״�� �־��ش�
		_iWritePos += iSize;
	}
	else
	{
		if (iSize < GetUnbrokenEnqueueSize())	// ������ ũ�Ⱑ �߸��� �ʴ� ���
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
	// ���� �� ������ ũ�� < ����� ������ ũ��
	if (GetUseSize() < iSize)
	{
		/////////////////////////////////////////////////////////////////////////
		// TODO : Dequeue ���� Solution 1. ���� �� ������ ũ�� ��ŭ�� ��� 
		/// �� �����Ͱ� �߸��µ� �ǹ̰� �ֳ�??????
		//
		/////////////////////////////////////////////////////////////////////////
		//iSize = GetUseSize();
		//if (_iWritePos > _iReadPos)		// WritePos�� ReadPos���� �ּ� �󿡼� �ڿ� ���� ���
		//{
		//	memcpy(pOutData, _pBuffer + _iReadPos, _iWritePos - _iReadPos);
		//	_iReadPos = _iWritePos;
		//}
		//else
		//{
		//	if (iSize < GetUnbrokenDequeueSize())	// ��� �����Ͱ� �߸��� �ʴ� ���
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
		// TODO : Dequeue ���� Solution 2. ��� �ߴ�
		//
		/////////////////////////////////////////////////////////////////////////
		return 0;
	}

	if (_iWritePos > _iReadPos)		// rear�� front���� �ڿ� ���� ���
	{
		memcpy(pOutData, _pBuffer + _iReadPos, iSize);
		_iReadPos += iSize;
	}
	else
	{
		if (iSize < GetUnbrokenDequeueSize())	// ������ ũ�Ⱑ �߸��� �ʴ� ���
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