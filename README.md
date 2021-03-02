# Heatman
Scuba diving heating regulator

The basic idea is:
1. We live in the country where the water at the lake bottom is usually 4 degrees Celsius, even in Summer, so we sometimes need electric heating underwater.
2. The heating vests, under suits, gloves etc. are designed for 12V supply. The total power can be up to 200W (110W under suit, 55W vest and 36W gloves). They are resistive devices, so the heating power is rising with square of voltage (P = U * U / R, where P is a power, U is a voltage and R is constant).
3. The most convenient li-ion cells can have voltage of 4.2V when fully charged and as low as 2.8V when discharged. They can be connected in series giving 5.6 - 8.4V (2 in series), 8.4 - 12.6V (3S) and 11.2 - 16.8V (4S)

Usually 3S battery is used for heating (voltage is 12.6V down to 8.4V), but as you can see it really doesn't match the heater 12V. At the end of discharge the power is only 45% od initial power.

We could use the 4S li-ion battery, which gives output voltage 16.8V when fully charged down to 11.2V fully discharged, but at the beginning it would generate much more heat than desired (theoretically 1.96 times more than @ 12V). So we need some voltage regulator to decrease the battery voltage to the level of expected supply voltage.

We don't really need the DC output because the heaters have high inertia, so we can switch the supply voltage on and off giving AVERAGE 12V value. Such regulation is called PWM (pulse with modulation) and is very effective.

My solution (circuit schematic will be added later):

1. Arduino board (nano or mini seems best candidates, because they are small)
2. N-channel "logic level" MOSFET connected to D9 output pin of Arduino board (can be any of 3, 5, 6, 9, 10, 11, see https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/ )
3. Resistor divider + zener diode 5.1V to measure battery voltage connected to A0 input (can be any of A0-A5, see https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)

Total cost of parts is about $5 (when ordered in China).

Feel free to comment and reuse my solution.

Contact to author: Jarek Andrzejewski fb.com/SP7SZM, ptja@ptja.pl
