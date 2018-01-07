#define BUFFERSIZE 1
#include "SIM900.h"

class gprs {
private:
     char _buffer[BUFFERSIZE];

public:
	void setupGPRS();
	void sendData(char *msg);
	void setting(char *url);
};