#ifndef HEADER_H

#define HEADER_H
#include <iostream>

class IProduct
{

public:
	IProduct(int p, int w) : m_price(p), m_weight(w) {}

	virtual int getPrice() { return m_price;}

	virtual int getWeight() { return m_weight;}

	virtual ~IProduct() {}

private:
	int m_price; // In RMB
	int m_weight; // In grams

};

class IAbstractFactory
{
public:
	virtual IProduct* createProduct(int productType) = 0;

	virtual ~IAbstractFactory() {}
};


class Hamburger : public IProduct
{
public:
	Hamburger(int price, int weight):
		IProduct(price, weight)
	{}

	virtual ~Hamburger() {}
};

class KingBurger : public IProduct
{
public:
	KingBurger(int price, int weight):
		IProduct(price, weight)
	{}

	virtual ~KingBurger() {}
};

enum McDonaldProduct
{
	HAMBURGER,
	DONUT,
	COKE
};

class McDonaldFactory : public IAbstractFactory
{
public:
	virtual IProduct* createProduct(int productType)
	{
		IProduct* mcDonaldProduct = nullptr;
		if (productType == HAMBURGER)
		{
			mcDonaldProduct = new Hamburger(10, 100);
			std::cout << "A Hamburger is produced" << std::endl;
		}
		else
		{
			mcDonaldProduct = new Hamburger(10, 100);
			std::cout << "The default product of McDonald: Hamburger is produced" << std::endl;
		}

		return mcDonaldProduct;
	}

	virtual ~McDonaldFactory() {}

};

enum BurgerKingProduct
{
	KING_BURGER,
	KING_DONUT,
	KING_COKE
};

class BurgerKingFactory : public IAbstractFactory
{
public:
	virtual IProduct* createProduct(int productType)
	{
		IProduct* burgerKingProduct = nullptr;
		if (productType == KING_BURGER)
		{
			burgerKingProduct = new KingBurger(10, 100);
			std::cout << "A KingBurger is produced" << std::endl;
		}
		else
		{
			burgerKingProduct = new KingBurger(10, 100);
			std::cout << "The default product of BurgerKing: KingBurger is produced" << std::endl;
		}

		return burgerKingProduct;
	}

	virtual ~BurgerKingFactory() {}

};


enum FACTORY_TYPE
{
	MCDONALD,
	BURGER_KING
};

class FactoryProducer
{
public:
	static IAbstractFactory* getFactory(FACTORY_TYPE type)
	{
		if (type == MCDONALD)
		{
			static McDonaldFactory mcFactory;
			return &mcFactory;
		}
		else
		{
			static BurgerKingFactory kingFactory;
			return &kingFactory;
		}

	}
};


#endif
