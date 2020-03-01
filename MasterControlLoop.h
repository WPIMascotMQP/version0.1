#ifndef MASTERCONTROLLOOP_H
#define MASTERCONTROLLOOP_H

#include <vector>
#include <iostream>

#include "behaviourtree/Behaviour.h"
#include "behaviourtree/BehaviourTree.h"
#include "communication/Controller.h"
#include "behaviourtree/composite/Sequence.h"
#include "behaviourtree/composite/Parallel.h"
#include "behaviourtree/composite/Utility.h"
#include "processors/AudioProcessor.h"
#include "processors/MotorProcessor.h"
#include "communication/SerialProcessor.h"
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
	extern BehaviourTree bt;
	extern Utility ut_t1;
		extern PhysicalUtilityDec pud;
			extern Sequence physical_sq;
		extern InteractionUtilityDec iud;
			extern Utility interaction_ut;
				extern InteractionHeadUtilityDec head_iud;
					extern InteractionMoveToHead move_to_head;
				extern InteractionHandUtilityDec hand_iud;
					extern InteractionMoveToHand move_to_hand;
				extern InteractionMotionUtilityDec motion_iud;
					extern Sequence interaction_motion_sq;
						extern Move move_hd_ccw;
						extern Move move_hd_cw;
						extern Move move_hd_cen;
						extern Move move_hd_up;
						extern Move move_hd_dwn;
		extern SeekingUtilityDec sud;
			extern Utility seeking_ut;
				extern SeekingSearchUtilityDec search_sud;
					extern SeekingMoveSearch move_search;
				extern SeekingBodyUtilityDec body_sud;
					extern SeekingMoveToBody move_to_body;
				extern SeekingMotionUtilityDec motion_sud;
					extern Sequence seeking_motion_sq;
						extern Move move_nk_up;
						extern Move move_nk_dwn;
						extern Move move_nk_cen;
}

namespace mcl {
	extern bool estop;
	extern std::mutex estop_lock;

	extern std::mutex bt_lock;
}

void executeBehaviours(std::string input);
void printDecoratorPriorities();

//std::vector<Behaviour*> currentBehaviours;
#endif
