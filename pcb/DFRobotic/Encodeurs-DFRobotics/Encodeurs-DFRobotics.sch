EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Encodeurs DFRobotics"
Date "2020-02-05"
Rev "2.0"
Comp "INSA - GEI"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5E31D429
P 3100 6950
F 0 "#FLG0101" H 3100 7025 50  0001 C CNN
F 1 "PWR_FLAG" H 3100 7123 50  0000 C CNN
F 2 "" H 3100 6950 50  0001 C CNN
F 3 "~" H 3100 6950 50  0001 C CNN
	1    3100 6950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J1
U 1 1 5E31D745
P 7900 1650
F 0 "J1" H 7818 2067 50  0000 C CNN
F 1 "DF3A-5P-2DS" H 7818 1976 50  0000 C CNN
F 2 "Insa:DF3A-5P-2DS" H 7900 1650 50  0001 C CNN
F 3 "~" H 7900 1650 50  0001 C CNN
	1    7900 1650
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J2
U 1 1 5E31F517
P 7800 4450
F 0 "J2" H 7718 4867 50  0000 C CNN
F 1 "DF3A-5P-2DS" H 7718 4776 50  0000 C CNN
F 2 "Insa:DF3A-5P-2DS" H 7800 4450 50  0001 C CNN
F 3 "~" H 7800 4450 50  0001 C CNN
	1    7800 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E3A840F
P 4000 1400
F 0 "R1" H 4070 1446 50  0000 L CNN
F 1 "200" H 4070 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3930 1400 50  0001 C CNN
F 3 "~" H 4000 1400 50  0001 C CNN
	1    4000 1400
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 5E3A88BC
P 3950 4200
F 0 "R2" H 4020 4246 50  0000 L CNN
F 1 "200" H 4020 4155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3880 4200 50  0001 C CNN
F 3 "~" H 3950 4200 50  0001 C CNN
	1    3950 4200
	-1   0    0    1   
$EndComp
Wire Wire Line
	3100 6950 2550 6950
Wire Notes Line
	600  3250 11150 3250
Text Notes 600  750  0    100  ~ 0
Sensor Left
Text Notes 650  3500 0    100  ~ 0
Sensor Right
Wire Notes Line
	6950 6550 500  6550
Text Notes 550  6750 0    100  ~ 0
Miscellaneous
$Comp
L power:+5V #PWR0102
U 1 1 5E3B84F3
P 2550 6950
F 0 "#PWR0102" H 2550 6800 50  0001 C CNN
F 1 "+5V" H 2565 7123 50  0000 C CNN
F 2 "" H 2550 6950 50  0001 C CNN
F 3 "" H 2550 6950 50  0001 C CNN
	1    2550 6950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5E3B9C7D
P 4000 1150
F 0 "#PWR0104" H 4000 1000 50  0001 C CNN
F 1 "+5V" H 4015 1323 50  0000 C CNN
F 2 "" H 4000 1150 50  0001 C CNN
F 3 "" H 4000 1150 50  0001 C CNN
	1    4000 1150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 5E3BA6CB
P 7350 1350
F 0 "#PWR0105" H 7350 1200 50  0001 C CNN
F 1 "+5V" H 7365 1523 50  0000 C CNN
F 2 "" H 7350 1350 50  0001 C CNN
F 3 "" H 7350 1350 50  0001 C CNN
	1    7350 1350
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 5E3BB24C
P 7300 4150
F 0 "#PWR0106" H 7300 4000 50  0001 C CNN
F 1 "+5V" H 7315 4323 50  0000 C CNN
F 2 "" H 7300 4150 50  0001 C CNN
F 3 "" H 7300 4150 50  0001 C CNN
	1    7300 4150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7600 4350 7300 4350
Wire Wire Line
	7300 4350 7300 4150
Wire Wire Line
	7700 1550 7350 1550
Wire Wire Line
	7350 1550 7350 1350
$Comp
L power:GND #PWR0107
U 1 1 5E3BBFE4
P 7300 4750
F 0 "#PWR0107" H 7300 4500 50  0001 C CNN
F 1 "GND" H 7305 4577 50  0000 C CNN
F 2 "" H 7300 4750 50  0001 C CNN
F 3 "" H 7300 4750 50  0001 C CNN
	1    7300 4750
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5E3BC5B6
P 3950 4750
F 0 "#PWR0108" H 3950 4500 50  0001 C CNN
F 1 "GND" H 3955 4577 50  0000 C CNN
F 2 "" H 3950 4750 50  0001 C CNN
F 3 "" H 3950 4750 50  0001 C CNN
	1    3950 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5E3BCD24
P 4050 2000
F 0 "#PWR0109" H 4050 1750 50  0001 C CNN
F 1 "GND" H 4055 1827 50  0000 C CNN
F 2 "" H 4050 2000 50  0001 C CNN
F 3 "" H 4050 2000 50  0001 C CNN
	1    4050 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5E3BD396
P 7350 1900
F 0 "#PWR0110" H 7350 1650 50  0001 C CNN
F 1 "GND" H 7355 1727 50  0000 C CNN
F 2 "" H 7350 1900 50  0001 C CNN
F 3 "" H 7350 1900 50  0001 C CNN
	1    7350 1900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7350 1850 7350 1900
Wire Wire Line
	7600 4650 7450 4650
Wire Wire Line
	7300 4650 7300 4750
Wire Wire Line
	7600 4450 6800 4450
Wire Wire Line
	7700 1650 6800 1650
Wire Wire Line
	7700 1450 7600 1450
Wire Wire Line
	7600 1450 7600 1750
Wire Wire Line
	7700 1850 7600 1850
Connection ~ 7600 1850
Wire Wire Line
	7600 1850 7350 1850
Wire Wire Line
	7600 4250 7450 4250
Wire Wire Line
	7450 4250 7450 4550
Connection ~ 7450 4650
Wire Wire Line
	7450 4650 7300 4650
Text Label 6800 1650 0    50   ~ 0
SENS_LEFT_A
Text Label 6800 4450 0    50   ~ 0
SENS_RIGHT_A
$Comp
L 74xGxx:74LVC2G34 U3
U 1 1 5E3E0666
P 6050 1450
F 0 "U3" H 6025 1717 50  0000 C CNN
F 1 "74LVC2G34" H 6025 1626 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6_Handsoldering" H 6050 1450 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 6050 1450 50  0001 C CNN
	1    6050 1450
	1    0    0    -1  
$EndComp
$Comp
L 74xGxx:74LVC2G34 U3
U 2 1 5E3E1F8F
P 6050 1950
F 0 "U3" H 6025 2217 50  0000 C CNN
F 1 "74LVC2G34" H 6025 2126 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6_Handsoldering" H 6050 1950 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 6050 1950 50  0001 C CNN
	2    6050 1950
	1    0    0    -1  
$EndComp
$Comp
L 74xGxx:74LVC2G34 U4
U 1 1 5E3E288C
P 6050 4200
F 0 "U4" H 6025 4467 50  0000 C CNN
F 1 "74LVC2G34" H 6025 4376 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6_Handsoldering" H 6050 4200 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 6050 4200 50  0001 C CNN
	1    6050 4200
	1    0    0    -1  
$EndComp
$Comp
L 74xGxx:74LVC2G34 U4
U 2 1 5E3E2D23
P 6050 4750
F 0 "U4" H 6025 5017 50  0000 C CNN
F 1 "74LVC2G34" H 6025 4926 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6_Handsoldering" H 6050 4750 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 6050 4750 50  0001 C CNN
	2    6050 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 1600 5700 1450
Wire Wire Line
	6800 1450 6800 1650
Wire Wire Line
	5700 4400 5700 4200
Wire Wire Line
	6800 4450 6800 4200
$Comp
L Device:C C3
U 1 1 5E4036A5
P 6000 2450
F 0 "C3" H 6115 2496 50  0000 L CNN
F 1 "100nF" H 6115 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6038 2300 50  0001 C CNN
F 3 "~" H 6000 2450 50  0001 C CNN
	1    6000 2450
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5E404996
P 6000 5650
F 0 "C4" H 6115 5696 50  0000 L CNN
F 1 "100nF" H 6115 5605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6038 5500 50  0001 C CNN
F 3 "~" H 6000 5650 50  0001 C CNN
	1    6000 5650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5700 1450 5750 1450
Wire Wire Line
	6800 1450 6300 1450
$Comp
L power:+5V #PWR0111
U 1 1 5E414062
P 6000 5500
F 0 "#PWR0111" H 6000 5350 50  0001 C CNN
F 1 "+5V" H 6015 5673 50  0000 C CNN
F 2 "" H 6000 5500 50  0001 C CNN
F 3 "" H 6000 5500 50  0001 C CNN
	1    6000 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5E41515B
P 6000 5800
F 0 "#PWR0112" H 6000 5550 50  0001 C CNN
F 1 "GND" H 6005 5627 50  0000 C CNN
F 2 "" H 6000 5800 50  0001 C CNN
F 3 "" H 6000 5800 50  0001 C CNN
	1    6000 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 4200 5750 4200
Wire Wire Line
	6800 4200 6300 4200
$Comp
L power:+5V #PWR0113
U 1 1 5E427842
P 6000 2300
F 0 "#PWR0113" H 6000 2150 50  0001 C CNN
F 1 "+5V" H 6015 2473 50  0000 C CNN
F 2 "" H 6000 2300 50  0001 C CNN
F 3 "" H 6000 2300 50  0001 C CNN
	1    6000 2300
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5E4288FB
P 6000 2600
F 0 "#PWR0114" H 6000 2350 50  0001 C CNN
F 1 "GND" H 6005 2427 50  0000 C CNN
F 2 "" H 6000 2600 50  0001 C CNN
F 3 "" H 6000 2600 50  0001 C CNN
	1    6000 2600
	-1   0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0115
U 1 1 5E42C9E5
P 2350 6950
F 0 "#PWR0115" H 2350 6800 50  0001 C CNN
F 1 "VCC" H 2365 7123 50  0000 C CNN
F 2 "" H 2350 6950 50  0001 C CNN
F 3 "" H 2350 6950 50  0001 C CNN
	1    2350 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 6950 2550 6950
Connection ~ 2550 6950
$Comp
L insa-sym:LOGO G1
U 1 1 5E3AFE48
P 7600 6800
F 0 "G1" H 7600 6348 60  0001 C CNN
F 1 "LOGO" H 7600 7252 60  0001 C CNN
F 2 "" H 7600 6800 50  0001 C CNN
F 3 "" H 7600 6800 50  0001 C CNN
	1    7600 6800
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:SFH9206 U1
U 1 1 5E3D772D
P 4400 1700
F 0 "U1" H 4400 2017 50  0000 C CNN
F 1 "SFH9206" H 4400 1926 50  0000 C CNN
F 2 "OptoDevice:Osram_SFH9x0x" H 4200 1500 50  0001 L CIN
F 3 "http://www.osram-os.com/Graphics/XPic6/00200860_0.pdf" V 4360 1740 50  0001 L CNN
	1    4400 1700
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Proximity:SFH9206 U2
U 1 1 5E3D94ED
P 4350 4500
F 0 "U2" H 4350 4817 50  0000 C CNN
F 1 "SFH9206" H 4350 4726 50  0000 C CNN
F 2 "OptoDevice:Osram_SFH9x0x" H 4150 4300 50  0001 L CIN
F 3 "http://www.osram-os.com/Graphics/XPic6/00200860_0.pdf" V 4310 4540 50  0001 L CNN
	1    4350 4500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5E3DF6F5
P 5600 2000
F 0 "#PWR0103" H 5600 1750 50  0001 C CNN
F 1 "GND" H 5605 1827 50  0000 C CNN
F 2 "" H 5600 2000 50  0001 C CNN
F 3 "" H 5600 2000 50  0001 C CNN
	1    5600 2000
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5E3E0496
P 5650 4800
F 0 "#PWR0116" H 5650 4550 50  0001 C CNN
F 1 "GND" H 5655 4627 50  0000 C CNN
F 2 "" H 5650 4800 50  0001 C CNN
F 3 "" H 5650 4800 50  0001 C CNN
	1    5650 4800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5750 1950 5600 1950
Wire Wire Line
	5600 1950 5600 2000
Wire Wire Line
	5750 4750 5650 4750
Wire Wire Line
	5650 4750 5650 4800
NoConn ~ 6300 1950
NoConn ~ 6300 4750
Wire Wire Line
	7700 1750 7600 1750
Connection ~ 7600 1750
Wire Wire Line
	7600 1750 7600 1850
Wire Wire Line
	7600 4550 7450 4550
Connection ~ 7450 4550
Wire Wire Line
	7450 4550 7450 4650
$Comp
L power:GND #PWR0117
U 1 1 5E3EAD1F
P 4750 2000
F 0 "#PWR0117" H 4750 1750 50  0001 C CNN
F 1 "GND" H 4755 1827 50  0000 C CNN
F 2 "" H 4750 2000 50  0001 C CNN
F 3 "" H 4750 2000 50  0001 C CNN
	1    4750 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 5E3F5334
P 4750 4750
F 0 "#PWR0118" H 4750 4500 50  0001 C CNN
F 1 "GND" H 4755 4577 50  0000 C CNN
F 2 "" H 4750 4750 50  0001 C CNN
F 3 "" H 4750 4750 50  0001 C CNN
	1    4750 4750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0119
U 1 1 5E3F7923
P 3950 3950
F 0 "#PWR0119" H 3950 3800 50  0001 C CNN
F 1 "+5V" H 3965 4123 50  0000 C CNN
F 2 "" H 3950 3950 50  0001 C CNN
F 3 "" H 3950 3950 50  0001 C CNN
	1    3950 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0120
U 1 1 5E3F8972
P 4750 1150
F 0 "#PWR0120" H 4750 1000 50  0001 C CNN
F 1 "+5V" H 4765 1323 50  0000 C CNN
F 2 "" H 4750 1150 50  0001 C CNN
F 3 "" H 4750 1150 50  0001 C CNN
	1    4750 1150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0121
U 1 1 5E3F948D
P 4750 3950
F 0 "#PWR0121" H 4750 3800 50  0001 C CNN
F 1 "+5V" H 4765 4123 50  0000 C CNN
F 2 "" H 4750 3950 50  0001 C CNN
F 3 "" H 4750 3950 50  0001 C CNN
	1    4750 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 1800 4050 1800
Wire Wire Line
	4050 1800 4050 2000
Wire Wire Line
	4100 1600 4000 1600
Wire Wire Line
	4000 1600 4000 1550
Wire Wire Line
	4000 1150 4000 1250
Wire Wire Line
	4700 1600 4750 1600
$Comp
L Device:R R3
U 1 1 5E3FD133
P 4750 1400
F 0 "R3" H 4820 1446 50  0000 L CNN
F 1 "200" H 4820 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4680 1400 50  0001 C CNN
F 3 "~" H 4750 1400 50  0001 C CNN
	1    4750 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5E3FE0A6
P 4750 4200
F 0 "R4" H 4820 4246 50  0000 L CNN
F 1 "200" H 4820 4155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4680 4200 50  0001 C CNN
F 3 "~" H 4750 4200 50  0001 C CNN
	1    4750 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 1150 4750 1250
Wire Wire Line
	4750 1550 4750 1600
Connection ~ 4750 1600
Wire Wire Line
	4750 1600 5700 1600
Wire Wire Line
	4700 1800 4750 1800
Wire Wire Line
	4750 1800 4750 2000
Wire Wire Line
	4750 3950 4750 4050
Wire Wire Line
	4650 4400 4750 4400
Wire Wire Line
	4750 4350 4750 4400
Connection ~ 4750 4400
Wire Wire Line
	4750 4400 5700 4400
Wire Wire Line
	4650 4600 4750 4600
Wire Wire Line
	4750 4600 4750 4750
Wire Wire Line
	4050 4600 3950 4600
Wire Wire Line
	3950 4600 3950 4750
Wire Wire Line
	4050 4400 3950 4400
Wire Wire Line
	3950 4400 3950 4350
Wire Wire Line
	3950 3950 3950 4050
$Comp
L power:GND #PWR?
U 1 1 5E40B069
P 2350 7300
F 0 "#PWR?" H 2350 7050 50  0001 C CNN
F 1 "GND" H 2355 7127 50  0000 C CNN
F 2 "" H 2350 7300 50  0001 C CNN
F 3 "" H 2350 7300 50  0001 C CNN
	1    2350 7300
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5E40B06F
P 2850 7300
F 0 "#FLG?" H 2850 7375 50  0001 C CNN
F 1 "PWR_FLAG" H 2850 7473 50  0000 C CNN
F 2 "" H 2850 7300 50  0001 C CNN
F 3 "~" H 2850 7300 50  0001 C CNN
	1    2850 7300
	-1   0    0    1   
$EndComp
Wire Wire Line
	2350 7300 2850 7300
$EndSCHEMATC
