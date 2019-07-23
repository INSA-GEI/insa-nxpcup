EESchema Schematic File Version 4
LIBS:Adaptateur_Camera2-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Insa:FTR-105-03-G-D-P-TR CN1
U 1 1 5C62E020
P 2050 2250
F 0 "CN1" H 2025 2665 50  0000 C CNN
F 1 "FTR-105-03-G-D-P-TR" H 2025 2574 50  0000 C CNN
F 2 "Insa:FTSH-10-1.27" H 2000 2600 50  0001 C CNN
F 3 "" H 2000 2600 50  0001 C CNN
	1    2050 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5C62E454
P 1750 2750
F 0 "#PWR0101" H 1750 2500 50  0001 C CNN
F 1 "GND" H 1755 2577 50  0000 C CNN
F 2 "" H 1750 2750 50  0001 C CNN
F 3 "" H 1750 2750 50  0001 C CNN
	1    1750 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 2050 1750 2150
Wire Wire Line
	1750 2150 1750 2250
Connection ~ 1750 2150
Wire Wire Line
	1750 2250 1750 2350
Connection ~ 1750 2250
Wire Wire Line
	1750 2350 1750 2450
Connection ~ 1750 2350
Wire Wire Line
	1750 2450 1750 2750
Connection ~ 1750 2450
Wire Wire Line
	2300 2050 2800 2050
Wire Wire Line
	2300 2150 2800 2150
Wire Wire Line
	2300 2250 2800 2250
Text Label 2500 2050 0    50   ~ 0
CCD_AO
Text Label 2500 2150 0    50   ~ 0
CCD_SI
Text Label 2500 2250 0    50   ~ 0
CCD_CLK
Wire Wire Line
	3000 2350 3000 1750
Wire Wire Line
	2300 2350 3000 2350
NoConn ~ 2300 2450
$Comp
L power:VDD #PWR0102
U 1 1 5C62E6FA
P 3000 1750
F 0 "#PWR0102" H 3000 1600 50  0001 C CNN
F 1 "VDD" H 3017 1923 50  0000 C CNN
F 2 "" H 3000 1750 50  0001 C CNN
F 3 "" H 3000 1750 50  0001 C CNN
	1    3000 1750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 5C8B5EDF
P 6050 2150
F 0 "J1" H 6130 2142 50  0000 L CNN
F 1 "Conn_01x06" H 6130 2051 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 6050 2150 50  0001 C CNN
F 3 "~" H 6050 2150 50  0001 C CNN
	1    6050 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 2450 5750 2450
Wire Wire Line
	5750 2450 5750 1800
Wire Wire Line
	5850 2350 5800 2350
Wire Wire Line
	5800 2350 5800 2650
Wire Wire Line
	5850 2250 5300 2250
Wire Wire Line
	5850 2050 5300 2050
Wire Wire Line
	5850 1950 5300 1950
NoConn ~ 5850 2150
$Comp
L power:VDD #PWR0103
U 1 1 5C8B6F45
P 5750 1800
F 0 "#PWR0103" H 5750 1650 50  0001 C CNN
F 1 "VDD" H 5767 1973 50  0000 C CNN
F 2 "" H 5750 1800 50  0001 C CNN
F 3 "" H 5750 1800 50  0001 C CNN
	1    5750 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5C8B7203
P 5800 2650
F 0 "#PWR0104" H 5800 2400 50  0001 C CNN
F 1 "GND" H 5805 2477 50  0000 C CNN
F 2 "" H 5800 2650 50  0001 C CNN
F 3 "" H 5800 2650 50  0001 C CNN
	1    5800 2650
	1    0    0    -1  
$EndComp
Text Label 5350 2250 0    50   ~ 0
CCD_AO
Text Label 5350 2050 0    50   ~ 0
CCD_CLK
Text Label 5350 1950 0    50   ~ 0
CCD_SI
$EndSCHEMATC
