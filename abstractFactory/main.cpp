#include "header.h"
#include <iostream>

using namespace std;


int main()
{
	cout<<"I want a King burger from BurgerKing" << endl;

	IAbstractFactory* factory = FactoryProducer::getFactory(BURGER_KING);

	factory->createProduct(KING_BURGER);

	cout<<"I want a cup of coke from BurgerKing" << endl;
	factory->createProduct(KING_COKE);


	IAbstractFactory* mcFactory = FactoryProducer::getFactory(MCDONALD);
	cout<<"I want a hamburger from BurgerKing" << endl;
	mcFactory->createProduct(HAMBURGER);

	cout<<"I want a cup of coke from BurgerKing" << endl;
	mcFactory->createProduct(COKE);

	return 0;
}

