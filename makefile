CFLAGS = -c -g -Wall --std=c++11 -lstdc++fs
OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV) -pthread

BEHAVIOURS = behaviours/
BEHAVIOURTREE = behaviourtree/
COMPOSITE = behaviourtree/composite/
DECORATOR = behaviourtree/decorator/
COMMUNICATION = communication/
DECORATORS = decorators/
KINEMATICS = kinematics/
PROCESSORS = processors/
MOTORSTATUS = processors/motorstatus/
TRACKERS = processors/visualtracking/

all: MasterControlLoop

MasterControlLoop: BehaviourTree.o \
	Controller.o \
	Logger.o \
	\
	BehaviourTree.o \
	Composite.o \
	Sequence.o \
	Parallel.o \
	SensorData.o \
	Utility.o \
	\
	AudioProcessor.o \
	MotorProcessor.o \
	SerialProcessor.o \
	VisualProcessor.o \
	\
	PUtilityDec.o \
	SUtilityDec.o \
	PhysicalUtilityDec.o \
	InteractionUtilityDec.o \
	InteractionHeadUtilityDec.o \
	InteractionHandUtilityDec.o \
	InteractionMotionUtilityDec.o \
	SeekingUtilityDec.o \
	SeekingSearchUtilityDec.o \
	SeekingBodyUtilityDec.o \
	SeekingMotionUtilityDec.o \
	\
	MoveBackDown.o \
	MoveFrontLeft.o \
	MoveUpRight.o \
	PhysicalMoveHead.o \
	InteractionMoveToHead.o \
	InteractionMoveToHand.o \
	SeekingMoveSearch.o \
	SeekingMoveToBody.o \
	Move.o \
	\
	MasterControlLoop.h
	g++ -g -Wall --std=c++11 -o MCL MasterControlLoop.cpp *.o -lm $(LIBS)

##### BEHAVIOUR CLASSES #####
PhysicalMoveHead.o: $(BEHAVIOURS)PhysicalMoveHead.cpp Behaviour.o $(BEHAVIOURS)PhysicalMoveHead.h
	g++ $(CFLAGS) $(BEHAVIOURS)PhysicalMoveHead.cpp


InteractionMoveToHead.o: $(BEHAVIOURS)InteractionMoveToHead.cpp Behaviour.o $(BEHAVIOURS)InteractionMoveToHead.h
	g++ $(CFLAGS) $(BEHAVIOURS)InteractionMoveToHead.cpp

InteractionMoveToHand.o: $(BEHAVIOURS)InteractionMoveToHand.cpp Behaviour.o $(BEHAVIOURS)InteractionMoveToHand.h
	g++ $(CFLAGS) $(BEHAVIOURS)InteractionMoveToHand.cpp


SeekingMoveSearch.o: $(BEHAVIOURS)SeekingMoveSearch.cpp Behaviour.o $(BEHAVIOURS)SeekingMoveSearch.h
	g++ $(CFLAGS) $(BEHAVIOURS)SeekingMoveSearch.cpp

SeekingMoveToBody.o: $(BEHAVIOURS)SeekingMoveToBody.cpp Behaviour.o $(BEHAVIOURS)SeekingMoveToBody.h
	g++ $(CFLAGS) $(BEHAVIOURS)SeekingMoveToBody.cpp


Move.o: $(BEHAVIOURS)Move.cpp Behaviour.o $(BEHAVIOURS)Move.h
	g++ $(CFLAGS) $(BEHAVIOURS)Move.cpp


MoveBackDown.o: $(BEHAVIOURS)MoveBackDown.cpp Behaviour.o $(BEHAVIOURS)MoveBackDown.h
	g++ $(CFLAGS) $(BEHAVIOURS)MoveBackDown.cpp

MoveFrontLeft.o: $(BEHAVIOURS)MoveFrontLeft.cpp Behaviour.o $(BEHAVIOURS)MoveFrontLeft.h
	g++ $(CFLAGS) $(BEHAVIOURS)MoveFrontLeft.cpp

MoveUpRight.o: $(BEHAVIOURS)MoveUpRight.cpp Behaviour.o $(BEHAVIOURS)MoveUpRight.h
	g++ $(CFLAGS) $(BEHAVIOURS)MoveUpRight.cpp

##### DECORATOR CLASSES #####
PhysicalUtilityDec.o: $(DECORATORS)PhysicalUtilityDec.cpp UtilityDec.o $(DECORATORS)PhysicalUtilityDec.h
	g++ $(CFLAGS) $(DECORATORS)PhysicalUtilityDec.cpp


InteractionUtilityDec.o: $(DECORATORS)InteractionUtilityDec.cpp UtilityDec.o $(DECORATORS)InteractionUtilityDec.h
	g++ $(CFLAGS) $(DECORATORS)InteractionUtilityDec.cpp

InteractionHeadUtilityDec.o: $(DECORATORS)InteractionHeadUtilityDec.cpp UtilityDec.o $(DECORATORS)InteractionHeadUtilityDec.h
	g++ $(CFLAGS) $(DECORATORS)InteractionHeadUtilityDec.cpp

InteractionHandUtilityDec.o: $(DECORATORS)InteractionHandUtilityDec.cpp UtilityDec.o $(DECORATORS)InteractionHandUtilityDec.h
	g++ $(CFLAGS) $(DECORATORS)InteractionHandUtilityDec.cpp

InteractionMotionUtilityDec.o: $(DECORATORS)InteractionMotionUtilityDec.cpp UtilityDec.o $(DECORATORS)InteractionMotionUtilityDec.h
	g++ $(CFLAGS) $(DECORATORS)InteractionMotionUtilityDec.cpp


SeekingUtilityDec.o: $(DECORATORS)SeekingUtilityDec.cpp UtilityDec.o $(DECORATORS)SeekingUtilityDec.h
	g++ $(CFLAGS) $(DECORATORS)SeekingUtilityDec.cpp

SeekingSearchUtilityDec.o: $(DECORATORS)SeekingSearchUtilityDec.cpp UtilityDec.o $(DECORATORS)SeekingSearchUtilityDec.h
	g++ $(CFLAGS) $(DECORATORS)SeekingSearchUtilityDec.cpp

SeekingBodyUtilityDec.o: $(DECORATORS)SeekingBodyUtilityDec.cpp UtilityDec.o $(DECORATORS)SeekingBodyUtilityDec.h
	g++ $(CFLAGS) $(DECORATORS)SeekingBodyUtilityDec.cpp

SeekingMotionUtilityDec.o: $(DECORATORS)SeekingMotionUtilityDec.cpp UtilityDec.o $(DECORATORS)SeekingMotionUtilityDec.h
	g++ $(CFLAGS) $(DECORATORS)SeekingMotionUtilityDec.cpp


PUtilityDec.o: $(DECORATORS)PUtilityDec.cpp UtilityDec.o $(DECORATORS)PUtilityDec.h
	g++ $(CFLAGS) $(DECORATORS)PUtilityDec.cpp

SUtilityDec.o: $(DECORATORS)SUtilityDec.cpp UtilityDec.o $(DECORATORS)SUtilityDec.h
	g++ $(CFLAGS) $(DECORATORS)SUtilityDec.cpp

##### BEHAVIOUR TREE CLASSES #####
BehaviourTree.o: $(BEHAVIOURTREE)BehaviourTree.cpp Node.o $(BEHAVIOURTREE)BehaviourTree.h
	g++ $(CFLAGS) $(BEHAVIOURTREE)BehaviourTree.cpp

Sequence.o: $(COMPOSITE)Sequence.cpp Composite.o $(COMPOSITE)Sequence.h
	g++ $(CFLAGS) $(COMPOSITE)Sequence.cpp

Parallel.o: $(COMPOSITE)Parallel.cpp Composite.o $(COMPOSITE)Parallel.h
	g++ $(CFLAGS) $(COMPOSITE)Parallel.cpp

Utility.o: $(COMPOSITE)Utility.cpp Composite.o UtilityDec.o $(COMPOSITE)Utility.h
	g++ $(CFLAGS) $(COMPOSITE)Utility.cpp

Composite.o: $(COMPOSITE)Composite.cpp Node.o $(COMPOSITE)Composite.h
	g++ $(CFLAGS) $(COMPOSITE)Composite.cpp

UtilityDec.o: $(DECORATOR)UtilityDec.cpp Decorator.o SensorData.o $(DECORATOR)UtilityDec.h
	g++ $(CFLAGS) $(DECORATOR)UtilityDec.cpp

Decorator.o: $(DECORATOR)Decorator.cpp Node.o $(DECORATOR)Decorator.h
	g++ $(CFLAGS) $(DECORATOR)Decorator.cpp

Behaviour.o: $(BEHAVIOURTREE)Behaviour.cpp Node.o Action.o $(BEHAVIOURTREE)Behaviour.h
	g++ $(CFLAGS) $(BEHAVIOURTREE)Behaviour.cpp

Node.o: $(BEHAVIOURTREE)Node.cpp Calculator.o Controller.o SensorData.o Status.o $(BEHAVIOURTREE)Node.h
	g++ $(CFLAGS) $(BEHAVIOURTREE)Node.cpp

##### COMMUNICATION CLASSES #####
SerialProcessor.o: $(COMMUNICATION)SerialProcessor.cpp SerialProcessor.o $(COMMUNICATION)SerialProcessor.h
	g++ $(CFLAGS) $(COMMUNICATION)SerialProcessor.cpp

##### PROCESSING CLASSES #####
Controller.o: $(COMMUNICATION)Controller.cpp Movement.o Position.o SensorData.o $(COMMUNICATION)Controller.h
	g++ $(CFLAGS) $(COMMUNICATION)Controller.cpp

Calculator.o: $(KINEMATICS)Calculator.cpp Movement.o SensorData.o Action.o $(KINEMATICS)Calculator.h
	g++ $(CFLAGS) $(KINEMATICS)Calculator.cpp
#Behaviour.o

SensorData.o: SensorData.cpp AudioProcessor.o MotorProcessor.o VisualProcessor.o Position.o SensorData.h
	g++ $(CFLAGS) SensorData.cpp

AudioProcessor.o: $(PROCESSORS)AudioProcessor.cpp SensorProcessor.o $(PROCESSORS)AudioProcessor.h
	g++ $(CFLAGS) $(PROCESSORS)AudioProcessor.cpp 

MotorProcessor.o: $(PROCESSORS)MotorProcessor.cpp SensorProcessor.o MotorStatus.o $(PROCESSORS)MotorProcessor.h
	g++ $(CFLAGS) $(PROCESSORS)MotorProcessor.cpp

VisualProcessor.o: $(PROCESSORS)VisualProcessor.cpp SensorProcessor.o VisualTrackerManager.o $(PROCESSORS)VisualProcessor.h
	g++ $(CFLAGS) $(PROCESSORS)VisualProcessor.cpp $(LIBS)

SensorProcessor.o: $(PROCESSORS)SensorProcessor.cpp $(PROCESSORS)SensorProcessor.h
	g++ $(CFLAGS) $(PROCESSORS)SensorProcessor.cpp

##### MOTOR STATUS CLASSES #####
MotorStatus.o: $(MOTORSTATUS)MotorStatus.cpp $(MOTORSTATUS)MotorStatus.h
	g++ $(CFLAGS) $(MOTORSTATUS)MotorStatus.cpp

##### VISUAL TRACKER CLASSES #####
VisualTrackerManager.o: $(TRACKERS)VisualTrackerManager.cpp VisualTracker.o $(TRACKERS)VisualTrackerManager.h
	g++ $(CFLAGS) $(TRACKERS)VisualTrackerManager.cpp $(LIBS)

VisualTracker.o: $(TRACKERS)VisualTracker.cpp $(TRACKERS)VisualTracker.h
	g++ $(CFLAGS) $(TRACKERS)VisualTracker.cpp $(LIBS)

##### DATA CLASSES #####
Movement.o: $(KINEMATICS)Movement.cpp Position.o $(KINEMATICS)Movement.h
	g++ $(CFLAGS) $(KINEMATICS)Movement.cpp
#Behaviour.o

Status.o: Status.cpp Action.o Status.h
	g++ $(CFLAGS) Status.cpp

Action.o: $(KINEMATICS)Action.cpp Position.o $(KINEMATICS)Action.h
	g++ $(CFLAGS) $(KINEMATICS)Action.cpp

Position.o: $(KINEMATICS)Position.cpp $(KINEMATICS)Position.h
	g++ $(CFLAGS) $(KINEMATICS)Position.cpp

Logger.o: Logger.cpp Logger.h
	g++ $(CFLAGS) Logger.cpp


##### CLEAN AND DOCS #####
clean:
	rm -f *.o MCL

docs:
	doxygen
