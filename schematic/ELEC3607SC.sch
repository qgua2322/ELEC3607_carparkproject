EESchema Schematic File Version 2
LIBS:ELEC3607SC-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Mylib
LIBS:ELEC3607SC-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ELEC3607 project9"
Date "2017-06-11"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ArduinoLCD U?
U 1 1 593BF852
P 1850 2800
F 0 "U?" H 1950 2800 60  0000 C CNN
F 1 "ArduinoLCD" H 1550 2800 60  0000 C CNN
F 2 "" H 1550 2800 60  0001 C CNN
F 3 "" H 1550 2800 60  0001 C CNN
	1    1850 2800
	1    0    0    -1  
$EndComp
$Comp
L ServoMotor U?
U 1 1 593C0206
P 6800 6700
F 0 "U?" H 6200 7500 60  0000 C CNN
F 1 "ServoMotor" H 6200 7700 60  0000 C CNN
F 2 "" H 6200 7650 60  0001 C CNN
F 3 "" H 6200 7650 60  0001 C CNN
	1    6800 6700
	1    0    0    -1  
$EndComp
$Comp
L BluetoothSh U?
U 1 1 593C0291
P 8900 3850
F 0 "U?" H 8900 3850 60  0000 C CNN
F 1 "BluetoothSh" H 8950 4100 60  0000 C CNN
F 2 "" H 8900 3850 60  0001 C CNN
F 3 "" H 8900 3850 60  0001 C CNN
	1    8900 3850
	1    0    0    -1  
$EndComp
$Comp
L LD274 D?
U 1 1 593C0212
P 7150 1000
F 0 "D?" H 7170 1070 50  0000 L CNN
F 1 "LD274" H 7110 890 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 7150 1175 50  0001 C CNN
F 3 "" H 7100 1000 50  0000 C CNN
	1    7150 1000
	1    0    0    -1  
$EndComp
$Comp
L IRsensor RSIP13?
U 1 1 593C046E
P 5650 1450
F 0 "RSIP13?" H 5050 1800 60  0000 C CNN
F 1 "IRsensor" H 5050 2000 60  0000 C CNN
F 2 "" H 5050 1800 60  0001 C CNN
F 3 "" H 5050 1800 60  0001 C CNN
	1    5650 1450
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 593C05CA
P 7500 1350
F 0 "R?" V 7580 1350 50  0000 C CNN
F 1 "220" V 7500 1350 50  0000 C CNN
F 2 "" V 7430 1350 50  0001 C CNN
F 3 "" H 7500 1350 50  0001 C CNN
	1    7500 1350
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 593C068D
P 5750 1250
F 0 "R?" V 5830 1250 50  0000 C CNN
F 1 "220" V 5750 1250 50  0000 C CNN
F 2 "" V 5680 1250 50  0001 C CNN
F 3 "" H 5750 1250 50  0001 C CNN
	1    5750 1250
	1    0    0    -1  
$EndComp
$Comp
L ArduinoDUE U?
U 1 1 593C99BA
P 5550 3200
F 0 "U?" H 5800 3200 60  0000 C CNN
F 1 "ArduinoDUE" H 5450 3200 60  0000 C CNN
F 2 "" H 5450 3200 60  0001 C CNN
F 3 "" H 5450 3200 60  0001 C CNN
	1    5550 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 3800 6700 3600
Wire Wire Line
	6700 3750 8100 4000
Wire Wire Line
	2850 2800 4450 3750
Wire Wire Line
	4450 3900 2850 2900
Wire Wire Line
	4450 4050 2850 3050
Wire Wire Line
	8100 3350 8100 2050
Wire Wire Line
	8100 2050 3650 2050
Connection ~ 3650 2050
Wire Wire Line
	7250 1000 7500 1000
Wire Wire Line
	7500 1000 7500 1200
Wire Wire Line
	6700 3350 7500 3350
Wire Wire Line
	7500 3350 7500 1500
Wire Wire Line
	4000 3850 2850 3850
Wire Wire Line
	4000 1400 4000 5950
Wire Wire Line
	4000 2700 4450 2700
Wire Wire Line
	4700 1400 4000 1400
Connection ~ 4000 2700
Wire Wire Line
	4700 1250 4700 850 
Wire Wire Line
	4700 850  5750 850 
Wire Wire Line
	5750 850  5750 1100
Wire Wire Line
	5750 1400 6900 1400
Wire Wire Line
	6900 1400 6900 3200
Wire Wire Line
	6900 3200 6700 3200
Wire Wire Line
	4700 1550 3650 1550
Wire Wire Line
	8100 3550 7800 3550
Wire Wire Line
	7800 3550 7800 1800
Wire Wire Line
	7800 1800 4000 1800
Connection ~ 4000 1800
Wire Wire Line
	6950 1000 6350 1000
Wire Wire Line
	6350 1000 6350 1800
Connection ~ 6350 1800
Wire Wire Line
	4600 5850 4350 5850
Wire Wire Line
	4350 5850 4350 2550
Wire Wire Line
	4350 2550 4450 2550
Wire Wire Line
	4000 5950 4600 5950
Connection ~ 4000 3850
Wire Wire Line
	4600 5900 4600 4900
Wire Wire Line
	4600 4900 7200 4900
Wire Wire Line
	7200 4900 7200 2450
Wire Wire Line
	7200 2450 6700 2450
Wire Wire Line
	3650 2700 2850 2700
Wire Wire Line
	4450 2400 3650 2400
Wire Wire Line
	3650 1550 3650 3750
Connection ~ 3650 2400
Wire Wire Line
	3650 3750 2850 3750
Connection ~ 3650 2700
Wire Wire Line
	2850 3600 3150 3600
Wire Wire Line
	3150 3600 3150 5350
Wire Wire Line
	3150 5350 7050 5350
Wire Wire Line
	7050 5350 7050 2900
Wire Wire Line
	7050 2900 6700 2900
Wire Wire Line
	6700 2750 6800 2750
Wire Wire Line
	6800 2750 6800 2150
Wire Wire Line
	6800 2150 3000 2150
Wire Wire Line
	3000 2150 3000 3450
Wire Wire Line
	3000 3450 2850 3450
Wire Wire Line
	6700 2200 6700 2600
Wire Wire Line
	2900 2200 6700 2200
Wire Wire Line
	2900 2200 2900 3200
Wire Wire Line
	2900 3200 2850 3200
Wire Wire Line
	2850 3300 2850 5200
Wire Wire Line
	2850 5200 6800 5200
Wire Wire Line
	6800 5200 6800 3050
Wire Wire Line
	6800 3050 6700 3050
$EndSCHEMATC
