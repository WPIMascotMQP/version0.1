#include <iostream>

#include "BehaviourTree.h"
#include "Controller.h"
#include "Sequence.h"
#include "MasterControlLoop.h"
#include "MoveBackDown.h"
#include "MoveFrontLeft.h"
#include "MoveUpRight.h"
#include "Parallel.h"
#include "Utility.h"
#include "UtilityDec.h"

extern std::vector<Behaviour*> currentBehaviours;

int main(int argc, char* argv[]) {
	BehaviourTree bt;
	Sequence sq;
	Parallel pl;
	Utility ut;

	UtilityDec murd;
	UtilityDec mfld;

	MoveUpRight mur;
	MoveFrontLeft mfl;
	MoveBackDown mbd;

	pl.addChild(&mur);
	pl.addChild(&mfl);
	pl.addChild(&mbd);
	pl.reset();

	murd.setChild(&mur);
	mfld.setChild(&mfl);
	ut.addChild(&murd);
	ut.addChild(&mfld);

	sq.addChild(&mur);
	sq.addChild(&mfl);
	sq.addChild(&mbd);
	sq.addChild(&pl);
	//sq.addChild(&ut);
	sq.reset();

	bt.setRoot(&sq);

	bt.execute();
	Controller *controller = &Node::controller;

	char key;
	while (std::cin.get() == '\n') {
		executeBehaviours();
		controller->execute();
	}
}

void executeBehaviours() {
	std::vector<Behaviour*>::iterator itr;
	for (itr = currentBehaviours.begin(); itr < currentBehaviours.end(); itr++) {
		Behaviour* behaviour = *itr;
		behaviour->executeP(status::success);
		currentBehaviours.erase(itr);
	}
}