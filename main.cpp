#include <iostream>
#include<wiringPi.h>
#include<sys/time.h>
#include<unistd.h>

struct timeval ts;
struct timeval te;
int PWMTime;
void PWMread();

int main()
{
	int value;
	wiringPiSetup();
	piHiPri(99);
	pinMode(28, INPUT); //echo
	pinMode(29, OUTPUT); //trig
	pinMode(0, INPUT);
	float distance;
	wiringPiISR(28, INT_EDGE_BOTH, PWMread);
	while (true)
	{
		digitalWrite(29, HIGH);
		delayMicroseconds(10);
		digitalWrite(29, LOW);
		delayMicroseconds(1000);
	}
}

void PWMread()
{
	int value = digitalRead(28);
	if (value == 1)
	{
		gettimeofday(&ts, NULL);
		return;
	}
	gettimeofday(&te, NULL);
	PWMTime = te.tv_usec - ts.tv_usec;
	std::cout << PWMTime * 340 / 20000 << "\n";
}


/*void wiringPisuckUp();
{
	piHiPri(99);
	if (wiringPiSetup() == -1) {
		printf("[WiringPiStatus] WiringPi initialization failed !");
	}
	std::cout << "[WiringPiStatus] WiringPI SetSuccessfull !" << "\n";

	//----light
	pinMode(26, OUTPUT);
	digitalWrite(26, HIGH);
	sleep(1);
	digitalWrite(26, LOW);

	//----buzzer
	pinMode(7, OUTPUT);
	digitalWrite(7, HIGH);

	pinMode(0, INPUT);
	wiringPiISR(0, INT_EDGE_BOTH, PWMread);
}

*/

/*while (true)
{
	digitalWrite(29, HIGH);
	delayMicroseconds(10);
	digitalWrite(29, LOW);

	value = digitalRead(28);
	std::cout << digitalRead;
	if (value == 0)
	{
		std::cout << "\n";
	}
}*/;