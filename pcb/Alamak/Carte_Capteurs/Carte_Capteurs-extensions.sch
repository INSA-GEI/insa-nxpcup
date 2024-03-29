EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L Connector_Generic:Conn_01x04 J11
U 1 1 5F756091
P 2300 2950
F 0 "J11" H 2250 3200 50  0000 L CNN
F 1 "DF3A-4P-2DS" H 2000 2600 50  0000 L CNN
F 2 "Insa:DF3A-4P-2DS" H 2300 2950 50  0001 C CNN
F 3 "~" H 2300 2950 50  0001 C CNN
	1    2300 2950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J12
U 1 1 5F756097
P 3750 2950
F 0 "J12" H 3700 3200 50  0000 L CNN
F 1 "DF3A-4P-2DS" H 3450 2600 50  0000 L CNN
F 2 "Insa:DF3A-4P-2DS" H 3750 2950 50  0001 C CNN
F 3 "~" H 3750 2950 50  0001 C CNN
	1    3750 2950
	1    0    0    -1  
$EndComp
Text Notes 1100 2450 0    50   ~ 0
ToF Sensors
Wire Wire Line
	1500 2950 2100 2950
Wire Wire Line
	1500 3150 2100 3150
Wire Wire Line
	2950 3150 3550 3150
Wire Wire Line
	2950 2950 3550 2950
Wire Wire Line
	2100 2850 1850 2850
Wire Wire Line
	1850 2850 1850 2750
Wire Wire Line
	2100 3050 1850 3050
Wire Wire Line
	1850 3050 1850 3250
Wire Wire Line
	3550 3050 3300 3050
Wire Wire Line
	3300 3050 3300 3250
Wire Wire Line
	3550 2850 3300 2850
Wire Wire Line
	3300 2850 3300 2750
$Comp
L power:+3.3V #PWR0133
U 1 1 5F7560D1
P 1850 2750
F 0 "#PWR0133" H 1850 2600 50  0001 C CNN
F 1 "+3.3V" H 1865 2923 50  0000 C CNN
F 2 "" H 1850 2750 50  0001 C CNN
F 3 "" H 1850 2750 50  0001 C CNN
	1    1850 2750
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0134
U 1 1 5F7560D7
P 3300 2750
F 0 "#PWR0134" H 3300 2600 50  0001 C CNN
F 1 "+3.3V" H 3315 2923 50  0000 C CNN
F 2 "" H 3300 2750 50  0001 C CNN
F 3 "" H 3300 2750 50  0001 C CNN
	1    3300 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0135
U 1 1 5F7560DD
P 3300 3300
F 0 "#PWR0135" H 3300 3050 50  0001 C CNN
F 1 "GND" H 3305 3127 50  0000 C CNN
F 2 "" H 3300 3300 50  0001 C CNN
F 3 "" H 3300 3300 50  0001 C CNN
	1    3300 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0136
U 1 1 5F7560E3
P 1850 3300
F 0 "#PWR0136" H 1850 3050 50  0001 C CNN
F 1 "GND" H 1855 3127 50  0000 C CNN
F 2 "" H 1850 3300 50  0001 C CNN
F 3 "" H 1850 3300 50  0001 C CNN
	1    1850 3300
	1    0    0    -1  
$EndComp
Text Label 1500 3150 0    50   ~ 0
SENS_SCL1
Text Label 2950 2950 0    50   ~ 0
SENS_SDA2
Text Label 2950 3150 0    50   ~ 0
SENS_SCL2
$Comp
L Device:C C9
U 1 1 5F7560F3
P 2700 3000
F 0 "C9" H 2550 3100 50  0000 L CNN
F 1 "100nF" V 2650 2700 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2738 2850 50  0001 C CNN
F 3 "~" H 2700 3000 50  0001 C CNN
	1    2700 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5F7560F9
P 1250 3000
F 0 "C8" H 1100 3100 50  0000 L CNN
F 1 "100nF" V 1200 2700 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 1288 2850 50  0001 C CNN
F 3 "~" H 1250 3000 50  0001 C CNN
	1    1250 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2850 2700 2850
Connection ~ 3300 2850
Wire Wire Line
	2700 3150 2700 3250
Wire Wire Line
	2700 3250 3300 3250
Connection ~ 3300 3250
Wire Wire Line
	3300 3250 3300 3300
Wire Wire Line
	1850 2850 1250 2850
Connection ~ 1850 2850
Wire Wire Line
	1250 3150 1250 3250
Wire Wire Line
	1250 3250 1850 3250
Connection ~ 1850 3250
Wire Wire Line
	1850 3250 1850 3300
$Comp
L Connector_Generic:Conn_01x05 J9
U 1 1 5F79BA8A
P 8900 1550
F 0 "J9" H 9000 1800 50  0000 L CNN
F 1 "DF3A-5P-2DS" H 8650 1200 50  0000 L CNN
F 2 "Insa:DF3A-5P-2DS" H 8900 1550 50  0001 C CNN
F 3 "~" H 8900 1550 50  0001 C CNN
	1    8900 1550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J10
U 1 1 5F79BA90
P 8900 2850
F 0 "J10" H 9000 3100 50  0000 L CNN
F 1 "DF3A-5P-2DS" H 8650 2500 50  0000 L CNN
F 2 "Insa:DF3A-5P-2DS" H 8900 2850 50  0001 C CNN
F 3 "~" H 8900 2850 50  0001 C CNN
	1    8900 2850
	1    0    0    -1  
$EndComp
Text Notes 6700 1100 0    50   ~ 0
Encoders
Wire Wire Line
	8700 2750 8500 2750
Wire Wire Line
	8500 2750 8500 2500
Wire Wire Line
	8700 3050 8500 3050
Wire Wire Line
	8500 3050 8500 3150
Wire Wire Line
	8700 1450 8500 1450
Wire Wire Line
	8700 1750 8500 1750
Wire Wire Line
	8500 1750 8500 1850
$Comp
L power:GND #PWR0137
U 1 1 5F79BA9E
P 8500 3250
F 0 "#PWR0137" H 8500 3000 50  0001 C CNN
F 1 "GND" H 8505 3077 50  0000 C CNN
F 2 "" H 8500 3250 50  0001 C CNN
F 3 "" H 8500 3250 50  0001 C CNN
	1    8500 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0138
U 1 1 5F79BAA4
P 8500 1950
F 0 "#PWR0138" H 8500 1700 50  0001 C CNN
F 1 "GND" H 8505 1777 50  0000 C CNN
F 2 "" H 8500 1950 50  0001 C CNN
F 3 "" H 8500 1950 50  0001 C CNN
	1    8500 1950
	1    0    0    -1  
$EndComp
Text Label 6700 1850 0    50   ~ 0
ENC_INDEX1
Text Label 6700 1750 0    50   ~ 0
ENC_SIG_A1
Text Label 6700 1650 0    50   ~ 0
ENC_SIG_B1
Text Label 6700 3100 0    50   ~ 0
ENC_INDEX2
Text Label 6700 3000 0    50   ~ 0
ENC_SIG_A2
Text Label 6700 2900 0    50   ~ 0
ENC_SIG_B2
$Comp
L Device:C C11
U 1 1 5F79BAB0
P 9250 2800
F 0 "C11" H 9100 2900 50  0000 L CNN
F 1 "100nF" V 9200 2500 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 9288 2650 50  0001 C CNN
F 3 "~" H 9250 2800 50  0001 C CNN
	1    9250 2800
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5F79BAB6
P 9250 1500
F 0 "C10" H 9100 1600 50  0000 L CNN
F 1 "100nF" V 9200 1200 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 9288 1350 50  0001 C CNN
F 3 "~" H 9250 1500 50  0001 C CNN
	1    9250 1500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8500 1200 8500 1450
$Comp
L power:+5V #PWR0139
U 1 1 5F79BABD
P 9350 4550
F 0 "#PWR0139" H 9350 4400 50  0001 C CNN
F 1 "+5V" H 9365 4723 50  0000 C CNN
F 2 "" H 9350 4550 50  0001 C CNN
F 3 "" H 9350 4550 50  0001 C CNN
	1    9350 4550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0140
U 1 1 5F79BAC3
P 8500 2500
F 0 "#PWR0140" H 8500 2350 50  0001 C CNN
F 1 "+5V" H 8515 2673 50  0000 C CNN
F 2 "" H 8500 2500 50  0001 C CNN
F 3 "" H 8500 2500 50  0001 C CNN
	1    8500 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 1200 9250 1200
Wire Wire Line
	9250 1200 9250 1350
Wire Wire Line
	8500 1850 9250 1850
Wire Wire Line
	9250 1850 9250 1650
Connection ~ 8500 1850
Wire Wire Line
	8500 1850 8500 1950
Wire Wire Line
	8500 2500 9250 2500
Wire Wire Line
	9250 2500 9250 2650
Connection ~ 8500 2500
Wire Wire Line
	9250 3150 9250 2950
Wire Wire Line
	8500 3150 9250 3150
Connection ~ 8500 3150
Wire Wire Line
	8500 3150 8500 3250
Wire Wire Line
	7950 1600 7950 1650
Wire Wire Line
	6700 1650 7950 1650
Connection ~ 7950 1650
Wire Wire Line
	7950 1650 7950 1850
$Comp
L Device:R_Pack04 RN4
U 1 1 5F79BADB
P 7750 1400
F 0 "RN4" H 8100 1450 50  0000 R CNN
F 1 "2.2K" H 8100 1350 50  0000 R CNN
F 2 "Resistor_SMD:R_Array_Convex_4x0603" V 8025 1400 50  0001 C CNN
F 3 "~" H 7750 1400 50  0001 C CNN
	1    7750 1400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7850 1600 7850 1750
Wire Wire Line
	6700 1750 7850 1750
Wire Wire Line
	7750 1600 7750 1850
$Comp
L Device:R_Pack04 RN5
U 1 1 5F79BAE4
P 7750 2050
F 0 "RN5" H 7470 2096 50  0000 R CNN
F 1 "3.3K" H 7470 2005 50  0000 R CNN
F 2 "Resistor_SMD:R_Array_Convex_4x0603" V 8025 2050 50  0001 C CNN
F 3 "~" H 7750 2050 50  0001 C CNN
	1    7750 2050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7850 1750 7850 1850
Connection ~ 7850 1750
Wire Wire Line
	8700 1650 8150 1650
Wire Wire Line
	8250 1550 8700 1550
Wire Wire Line
	8700 1350 8350 1350
Wire Wire Line
	7650 2250 7750 2250
Connection ~ 7750 2250
Wire Wire Line
	7750 2250 7850 2250
Connection ~ 7850 2250
Wire Wire Line
	7850 2250 7950 2250
Connection ~ 7750 1850
$Comp
L Device:R_Pack04 RN6
U 1 1 5F79BAFB
P 7750 2700
F 0 "RN6" H 8100 2750 50  0000 R CNN
F 1 "2.2K" H 8100 2650 50  0000 R CNN
F 2 "Resistor_SMD:R_Array_Convex_4x0603" V 8025 2700 50  0001 C CNN
F 3 "~" H 7750 2700 50  0001 C CNN
	1    7750 2700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7950 1200 8150 1200
Wire Wire Line
	8150 1200 8150 1650
Wire Wire Line
	7850 1200 7850 1150
Wire Wire Line
	7850 1150 8250 1150
Wire Wire Line
	8250 1150 8250 1550
Wire Wire Line
	7750 1200 7750 1100
Wire Wire Line
	7750 1100 8350 1100
Wire Wire Line
	8350 1100 8350 1350
Wire Wire Line
	7650 3500 7750 3500
Connection ~ 7750 3500
Wire Wire Line
	7750 3500 7850 3500
Connection ~ 7850 3500
Wire Wire Line
	7850 3500 7950 3500
Connection ~ 7950 3500
Wire Wire Line
	7850 2450 7850 2500
Wire Wire Line
	7750 2400 7750 2500
Wire Wire Line
	7950 2900 7950 3100
Wire Wire Line
	7850 2900 7850 3000
Wire Wire Line
	7750 2900 7750 3100
Connection ~ 7750 3100
Wire Wire Line
	6700 3000 7850 3000
Connection ~ 7850 3000
Wire Wire Line
	7850 3000 7850 3100
Connection ~ 7950 2900
Wire Wire Line
	6700 2900 7950 2900
Wire Wire Line
	6700 3100 7750 3100
Wire Wire Line
	8350 3500 8350 3150
Wire Wire Line
	8350 3150 8500 3150
Wire Wire Line
	7950 3500 8350 3500
Wire Wire Line
	8150 2500 8150 2950
Wire Wire Line
	8150 2500 7950 2500
Wire Wire Line
	8250 2450 8250 2850
Wire Wire Line
	8250 2450 7850 2450
Wire Wire Line
	8350 2400 8350 2650
Wire Wire Line
	8350 2400 7750 2400
Wire Wire Line
	8350 2650 8700 2650
Wire Wire Line
	8250 2850 8700 2850
Wire Wire Line
	8150 2950 8700 2950
Wire Wire Line
	7950 2250 8350 2250
Wire Wire Line
	8350 2250 8350 1850
Wire Wire Line
	8350 1850 8500 1850
Connection ~ 7950 2250
NoConn ~ 7650 1200
NoConn ~ 7650 1600
NoConn ~ 7650 2500
NoConn ~ 7650 2900
NoConn ~ 7650 3100
NoConn ~ 7650 1850
Wire Wire Line
	6700 1850 7750 1850
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J?
U 1 1 5F7A4CB8
P 6050 4900
AR Path="/5F79603F/5F7A4CB8" Ref="J?"  Part="1" 
AR Path="/5F74E4C5/5F7A4CB8" Ref="J14"  Part="1" 
F 0 "J14" H 6100 5225 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 6100 5226 50  0001 C CNN
F 2 "Connector_Multicomp:Multicomp_MC9A12-1034_2x05_P2.54mm_Vertical" H 6050 4900 50  0001 C CNN
F 3 "~" H 6050 4900 50  0001 C CNN
	1    6050 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 4700 5350 4700
Wire Wire Line
	6350 4800 6850 4800
Text Label 5350 4700 0    50   ~ 0
PIXY2_RX
Text Label 6850 4800 2    50   ~ 0
PIXY2_TX
$Comp
L power:+5V #PWR?
U 1 1 5F7A4CC2
P 6600 4700
AR Path="/5F79603F/5F7A4CC2" Ref="#PWR?"  Part="1" 
AR Path="/5F74E4C5/5F7A4CC2" Ref="#PWR0148"  Part="1" 
F 0 "#PWR0148" H 6600 4550 50  0001 C CNN
F 1 "+5V" H 6615 4873 50  0000 C CNN
F 2 "" H 6600 4700 50  0001 C CNN
F 3 "" H 6600 4700 50  0001 C CNN
	1    6600 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F7A4CC8
P 6600 4900
AR Path="/5F79603F/5F7A4CC8" Ref="#PWR?"  Part="1" 
AR Path="/5F74E4C5/5F7A4CC8" Ref="#PWR0149"  Part="1" 
F 0 "#PWR0149" H 6600 4650 50  0001 C CNN
F 1 "GND" H 6605 4727 50  0000 C CNN
F 2 "" H 6600 4900 50  0001 C CNN
F 3 "" H 6600 4900 50  0001 C CNN
	1    6600 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 4700 6350 4700
Wire Wire Line
	6600 4900 6350 4900
NoConn ~ 5850 4800
NoConn ~ 5850 4900
NoConn ~ 5850 5000
NoConn ~ 5850 5100
NoConn ~ 6350 5000
NoConn ~ 6350 5100
Text Notes 5300 4400 0    50   ~ 0
Pixy2
$Comp
L Device:R_Pack04 RN7
U 1 1 5F79BAF5
P 7750 3300
F 0 "RN7" H 8100 3350 50  0000 R CNN
F 1 "3.3K" H 8100 3250 50  0000 R CNN
F 2 "Resistor_SMD:R_Array_Convex_4x0603" V 8025 3300 50  0001 C CNN
F 3 "~" H 7750 3300 50  0001 C CNN
	1    7750 3300
	-1   0    0    -1  
$EndComp
Text HLabel 1450 1000 0    50   BiDi ~ 0
SENS_SDA1
Text Label 1500 2950 0    50   ~ 0
SENS_SDA1
Wire Wire Line
	1450 1000 2350 1000
Text Label 2350 1000 2    50   ~ 0
SENS_SDA1
Text HLabel 3800 1000 0    50   Output ~ 0
ENC_SIG_A1
Text HLabel 3800 1100 0    50   Output ~ 0
ENC_SIG_B1
Text HLabel 3800 1200 0    50   Output ~ 0
ENC_SIG_A2
Text HLabel 3800 1300 0    50   Output ~ 0
ENC_SIG_B2
Text HLabel 3800 1400 0    50   Output ~ 0
ENC_INDEX1
Text HLabel 3800 1500 0    50   Output ~ 0
ENC_INDEX2
Text HLabel 1450 1100 0    50   Input ~ 0
SENS_SCL1
Text HLabel 1450 1250 0    50   BiDi ~ 0
SENS_SDA2
Text HLabel 1450 1350 0    50   Input ~ 0
SENS_SCL2
Text HLabel 1450 1600 0    50   Output ~ 0
PIXY2_TX
Text HLabel 1450 1700 0    50   Input ~ 0
PIXY2_RX
Wire Wire Line
	1450 1100 2350 1100
Wire Wire Line
	1450 1250 2350 1250
Wire Wire Line
	1450 1350 2350 1350
Wire Wire Line
	1450 1600 2350 1600
Wire Wire Line
	1450 1700 2350 1700
Wire Wire Line
	3800 1500 4850 1500
Wire Wire Line
	3800 1400 4850 1400
Wire Wire Line
	3800 1300 4850 1300
Wire Wire Line
	3800 1200 4850 1200
Wire Wire Line
	3800 1100 4850 1100
Wire Wire Line
	3800 1000 4850 1000
Text Label 2350 1100 2    50   ~ 0
SENS_SCL1
Text Label 2350 1250 2    50   ~ 0
SENS_SDA2
Text Label 2350 1350 2    50   ~ 0
SENS_SCL2
Text Label 4850 1100 2    50   ~ 0
ENC_SIG_B1
Text Label 4850 1000 2    50   ~ 0
ENC_SIG_A1
Text Label 4850 1400 2    50   ~ 0
ENC_INDEX1
Text Label 4850 1300 2    50   ~ 0
ENC_SIG_B2
Text Label 4850 1200 2    50   ~ 0
ENC_SIG_A2
Text Label 4850 1500 2    50   ~ 0
ENC_INDEX2
Text Label 2350 1700 2    50   ~ 0
PIXY2_RX
Text Label 2350 1600 2    50   ~ 0
PIXY2_TX
$Comp
L power:+BATT #PWR0150
U 1 1 5FA4BEFB
P 8050 4550
F 0 "#PWR0150" H 8050 4400 50  0001 C CNN
F 1 "+BATT" H 8065 4723 50  0000 C CNN
F 2 "" H 8050 4550 50  0001 C CNN
F 3 "" H 8050 4550 50  0001 C CNN
	1    8050 4550
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AMS1117-5.0 U5
U 1 1 5FA4BF01
P 8900 4550
F 0 "U5" H 8900 4792 50  0000 C CNN
F 1 "ZLDO1117G50TA" H 8900 4701 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 8900 4750 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1769101.pdf" H 9000 4300 50  0001 C CNN
	1    8900 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0151
U 1 1 5FA4BF07
P 8900 4950
F 0 "#PWR0151" H 8900 4700 50  0001 C CNN
F 1 "GND" H 8905 4777 50  0000 C CNN
F 2 "" H 8900 4950 50  0001 C CNN
F 3 "" H 8900 4950 50  0001 C CNN
	1    8900 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5FA4BF0D
P 8300 4750
F 0 "C12" H 8415 4796 50  0000 L CNN
F 1 "4.7µF" H 8415 4705 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 8338 4600 50  0001 C CNN
F 3 "~" H 8300 4750 50  0001 C CNN
	1    8300 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C13
U 1 1 5FA4BF13
P 9350 4750
F 0 "C13" H 9465 4796 50  0000 L CNN
F 1 "4.7µF" H 9465 4705 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 9388 4600 50  0001 C CNN
F 3 "~" H 9350 4750 50  0001 C CNN
	1    9350 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 4550 8300 4550
Wire Wire Line
	8300 4900 8900 4900
Wire Wire Line
	8900 4850 8900 4900
Wire Wire Line
	9200 4550 9350 4550
Wire Wire Line
	9350 4600 9350 4550
Connection ~ 9350 4550
Wire Wire Line
	8300 4600 8300 4550
Connection ~ 8300 4550
Wire Wire Line
	8300 4550 8600 4550
Connection ~ 8900 4900
Wire Wire Line
	8900 4900 9350 4900
Wire Wire Line
	8900 4900 8900 4950
$Comp
L power:+5V #PWR0152
U 1 1 5FA7D3D3
P 8500 1200
F 0 "#PWR0152" H 8500 1050 50  0001 C CNN
F 1 "+5V" H 8515 1373 50  0000 C CNN
F 2 "" H 8500 1200 50  0001 C CNN
F 3 "" H 8500 1200 50  0001 C CNN
	1    8500 1200
	1    0    0    -1  
$EndComp
Connection ~ 8500 1200
$EndSCHEMATC
