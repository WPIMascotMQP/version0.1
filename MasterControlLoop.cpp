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
#include "processors/MotorProcessor.h"
#include "processors/VisualProcessor.h"
#include "SensorData.h"

#include "decorators/PhysicalUtilityDec.h"
#include "decorators/InteractionUtilityDec.h"
#include "decorators/InteractionHandUtilityDec.h"
#include "decorators/InteractionHeadUtilityDec.h"
#include "decorators/InteractionMotionUtilityDec.h"
#include "decorators/SeekingUtilityDec.h"
#include "decorators/SeekingSearchUtilityDec.h"
#include "decorators/SeekingBodyUtilityDec.h"
#include "decorators/SeekingMotionUtilityDec.h"

extern std::vector<Behaviour*> currentBehaviours;

int main(int argc, char* argv[]) {
	logger::startLog();
	BehaviourTree bt;
	Utility ut_t1;
		PhysicalUtilityDec pud;
			Sequence physical_sq;
		InteractionUtilityDec iud;
			Utility interaction_ut;
				InteractionHeadUtilityDec head_iud;
				InteractionHandUtilityDec hand_iud;
				InteractionMotionUtilityDec motion_iud;
					Sequence interaction_motion_sq;
		SeekingUtilityDec sud;
			Utility seeking_ut;
				SeekingSearchUtilityDec search_sud;
				SeekingBodyUtilityDec body_sud;
				SeekingMotionUtilityDec motion_sud;
					Sequence seeking_motion_sq;
	bt << ut_t1;
		ut_t1 << pud << iud << sud;
			pud << physical_sq;
			iud << interaction_ut;
				interaction_ut << head_iud << hand_iud << motion_iud;
					motion_iud << interaction_motion_sq;
			sud << seeking_ut;
				seeking_ut << search_sud << body_sud << motion_sud;
					motion_sud << seeking_motion_sq;
					
	Sequence sq;
	Parallel pl;
	Utility ut;

	MoveUpRight mur;
	MoveFrontLeft mfl;
	MoveBackDown mbd;

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

	//ap.startThread();
	//mp.startThread();
	processor::vp.startThread();

	std::string input;
	std::getline(std::cin, input);
	data::sensorData.setInput(input);
	while (input != "x") {
		executeBehaviours(input);
		controller->execute();

		std::getline(std::cin, input);
		data::sensorData.setInput(input);
	}
	//ap.killThread();
	//mp.killThread();
	processor::vp.killThread();
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
