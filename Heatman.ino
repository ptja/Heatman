// uncomment for testing only
//#define UNIT_TESTING 1

// pin controlling output MOSFET
#define PWMpin 9

// battery voltage input (via divider)
#define INPUT_VOLTAGE_PIN A0

// number of samples of battery voltage for calculating average
#define SAMPLES 1024

// maximum analog reading (10 bit for Uno, Nano etc., 12 bit for Zero, Due etc.)
#define ANALOG_MAX_VALUE 1024

// ADC reference voltage (typically 5V for Uno, Nano etc., 3.3V for Zero, Due etc.)
#define VREF ((float)5.0)

// battery voltage to ADC divider. It should give a bit less than VREF @ maximum expected battery voltage
// for example for 4S li-ion battery maximum is 16.8V, so the divider can be 5V / 16.8V = 0,2976 (rounded down: 0.28)
#define DIVIDER ((float)0.28)

// typically 12V, but you can change it up/down to get less/more heat
#define DESIRED_OUTPUT_VOLTAGE 12.0

// PWM value for constant "on"
#define PWM_MAX_VALUE 255

void setup() {
	Serial.begin(115200);
	Serial.println("Scuba diver heating regulator.\r\n(C) 2020 Jarek Andrzejewski SP7SZM\r\n");

#ifdef UNIT_TESTING
	Serial.println("Testing\r\n");
	for (int i=0;i<=1024;i++) {
		Serial.print(i);
		Serial.print(";");
		Serial.print(AnalogRead2AccuVoltage(i));
		Serial.print(";");
		Serial.println(AccuVoltage2PWM(AnalogRead2AccuVoltage(i), DESIRED_OUTPUT_VOLTAGE));
	}
#endif
}

void loop() {
	long averageAnalogReading = 0;
	for (int i=0;i<SAMPLES; i++) {
		int analogReading = analogRead(INPUT_VOLTAGE_PIN);
		averageAnalogReading += analogReading;
		delay(1);
	}
	averageAnalogReading = (int)(averageAnalogReading >> 10); // use divide instead of bit shift if SAMPLES is not power of 2
	float voltage = AnalogRead2AccuVoltage(averageAnalogReading);
	int pwm = AccuVoltage2PWM(voltage, DESIRED_OUTPUT_VOLTAGE);
	analogWrite(PWMpin, pwm);
	
	Serial.print(voltage);
	Serial.print("V, PWM=");
	Serial.println(pwm);

}

float AnalogRead2AccuVoltage(int value) {
	return VREF * (float)value/(float)ANALOG_MAX_VALUE / DIVIDER;
}


int AccuVoltage2PWM(float inputVoltage, float desiredVoltage) {
	if (inputVoltage<desiredVoltage) {
		return PWM_MAX_VALUE;
	} else {
		return (int)((float)PWM_MAX_VALUE * desiredVoltage/inputVoltage);
	}
}