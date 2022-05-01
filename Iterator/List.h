#pragma once
#include <list>
using namespace std;
class ListIterator;

enum class Iterators {
	STEP,
	VALUE
};

class List
{
public:
	list <int> lst;
	list <int>::iterator lastiter;
public:
	friend class ListIterator;

	List(size_t aSize) {
		lst.resize(aSize);
		lastiter = lst.begin();
	}

	virtual ~List() {}

	bool append(int a) {
		if (lastiter == lst.end())
			return false;
		lst.insert(lastiter, a);
		if (lastiter == lst.end())
			return true;
		auto prelast = lastiter++;
		lst.erase(prelast);
		return true;
	}

	bool remove() {
		if (lastiter == lst.begin())
			return false;
		lst.pop_back();
		lst.resize(lst.size() + 1);
		lastiter--;
		return true;
	}
	ListIterator* createIterator(Iterators its, const int aStep) const;
};

class ListIterator
{
protected:
	friend class List;
	const List* pList;
	list <int>::iterator iter;
	int currentItem()
	{
		return *(iter);
	}
	virtual bool first() = 0;
	virtual bool next() = 0;
public:
	ListIterator(const List* aPList) : pList(aPList), iter(pList->lastiter)
	{
		if (pList->lst.begin() == pList->lst.end())
		{
			throw exception("Ошибка! Список пуст!");
		}
	}
	bool operator()()
	{
		return first();
	}
	bool operator++()
	{
		return next();
	}
	int operator*()
	{
		return currentItem();
	}
};

class ListIteratorStep : public ListIterator
{
private:
	int step;

	bool first() override {
		iter = pList->lastiter;
		iter--;

		auto i = 0;
		while (i < step)
		{
			i++;
			if (iter == pList->lst.begin())
				return false;
			iter--;
		}
		return true;
	}
	bool next() override
	{
		if (iter == pList->lst.begin())
			return false;
		iter--;

		auto i = 0;
		while (i < step)
		{
			i++;
			if (iter == pList->lst.begin())
				return false;
			iter--;
		}
		return true;
	}
public:
	void setStep(int aStep)
	{
		if (aStep <= 0)
			throw exception("Ошибка! Неверное значение шага!");
		step = aStep - 1;
	}
	int getStep() const { return step; }
	ListIteratorStep(const List* aPList, int aStep = 1) : ListIterator(aPList)
	{
		setStep(aStep);
	}
};

class ListIteratorValue : public ListIterator
{
private:
	int value;

	bool first() override
	{
		iter = pList->lastiter;
		iter--;
		while (*iter != value)
		{
			if (iter == pList->lst.begin())
				return false;
			iter--;
		}
		return true;
	}
	bool next() override
	{
		if (iter == pList->lst.begin())
			return false;
		iter--;
		while (*iter != value)
		{
			if (iter == pList->lst.begin())
				return false;
			iter--;
		}
		return true;
	}
public:
	void setValue(int aValue)
	{
		value = aValue;
	}
	int getValue() const { return value; }
	ListIteratorValue(const List* aPList, int aValue) : ListIterator(aPList)
	{
		setValue(aValue);
	}
};

ListIterator* List::createIterator(Iterators its, const int aNumber) const {
	if (its == Iterators::STEP)
		return new ListIteratorStep(this, aNumber);
	if (its == Iterators::VALUE)
		return new ListIteratorValue(this, aNumber);
	return nullptr;
}