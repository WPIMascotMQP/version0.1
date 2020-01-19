#ifndef TOUCHPROCESSOR_H
#define TOUCHPROCESSOR_H

class TouchProcessor : public SensorProcessor {
public:
	TouchProcessor();
	~TouchProcessor();

	void startThread();
	void process();
protected:
private:
};
#endif