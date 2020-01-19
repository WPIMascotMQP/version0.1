CFLAGS = -c -g -Wall --std=c++11
OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV) -pthread

PROCESSORS = processors/
KINEMATICS = kinematics/

all: MasterControlLoop

MasterControlLoop: BehaviourTree.o Composite.o Controller.o \
	Decorator.o Sequence.o MoveBackDown.o MoveFrontLeft.o \
	MoveUpRight.o Node.o Parallel.o SensorData.o Utility.o \
	UtilityDec.o PUtilityDec.o SUtilityDec.o VisualProcessor.o \
	MasterControlLoop.h
	g++ -g -Wall --std=c++11 -o MCL MasterControlLoop.cpp *.o -lm $(LIBS)

##### BEHAVIOUR CLASSES #####
MoveBackDown.o: MoveBackDown.cpp Behaviour.o MoveBackDown.h
	g++ $(CFLAGS) MoveBackDown.cpp

MoveFrontLeft.o: MoveFrontLeft.cpp Behaviour.o MoveFrontLeft.h
	g++ $(CFLAGS) MoveFrontLeft.cpp

MoveUpRight.o: MoveUpRight.cpp Behaviour.o MoveUpRight.h
	g++ $(CFLAGS) MoveUpRight.cpp

##### DECORATOR CLASSES #####
PUtilityDec.o: PUtilityDec.cpp Decorator.o PUtilityDec.h
	g++ $(CFLAGS) PUtilityDec.cpp

SUtilityDec.o: SUtilityDec.cpp Decorator.o SUtilityDec.h
	g++ $(CFLAGS) SUtilityDec.cpp

##### BEHAVIOUR TREE CLASSES #####
BehaviourTree.o: BehaviourTree.cpp Node.o BehaviourTree.h
	g++ $(CFLAGS) BehaviourTree.cpp

Sequence.o: Sequence.cpp Composite.o Sequence.h
	g++ $(CFLAGS) Sequence.cpp

Parallel.o: Parallel.cpp Composite.o Parallel.h
	g++ $(CFLAGS) Parallel.cpp

Utility.o: Utility.cpp Composite.o UtilityDec.o Utility.h
	g++ $(CFLAGS) Utility.cpp

Composite.o: Composite.cpp Node.o Composite.h
	g++ $(CFLAGS) Composite.cpp

UtilityDec.o: UtilityDec.cpp Decorator.o UtilityDec.h
	g++ $(CFLAGS) UtilityDec.cpp

Decorator.o: Decorator.cpp Node.o Decorator.h
	g++ $(CFLAGS) Decorator.cpp

Behaviour.o: Behaviour.cpp Node.o Action.o Behaviour.h
	g++ $(CFLAGS) Behaviour.cpp

Node.o: Node.cpp Calculator.o Controller.o SensorData.o Status.o Node.h
	g++ $(CFLAGS) Node.cpp

##### PROCESSING CLASSES #####
Controller.o: Controller.cpp Movement.o Position.o SensorData.o Controller.h
	g++ $(CFLAGS) Controller.cpp

Calculator.o: $(KINEMATICS)Calculator.cpp Movement.o SensorData.o Action.o $(KINEMATICS)Calculator.h
	g++ $(CFLAGS) $(KINEMATICS)Calculator.cpp
#Behaviour.o

AudioProcessor.o: $(PROCESSORSc)AudioProcessor.cpp SensorProcessor.o $(PROCESSORS)AudioProcessor.h
	g++ $(CFLAGS) $(PROCESSORS)AudioProcessor.cpp 

TouchProcessor.o: $(PROCESSORS)TouchProcessor.cpp SensorProcessor.o $(PROCESSORS)TouchProcessor.h
	g++ $(CFLAGS) $(PROCESSORS)TouchProcessor.cpp

VisualProcessor.o: $(PROCESSORS)VisualProcessor.cpp SensorProcessor.o $(PROCESSORS)VisualProcessor.h
	g++ $(CFLAGS) $(PROCESSORS)VisualProcessor.cpp $(LIBS)

SensorProcessor.o: $(PROCESSORS)SensorProcessor.cpp $(PROCESSORS)SensorProcessor.h
	g++ $(CFLAGS) $(PROCESSORS)SensorProcessor.cpp

##### DATA CLASSES #####
Movement.o: Movement.cpp Position.o Movement.h
	g++ $(CFLAGS) Movement.cpp
#Behaviour.o

Status.o: Status.cpp Action.o Status.h
	g++ $(CFLAGS) Status.cpp

Action.o: Action.cpp Position.o Action.h
	g++ $(CFLAGS) Action.cpp

SensorData.o: SensorData.cpp Position.o SensorData.h
	g++ $(CFLAGS) SensorData.cpp

Position.o: Position.cpp Position.h
	g++ $(CFLAGS) Position.cpp

clean:
	rm -f *.o MCL

docs:
	doxygen
