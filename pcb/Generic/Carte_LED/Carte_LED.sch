EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Carte_LED"
Date "2020-02-05"
Rev "1.1"
Comp "INSA GEI"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+BATT #PWR0101
U 1 1 5DB254E3
P 2150 1200
F 0 "#PWR0101" H 2150 1050 50  0001 C CNN
F 1 "+BATT" H 2165 1373 50  0000 C CNN
F 2 "" H 2150 1200 50  0001 C CNN
F 3 "" H 2150 1200 50  0001 C CNN
	1    2150 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5DB263A8
P 2150 1350
F 0 "#PWR0102" H 2150 1100 50  0001 C CNN
F 1 "GND" H 2155 1177 50  0000 C CNN
F 2 "" H 2150 1350 50  0001 C CNN
F 3 "" H 2150 1350 50  0001 C CNN
	1    2150 1350
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5DB28080
P 2650 1150
F 0 "#FLG0101" H 2650 1225 50  0001 C CNN
F 1 "PWR_FLAG" H 2650 1323 50  0000 C CNN
F 2 "" H 2650 1150 50  0001 C CNN
F 3 "~" H 2650 1150 50  0001 C CNN
	1    2650 1150
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5DB283CA
P 2650 1350
F 0 "#FLG0102" H 2650 1425 50  0001 C CNN
F 1 "PWR_FLAG" H 2650 1523 50  0000 C CNN
F 2 "" H 2650 1350 50  0001 C CNN
F 3 "~" H 2650 1350 50  0001 C CNN
	1    2650 1350
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5DB286DE
P 1650 1300
F 0 "J1" H 1568 1067 50  0000 C CNN
F 1 "Conn_01x02" H 1568 1066 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1650 1300 50  0001 C CNN
F 3 "~" H 1650 1300 50  0001 C CNN
	1    1650 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	1850 1200 2150 1200
Wire Wire Line
	1850 1300 2150 1300
Wire Wire Line
	2150 1300 2150 1350
Wire Wire Line
	2150 1200 2650 1200
Wire Wire Line
	2650 1200 2650 1150
Connection ~ 2150 1200
Wire Wire Line
	2150 1300 2650 1300
Wire Wire Line
	2650 1300 2650 1350
Connection ~ 2150 1300
$Comp
L Device:R R1
U 1 1 5DB3D9FC
P 2000 4450
F 0 "R1" H 2070 4496 50  0000 L CNN
F 1 "0R" H 2070 4405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P2.54mm_Vertical" V 1930 4450 50  0001 C CNN
F 3 "~" H 2000 4450 50  0001 C CNN
	1    2000 4450
	-1   0    0    1   
$EndComp
$Comp
L power:+BATT #PWR0103
U 1 1 5DB41AB0
P 4150 1650
F 0 "#PWR0103" H 4150 1500 50  0001 C CNN
F 1 "+BATT" H 4165 1823 50  0000 C CNN
F 2 "" H 4150 1650 50  0001 C CNN
F 3 "" H 4150 1650 50  0001 C CNN
	1    4150 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5DB41E88
P 3150 5900
F 0 "#PWR0104" H 3150 5650 50  0001 C CNN
F 1 "GND" H 3155 5727 50  0000 C CNN
F 2 "" H 3150 5900 50  0001 C CNN
F 3 "" H 3150 5900 50  0001 C CNN
	1    3150 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 5850 3150 5900
$Comp
L Mechanical:MountingHole H1
U 1 1 5DB43E65
P 1700 2000
F 0 "H1" H 1800 2000 50  0000 L CNN
F 1 "MountingHole" H 1800 1955 50  0001 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 1700 2000 50  0001 C CNN
F 3 "~" H 1700 2000 50  0001 C CNN
	1    1700 2000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5DB44B5D
P 2250 2000
F 0 "H2" H 2350 2000 50  0000 L CNN
F 1 "MountingHole" H 2350 1955 50  0001 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 2250 2000 50  0001 C CNN
F 3 "~" H 2250 2000 50  0001 C CNN
	1    2250 2000
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5E2F1F3A
P 5950 1200
F 0 "JP1" H 5950 1313 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 5950 1314 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 5950 1314 50  0001 C CNN
F 3 "~" H 5950 1200 50  0001 C CNN
	1    5950 1200
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP2
U 1 1 5E2F3C63
P 5950 1650
F 0 "JP2" H 5950 1763 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 5950 1764 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 5950 1650 50  0001 C CNN
F 3 "~" H 5950 1650 50  0001 C CNN
	1    5950 1650
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AMS1117-5.0 U1
U 1 1 5E2F49C4
P 5000 1650
F 0 "U1" H 5000 1892 50  0000 C CNN
F 1 "ZLDO1117G50TA" H 5000 1801 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 5000 1850 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1769101.pdf" H 5100 1400 50  0001 C CNN
	1    5000 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5E2F8E21
P 5000 2050
F 0 "#PWR0105" H 5000 1800 50  0001 C CNN
F 1 "GND" H 5005 1877 50  0000 C CNN
F 2 "" H 5000 2050 50  0001 C CNN
F 3 "" H 5000 2050 50  0001 C CNN
	1    5000 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5E2F92A1
P 4400 1850
F 0 "C1" H 4515 1896 50  0000 L CNN
F 1 "4.7µF" H 4515 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4438 1700 50  0001 C CNN
F 3 "~" H 4400 1850 50  0001 C CNN
	1    4400 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E2F9B24
P 5450 1850
F 0 "C2" H 5565 1896 50  0000 L CNN
F 1 "4.7µF" H 5565 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5488 1700 50  0001 C CNN
F 3 "~" H 5450 1850 50  0001 C CNN
	1    5450 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 1650 4400 1650
Wire Wire Line
	4400 2000 5000 2000
Wire Wire Line
	5000 1950 5000 2000
Wire Wire Line
	5300 1650 5450 1650
Wire Wire Line
	5450 1700 5450 1650
Connection ~ 5450 1650
Wire Wire Line
	5450 1650 5800 1650
Wire Wire Line
	4400 1700 4400 1650
Connection ~ 4400 1650
Wire Wire Line
	4400 1650 4700 1650
Connection ~ 5000 2000
Wire Wire Line
	5000 2000 5450 2000
Wire Wire Line
	5000 2000 5000 2050
$Comp
L power:+5V #PWR0106
U 1 1 5E2FC762
P 6300 1050
F 0 "#PWR0106" H 6300 900 50  0001 C CNN
F 1 "+5V" H 6315 1223 50  0000 C CNN
F 2 "" H 6300 1050 50  0001 C CNN
F 3 "" H 6300 1050 50  0001 C CNN
	1    6300 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1650 6300 1650
Wire Wire Line
	6300 1650 6300 1200
Wire Wire Line
	6100 1200 6300 1200
Connection ~ 6300 1200
Wire Wire Line
	6300 1200 6300 1050
Wire Wire Line
	5800 1200 4400 1200
Wire Wire Line
	4400 1200 4400 1650
$Comp
L power:+5V #PWR0107
U 1 1 5E306037
P 3100 4150
F 0 "#PWR0107" H 3100 4000 50  0001 C CNN
F 1 "+5V" H 3115 4323 50  0000 C CNN
F 2 "" H 3100 4150 50  0001 C CNN
F 3 "" H 3100 4150 50  0001 C CNN
	1    3100 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5E3074BF
P 2000 4900
F 0 "D1" V 2039 4782 50  0000 R CNN
F 1 "VLCS5830" V 1948 4782 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_Clear" H 2000 4900 50  0001 C CNN
F 3 "~" H 2000 4900 50  0001 C CNN
	1    2000 4900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D2
U 1 1 5E307AE6
P 2000 5450
F 0 "D2" V 2039 5332 50  0000 R CNN
F 1 "VLCS5830" V 1948 5332 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_Clear" H 2000 5450 50  0001 C CNN
F 3 "~" H 2000 5450 50  0001 C CNN
	1    2000 5450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5E3095D8
P 2450 4450
F 0 "R2" H 2520 4496 50  0000 L CNN
F 1 "0R" H 2520 4405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P2.54mm_Vertical" V 2380 4450 50  0001 C CNN
F 3 "~" H 2450 4450 50  0001 C CNN
	1    2450 4450
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D3
U 1 1 5E3095DE
P 2450 4900
F 0 "D3" V 2489 4782 50  0000 R CNN
F 1 "VLCS5830" V 2398 4782 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_Clear" H 2450 4900 50  0001 C CNN
F 3 "~" H 2450 4900 50  0001 C CNN
	1    2450 4900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D4
U 1 1 5E3095E4
P 2450 5450
F 0 "D4" V 2489 5332 50  0000 R CNN
F 1 "VLCS5830" V 2398 5332 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_Clear" H 2450 5450 50  0001 C CNN
F 3 "~" H 2450 5450 50  0001 C CNN
	1    2450 5450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 5E30A397
P 2900 4450
F 0 "R3" H 2970 4496 50  0000 L CNN
F 1 "0R" H 2970 4405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P2.54mm_Vertical" V 2830 4450 50  0001 C CNN
F 3 "~" H 2900 4450 50  0001 C CNN
	1    2900 4450
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D5
U 1 1 5E30A39D
P 2900 4900
F 0 "D5" V 2939 4782 50  0000 R CNN
F 1 "VLCS5830" V 2848 4782 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_Clear" H 2900 4900 50  0001 C CNN
F 3 "~" H 2900 4900 50  0001 C CNN
	1    2900 4900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D6
U 1 1 5E30A3A3
P 2900 5450
F 0 "D6" V 2939 5332 50  0000 R CNN
F 1 "VLCS5830" V 2848 5332 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_Clear" H 2900 5450 50  0001 C CNN
F 3 "~" H 2900 5450 50  0001 C CNN
	1    2900 5450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R4
U 1 1 5E30B543
P 3300 4450
F 0 "R4" H 3370 4496 50  0000 L CNN
F 1 "0R" H 3370 4405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P2.54mm_Vertical" V 3230 4450 50  0001 C CNN
F 3 "~" H 3300 4450 50  0001 C CNN
	1    3300 4450
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D7
U 1 1 5E30B549
P 3300 4900
F 0 "D7" V 3339 4782 50  0000 R CNN
F 1 "VLCS5830" V 3248 4782 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_Clear" H 3300 4900 50  0001 C CNN
F 3 "~" H 3300 4900 50  0001 C CNN
	1    3300 4900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D8
U 1 1 5E30B54F
P 3300 5450
F 0 "D8" V 3339 5332 50  0000 R CNN
F 1 "VLCS5830" V 3248 5332 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_Clear" H 3300 5450 50  0001 C CNN
F 3 "~" H 3300 5450 50  0001 C CNN
	1    3300 5450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R5
U 1 1 5E30C587
P 3750 4450
F 0 "R5" H 3820 4496 50  0000 L CNN
F 1 "0R" H 3820 4405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P2.54mm_Vertical" V 3680 4450 50  0001 C CNN
F 3 "~" H 3750 4450 50  0001 C CNN
	1    3750 4450
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D9
U 1 1 5E30C58D
P 3750 4900
F 0 "D9" V 3789 4782 50  0000 R CNN
F 1 "VLCS5830" V 3698 4782 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_Clear" H 3750 4900 50  0001 C CNN
F 3 "~" H 3750 4900 50  0001 C CNN
	1    3750 4900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D10
U 1 1 5E30C593
P 3750 5450
F 0 "D10" V 3789 5332 50  0000 R CNN
F 1 "VLCS5830" V 3698 5332 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_Clear" H 3750 5450 50  0001 C CNN
F 3 "~" H 3750 5450 50  0001 C CNN
	1    3750 5450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R6
U 1 1 5E310223
P 4200 4450
F 0 "R6" H 4270 4496 50  0000 L CNN
F 1 "0R" H 4270 4405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P2.54mm_Vertical" V 4130 4450 50  0001 C CNN
F 3 "~" H 4200 4450 50  0001 C CNN
	1    4200 4450
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D11
U 1 1 5E310229
P 4200 4900
F 0 "D11" V 4239 4782 50  0000 R CNN
F 1 "VLCS5830" V 4148 4782 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_Clear" H 4200 4900 50  0001 C CNN
F 3 "~" H 4200 4900 50  0001 C CNN
	1    4200 4900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D12
U 1 1 5E31022F
P 4200 5450
F 0 "D12" V 4239 5332 50  0000 R CNN
F 1 "VLCS5830" V 4148 5332 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_Clear" H 4200 5450 50  0001 C CNN
F 3 "~" H 4200 5450 50  0001 C CNN
	1    4200 5450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2000 4300 2000 4150
Wire Wire Line
	2000 4150 2450 4150
Wire Wire Line
	4200 4150 4200 4300
Connection ~ 3100 4150
Wire Wire Line
	3100 4150 3300 4150
Wire Wire Line
	2000 5600 2000 5850
Wire Wire Line
	2000 5850 2450 5850
Wire Wire Line
	4200 5850 4200 5600
Connection ~ 3150 5850
Wire Wire Line
	3150 5850 3300 5850
Wire Wire Line
	3750 5600 3750 5850
Connection ~ 3750 5850
Wire Wire Line
	3750 5850 4200 5850
Wire Wire Line
	3300 5600 3300 5850
Connection ~ 3300 5850
Wire Wire Line
	3300 5850 3750 5850
Wire Wire Line
	2900 5600 2900 5850
Connection ~ 2900 5850
Wire Wire Line
	2900 5850 3150 5850
Wire Wire Line
	2450 5600 2450 5850
Connection ~ 2450 5850
Wire Wire Line
	2450 5850 2900 5850
Wire Wire Line
	2450 4300 2450 4150
Connection ~ 2450 4150
Wire Wire Line
	2450 4150 2900 4150
Wire Wire Line
	2900 4300 2900 4150
Connection ~ 2900 4150
Wire Wire Line
	2900 4150 3100 4150
Wire Wire Line
	3300 4300 3300 4150
Connection ~ 3300 4150
Wire Wire Line
	3300 4150 3750 4150
Wire Wire Line
	3750 4300 3750 4150
Connection ~ 3750 4150
Wire Wire Line
	3750 4150 4200 4150
Wire Wire Line
	2000 4600 2000 4750
Wire Wire Line
	2000 5050 2000 5300
Wire Wire Line
	2450 5300 2450 5050
Wire Wire Line
	2450 4750 2450 4600
Wire Wire Line
	2900 4600 2900 4750
Wire Wire Line
	2900 5050 2900 5300
Wire Wire Line
	3300 5300 3300 5050
Wire Wire Line
	3300 4750 3300 4600
Wire Wire Line
	3750 4600 3750 4750
Wire Wire Line
	3750 5050 3750 5300
Wire Wire Line
	4200 5300 4200 5050
Wire Wire Line
	4200 4750 4200 4600
Text Notes 900  4900 0    50   ~ 0
VLCS5B30: 2.5V@35mA
$Comp
L insa-sym:LOGO G1
U 1 1 5E3B0BBE
P 7600 6800
F 0 "G1" H 7600 6348 60  0001 C CNN
F 1 "LOGO" H 7600 7252 60  0001 C CNN
F 2 "Insa:insa-image" H 7600 6800 50  0001 C CNN
F 3 "" H 7600 6800 50  0001 C CNN
	1    7600 6800
	1    0    0    -1  
$EndComp
$EndSCHEMATC
