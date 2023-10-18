// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet() noexcept
{
	MaxPower = 0;
}

TSet::TSet(int np)
{
	if (np < 0) { throw out_of_range("size should be greater than zero"); return; }
	if (np == 0) { MaxPower = 0; return; }
	if (np > 0)
	{
		MaxPower = np;
		TBitField x(np);
		BitField = x;
	}
}

TSet::TSet(const TSet& s)
{
	if (s.GetMaxPower())
	{
		MaxPower = s.GetMaxPower();
		TBitField x(MaxPower);
		BitField = x;

		for (int i = 0; i < s.GetMaxPower(); ++i) if (s.IsMember(i)) BitField.SetBit(i);
	}
	else TSet();
}

TSet::TSet(const TBitField& bf)
{
	if (bf.GetLength())
	{
		MaxPower = bf.GetLength();
		BitField = bf;
	}
	else MaxPower = 0;
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower() const
{
	return MaxPower;
}

void TSet::InsElem(const int Elem)
{
	if (Elem >= GetMaxPower() || Elem < 0) throw out_of_range("Element should belong to this set");
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem)
{
	if (Elem >= GetMaxPower() || Elem < 0) throw out_of_range("Element should belong to this set");
	BitField.ClrBit(Elem);
}

int TSet::IsMember(const int Elem) const
{
	if (Elem >= GetMaxPower() || Elem < 0) throw out_of_range("Element should belong to this set");
	return BitField.GetBit(Elem) == 1;
}

int TSet::operator== (const TSet& s) const
{
	return MaxPower == s.GetMaxPower() && BitField == s.BitField;
}

int TSet::operator!= (const TSet& s) const
{
	return !(this->operator==(s));
}

TSet& TSet::operator=(const TSet& s)
{

	if (*this == s) return *this;
	if (s.GetMaxPower())
	{
		MaxPower = s.GetMaxPower();
		BitField = s.BitField;
	}
	else
	{
		TBitField x;
		BitField = x;
		MaxPower = 0;
	}
	return *this;
}

TSet TSet::operator+(const int Elem)
{
	if (Elem >= GetMaxPower() || Elem < 0) throw out_of_range("Element should belong to this set");
	else
	{
		TSet x(*this);
		x.InsElem(Elem);
		return x;
	}
}

TSet TSet::operator- (const int Elem)
{
	if (Elem >= GetMaxPower() || Elem < 0) throw out_of_range("Element should belong to this set");
	else
	{
		TSet x(*this);
		x.DelElem(Elem);
		return x;
	}
}

TSet TSet::operator+ (const TSet& s)
{
	TSet x = s;
	x.BitField = this->BitField | s.BitField;
	return x;
}

TSet TSet::operator* (const TSet& s)
{
	TSet x = s;
	x.BitField = this->BitField & s.BitField;
	return x;
}

TSet TSet::operator~ (void)
{

	TSet x(*this);
	x.BitField = ~x.BitField;
	return x;
}

istream& operator>> (istream& istr, TSet& bf)
{
	for (int i = 0; i < bf.MaxPower; ++i)
	{
		bool x;
		cin >> x;
		if (x) bf.InsElem(i);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& bf)
{
	for (int i = 0; i < bf.MaxPower; ++i)
		cout<<bg.Ismember(i);
	return ostr;
}
