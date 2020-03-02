#include "MasterControlLoop.h"

namespace nodes {
	BehaviourTree bt;
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

namespace mcl {
	bool estop;
	std::mutex estop_lock;

	std::mutex bt_lock;
}

int main(int argc, char* argv[]) {
	logger::startLog();
	// Create Behaviour Tree Objects
	using namespace nodes;

	// Link Behaviour Tree
	bt << ut_t1;
		ut_t1 << pud << iud << sud;
			pud << physical_sq;
				physical_sq << move_hd_up << move_hd_dwn;
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
						seeking_motion_sq << move_nk_up << move_hd_up << move_hd_cen << move_nk_dwn << move_nk_cen;
	logger::log("Behaviour Tree Objects Linked");
	interaction_motion_sq.reset();
	seeking_motion_sq.reset();

	//coms::behaviour_list_execute.push_back(&bt);

	//ap.startThread();
	processor::mp.startThread();
	processor::vp.startThread();
	serial::serial.startThread();

	std::string input = "";
	while(1) {
		std::getline(std::cin, input);
		if(input == "x") {
			break;
		}
		if(mcl::estop && input != "s") {
			continue;
		}
		mcl::estop_lock.lock();
		mcl::estop = false;
		mcl::estop_lock.unlock();

		data::sensor_data.setInput(input);
		serial::serial.finishBehaviours();

		executeBehaviours(input);
		coms::controller.execute();
	}
	logger::log("-----");
	logger::log("Exiting");
	logger::log("-----");
	//ap.killThread();
	processor::mp.killThread();
	processor::vp.killThread();
	serial::serial.killThread();


	coms::controller.clear();
	logger::log("Exited");
	logger::endLog();
}

void executeBehaviours(std::string input) {
	std::vector<Behaviour*>::iterator itr = coms::behaviour_list_execute.begin();
	while (itr < coms::behaviour_list_execute.end()) {
		Behaviour* behaviour = *itr;
		Status* result = input.find("f") == std::string::npos ?
			behaviour->executeP(Status().setSuccess()) : behaviour->executeP(Status().setFailure());
		logger::log("Executed Behaviour", behaviour->toString(), "Status", result->toString());
		coms::behaviour_list_execute.erase(itr);
	}

	size_t ind = 0;
	std::vector<std::string> tokens;
	while((ind = s.find(" ")) != std::string::npos) {
		tokens.push_back(input.substr(0, ind));
		input.erase(0, ind + 1);
	}
	if(tokens.at(0) == "d" && tokens.size() == 3) {
		double dy = std::atod(tokens.at(1));
		double dp = std::atod(tokens.at(2));
		std::shared_ptr<Position> pos = cal::calculator.getDeltaPosition(0, 0, dy, dp);
		coms::controller.addPosition(pos);
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
