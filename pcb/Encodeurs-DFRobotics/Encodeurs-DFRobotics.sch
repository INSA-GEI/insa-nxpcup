EESchema Schematic File Version 4
EELAYER 30 0
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
L power:GND #PWR0101
U 1 1 5E31CE6F
P 2600 7350
F 0 "#PWR0101" H 2600 7100 50  0001 C CNN
F 1 "GND" H 2605 7177 50  0000 C CNN
F 2 "" H 2600 7350 50  0001 C CNN
F 3 "" H 2600 7350 50  0001 C CNN
	1    2600 7350
	1    0    0    -1  
$EndComp
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
P 9800 1950
F 0 "J1" H 9718 2367 50  0000 C CNN
F 1 "DF3A-5P-2DS" H 9718 2276 50  0000 C CNN
F 2 "Insa:DF3A-5P-2DS" H 9800 1950 50  0001 C CNN
F 3 "~" H 9800 1950 50  0001 C CNN
	1    9800 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J2
U 1 1 5E31F517
P 9750 4600
F 0 "J2" H 9668 5017 50  0000 C CNN
F 1 "DF3A-5P-2DS" H 9668 4926 50  0000 C CNN
F 2 "Insa:DF3A-5P-2DS" H 9750 4600 50  0001 C CNN
F 3 "~" H 9750 4600 50  0001 C CNN
	1    9750 4600
	1    0    0    -1  
$EndComp
$Comp
L Insa:AEDR-3800 U1
U 1 1 5E3A6A7F
P 6350 1900
F 0 "U1" H 6325 2315 50  0000 C CNN
F 1 "AEDR-8300" H 6325 2224 50  0000 C CNN
F 2 "Insa:AEDR-8300" H 6350 2200 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2343282.pdf" H 6350 1400 50  0001 C CNN
	1    6350 1900
	1    0    0    -1  
$EndComp
$Comp
L Insa:AEDR-3800 U2
U 1 1 5E3A6F7C
P 6350 4550
F 0 "U2" H 6325 4965 50  0000 C CNN
F 1 "AEDR-8300" H 6325 4874 50  0000 C CNN
F 2 "Insa:AEDR-8300" H 6350 4850 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2343282.pdf" H 6350 4050 50  0001 C CNN
	1    6350 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5E3A78B4
P 5350 2000
F 0 "C1" H 5465 2046 50  0000 L CNN
F 1 "1µF" H 5465 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5388 1850 50  0001 C CNN
F 3 "~" H 5350 2000 50  0001 C CNN
	1    5350 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E3A7F61
P 5350 4700
F 0 "C2" H 5465 4746 50  0000 L CNN
F 1 "1µF" H 5465 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5388 4550 50  0001 C CNN
F 3 "~" H 5350 4700 50  0001 C CNN
	1    5350 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E3A840F
P 5700 1750
F 0 "R1" H 5770 1796 50  0000 L CNN
F 1 "200" H 5770 1705 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5630 1750 50  0001 C CNN
F 3 "~" H 5700 1750 50  0001 C CNN
	1    5700 1750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5E3A88BC
P 5700 4400
F 0 "R2" H 5770 4446 50  0000 L CNN
F 1 "200" H 5770 4355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5630 4400 50  0001 C CNN
F 3 "~" H 5700 4400 50  0001 C CNN
	1    5700 4400
	0    -1   -1   0   
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5E3A946A
P 3100 7350
F 0 "#FLG0102" H 3100 7425 50  0001 C CNN
F 1 "PWR_FLAG" H 3100 7523 50  0000 C CNN
F 2 "" H 3100 7350 50  0001 C CNN
F 3 "~" H 3100 7350 50  0001 C CNN
	1    3100 7350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2600 7350 3100 7350
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
Wire Wire Line
	5950 1750 5850 1750
Wire Wire Line
	5550 1750 5350 1750
Wire Wire Line
	5350 1750 5350 1650
Wire Wire Line
	5350 1750 5350 1850
Connection ~ 5350 1750
Wire Wire Line
	5350 2150 5350 2200
Wire Wire Line
	5350 2200 5950 2200
Wire Wire Line
	5950 2100 5950 2200
Connection ~ 5950 2200
Wire Wire Line
	5950 1850 5350 1850
Connection ~ 5350 1850
Wire Wire Line
	5950 4400 5850 4400
Wire Wire Line
	5550 4400 5350 4400
Wire Wire Line
	5350 4400 5350 4300
Wire Wire Line
	5350 4400 5350 4500
Connection ~ 5350 4400
Wire Wire Line
	5350 4850 5950 4850
Wire Wire Line
	5950 4750 5950 4850
Connection ~ 5950 4850
Wire Wire Line
	5950 4500 5350 4500
Connection ~ 5350 4500
Wire Wire Line
	5350 4500 5350 4550
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
L power:+5V #PWR0103
U 1 1 5E3B90E5
P 5350 4300
F 0 "#PWR0103" H 5350 4150 50  0001 C CNN
F 1 "+5V" H 5365 4473 50  0000 C CNN
F 2 "" H 5350 4300 50  0001 C CNN
F 3 "" H 5350 4300 50  0001 C CNN
	1    5350 4300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5E3B9C7D
P 5350 1650
F 0 "#PWR0104" H 5350 1500 50  0001 C CNN
F 1 "+5V" H 5365 1823 50  0000 C CNN
F 2 "" H 5350 1650 50  0001 C CNN
F 3 "" H 5350 1650 50  0001 C CNN
	1    5350 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 5E3BA6CB
P 9250 1650
F 0 "#PWR0105" H 9250 1500 50  0001 C CNN
F 1 "+5V" H 9265 1823 50  0000 C CNN
F 2 "" H 9250 1650 50  0001 C CNN
F 3 "" H 9250 1650 50  0001 C CNN
	1    9250 1650
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 5E3BB24C
P 9250 4300
F 0 "#PWR0106" H 9250 4150 50  0001 C CNN
F 1 "+5V" H 9265 4473 50  0000 C CNN
F 2 "" H 9250 4300 50  0001 C CNN
F 3 "" H 9250 4300 50  0001 C CNN
	1    9250 4300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9550 4500 9250 4500
Wire Wire Line
	9250 4500 9250 4300
Wire Wire Line
	9600 1850 9250 1850
Wire Wire Line
	9250 1850 9250 1650
$Comp
L power:GND #PWR0107
U 1 1 5E3BBFE4
P 9250 4900
F 0 "#PWR0107" H 9250 4650 50  0001 C CNN
F 1 "GND" H 9255 4727 50  0000 C CNN
F 2 "" H 9250 4900 50  0001 C CNN
F 3 "" H 9250 4900 50  0001 C CNN
	1    9250 4900
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5E3BC5B6
P 5350 4850
F 0 "#PWR0108" H 5350 4600 50  0001 C CNN
F 1 "GND" H 5355 4677 50  0000 C CNN
F 2 "" H 5350 4850 50  0001 C CNN
F 3 "" H 5350 4850 50  0001 C CNN
	1    5350 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5E3BCD24
P 5350 2200
F 0 "#PWR0109" H 5350 1950 50  0001 C CNN
F 1 "GND" H 5355 2027 50  0000 C CNN
F 2 "" H 5350 2200 50  0001 C CNN
F 3 "" H 5350 2200 50  0001 C CNN
	1    5350 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5E3BD396
P 9250 2200
F 0 "#PWR0110" H 9250 1950 50  0001 C CNN
F 1 "GND" H 9255 2027 50  0000 C CNN
F 2 "" H 9250 2200 50  0001 C CNN
F 3 "" H 9250 2200 50  0001 C CNN
	1    9250 2200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9250 2150 9250 2200
Wire Wire Line
	9550 4800 9400 4800
Wire Wire Line
	9250 4800 9250 4900
Connection ~ 5350 4850
Connection ~ 5350 2200
Wire Wire Line
	6700 1900 7600 1900
Wire Wire Line
	6700 2050 7600 2050
Wire Wire Line
	6700 4550 7650 4550
Wire Wire Line
	6700 4700 7650 4700
Wire Wire Line
	9550 4700 8750 4700
Wire Wire Line
	9550 4600 8750 4600
Wire Wire Line
	9600 2050 8700 2050
Wire Wire Line
	9600 1950 8700 1950
Wire Wire Line
	9600 1750 9500 1750
Wire Wire Line
	9500 1750 9500 2150
Wire Wire Line
	9600 2150 9500 2150
Connection ~ 9500 2150
Wire Wire Line
	9500 2150 9250 2150
Wire Wire Line
	9550 4400 9400 4400
Wire Wire Line
	9400 4400 9400 4800
Connection ~ 9400 4800
Wire Wire Line
	9400 4800 9250 4800
Text Label 8700 2050 0    50   ~ 0
SENS_LEFT_B
Text Label 8700 1950 0    50   ~ 0
SENS_LEFT_A
Text Label 8750 4600 0    50   ~ 0
SENS_RIGHT_A
Text Label 8750 4700 0    50   ~ 0
SENS_RIGHT_B
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5E3C2D4D
P 5950 4200
F 0 "#FLG0103" H 5950 4275 50  0001 C CNN
F 1 "PWR_FLAG" H 5950 4373 50  0000 C CNN
F 2 "" H 5950 4200 50  0001 C CNN
F 3 "~" H 5950 4200 50  0001 C CNN
	1    5950 4200
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 5E3C3632
P 5950 1550
F 0 "#FLG0104" H 5950 1625 50  0001 C CNN
F 1 "PWR_FLAG" H 5950 1723 50  0000 C CNN
F 2 "" H 5950 1550 50  0001 C CNN
F 3 "~" H 5950 1550 50  0001 C CNN
	1    5950 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 4200 5950 4400
Connection ~ 5950 4400
Wire Wire Line
	5950 1550 5950 1750
Connection ~ 5950 1750
$Comp
L 74xGxx:74LVC2G34 U3
U 1 1 5E3E0666
P 7950 1750
F 0 "U3" H 7925 2017 50  0000 C CNN
F 1 "74LVC2G34" H 7925 1926 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6_Handsoldering" H 7950 1750 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 7950 1750 50  0001 C CNN
	1    7950 1750
	1    0    0    -1  
$EndComp
$Comp
L 74xGxx:74LVC2G34 U3
U 2 1 5E3E1F8F
P 7950 2250
F 0 "U3" H 7925 2517 50  0000 C CNN
F 1 "74LVC2G34" H 7925 2426 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6_Handsoldering" H 7950 2250 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 7950 2250 50  0001 C CNN
	2    7950 2250
	1    0    0    -1  
$EndComp
$Comp
L 74xGxx:74LVC2G34 U4
U 1 1 5E3E288C
P 8000 4350
F 0 "U4" H 7975 4617 50  0000 C CNN
F 1 "74LVC2G34" H 7975 4526 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6_Handsoldering" H 8000 4350 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 8000 4350 50  0001 C CNN
	1    8000 4350
	1    0    0    -1  
$EndComp
$Comp
L 74xGxx:74LVC2G34 U4
U 2 1 5E3E2D23
P 8000 4900
F 0 "U4" H 7975 5167 50  0000 C CNN
F 1 "74LVC2G34" H 7975 5076 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6_Handsoldering" H 8000 4900 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 8000 4900 50  0001 C CNN
	2    8000 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 1900 7600 1750
Wire Wire Line
	7600 2050 7600 2250
Wire Wire Line
	8700 1750 8700 1950
Wire Wire Line
	8700 2250 8700 2050
Wire Wire Line
	7650 4550 7650 4350
Wire Wire Line
	7650 4700 7650 4900
Wire Wire Line
	8750 4900 8750 4700
Wire Wire Line
	8750 4600 8750 4350
$Comp
L Device:C C3
U 1 1 5E4036A5
P 7900 2750
F 0 "C3" H 8015 2796 50  0000 L CNN
F 1 "100nF" H 8015 2705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7938 2600 50  0001 C CNN
F 3 "~" H 7900 2750 50  0001 C CNN
	1    7900 2750
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5E404996
P 7950 5800
F 0 "C4" H 8065 5846 50  0000 L CNN
F 1 "100nF" H 8065 5755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7988 5650 50  0001 C CNN
F 3 "~" H 7950 5800 50  0001 C CNN
	1    7950 5800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7600 1750 7650 1750
Wire Wire Line
	7600 2250 7650 2250
Wire Wire Line
	8200 2250 8700 2250
Wire Wire Line
	8700 1750 8200 1750
$Comp
L power:+5V #PWR0111
U 1 1 5E414062
P 7950 5650
F 0 "#PWR0111" H 7950 5500 50  0001 C CNN
F 1 "+5V" H 7965 5823 50  0000 C CNN
F 2 "" H 7950 5650 50  0001 C CNN
F 3 "" H 7950 5650 50  0001 C CNN
	1    7950 5650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5E41515B
P 7950 5950
F 0 "#PWR0112" H 7950 5700 50  0001 C CNN
F 1 "GND" H 7955 5777 50  0000 C CNN
F 2 "" H 7950 5950 50  0001 C CNN
F 3 "" H 7950 5950 50  0001 C CNN
	1    7950 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 4350 7700 4350
Wire Wire Line
	7650 4900 7700 4900
Wire Wire Line
	8250 4900 8750 4900
Wire Wire Line
	8750 4350 8250 4350
$Comp
L power:+5V #PWR0113
U 1 1 5E427842
P 7900 2600
F 0 "#PWR0113" H 7900 2450 50  0001 C CNN
F 1 "+5V" H 7915 2773 50  0000 C CNN
F 2 "" H 7900 2600 50  0001 C CNN
F 3 "" H 7900 2600 50  0001 C CNN
	1    7900 2600
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5E4288FB
P 7900 2900
F 0 "#PWR0114" H 7900 2650 50  0001 C CNN
F 1 "GND" H 7905 2727 50  0000 C CNN
F 2 "" H 7900 2900 50  0001 C CNN
F 3 "" H 7900 2900 50  0001 C CNN
	1    7900 2900
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
$EndSCHEMATC
