#include <iostream>

#include "behaviourtree/BehaviourTree.h"
#include "communication/Controller.h"
#include "behaviourtree/composite/Sequence.h"
#include "MasterControlLoop.h"
#include "behaviourtree/composite/Parallel.h"
#include "behaviourtree/composite/Utility.h"
#include "processors/AudioProcessor.h"
#include "processors/MotorProcessor.h"
#include "processors/VisualProcessor.h"
#include "SensorData.h"

#include "behaviours/PhysicalMoveHead.h"
#include "behaviours/InteractionMoveToHead.h"
#include "behaviours/InteractionMoveToHand.h"
#include "behaviours/SeekingMoveSearch.h"
#include "behaviours/SeekingMoveToBody.h"
#include "behaviours/Move.h"

#include "decorators/PhysicalUtilityDec.h"
#include "decorators/InteractionUtilityDec.h"
#include "decorators/InteractionHandUtilityDec.h"
#include "decorators/InteractionHeadUtilityDec.h"
#include "decorators/InteractionMotionUtilityDec.h"
#include "decorators/SeekingUtilityDec.h"
#include "decorators/SeekingSearchUtilityDec.h"
#include "decorators/SeekingBodyUtilityDec.h"
#include "decorators/SeekingMotionUtilityDec.h"

namespace nodes {
	Utility ut_t1;
		PhysicalUtilityDec pud;
			Sequence physical_sq;
		InteractionUtilityDec iud;
			Utility interaction_ut;
				InteractionHeadUtilityDec head_iud;
					InteractionMoveToHead move_to_head;
				InteractionHandUtilityDec hand_iud;
					InteractionMoveToHand move_to_hand;
				InteractionMotionUtilityDec motion_iud;
					Sequence interaction_motion_sq;
						Move move_hd_ccw;
						Move move_hd_cw;
						Move move_hd_cen;
						Move move_hd_up;
						Move move_hd_dwn;
		SeekingUtilityDec sud;
			Utility seeking_ut;
				SeekingSearchUtilityDec search_sud;
					SeekingMoveSearch move_search;
				SeekingBodyUtilityDec body_sud;
					SeekingMoveToBody move_to_body;
				SeekingMotionUtilityDec motion_sud;
					Sequence seeking_motion_sq;
						Move move_nk_up;
						Move move_nk_dwn;
						Move move_nk_cen;
}

int main(int argc, char* argv[]) {
	logger::startLog();
	// Create Behaviour Tree Objects
	using namespace nodes;
	BehaviourTree bt;

	// Link Behaviour Tree
	bt << ut_t1;
		ut_t1 << pud << iud << sud;
			pud << physical_sq;
			iud << interaction_ut;
				interaction_ut << head_iud << hand_iud << motion_iud;
					head_iud << move_to_head;
					hand_iud << move_to_hand;
					motion_iud << interaction_motion_sq;
						interaction_motion_sq << move_hd_ccw << move_hd_cw << move_hd_cen << move_hd_up << move_hd_dwn << move_hd_cen;
			sud << seeking_ut;
				seeking_ut << search_sud << body_sud << motion_sud;
					search_sud << move_search;
					body_sud << move_to_body;
					motion_sud << seeking_motion_sq;
						seeking_ut << move_nk_up << move_hd_up << move_hd_cen << move_nk_dwn << move_nk_cen;
	logger::log("Behaviour Tree Objects Linked");
	interaction_motion_sq.reset();
	seeking_motion_sq.reset();
	coms::current_behaviours.push_back(&bt);

	//ap.startThread();
	//mp.startThread();
	processor::vp.startThread();
	logger::log("VisualProcessor Thread Started");

	std::string input;
	std::getline(std::cin, input);
	data::sensor_data.setInput(input);
	while (input != "x") {
		executeBehaviours(input);
		coms::controller.execute();

		//printDecoratorPriorities();

		std::getline(std::cin, input);
		data::sensor_data.setInput(input);
	}
	//ap.killThread();
	//mp.killThread();
	processor::vp.killThread();
	logger::log("VisualProcessor Thread Killed");
	logger::endLog();
}

void executeBehaviours(std::string input) {
	std::vector<Behaviour*>::iterator itr;
	for (itr = coms::current_behaviours.begin(); itr < coms::current_behaviours.end(); itr++) {
		Behaviour* behaviour = *itr;
		Status* result = input.find("f") == std::string::npos ?
			behaviour->executeP(Status().setSuccess()) : behaviour->executeP(Status().setFailure());
		coms::current_behaviours.erase(itr);
	}
}

void printDecoratorPriorities() {
	using namespace nodes;
	logger::verbose("PhysicalUtilityDec Priority: ", pud.getPriority());
	logger::verbose("InteractionUtilityDec Priority: ", iud.getPriority());
	logger::verbose("  InteractionHeadUtilityDec Priority: ", head_iud.getPriority());
	logger::verbose("  InteractionHandUtilityDec Priority: ", hand_iud.getPriority());
	logger::verbose("  InteractionMotionUtilityDec", motion_iud.getPriority());
	logger::verbose("SeekingUtilityDec Priority: ", sud.getPriority());
	logger::verbose("  SeekingSearchUtilityDec Priority: ", search_sud.getPriority());
	logger::verbose("  SeekingBodyUtilityDec Priority: ", body_sud.getPriority());
	logger::verbose("  SeekingMotionUtilityDec Priority: ", motion_sud.getPriority());
	logger::verbose("");
}
