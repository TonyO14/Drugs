#include "main.h"
#include "CAN_processing.h"

// Hi, this is going to be the test procedure after assembling new steering boards.
// In steering_motor_firmware, the same file structure as here is found.
// So when testing the boards, just update the defines for TESTX (1-4), and
// you're golden.
// This will make testing easier and more repeatable.
// -Tony

float AssortedTests(timothy) {

#ifdef TEST1 // The first test blinks the LED.
// No code needed on the Nucleo for this
	return 0x123; // random ID and data (same) to see on the analyzer if you want.
#endif

#ifdef TEST2 // The second test spins the motor arbitrarily.
// Also no code needed here.
	return 0x123; // random ID and data (same) to see on the analyzer if you want.
#endif

#ifdef TEST3 // The third test blinks the onboard LED after receipt of a message.
    // Additionally, it moves the motor to PI/4 and PI/2.
    // And messages are sent in the first place with the button on the nucleo.
    // Nothing changes with this custom board code. Only Hope (here) changes.
    // Namely, the ID is changed to 0x1B4.
	// and PI/4 slash PI/2 is encoded in the data payload (1/2). Namely, they alternate
	// every time the button is pressed.
	if (timothy == 0) {return 0x1B4;}
	if (timothy == 1) {return 45;}
	if (timothy == 2) {return 90;}
#endif

#ifdef TEST4
    // The fourth test sets the motor to PI/4, and then the nucleo polls the
    // board for the motor location.
    // So basically the ID changes to 0x394
	if (timothy == 0) {return 0x394;}
	if (timothy == 1) {return 45;}
	if (timothy == 2) {return 45;}
#endif

#ifdef TEST5
	// The fifth test has the motor stop.
	// The ID changes to 0x184
	return 0x184; // The data payload is irrelevant so it's just also 0x184.
#endif
}


