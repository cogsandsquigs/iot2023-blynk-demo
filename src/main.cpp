/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/admin/Projects/iot2023-blynk-demo/src/main.ino"
// Where the secrets are located. This should ALWAYS come first! Otherwise, Blynk won't initialize properly.
#include "env.h"

// Other libraries.
#include "blynk.h" // Blynk library that allows us to connect to the Blynk cloud.

// Configuration.
void setup();
void loop();
#line 8 "/Users/admin/Projects/iot2023-blynk-demo/src/main.ino"
#define HARDWARE_BUTTON_PIN D7						   // The hardware button that will be used to send push notifications.
#define VIRTUAL_BUTTON_PIN V0						   // The virtual button that will also be used to send push notifications.
#define VIRTUAL_LED_PIN V1							   // The virtual LED that will be used to display the state of the hardware button.
#define NOTIFY_EVENT_CODE "notify"					   // Notification event code. Replace "notify" with the code for the event you created.
#define HARDWARE_NOTIFY_MSG "Hardware button pressed!" // Notification message for the hardware button.
#define VIRTUAL_NOTIFY_MSG "Virtual button pressed!"   // Notification message for the hardware button.

// Multi-threading.
SYSTEM_THREAD(ENABLED);

// Variable for checking if the button has already been pressed.
bool hardware_button_pressed = false;

// Configure connection to Blynk cloud.
void setup()
{
	pinMode(HARDWARE_BUTTON_PIN, INPUT);
	Serial.begin(9600);

	// Connects to Blynk cloud. BLYNK_AUTH_TOKEN is the token that allows the device to connect to the Blynk cloud,
	// and is stored in "env.h". BLYNK_TEMPLATE_ID and BLYNK_TEMPLATE_NAME are the template ID and name of the
	// template that the device is connected to. These are also stored in "env.h". "env.h" is not included in the
	// repository, so you will need to create your own file with these values.
	Blynk.begin(BLYNK_AUTH_TOKEN);
}

// Check the state of the hardware button and send push notifications to the device owner.
void loop()
{
	// Runs code that allows Blynk to communicate with the device. Should come first here.
	Blynk.run();

	int button_state = digitalRead(HARDWARE_BUTTON_PIN);

	// Write the button state to the virtual LED.
	Blynk.virtualWrite(VIRTUAL_LED_PIN, button_state);

	// If the button is pressed for the first time, send a push notification to the device owner.
	if (button_state && !hardware_button_pressed)
	{
		Serial.println(HARDWARE_NOTIFY_MSG);

		// Sends an event to Blynk cloud. This event should be configured so that it sends a push notification to the
		// device owner.
		Blynk.logEvent(NOTIFY_EVENT_CODE, HARDWARE_NOTIFY_MSG);

		// If the button is pressed, and the button has not been pressed before, then set hardware_button_pressed to true.
		hardware_button_pressed = true;
	}
	// If the button has been pressed before, and the button is not pressed, then set hardware_button_pressed to false.
	else if (!button_state && hardware_button_pressed)
	{
		// If the button is not pressed, but the button has been pressed before, then set hardware_button_pressed to false.
		hardware_button_pressed = false;
	}
}

// This code runs everytime the virtual pin V0 changes. There is no need to put this in the loop, as Blynk will
// automatically run this code when the virtual pin changes. This code is used to check if the virtual button
// has been pressed. If it has, then send a push notification to the device owner.
BLYNK_WRITE(VIRTUAL_BUTTON_PIN)
{
	// Checks if the button was pressed (param.asInt() == 1). If it is, then send a push notification to the device owner.
	if (param.asInt())
	{
		Serial.println(VIRTUAL_NOTIFY_MSG);

		// Sends an event to Blynk cloud. This event should be configured so that it sends a push notification to the
		// device owner.
		Blynk.logEvent(NOTIFY_EVENT_CODE, VIRTUAL_NOTIFY_MSG);
	}
}