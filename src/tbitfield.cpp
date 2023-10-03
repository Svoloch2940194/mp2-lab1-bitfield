// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

int TBitField::GetMemIndex(const int n) const
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const
{
	return 1 << (n % (sizeof(TELEM) * 8));
}

TBitField::TBitField() noexcept
{
	BitLen = 0;
	MemLen = 0;
	pMem = nullptr;
}

TBitField::TBitField(int len)
{
	if (len < 0) { throw out_of_range("Size should be greater than zero"); return; }
	if (len == 0) { TBitField(); return; }
	if (len > 0)
	{
		BitLen = len;
		MemLen = GetMemIndex(BitLen) + 1 * (BitLen % (sizeof(TELEM) * 8) != 0);
		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; ++i) pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf)
{
	if (bf.BitLen)
	{
		BitLen = bf.BitLen;
		MemLen = GetMemIndex(BitLen) + 1 * (BitLen % (sizeof(TELEM) * 8) != 0);
		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; ++i) pMem[i] = bf.pMem[i];
	}
	else TBitField();
}

TBitField::~TBitField()
{
	if (pMem != nullptr)delete pMem;
}

int TBitField::GetLength() const
{
	return BitLen;
}

void TBitField::SetBit(const int n)
{
	if (n < 0) throw out_of_range("index should be greater or eqals than zero");
	if (n >= BitLen) throw out_of_range("index should be less than length of erray");
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n)
{
	if (n < 0) throw out_of_range("index should be greater or eqals than zero");
	if (n >= BitLen) throw out_of_range("index should be less than length of erray");
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const
{
	if (n < 0) throw out_of_range("index should be greater or eqals than zero");
	if (n >= BitLen) throw out_of_range("index should be less than length of erray");
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

int TBitField::operator==(const TBitField& bf) const
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; ++i)
		{
			if (pMem[i] != bf.pMem[i]) return false;
		}
		return true;
	}
	return false;
}

int TBitField::operator!=(const TBitField& bf) const
{
	return !(this->operator==(bf));
}

TBitField& TBitField::operator=(const TBitField& bf)
{
	if (bf.BitLen > 0 && *this != bf)
	{
		delete pMem;
		BitLen = bf.BitLen;
		MemLen = BitLen / (sizeof(TELEM) * 8) + 1 * (BitLen % (sizeof(TELEM) * 8) != 0);

		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; ++i) pMem[i] = bf.pMem[i];
	}
	else
	{
		if (BitLen > 0) delete pMem;
		TBitField();
	}

	return *this;
}

TBitField TBitField::operator|(const TBitField& bf)
{
	TBitField x;
	if (BitLen > bf.BitLen) x = *this;
	else x = bf;

	for (int i = 0; i < min(bf.MemLen, MemLen); ++i) x.pMem[i] |= this->pMem[i], x.pMem[i] |= bf.pMem[i];
	return x;
}

TBitField  TBitField::operator&(const TBitField& bf)
{
	TBitField x;

	if (BitLen > bf.BitLen) x = *this;
	else x = bf;

	for (int i = 0; i < max(bf.MemLen, MemLen); ++i)
	{
		if (i < this->MemLen) x.pMem[i] &= this->pMem[i];
		else x.pMem[i] &= 0;

		if (i < bf.MemLen) x.pMem[i] &= bf.pMem[i];
		else x.pMem[i] &= 0;
	}

	return x;
}

TBitField TBitField::operator~()
{
	TBitField x(BitLen);
	for (int i = 0; i < BitLen; ++i)
	{
		if (!(GetBit(i))) x.SetBit(i);
	}

	return x;
}

istream& operator>> (istream& istr, TBitField& bf)
{
	for (int i = 0; i < bf.BitLen; ++i)
	{
		bool x;
		cin >> x;
		if (x) bf.SetBit(i);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf)
{
	for (int i = 0; i < bf.BitLen; ++i)
	{
		if (bf.GetBit(i)) cout << 1;
		else cout << 0;
	}
	return ostr;
}
