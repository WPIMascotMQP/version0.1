CFLAGS = -c -g -Wall --std=c++11
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


all: MasterControlLoop

MasterControlLoop: BehaviourTree.o Composite.o Controller.o \
	Decorator.o Sequence.o MoveBackDown.o MoveFrontLeft.o \
	MoveUpRight.o Node.o Parallel.o SensorData.o Utility.o \
	UtilityDec.o PUtilityDec.o SUtilityDec.o AudioProcessor.o \
	TouchProcessor.o VisualProcessor.o \
	MasterControlLoop.h
	g++ -g -Wall --std=c++11 -o MCL MasterControlLoop.cpp *.o -lm $(LIBS)

##### BEHAVIOUR CLASSES #####
MoveBackDown.o: $(BEHAVIOURS)MoveBackDown.cpp Behaviour.o $(BEHAVIOURS)MoveBackDown.h
	g++ $(CFLAGS) $(BEHAVIOURS)MoveBackDown.cpp

MoveFrontLeft.o: $(BEHAVIOURS)MoveFrontLeft.cpp Behaviour.o $(BEHAVIOURS)MoveFrontLeft.h
	g++ $(CFLAGS) $(BEHAVIOURS)MoveFrontLeft.cpp

MoveUpRight.o: $(BEHAVIOURS)MoveUpRight.cpp Behaviour.o $(BEHAVIOURS)MoveUpRight.h
	g++ $(CFLAGS) $(BEHAVIOURS)MoveUpRight.cpp

##### DECORATOR CLASSES #####
PUtilityDec.o: $(DECORATORS)PUtilityDec.cpp Decorator.o $(DECORATORS)PUtilityDec.h
	g++ $(CFLAGS) $(DECORATORS)PUtilityDec.cpp

SUtilityDec.o: $(DECORATORS)SUtilityDec.cpp Decorator.o $(DECORATORS)SUtilityDec.h
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

UtilityDec.o: $(DECORATOR)UtilityDec.cpp Decorator.o $(DECORATOR)UtilityDec.h
	g++ $(CFLAGS) $(DECORATOR)UtilityDec.cpp

Decorator.o: $(DECORATOR)Decorator.cpp Node.o $(DECORATOR)Decorator.h
	g++ $(CFLAGS) $(DECORATOR)Decorator.cpp

Behaviour.o: $(BEHAVIOURTREE)Behaviour.cpp Node.o Action.o $(BEHAVIOURTREE)Behaviour.h
	g++ $(CFLAGS) $(BEHAVIOURTREE)Behaviour.cpp

Node.o: $(BEHAVIOURTREE)Node.cpp Calculator.o Controller.o SensorData.o Status.o $(BEHAVIOURTREE)Node.h
	g++ $(CFLAGS) $(BEHAVIOURTREE)Node.cpp

##### PROCESSING CLASSES #####
Controller.o: $(COMMUNICATION)Controller.cpp Movement.o Position.o SensorData.o $(COMMUNICATION)Controller.h
	g++ $(CFLAGS) $(COMMUNICATION)Controller.cpp

Calculator.o: $(KINEMATICS)Calculator.cpp Movement.o SensorData.o Action.o $(KINEMATICS)Calculator.h
	g++ $(CFLAGS) $(KINEMATICS)Calculator.cpp
#Behaviour.o

AudioProcessor.o: $(PROCESSORS)AudioProcessor.cpp SensorProcessor.o $(PROCESSORS)AudioProcessor.h
	g++ $(CFLAGS) $(PROCESSORS)AudioProcessor.cpp 

TouchProcessor.o: $(PROCESSORS)TouchProcessor.cpp SensorProcessor.o $(PROCESSORS)TouchProcessor.h
	g++ $(CFLAGS) $(PROCESSORS)TouchProcessor.cpp

VisualProcessor.o: $(PROCESSORS)VisualProcessor.cpp SensorProcessor.o $(PROCESSORS)VisualProcessor.h
	g++ $(CFLAGS) $(PROCESSORS)VisualProcessor.cpp $(LIBS)

SensorProcessor.o: $(PROCESSORS)SensorProcessor.cpp $(PROCESSORS)SensorProcessor.h
	g++ $(CFLAGS) $(PROCESSORS)SensorProcessor.cpp

##### DATA CLASSES #####
Movement.o: $(KINEMATICS)Movement.cpp Position.o $(KINEMATICS)Movement.h
	g++ $(CFLAGS) $(KINEMATICS)Movement.cpp
#Behaviour.o

Status.o: Status.cpp Action.o Status.h
	g++ $(CFLAGS) Status.cpp

Action.o: $(KINEMATICS)Action.cpp Position.o $(KINEMATICS)Action.h
	g++ $(CFLAGS) $(KINEMATICS)Action.cpp

SensorData.o: SensorData.cpp Position.o SensorData.h
	g++ $(CFLAGS) SensorData.cpp

Position.o: $(KINEMATICS)Position.cpp $(KINEMATICS)Position.h
	g++ $(CFLAGS) $(KINEMATICS)Position.cpp

clean:
	rm -f *.o MCL

docs:
	doxygen
