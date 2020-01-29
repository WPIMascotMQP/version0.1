#include <iostream>

#include "behaviourtree/BehaviourTree.h"
#include "communication/Controller.h"
#include "behaviourtree/composite/Sequence.h"
#include "MasterControlLoop.h"
#include "behaviours/MoveBackDown.h"
#include "behaviours/MoveFrontLeft.h"
#include "behaviours/MoveUpRight.h"
#include "behaviourtree/composite/Parallel.h"
#include "behaviourtree/composite/Utility.h"
#include "decorators/SUtilityDec.h"
#include "decorators/PUtilityDec.h"
#include "processors/AudioProcessor.h"
#include "processors/TouchProcessor.h"
#include "processors/VisualProcessor.h"

extern std::vector<Behaviour*> currentBehaviours;

int main(int argc, char* argv[]) {
	logger::startLog();
	BehaviourTree bt;
	Sequence sq;
	Parallel pl;
	Utility ut;

	SUtilityDec sud;
	PUtilityDec pud;

	MoveUpRight mur;
	MoveFrontLeft mfl;
	MoveBackDown mbd;

	AudioProcessor ap;
	TouchProcessor tp;
	VisualProcessor vp(0);

	pl.addChild(&mur);
	pl.addChild(&mfl);
	pl.addChild(&mbd);
	pl.reset();

	sq.addChild(&mur);
	sq.addChild(&mfl);
	sq.addChild(&mbd);
	sq.reset();

	sud.setChild(&sq);
	pud.setChild(&pl);
	ut.addChild(&sud);
	ut.addChild(&pud);

	bt.setRoot(&ut);

	currentBehaviours.push_back(&bt);
	Controller* controller = &Node::controller;
	SensorData* data = &Node::data;

	//ap.startThread();
	//tp.startThread();
	vp.startThread();

	std::string input;
	std::getline(std::cin, input);
	data->setInput(input);
	while (input != "x") {
		executeBehaviours(input);
		controller->execute();

		std::getline(std::cin, input);
		data->setInput(input);
	}
	//ap.killThread();
	//tp.killThread();
	vp.killThread();
	logger::endLog();
}

void executeBehaviours(std::string input) {
	std::vector<Behaviour*>::iterator itr;
	for (itr = currentBehaviours.begin(); itr < currentBehaviours.end(); itr++) {
		Behaviour* behaviour = *itr;
		Status* result = input.find("f") == std::string::npos ? 
			behaviour->executeP(Status().setSuccess()) : behaviour->executeP(Status().setFailure());
		currentBehaviours.erase(itr);
	}
}
