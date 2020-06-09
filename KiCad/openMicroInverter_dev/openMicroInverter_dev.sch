EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A2 23386 16535
encoding utf-8
Sheet 1 1
Title "open Micro Inverter with Arduino - development model"
Date "2020-06-09"
Rev "1.1"
Comp ""
Comment1 "Design by: M. Stokroos"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L openMicroInverter_dev-rescue:ARDUINO_SHIELD_R3-SmartInverter_proto-rescue P3
U 1 1 56D75177
P 9800 11500
F 0 "P3" H 10050 10550 60  0000 C CNN
F 1 "ARDUINO_R3" H 9800 12650 60  0000 C CNN
F 2 "" H 12550 9900 60  0000 C CNN
F 3 "" H 12550 9900 60  0000 C CNN
	1    9800 11500
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:LEM_LA55-P-SmartInverter_proto-rescue T3
U 1 1 56D75178
P 19100 3500
F 0 "T3" H 19250 3200 60  0000 C CNN
F 1 "LEM_LA55-P" H 19450 3850 60  0000 C CNN
F 2 "" H 19100 3500 60  0000 C CNN
F 3 "" H 19100 3500 60  0000 C CNN
	1    19100 3500
	-1   0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:LEM_LV25-P-SmartInverter_proto-rescue T2
U 1 1 56D75179
P 14900 3500
F 0 "T2" H 15100 3800 60  0000 C CNN
F 1 "LEM_LV25-P" H 14550 3200 60  0000 C CNN
F 2 "" H 14900 3500 60  0000 C CNN
F 3 "" H 14900 3500 60  0000 C CNN
	1    14900 3500
	-1   0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:HIP4082-SmartInverter_proto-rescue U1
U 1 1 56D7517A
P 3100 3600
F 0 "U1" H 3350 2550 60  0000 C CNN
F 1 "HIP4082" H 3100 4450 60  0000 C CNN
F 2 "" H 3000 3600 60  0000 C CNN
F 3 "" H 3000 3600 60  0000 C CNN
	1    3100 3600
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:Q_POWERMOSFET_GDS-SmartInverter_proto-rescue Q1
U 1 1 56D7517B
P 5900 3000
F 0 "Q1" H 6200 2850 50  0000 R CNN
F 1 "N-CHANNEL" H 5950 3200 50  0001 R CNN
F 2 "" H 6100 3100 50  0000 C CNN
F 3 "" H 5900 3000 50  0000 C CNN
	1    5900 3000
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:Q_POWERMOSFET_GDS-SmartInverter_proto-rescue Q2
U 1 1 56D7517D
P 7600 3000
F 0 "Q2" H 7900 2850 50  0000 R CNN
F 1 "N-CHANNEL" H 8250 3150 50  0001 R CNN
F 2 "" H 7800 3100 50  0000 C CNN
F 3 "" H 7600 3000 50  0000 C CNN
	1    7600 3000
	-1   0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:Q_POWERMOSFET_GDS-SmartInverter_proto-rescue Q4
U 1 1 56D7517E
P 7600 4100
F 0 "Q4" H 7900 3950 50  0000 R CNN
F 1 "N-CHANNEL" H 8200 4300 50  0001 R CNN
F 2 "" H 7800 4200 50  0000 C CNN
F 3 "" H 7600 4100 50  0000 C CNN
	1    7600 4100
	-1   0    0    -1  
$EndComp
Text Label 7800 3400 2    60   ~ 0
AHS
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R3
U 1 1 56D7517F
P 5450 3000
F 0 "R3" V 5530 3000 50  0000 C CNN
F 1 "15" V 5450 3000 50  0000 C CNN
F 2 "" V 5380 3000 50  0000 C CNN
F 3 "" H 5450 3000 50  0000 C CNN
	1    5450 3000
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R13
U 1 1 56D75180
P 5450 4100
F 0 "R13" V 5530 4100 50  0000 C CNN
F 1 "15" V 5450 4100 50  0000 C CNN
F 2 "" V 5380 4100 50  0000 C CNN
F 3 "" H 5450 4100 50  0000 C CNN
	1    5450 4100
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R4
U 1 1 56D75181
P 8050 3000
F 0 "R4" V 8130 3000 50  0000 C CNN
F 1 "15" V 8050 3000 50  0000 C CNN
F 2 "" V 7980 3000 50  0000 C CNN
F 3 "" H 8050 3000 50  0000 C CNN
	1    8050 3000
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R14
U 1 1 56D75182
P 8050 4100
F 0 "R14" V 8130 4100 50  0000 C CNN
F 1 "15" V 8050 4100 50  0000 C CNN
F 2 "" V 7980 4100 50  0000 C CNN
F 3 "" H 8050 4100 50  0000 C CNN
	1    8050 4100
	0    1    1    0   
$EndComp
Text Label 8200 3000 2    60   ~ 0
AHO
Text Label 8200 4100 2    60   ~ 0
ALO
Text Label 4050 4000 2    60   ~ 0
AHS
Text Label 4050 4200 2    60   ~ 0
AHO
Text Label 4050 3600 2    60   ~ 0
ALO
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C5
U 1 1 56D75183
P 3800 2700
F 0 "C5" H 3825 2800 50  0000 L CNN
F 1 "100n" H 3825 2600 50  0000 L CNN
F 2 "" H 3838 2550 50  0000 C CNN
F 3 "" H 3800 2700 50  0000 C CNN
	1    3800 2700
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C7
U 1 1 56D75184
P 4300 4200
F 0 "C7" H 4325 4300 50  0000 L CNN
F 1 "100n" H 4325 4100 50  0000 L CNN
F 2 "" H 4338 4050 50  0000 C CNN
F 3 "" H 4300 4200 50  0000 C CNN
	1    4300 4200
	1    0    0    -1  
$EndComp
Text Label 6300 3600 2    60   ~ 0
OUT_A
Text Label 7200 3600 0    60   ~ 0
OUT_B
Text Label 5200 2000 0    60   ~ 0
P12V0
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R22
U 1 1 56D75185
P 3600 6900
F 0 "R22" V 3680 6900 50  0000 C CNN
F 1 "22K" V 3600 6900 50  0000 C CNN
F 2 "" V 3530 6900 50  0000 C CNN
F 3 "" H 3600 6900 50  0000 C CNN
	1    3600 6900
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R24
U 1 1 56D75186
P 3600 7100
F 0 "R24" V 3680 7100 50  0000 C CNN
F 1 "1K" V 3600 7100 50  0000 C CNN
F 2 "" V 3530 7100 50  0000 C CNN
F 3 "" H 3600 7100 50  0000 C CNN
	1    3600 7100
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R26
U 1 1 56D75187
P 3850 7450
F 0 "R26" V 3930 7450 50  0000 C CNN
F 1 "330" V 3850 7450 50  0000 C CNN
F 2 "" V 3780 7450 50  0000 C CNN
F 3 "" H 3850 7450 50  0000 C CNN
	1    3850 7450
	-1   0    0    1   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R20
U 1 1 56D75188
P 4300 6300
F 0 "R20" V 4380 6300 50  0000 C CNN
F 1 "22K" V 4300 6300 50  0000 C CNN
F 2 "" V 4230 6300 50  0000 C CNN
F 3 "" H 4300 6300 50  0000 C CNN
	1    4300 6300
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R23
U 1 1 56D75189
P 5250 7000
F 0 "R23" V 5330 7000 50  0000 C CNN
F 1 "220" V 5250 7000 50  0000 C CNN
F 2 "" V 5180 7000 50  0000 C CNN
F 3 "" H 5250 7000 50  0000 C CNN
	1    5250 7000
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C9
U 1 1 56D7518A
P 4450 6000
F 0 "C9" V 4250 5950 50  0000 L CNN
F 1 "1n5" V 4350 6100 50  0000 L CNN
F 2 "" H 4488 5850 50  0000 C CNN
F 3 "" H 4450 6000 50  0000 C CNN
	1    4450 6000
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:TRANSFO-SmartInverter_proto-rescue T5
U 1 1 56D7518B
P 17800 4900
F 0 "T5" H 17800 5150 50  0000 C CNN
F 1 "XFMR 18V/240V" H 17750 4550 50  0000 C CNN
F 2 "" H 17800 4900 50  0000 C CNN
F 3 "" H 17800 4900 50  0000 C CNN
	1    17800 4900
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:CP-SmartInverter_proto-rescue C1
U 1 1 56D7518C
P 6500 2250
F 0 "C1" H 6525 2350 50  0000 L CNN
F 1 "3300uF" H 6525 2150 50  0000 L CNN
F 2 "" H 6538 2100 50  0000 C CNN
F 3 "" H 6500 2250 50  0000 C CNN
	1    6500 2250
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR01
U 1 1 56D7518D
P 6500 2450
F 0 "#PWR01" H 6500 2200 50  0001 C CNN
F 1 "GND" H 6500 2300 50  0000 C CNN
F 2 "" H 6500 2450 50  0000 C CNN
F 3 "" H 6500 2450 50  0000 C CNN
	1    6500 2450
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR010
U 1 1 56D7518E
P 6750 4700
F 0 "#PWR010" H 6750 4450 50  0001 C CNN
F 1 "GND" H 6750 4550 50  0000 C CNN
F 2 "" H 6750 4700 50  0000 C CNN
F 3 "" H 6750 4700 50  0000 C CNN
	1    6750 4700
	1    0    0    -1  
$EndComp
Text Label 16900 4700 0    60   ~ 0
OUT_A
Text Label 16900 5100 0    60   ~ 0
OUT_B
$Comp
L openMicroInverter_dev-rescue:INDUCTOR-SmartInverter_proto-rescue L1
U 1 1 56D7518F
P 18700 4400
F 0 "L1" V 18650 4400 50  0000 C CNN
F 1 "INDUCTOR" V 18800 4400 50  0000 C CNN
F 2 "" H 18700 4400 50  0000 C CNN
F 3 "" H 18700 4400 50  0000 C CNN
	1    18700 4400
	0    -1   -1   0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C8
U 1 1 56D75190
P 19100 4750
F 0 "C8" H 19125 4850 50  0000 L CNN
F 1 "1uF/400Vac" H 19125 4650 50  0000 L CNN
F 2 "" H 19138 4600 50  0000 C CNN
F 3 "" H 19100 4750 50  0000 C CNN
	1    19100 4750
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:RELAY_DPST_NO-SmartInverter_proto-rescue K1
U 1 1 56D75191
P 17200 2650
F 0 "K1" V 16900 2250 60  0000 C CNN
F 1 "ISLANDING RELAY" V 17750 2600 60  0000 C CNN
F 2 "" H 17200 2650 60  0000 C CNN
F 3 "" H 17200 2650 60  0000 C CNN
	1    17200 2650
	0    -1   -1   0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:D-SmartInverter_proto-rescue D2
U 1 1 56D75192
P 17200 3400
F 0 "D2" H 17200 3500 50  0000 C CNN
F 1 "D" H 17200 3300 50  0000 C CNN
F 2 "" H 17200 3400 50  0000 C CNN
F 3 "" H 17200 3400 50  0000 C CNN
	1    17200 3400
	-1   0    0    1   
$EndComp
$Comp
L openMicroInverter_dev-rescue:CONN_01X02-SmartInverter_proto-rescue P1
U 1 1 56D75193
P 14200 2550
F 0 "P1" H 14200 2700 50  0000 C CNN
F 1 "CONN_01X02" V 14300 2550 50  0001 C CNN
F 2 "" H 14200 2550 50  0000 C CNN
F 3 "" H 14200 2550 50  0000 C CNN
	1    14200 2550
	-1   0    0    1   
$EndComp
Text Notes 13400 2650 0    60   ~ 0
grid\n230V/50Hz
Text Notes 14050 2550 0    60   ~ 0
L
Text Notes 14050 2650 0    60   ~ 0
N
$Comp
L openMicroInverter_dev-rescue:CONN_01X02-SmartInverter_proto-rescue P2
U 1 1 56D75194
P 21450 2550
F 0 "P2" H 21450 2400 50  0000 C CNN
F 1 "CONN_01X02" V 21550 2550 50  0001 C CNN
F 2 "" H 21450 2550 50  0000 C CNN
F 3 "" H 21450 2550 50  0000 C CNN
	1    21450 2550
	1    0    0    -1  
$EndComp
Text Notes 21650 2550 0    60   ~ 0
local load
Text Notes 18400 5300 0    60   ~ 0
output filter can be: L, LC or LCL
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R5
U 1 1 56D75195
P 15450 3400
F 0 "R5" V 15530 3400 50  0000 C CNN
F 1 "8K2" V 15450 3400 50  0000 C CNN
F 2 "" V 15380 3400 50  0000 C CNN
F 3 "" H 15450 3400 50  0000 C CNN
	1    15450 3400
	0    -1   -1   0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R7
U 1 1 56D75196
P 15450 3600
F 0 "R7" V 15530 3600 50  0000 C CNN
F 1 "8K2" V 15450 3600 50  0000 C CNN
F 2 "" V 15380 3600 50  0000 C CNN
F 3 "" H 15450 3600 50  0000 C CNN
	1    15450 3600
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R1
U 1 1 56D75197
P 15700 3050
F 0 "R1" V 15780 3050 50  0000 C CNN
F 1 "8K2" V 15700 3050 50  0000 C CNN
F 2 "" V 15630 3050 50  0000 C CNN
F 3 "" H 15700 3050 50  0000 C CNN
	1    15700 3050
	-1   0    0    1   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R2
U 1 1 56D75198
P 16000 3050
F 0 "R2" V 16080 3050 50  0000 C CNN
F 1 "8K2" V 16000 3050 50  0000 C CNN
F 2 "" V 15930 3050 50  0000 C CNN
F 3 "" H 16000 3050 50  0000 C CNN
	1    16000 3050
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:LEM_LV25-P-SmartInverter_proto-rescue T4
U 1 1 56D75199
P 21500 4700
F 0 "T4" H 21650 4400 60  0000 C CNN
F 1 "LEM_LV25-P" H 21850 5000 60  0000 C CNN
F 2 "" H 21500 4700 60  0000 C CNN
F 3 "" H 21500 4700 60  0000 C CNN
	1    21500 4700
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R16
U 1 1 56D7519A
P 22000 5050
F 0 "R16" V 22080 5050 50  0000 C CNN
F 1 "100" V 22000 5050 50  0000 C CNN
F 2 "" V 21930 5050 50  0000 C CNN
F 3 "" H 22000 5050 50  0000 C CNN
	1    22000 5050
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R8
U 1 1 56D7519B
P 18600 3700
F 0 "R8" V 18680 3700 50  0000 C CNN
F 1 "56" V 18600 3700 50  0000 C CNN
F 2 "" V 18530 3700 50  0000 C CNN
F 3 "" H 18600 3700 50  0000 C CNN
	1    18600 3700
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R9
U 1 1 56D7519C
P 14400 3850
F 0 "R9" V 14480 3850 50  0000 C CNN
F 1 "100" V 14400 3850 50  0000 C CNN
F 2 "" V 14330 3850 50  0000 C CNN
F 3 "" H 14400 3850 50  0000 C CNN
	1    14400 3850
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR07
U 1 1 56D7519D
P 14400 4200
F 0 "#PWR07" H 14400 3950 50  0001 C CNN
F 1 "GND" H 14400 4050 50  0000 C CNN
F 2 "" H 14400 4200 50  0000 C CNN
F 3 "" H 14400 4200 50  0000 C CNN
	1    14400 4200
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR06
U 1 1 56D7519E
P 18600 3900
F 0 "#PWR06" H 18600 3650 50  0001 C CNN
F 1 "GND" H 18600 3750 50  0000 C CNN
F 2 "" H 18600 3900 50  0000 C CNN
F 3 "" H 18600 3900 50  0000 C CNN
	1    18600 3900
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR011
U 1 1 56D7519F
P 22000 5400
F 0 "#PWR011" H 22000 5150 50  0001 C CNN
F 1 "GND" H 22000 5250 50  0000 C CNN
F 2 "" H 22000 5400 50  0000 C CNN
F 3 "" H 22000 5400 50  0000 C CNN
	1    22000 5400
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C3
U 1 1 56D751A0
P 4600 2350
F 0 "C3" H 4625 2450 50  0000 L CNN
F 1 "100n" H 4625 2250 50  0000 L CNN
F 2 "" H 4638 2200 50  0000 C CNN
F 3 "" H 4600 2350 50  0000 C CNN
	1    4600 2350
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:CP-SmartInverter_proto-rescue C4
U 1 1 56D751A1
P 4900 2350
F 0 "C4" H 4925 2450 50  0000 L CNN
F 1 "10uF" H 4925 2250 50  0000 L CNN
F 2 "" H 4938 2200 50  0000 C CNN
F 3 "" H 4900 2350 50  0000 C CNN
	1    4900 2350
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR03
U 1 1 56D751A2
P 4600 2600
F 0 "#PWR03" H 4600 2350 50  0001 C CNN
F 1 "GND" H 4600 2450 50  0000 C CNN
F 2 "" H 4600 2600 50  0000 C CNN
F 3 "" H 4600 2600 50  0000 C CNN
	1    4600 2600
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR04
U 1 1 56D751A3
P 4900 2600
F 0 "#PWR04" H 4900 2350 50  0001 C CNN
F 1 "GND" H 4900 2450 50  0000 C CNN
F 2 "" H 4900 2600 50  0000 C CNN
F 3 "" H 4900 2600 50  0000 C CNN
	1    4900 2600
	1    0    0    -1  
$EndComp
Text Label 11500 2000 0    60   ~ 0
VBATT+
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R29
U 1 1 56D751A4
P 3600 9600
F 0 "R29" V 3680 9600 50  0000 C CNN
F 1 "22K" V 3600 9600 50  0000 C CNN
F 2 "" V 3530 9600 50  0000 C CNN
F 3 "" H 3600 9600 50  0000 C CNN
	1    3600 9600
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R31
U 1 1 56D751A5
P 3600 9800
F 0 "R31" V 3680 9800 50  0000 C CNN
F 1 "1K" V 3600 9800 50  0000 C CNN
F 2 "" V 3530 9800 50  0000 C CNN
F 3 "" H 3600 9800 50  0000 C CNN
	1    3600 9800
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R28
U 1 1 56D751A6
P 4300 9000
F 0 "R28" V 4380 9000 50  0000 C CNN
F 1 "22K" V 4300 9000 50  0000 C CNN
F 2 "" V 4230 9000 50  0000 C CNN
F 3 "" H 4300 9000 50  0000 C CNN
	1    4300 9000
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R30
U 1 1 56D751A7
P 5250 9700
F 0 "R30" V 5330 9700 50  0000 C CNN
F 1 "220" V 5250 9700 50  0000 C CNN
F 2 "" V 5180 9700 50  0000 C CNN
F 3 "" H 5250 9700 50  0000 C CNN
	1    5250 9700
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C19
U 1 1 56D751A8
P 4300 8800
F 0 "C19" V 4100 8750 50  0000 L CNN
F 1 "1n5" V 4200 8900 50  0000 L CNN
F 2 "" H 4338 8650 50  0000 C CNN
F 3 "" H 4300 8800 50  0000 C CNN
	1    4300 8800
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R38
U 1 1 56D751A9
P 3600 12100
F 0 "R38" V 3680 12100 50  0000 C CNN
F 1 "22K" V 3600 12100 50  0000 C CNN
F 2 "" V 3530 12100 50  0000 C CNN
F 3 "" H 3600 12100 50  0000 C CNN
	1    3600 12100
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R40
U 1 1 56D751AA
P 3600 12300
F 0 "R40" V 3680 12300 50  0000 C CNN
F 1 "1K" V 3600 12300 50  0000 C CNN
F 2 "" V 3530 12300 50  0000 C CNN
F 3 "" H 3600 12300 50  0000 C CNN
	1    3600 12300
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R37
U 1 1 56D751AB
P 4300 11500
F 0 "R37" V 4380 11500 50  0000 C CNN
F 1 "22K" V 4300 11500 50  0000 C CNN
F 2 "" V 4230 11500 50  0000 C CNN
F 3 "" H 4300 11500 50  0000 C CNN
	1    4300 11500
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R39
U 1 1 56D751AC
P 5250 12200
F 0 "R39" V 5330 12200 50  0000 C CNN
F 1 "220" V 5250 12200 50  0000 C CNN
F 2 "" V 5180 12200 50  0000 C CNN
F 3 "" H 5250 12200 50  0000 C CNN
	1    5250 12200
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C21
U 1 1 56D751AD
P 4300 11300
F 0 "C21" V 4100 11250 50  0000 L CNN
F 1 "1n5" V 4200 11400 50  0000 L CNN
F 2 "" H 4338 11150 50  0000 C CNN
F 3 "" H 4300 11300 50  0000 C CNN
	1    4300 11300
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R46
U 1 1 56D751AE
P 3600 14600
F 0 "R46" V 3680 14600 50  0000 C CNN
F 1 "22K" V 3600 14600 50  0000 C CNN
F 2 "" V 3530 14600 50  0000 C CNN
F 3 "" H 3600 14600 50  0000 C CNN
	1    3600 14600
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R48
U 1 1 56D751AF
P 3600 14800
F 0 "R48" V 3680 14800 50  0000 C CNN
F 1 "1K" V 3600 14800 50  0000 C CNN
F 2 "" V 3530 14800 50  0000 C CNN
F 3 "" H 3600 14800 50  0000 C CNN
	1    3600 14800
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R44
U 1 1 56D751B0
P 4300 14000
F 0 "R44" V 4380 14000 50  0000 C CNN
F 1 "22K" V 4300 14000 50  0000 C CNN
F 2 "" V 4230 14000 50  0000 C CNN
F 3 "" H 4300 14000 50  0000 C CNN
	1    4300 14000
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R47
U 1 1 56D751B1
P 5250 14700
F 0 "R47" V 5330 14700 50  0000 C CNN
F 1 "220" V 5250 14700 50  0000 C CNN
F 2 "" V 5180 14700 50  0000 C CNN
F 3 "" H 5250 14700 50  0000 C CNN
	1    5250 14700
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C22
U 1 1 56D751B2
P 4300 13800
F 0 "C22" V 4100 13800 50  0000 L CNN
F 1 "1n5" V 4200 13900 50  0000 L CNN
F 2 "" H 4338 13650 50  0000 C CNN
F 3 "" H 4300 13800 50  0000 C CNN
	1    4300 13800
	0    1    1    0   
$EndComp
Text Label 13700 3500 0    60   ~ 0
Vline_scaled
Text Label 18000 3500 0    60   ~ 0
Iinv_scaled
Text Label 22600 4700 2    60   ~ 0
Vinv_scaled
$Comp
L openMicroInverter_dev-rescue:LEM_LA55-P-SmartInverter_proto-rescue T1
U 1 1 56D751B3
P 10400 2400
F 0 "T1" H 10550 2100 60  0000 C CNN
F 1 "LEM_LA55-P" V 10200 2950 60  0000 C CNN
F 2 "" H 10400 2400 60  0000 C CNN
F 3 "" H 10400 2400 60  0000 C CNN
	1    10400 2400
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R6
U 1 1 56D751B4
P 10400 3150
F 0 "R6" V 10480 3150 50  0000 C CNN
F 1 "56" V 10400 3150 50  0000 C CNN
F 2 "" V 10330 3150 50  0000 C CNN
F 3 "" H 10400 3150 50  0000 C CNN
	1    10400 3150
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR05
U 1 1 56D751B5
P 10400 3400
F 0 "#PWR05" H 10400 3150 50  0001 C CNN
F 1 "GND" H 10400 3250 50  0000 C CNN
F 2 "" H 10400 3400 50  0000 C CNN
F 3 "" H 10400 3400 50  0000 C CNN
	1    10400 3400
	1    0    0    -1  
$EndComp
Text Label 11100 2800 2    60   ~ 0
Ibatt_scaled
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R19
U 1 1 56D751B6
P 10000 6850
F 0 "R19" V 10080 6850 50  0000 C CNN
F 1 "56K" V 10000 6850 50  0000 C CNN
F 2 "" V 9930 6850 50  0000 C CNN
F 3 "" H 10000 6850 50  0000 C CNN
	1    10000 6850
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R25
U 1 1 56D751B7
P 10000 8150
F 0 "R25" V 10080 8150 50  0000 C CNN
F 1 "8.2K" V 10000 8150 50  0000 C CNN
F 2 "" V 9930 8150 50  0000 C CNN
F 3 "" H 10000 8150 50  0000 C CNN
	1    10000 8150
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR015
U 1 1 56D751B8
P 10000 8500
F 0 "#PWR015" H 10000 8250 50  0001 C CNN
F 1 "GND" H 10000 8350 50  0000 C CNN
F 2 "" H 10000 8500 50  0000 C CNN
F 3 "" H 10000 8500 50  0000 C CNN
	1    10000 8500
	1    0    0    -1  
$EndComp
Text Label 9300 7800 0    60   ~ 0
Vbatt_scaled
Text Label 2750 6900 0    60   ~ 0
Vline_scaled
Text Label 2750 9600 0    60   ~ 0
Iinv_scaled
Text Label 2850 12100 0    60   ~ 0
Vinv_scaled
Text Label 2800 14600 0    60   ~ 0
Ibatt_scaled
Text Label 5550 7000 0    60   ~ 0
Vin_ac
Text Label 5550 9700 0    60   ~ 0
Iinv_ac
Text Label 5550 12200 0    60   ~ 0
Vinv_ac
Text Label 5550 14700 0    60   ~ 0
Ibatt
Text Label 8500 11800 0    60   ~ 0
Vin_ac
Text Label 8500 11900 0    60   ~ 0
Iinv_ac
Text Label 8500 12000 0    60   ~ 0
Vinv_ac
Text Label 8500 12100 0    60   ~ 0
Ibatt
Text Label 8500 12200 0    60   ~ 0
Vbatt_scaled
Text Label 10700 11000 0    50   ~ 0
XOR_OUT
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R33
U 1 1 56D751B9
P 11700 11000
F 0 "R33" V 11780 11000 50  0000 C CNN
F 1 "10K" V 11700 11000 50  0000 C CNN
F 2 "" V 11630 11000 50  0000 C CNN
F 3 "" H 11700 11000 50  0000 C CNN
	1    11700 11000
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR018
U 1 1 56D751BB
P 12050 11500
F 0 "#PWR018" H 12050 11250 50  0001 C CNN
F 1 "GND" H 12050 11350 50  0000 C CNN
F 2 "" H 12050 11500 50  0000 C CNN
F 3 "" H 12050 11500 50  0000 C CNN
	1    12050 11500
	1    0    0    -1  
$EndComp
Text Label 12400 11900 2    60   ~ 0
~grid_connect_relay
Text Label 10700 11400 0    50   ~ 0
H_DIS
Text Label 10700 11300 0    50   ~ 0
H_PWMB
Text Label 10700 11200 0    50   ~ 0
H_PWMA
Text Label 10700 10900 0    50   ~ 0
PLL_LOCK
Text Label 11200 11500 0    60   ~ 0
Vin_ac
Text Notes 11200 11600 0    60   ~ 0
(ZCD input)
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR014
U 1 1 56D751BC
P 4350 7400
F 0 "#PWR014" H 4350 7150 50  0001 C CNN
F 1 "GND" H 4350 7250 50  0000 C CNN
F 2 "" H 4350 7400 50  0000 C CNN
F 3 "" H 4350 7400 50  0000 C CNN
	1    4350 7400
	1    0    0    -1  
$EndComp
Text Label 11500 4600 0    60   ~ 0
VBATT-
$Comp
L openMicroInverter_dev-rescue:CP-SmartInverter_proto-rescue C2
U 1 1 56D751BD
P 7000 2250
F 0 "C2" H 7025 2350 50  0000 L CNN
F 1 "3300uF" H 7025 2150 50  0000 L CNN
F 2 "" H 7038 2100 50  0000 C CNN
F 3 "" H 7000 2250 50  0000 C CNN
	1    7000 2250
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR02
U 1 1 56D751BE
P 7000 2450
F 0 "#PWR02" H 7000 2200 50  0001 C CNN
F 1 "GND" H 7000 2300 50  0000 C CNN
F 2 "" H 7000 2450 50  0000 C CNN
F 3 "" H 7000 2450 50  0000 C CNN
	1    7000 2450
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R36
U 1 1 56D751BF
P 10850 12100
F 0 "R36" V 10930 12100 50  0000 C CNN
F 1 "10K" V 10850 12100 50  0000 C CNN
F 2 "" V 10780 12100 50  0000 C CNN
F 3 "" H 10850 12100 50  0000 C CNN
	1    10850 12100
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:Q_NPN_CBE-SmartInverter_proto-rescue Q5
U 1 1 56D751C0
P 11400 12300
F 0 "Q5" H 11700 12350 50  0000 R CNN
F 1 "Q_NPN_CBE" H 12000 12250 50  0000 R CNN
F 2 "" H 11600 12400 50  0000 C CNN
F 3 "" H 11400 12300 50  0000 C CNN
	1    11400 12300
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR020
U 1 1 56D751C1
P 11500 12550
F 0 "#PWR020" H 11500 12300 50  0001 C CNN
F 1 "GND" H 11500 12400 50  0000 C CNN
F 2 "" H 11500 12550 50  0000 C CNN
F 3 "" H 11500 12550 50  0000 C CNN
	1    11500 12550
	1    0    0    -1  
$EndComp
Text Label 15750 4150 0    60   ~ 0
~grid_connect_relay
Text Label 18100 3050 2    60   ~ 0
P12V0
Text Notes 11600 10850 0    60   ~ 0
PLL loopfilter\n(obsolete)
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R12
U 1 1 56D751C2
P 20800 4400
F 0 "R12" V 20880 4400 50  0000 C CNN
F 1 "8K2" V 20800 4400 50  0000 C CNN
F 2 "" V 20730 4400 50  0000 C CNN
F 3 "" H 20800 4400 50  0000 C CNN
	1    20800 4400
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R11
U 1 1 56D751C3
P 20350 4400
F 0 "R11" V 20430 4400 50  0000 C CNN
F 1 "8K2" V 20350 4400 50  0000 C CNN
F 2 "" V 20280 4400 50  0000 C CNN
F 3 "" H 20350 4400 50  0000 C CNN
	1    20350 4400
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R18
U 1 1 56D751C4
P 20800 5100
F 0 "R18" V 20880 5100 50  0000 C CNN
F 1 "8K2" V 20800 5100 50  0000 C CNN
F 2 "" V 20730 5100 50  0000 C CNN
F 3 "" H 20800 5100 50  0000 C CNN
	1    20800 5100
	0    1    1    0   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R17
U 1 1 56D751C5
P 20350 5100
F 0 "R17" V 20430 5100 50  0000 C CNN
F 1 "8K2" V 20350 5100 50  0000 C CNN
F 2 "" V 20280 5100 50  0000 C CNN
F 3 "" H 20350 5100 50  0000 C CNN
	1    20350 5100
	0    1    1    0   
$EndComp
Text Notes 20200 4800 0    60   ~ 0
PR02 RESISTORS
Text Notes 16250 3650 1    60   ~ 0
PR02 RESISTORS
Text Notes 6300 1850 0    60   ~ 0
H-BRIDGE
Text Label 2000 3400 0    50   ~ 0
H_PWMB
Text Label 2000 3600 0    50   ~ 0
H_PWMA
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR09
U 1 1 56D751C6
P 1700 4300
F 0 "#PWR09" H 1700 4050 50  0001 C CNN
F 1 "GND" H 1700 4150 50  0000 C CNN
F 2 "" H 1700 4300 50  0000 C CNN
F 3 "" H 1700 4300 50  0000 C CNN
	1    1700 4300
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R10
U 1 1 56D751C7
P 2050 3800
F 0 "R10" V 2130 3800 50  0000 C CNN
F 1 "33K" V 2050 3800 50  0000 C CNN
F 2 "" V 1980 3800 50  0000 C CNN
F 3 "" H 2050 3800 50  0000 C CNN
	1    2050 3800
	0    1    1    0   
$EndComp
Text Label 8500 11300 0    60   ~ 0
P5V0
$Comp
L openMicroInverter_dev-rescue:CP-SmartInverter_proto-rescue C20
U 1 1 56D751C9
P 12050 11250
F 0 "C20" H 12075 11350 50  0000 L CNN
F 1 "47uF" H 12075 11150 50  0000 L CNN
F 2 "" H 12088 11100 50  0000 C CNN
F 3 "" H 12050 11250 50  0000 C CNN
	1    12050 11250
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:MCP6004-SmartInverter_proto-rescue U2
U 1 1 56D751CA
P 4350 7000
F 0 "U2" H 4550 6800 60  0000 C CNN
F 1 "MCP6004" H 4600 7200 50  0000 C CNN
F 2 "" H 4450 7000 60  0000 C CNN
F 3 "" H 4450 7000 60  0000 C CNN
	1    4350 7000
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:MCP6004-SmartInverter_proto-rescue U2
U 2 1 56D751CB
P 4350 9700
F 0 "U2" H 4550 9500 60  0000 C CNN
F 1 "MCP6004" H 4600 9900 50  0000 C CNN
F 2 "" H 4450 9700 60  0000 C CNN
F 3 "" H 4450 9700 60  0000 C CNN
	2    4350 9700
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:MCP6004-SmartInverter_proto-rescue U2
U 3 1 56D751CC
P 4350 12200
F 0 "U2" H 4550 12000 60  0000 C CNN
F 1 "MCP6004" H 4600 12400 50  0000 C CNN
F 2 "" H 4450 12200 60  0000 C CNN
F 3 "" H 4450 12200 60  0000 C CNN
	3    4350 12200
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:MCP6004-SmartInverter_proto-rescue U2
U 4 1 56D751CD
P 4350 14700
F 0 "U2" H 4550 14500 60  0000 C CNN
F 1 "MCP6004" H 4600 14900 50  0000 C CNN
F 2 "" H 4450 14700 60  0000 C CNN
F 3 "" H 4450 14700 60  0000 C CNN
	4    4350 14700
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C14
U 1 1 56D751CE
P 6050 6750
F 0 "C14" H 6075 6850 50  0000 L CNN
F 1 "100n" H 6075 6650 50  0000 L CNN
F 2 "" H 6088 6600 50  0000 C CNN
F 3 "" H 6050 6750 50  0000 C CNN
	1    6050 6750
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR012
U 1 1 56D751CF
P 6050 6950
F 0 "#PWR012" H 6050 6700 50  0001 C CNN
F 1 "GND" H 6050 6800 50  0000 C CNN
F 2 "" H 6050 6950 50  0000 C CNN
F 3 "" H 6050 6950 50  0000 C CNN
	1    6050 6950
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R27
U 1 1 56D751D0
P 3850 7850
F 0 "R27" V 3930 7850 50  0000 C CNN
F 1 "3.3" V 3850 7850 50  0000 C CNN
F 2 "" V 3780 7850 50  0000 C CNN
F 3 "" H 3850 7850 50  0000 C CNN
	1    3850 7850
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR016
U 1 1 56D751D1
P 3850 8150
F 0 "#PWR016" H 3850 7900 50  0001 C CNN
F 1 "GND" H 3850 8000 50  0000 C CNN
F 2 "" H 3850 8150 50  0000 C CNN
F 3 "" H 3850 8150 50  0000 C CNN
	1    3850 8150
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R32
U 1 1 56D751D2
P 3850 10050
F 0 "R32" V 3930 10050 50  0000 C CNN
F 1 "330" V 3850 10050 50  0000 C CNN
F 2 "" V 3780 10050 50  0000 C CNN
F 3 "" H 3850 10050 50  0000 C CNN
	1    3850 10050
	-1   0    0    1   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R34
U 1 1 56D751D3
P 3850 10400
F 0 "R34" V 3930 10400 50  0000 C CNN
F 1 "3.3" V 3850 10400 50  0000 C CNN
F 2 "" V 3780 10400 50  0000 C CNN
F 3 "" H 3850 10400 50  0000 C CNN
	1    3850 10400
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR017
U 1 1 56D751D4
P 3850 10600
F 0 "#PWR017" H 3850 10350 50  0001 C CNN
F 1 "GND" H 3850 10450 50  0000 C CNN
F 2 "" H 3850 10600 50  0000 C CNN
F 3 "" H 3850 10600 50  0000 C CNN
	1    3850 10600
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R41
U 1 1 56D751D5
P 3850 12550
F 0 "R41" V 3930 12550 50  0000 C CNN
F 1 "330" V 3850 12550 50  0000 C CNN
F 2 "" V 3780 12550 50  0000 C CNN
F 3 "" H 3850 12550 50  0000 C CNN
	1    3850 12550
	-1   0    0    1   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R42
U 1 1 56D751D6
P 3850 12900
F 0 "R42" V 3930 12900 50  0000 C CNN
F 1 "3.3" V 3850 12900 50  0000 C CNN
F 2 "" V 3780 12900 50  0000 C CNN
F 3 "" H 3850 12900 50  0000 C CNN
	1    3850 12900
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR021
U 1 1 56D751D7
P 3850 13100
F 0 "#PWR021" H 3850 12850 50  0001 C CNN
F 1 "GND" H 3850 12950 50  0000 C CNN
F 2 "" H 3850 13100 50  0000 C CNN
F 3 "" H 3850 13100 50  0000 C CNN
	1    3850 13100
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R49
U 1 1 56D751D8
P 3850 15050
F 0 "R49" V 3930 15050 50  0000 C CNN
F 1 "330" V 3850 15050 50  0000 C CNN
F 2 "" V 3780 15050 50  0000 C CNN
F 3 "" H 3850 15050 50  0000 C CNN
	1    3850 15050
	-1   0    0    1   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R50
U 1 1 56D751D9
P 3850 15400
F 0 "R50" V 3930 15400 50  0000 C CNN
F 1 "3.3" V 3850 15400 50  0000 C CNN
F 2 "" V 3780 15400 50  0000 C CNN
F 3 "" H 3850 15400 50  0000 C CNN
	1    3850 15400
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR023
U 1 1 56D751DA
P 3850 15600
F 0 "#PWR023" H 3850 15350 50  0001 C CNN
F 1 "GND" H 3850 15450 50  0000 C CNN
F 2 "" H 3850 15600 50  0000 C CNN
F 3 "" H 3850 15600 50  0000 C CNN
	1    3850 15600
	1    0    0    -1  
$EndComp
Text Label 2750 7100 0    60   ~ 0
P5V0
Text Label 2750 9800 0    60   ~ 0
P5V0
Text Label 2850 12300 0    60   ~ 0
P5V0
Text Label 2800 14800 0    60   ~ 0
P5V0
Text Notes 3950 7250 0    60   ~ 0
1.25V
Text Notes 4900 7150 0    60   ~ 0
2.5V
Text Label 6350 6500 0    60   ~ 0
P5V0
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R15
U 1 1 56D751DB
P 2250 4400
F 0 "R15" V 2330 4400 50  0000 C CNN
F 1 "10K" V 2250 4400 50  0000 C CNN
F 2 "" V 2180 4400 50  0000 C CNN
F 3 "" H 2250 4400 50  0000 C CNN
	1    2250 4400
	0    1    1    0   
$EndComp
Text Label 1900 4400 0    50   ~ 0
P5V0
Text Label 1900 4650 0    50   ~ 0
H_DIS
$Comp
L openMicroInverter_dev-rescue:D-SmartInverter_proto-rescue D1
U 1 1 56D751DC
P 4050 2000
F 0 "D1" H 4050 2100 50  0000 C CNN
F 1 "1N4935" H 4050 1900 50  0000 C CNN
F 2 "" H 4050 2000 50  0000 C CNN
F 3 "" H 4050 2000 50  0000 C CNN
	1    4050 2000
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:D-SmartInverter_proto-rescue D3
U 1 1 56D751DD
P 4550 3800
F 0 "D3" H 4550 3900 50  0000 C CNN
F 1 "1N4935" H 4550 3700 50  0000 C CNN
F 2 "" H 4550 3800 50  0000 C CNN
F 3 "" H 4550 3800 50  0000 C CNN
	1    4550 3800
	-1   0    0    1   
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R43
U 1 1 56D751DE
P 10000 14100
F 0 "R43" V 10080 14100 50  0000 C CNN
F 1 "1K" V 10000 14100 50  0000 C CNN
F 2 "" V 9930 14100 50  0000 C CNN
F 3 "" H 10000 14100 50  0000 C CNN
	1    10000 14100
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R45
U 1 1 56D751DF
P 10000 14850
F 0 "R45" V 10080 14850 50  0000 C CNN
F 1 "1K" V 10000 14850 50  0000 C CNN
F 2 "" V 9930 14850 50  0000 C CNN
F 3 "" H 10000 14850 50  0000 C CNN
	1    10000 14850
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR022
U 1 1 56D751E0
P 10000 15150
F 0 "#PWR022" H 10000 14900 50  0001 C CNN
F 1 "GND" H 10000 15000 50  0000 C CNN
F 2 "" H 10000 15150 50  0000 C CNN
F 3 "" H 10000 15150 50  0000 C CNN
	1    10000 15150
	1    0    0    -1  
$EndComp
Text Label 10300 13800 2    60   ~ 0
P5V0
Text Label 10400 14500 0    60   ~ 0
VREF_CP
Text Label 10700 11700 0    50   ~ 0
VREF_CP
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R21
U 1 1 56D751E1
P 10000 7350
F 0 "R21" V 10080 7350 50  0000 C CNN
F 1 "1K" V 10000 7350 50  0000 C CNN
F 2 "" V 9930 7350 50  0000 C CNN
F 3 "" H 10000 7350 50  0000 C CNN
	1    10000 7350
	1    0    0    -1  
$EndComp
Text Notes 10100 7850 0    60   ~ 0
FS=39.75V
$Comp
L openMicroInverter_dev-rescue:R-SmartInverter_proto-rescue R35
U 1 1 56D751E2
P 10850 11500
F 0 "R35" V 10930 11500 50  0000 C CNN
F 1 "R" V 10850 11500 50  0000 C CNN
F 2 "" V 10780 11500 50  0000 C CNN
F 3 "" H 10850 11500 50  0000 C CNN
	1    10850 11500
	0    1    1    0   
$EndComp
Text Label 21700 4200 0    60   ~ 0
P15V0
Text Label 21600 5200 0    60   ~ 0
N15V0
Text Label 19200 4000 0    60   ~ 0
N15V0
Text Label 19200 3000 0    60   ~ 0
P15V0
Text Label 15100 3000 0    60   ~ 0
P15V0
Text Label 15100 4100 0    60   ~ 0
N15V0
Text Label 9800 2400 0    60   ~ 0
N15V0
Text Label 10900 2400 0    60   ~ 0
P15V0
Text Label 20200 10000 2    60   ~ 0
P15V0
Text Label 20200 11400 2    60   ~ 0
N15V0
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C10
U 1 1 56D751E3
P 17000 10350
F 0 "C10" H 17025 10450 50  0000 L CNN
F 1 "100n" H 17025 10250 50  0000 L CNN
F 2 "" H 17038 10200 50  0000 C CNN
F 3 "" H 17000 10350 50  0000 C CNN
	1    17000 10350
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C15
U 1 1 56D751E4
P 17000 11050
F 0 "C15" H 17025 11150 50  0000 L CNN
F 1 "100n" H 17025 10950 50  0000 L CNN
F 2 "" H 17038 10900 50  0000 C CNN
F 3 "" H 17000 11050 50  0000 C CNN
	1    17000 11050
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C11
U 1 1 56D751E5
P 17500 10350
F 0 "C11" H 17525 10450 50  0000 L CNN
F 1 "100n" H 17525 10250 50  0000 L CNN
F 2 "" H 17538 10200 50  0000 C CNN
F 3 "" H 17500 10350 50  0000 C CNN
	1    17500 10350
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C16
U 1 1 56D751E6
P 17500 11050
F 0 "C16" H 17525 11150 50  0000 L CNN
F 1 "100n" H 17525 10950 50  0000 L CNN
F 2 "" H 17538 10900 50  0000 C CNN
F 3 "" H 17500 11050 50  0000 C CNN
	1    17500 11050
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C12
U 1 1 56D751E7
P 18000 10350
F 0 "C12" H 18025 10450 50  0000 L CNN
F 1 "100n" H 18025 10250 50  0000 L CNN
F 2 "" H 18038 10200 50  0000 C CNN
F 3 "" H 18000 10350 50  0000 C CNN
	1    18000 10350
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C17
U 1 1 56D751E8
P 18000 11050
F 0 "C17" H 18025 11150 50  0000 L CNN
F 1 "100n" H 18025 10950 50  0000 L CNN
F 2 "" H 18038 10900 50  0000 C CNN
F 3 "" H 18000 11050 50  0000 C CNN
	1    18000 11050
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C13
U 1 1 56D751E9
P 18500 10350
F 0 "C13" H 18525 10450 50  0000 L CNN
F 1 "100n" H 18525 10250 50  0000 L CNN
F 2 "" H 18538 10200 50  0000 C CNN
F 3 "" H 18500 10350 50  0000 C CNN
	1    18500 10350
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C18
U 1 1 56D751EA
P 18500 11050
F 0 "C18" H 18525 11150 50  0000 L CNN
F 1 "100n" H 18525 10950 50  0000 L CNN
F 2 "" H 18538 10900 50  0000 C CNN
F 3 "" H 18500 11050 50  0000 C CNN
	1    18500 11050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 3200 6000 3400
Wire Wire Line
	6000 3400 6000 3600
Wire Wire Line
	6000 3600 6000 3900
Wire Wire Line
	7500 3200 7500 3400
Wire Wire Line
	7500 3400 7500 3600
Wire Wire Line
	7500 3600 7500 3900
Wire Wire Line
	6000 3600 6300 3600
Connection ~ 6000 3600
Wire Wire Line
	7500 3600 7200 3600
Connection ~ 7500 3600
Wire Wire Line
	6000 2800 6000 2000
Wire Wire Line
	7500 2800 7500 2000
Wire Wire Line
	7500 4600 7500 4300
Wire Wire Line
	6000 4600 6000 4300
Connection ~ 6000 3400
Wire Wire Line
	5200 3400 5200 4100
Wire Wire Line
	7500 3400 7800 3400
Connection ~ 7500 3400
Wire Wire Line
	5600 3000 5700 3000
Wire Wire Line
	5200 4100 5300 4100
Wire Wire Line
	5600 4100 5700 4100
Wire Wire Line
	7800 3000 7900 3000
Wire Wire Line
	7800 4100 7900 4100
Wire Wire Line
	8200 3000 8500 3000
Wire Wire Line
	8200 4100 8500 4100
Wire Wire Line
	3700 4000 4300 4000
Wire Wire Line
	3700 4200 4050 4200
Wire Wire Line
	3700 3600 4050 3600
Wire Wire Line
	3700 3000 5300 3000
Wire Wire Line
	3700 3200 3800 3200
Wire Wire Line
	3800 3200 5500 3200
Wire Wire Line
	5500 3200 5500 3400
Wire Wire Line
	5500 3400 6000 3400
Wire Wire Line
	3700 3400 5200 3400
Wire Wire Line
	3700 3800 4300 3800
Wire Wire Line
	4300 3800 4400 3800
Wire Wire Line
	4300 2000 4300 3800
Connection ~ 4300 3800
Wire Wire Line
	3800 2850 3800 3200
Connection ~ 3800 3200
Wire Wire Line
	2300 2000 3800 2000
Wire Wire Line
	3800 2000 3900 2000
Wire Wire Line
	2300 2000 2300 3000
Wire Wire Line
	2300 3000 2500 3000
Connection ~ 3800 2000
Wire Wire Line
	3800 2000 3800 2550
Wire Wire Line
	4200 2000 4300 2000
Wire Wire Line
	4300 2000 4600 2000
Wire Wire Line
	4600 2000 4900 2000
Wire Wire Line
	4900 2000 5200 2000
Wire Wire Line
	3700 4400 4300 4400
Wire Wire Line
	4300 4400 4800 4400
Wire Wire Line
	4800 4400 4800 3800
Wire Wire Line
	4800 3800 4700 3800
Wire Wire Line
	4300 4350 4300 4400
Connection ~ 4300 4400
Wire Wire Line
	4300 4000 4300 4050
Connection ~ 4300 2000
Wire Wire Line
	6500 2400 6500 2450
Wire Wire Line
	6500 2100 6500 2000
Wire Wire Line
	6750 4600 6750 4700
Wire Wire Line
	17400 4700 16900 4700
Wire Wire Line
	17400 5100 16900 5100
Wire Wire Line
	18200 4700 18200 4400
Wire Wire Line
	18200 4400 18400 4400
Wire Wire Line
	19100 4400 19100 4600
Connection ~ 19100 4400
Wire Wire Line
	18200 5100 19100 5100
Wire Wire Line
	19100 5100 20000 5100
Wire Wire Line
	20000 5100 20200 5100
Wire Wire Line
	19100 4900 19100 5100
Connection ~ 19100 5100
Wire Wire Line
	17600 3050 17700 3050
Wire Wire Line
	17700 3050 18100 3050
Wire Wire Line
	17700 3050 17700 3400
Wire Wire Line
	17700 3400 17350 3400
Wire Wire Line
	16800 3050 16700 3050
Wire Wire Line
	16700 3050 16700 3400
Wire Wire Line
	16700 3400 16700 4150
Wire Wire Line
	16700 3400 17050 3400
Wire Wire Line
	14500 2400 15700 2400
Wire Wire Line
	15700 2400 16800 2400
Wire Wire Line
	14500 2700 16000 2700
Wire Wire Line
	16000 2700 16800 2700
Wire Wire Line
	14500 2400 14500 2500
Wire Wire Line
	14500 2500 14400 2500
Wire Wire Line
	14500 2700 14500 2600
Wire Wire Line
	14500 2600 14400 2600
Wire Wire Line
	17600 2400 19700 2400
Wire Wire Line
	19700 2400 21250 2400
Wire Wire Line
	17600 2700 20000 2700
Wire Wire Line
	20000 2700 21250 2700
Wire Wire Line
	21250 2400 21250 2500
Wire Wire Line
	21250 2700 21250 2600
Wire Wire Line
	15200 3400 15300 3400
Wire Wire Line
	15200 3600 15300 3600
Wire Wire Line
	15600 3400 15700 3400
Wire Wire Line
	15700 3400 15700 3200
Wire Wire Line
	15600 3600 16000 3600
Wire Wire Line
	16000 3600 16000 3200
Wire Wire Line
	15700 2900 15700 2400
Connection ~ 15700 2400
Wire Wire Line
	16000 2900 16000 2700
Connection ~ 16000 2700
Wire Wire Line
	20000 5100 20000 2700
Wire Wire Line
	21200 4600 21100 4600
Wire Wire Line
	21100 4600 21100 4400
Wire Wire Line
	19000 4400 19100 4400
Wire Wire Line
	19100 4400 19700 4400
Wire Wire Line
	19700 4400 20200 4400
Wire Wire Line
	19400 3600 19700 3600
Wire Wire Line
	19700 3600 19700 4400
Connection ~ 19700 4400
Wire Wire Line
	19400 3400 19700 3400
Wire Wire Line
	19700 3400 19700 2400
Connection ~ 19700 2400
Connection ~ 20000 2700
Wire Wire Line
	21200 4800 21100 4800
Wire Wire Line
	21100 4800 21100 5100
Connection ~ 20000 5100
Wire Wire Line
	21800 4700 22000 4700
Wire Wire Line
	22000 4700 22600 4700
Wire Wire Line
	22000 4700 22000 4900
Connection ~ 22000 4700
Wire Wire Line
	22000 5400 22000 5200
Wire Wire Line
	18600 3500 18600 3550
Wire Wire Line
	18000 3500 18600 3500
Wire Wire Line
	18600 3500 18800 3500
Wire Wire Line
	18600 3900 18600 3850
Wire Wire Line
	13700 3500 14400 3500
Wire Wire Line
	14400 3500 14600 3500
Wire Wire Line
	14400 3500 14400 3700
Wire Wire Line
	14400 4000 14400 4200
Wire Wire Line
	4600 2200 4600 2000
Connection ~ 4600 2000
Wire Wire Line
	4900 2200 4900 2000
Connection ~ 4900 2000
Wire Wire Line
	4600 2500 4600 2600
Wire Wire Line
	4900 2500 4900 2600
Wire Wire Line
	3750 7100 3850 7100
Wire Wire Line
	3850 7100 3950 7100
Wire Wire Line
	3850 7300 3850 7100
Connection ~ 3850 7100
Wire Wire Line
	3750 6900 3850 6900
Wire Wire Line
	3850 6900 3950 6900
Wire Wire Line
	4950 7000 5000 7000
Wire Wire Line
	5000 7000 5100 7000
Wire Wire Line
	5400 7000 5550 7000
Wire Wire Line
	4150 6300 3850 6300
Wire Wire Line
	3850 6000 3850 6300
Wire Wire Line
	3850 6300 3850 6900
Connection ~ 3850 6900
Wire Wire Line
	4450 6300 5000 6300
Wire Wire Line
	5000 6000 5000 6300
Wire Wire Line
	5000 6300 5000 7000
Connection ~ 5000 7000
Wire Wire Line
	4600 6000 5000 6000
Connection ~ 5000 6300
Wire Wire Line
	4300 6000 3850 6000
Connection ~ 3850 6300
Wire Wire Line
	3450 6900 2750 6900
Wire Wire Line
	3450 7100 2750 7100
Wire Wire Line
	3750 9800 3850 9800
Wire Wire Line
	3850 9800 3950 9800
Wire Wire Line
	3850 9900 3850 9800
Connection ~ 3850 9800
Wire Wire Line
	3750 9600 3850 9600
Wire Wire Line
	3850 9600 3950 9600
Wire Wire Line
	4950 9700 5000 9700
Wire Wire Line
	5000 9700 5100 9700
Wire Wire Line
	5400 9700 5550 9700
Wire Wire Line
	4150 9000 3850 9000
Wire Wire Line
	3850 8800 3850 9000
Wire Wire Line
	3850 9000 3850 9600
Connection ~ 3850 9600
Wire Wire Line
	4450 9000 5000 9000
Wire Wire Line
	5000 8800 5000 9000
Wire Wire Line
	5000 9000 5000 9700
Connection ~ 5000 9700
Wire Wire Line
	4450 8800 5000 8800
Connection ~ 5000 9000
Wire Wire Line
	4150 8800 3850 8800
Connection ~ 3850 9000
Wire Wire Line
	3450 9600 2750 9600
Wire Wire Line
	3450 9800 2750 9800
Wire Wire Line
	3750 12300 3850 12300
Wire Wire Line
	3850 12300 3950 12300
Wire Wire Line
	3850 12400 3850 12300
Connection ~ 3850 12300
Wire Wire Line
	3750 12100 3850 12100
Wire Wire Line
	3850 12100 3950 12100
Wire Wire Line
	4950 12200 5000 12200
Wire Wire Line
	5000 12200 5100 12200
Wire Wire Line
	5400 12200 5550 12200
Wire Wire Line
	4150 11500 3850 11500
Wire Wire Line
	3850 11300 3850 11500
Wire Wire Line
	3850 11500 3850 12100
Connection ~ 3850 12100
Wire Wire Line
	4450 11500 5000 11500
Wire Wire Line
	5000 11300 5000 11500
Wire Wire Line
	5000 11500 5000 12200
Connection ~ 5000 12200
Wire Wire Line
	4450 11300 5000 11300
Connection ~ 5000 11500
Wire Wire Line
	4150 11300 3850 11300
Connection ~ 3850 11500
Wire Wire Line
	3450 12100 2850 12100
Wire Wire Line
	3450 12300 2850 12300
Wire Wire Line
	3750 14800 3850 14800
Wire Wire Line
	3850 14800 3950 14800
Wire Wire Line
	3850 14900 3850 14800
Connection ~ 3850 14800
Wire Wire Line
	3750 14600 3850 14600
Wire Wire Line
	3850 14600 3950 14600
Wire Wire Line
	4950 14700 5000 14700
Wire Wire Line
	5000 14700 5100 14700
Wire Wire Line
	5400 14700 5550 14700
Wire Wire Line
	4150 14000 3850 14000
Wire Wire Line
	3850 13800 3850 14000
Wire Wire Line
	3850 14000 3850 14600
Connection ~ 3850 14600
Wire Wire Line
	4450 14000 5000 14000
Wire Wire Line
	5000 13800 5000 14000
Wire Wire Line
	5000 14000 5000 14700
Connection ~ 5000 14700
Wire Wire Line
	4450 13800 5000 13800
Connection ~ 5000 14000
Wire Wire Line
	4150 13800 3850 13800
Connection ~ 3850 14000
Wire Wire Line
	3450 14600 2800 14600
Wire Wire Line
	3450 14800 2800 14800
Connection ~ 18600 3500
Connection ~ 14400 3500
Wire Wire Line
	10300 2000 10300 2100
Wire Wire Line
	10500 2100 10500 2000
Wire Wire Line
	10500 2000 11500 2000
Wire Wire Line
	10400 2700 10400 2800
Wire Wire Line
	10400 2800 10400 3000
Wire Wire Line
	10400 3300 10400 3400
Wire Wire Line
	10400 2800 11100 2800
Connection ~ 10400 2800
Wire Wire Line
	10000 7500 10000 7800
Wire Wire Line
	10000 7800 10000 8000
Wire Wire Line
	10000 8300 10000 8500
Wire Wire Line
	10000 7800 9300 7800
Connection ~ 10000 7800
Wire Wire Line
	9100 11800 8500 11800
Wire Wire Line
	9100 11900 8500 11900
Wire Wire Line
	9100 12000 8500 12000
Wire Wire Line
	9100 12100 8500 12100
Wire Wire Line
	9100 12200 8500 12200
Wire Wire Line
	10500 11000 11550 11000
Wire Wire Line
	11850 11000 12050 11000
Wire Wire Line
	12050 11000 12500 11000
Wire Wire Line
	12050 11000 12050 11100
Wire Wire Line
	12050 11400 12050 11500
Wire Wire Line
	10500 12100 10700 12100
Wire Wire Line
	10500 11400 10700 11400
Wire Wire Line
	10500 11700 10700 11700
Wire Wire Line
	10500 10900 10700 10900
Wire Wire Line
	8900 12300 8900 13000
Wire Wire Line
	8900 12300 9100 12300
Connection ~ 12050 11000
Wire Wire Line
	10500 11200 10700 11200
Wire Wire Line
	10500 11300 10700 11300
Wire Wire Line
	7000 2400 7000 2450
Wire Wire Line
	7000 2100 7000 2000
Wire Wire Line
	11000 12100 11100 12100
Wire Wire Line
	11100 12100 11100 12300
Wire Wire Line
	11100 12300 11200 12300
Wire Wire Line
	11500 12500 11500 12550
Wire Wire Line
	11500 11900 11500 12100
Wire Wire Line
	8900 13000 12500 13000
Wire Wire Line
	12500 13000 12500 11000
Wire Wire Line
	12400 11900 11500 11900
Wire Wire Line
	16700 4150 15750 4150
Connection ~ 16700 3400
Connection ~ 17700 3050
Wire Wire Line
	20500 5100 20650 5100
Wire Wire Line
	21100 5100 20950 5100
Wire Wire Line
	21100 4400 20950 4400
Wire Wire Line
	20650 4400 20500 4400
Wire Wire Line
	2500 3400 2000 3400
Wire Wire Line
	2500 3600 2000 3600
Wire Wire Line
	2500 4000 1700 4000
Wire Wire Line
	1700 3800 1700 4000
Wire Wire Line
	1700 4000 1700 4300
Wire Wire Line
	2500 3800 2200 3800
Wire Wire Line
	1700 3800 1900 3800
Connection ~ 1700 4000
Wire Wire Line
	9100 11300 8500 11300
Wire Wire Line
	4350 6600 4350 6500
Wire Wire Line
	4350 6500 6050 6500
Wire Wire Line
	6050 6500 6350 6500
Wire Wire Line
	6050 6600 6050 6500
Connection ~ 6050 6500
Wire Wire Line
	6050 6900 6050 6950
Wire Wire Line
	3850 7600 3850 7700
Wire Wire Line
	3850 8000 3850 8150
Wire Wire Line
	3850 10200 3850 10250
Wire Wire Line
	3850 10550 3850 10600
Wire Wire Line
	3850 12700 3850 12750
Wire Wire Line
	3850 13050 3850 13100
Wire Wire Line
	3850 15200 3850 15250
Wire Wire Line
	3850 15550 3850 15600
Wire Wire Line
	2100 4400 1900 4400
Wire Wire Line
	2400 4400 2450 4400
Wire Wire Line
	2450 4400 2500 4400
Wire Wire Line
	2450 4400 2450 4650
Wire Wire Line
	2450 4650 1900 4650
Connection ~ 2450 4400
Wire Wire Line
	2500 4200 2000 4200
Wire Wire Line
	10000 15000 10000 15150
Wire Wire Line
	10000 14250 10000 14500
Wire Wire Line
	10000 14500 10000 14700
Wire Wire Line
	10000 13950 10000 13800
Wire Wire Line
	10000 13800 10300 13800
Wire Wire Line
	10000 14500 10400 14500
Connection ~ 10000 14500
Wire Wire Line
	10000 7000 10000 7200
Wire Wire Line
	10500 11600 10600 11600
Wire Wire Line
	10600 11600 10600 11500
Wire Wire Line
	10600 11500 10700 11500
Wire Wire Line
	11000 11500 11200 11500
Wire Wire Line
	19200 3000 19100 3000
Wire Wire Line
	19100 3000 19100 3200
Wire Wire Line
	19100 3800 19100 4000
Wire Wire Line
	19100 4000 19200 4000
Wire Wire Line
	21500 4400 21500 4200
Wire Wire Line
	21500 4200 21700 4200
Wire Wire Line
	21500 5000 21500 5200
Wire Wire Line
	21500 5200 21600 5200
Wire Wire Line
	14900 3200 14900 3000
Wire Wire Line
	14900 3000 15100 3000
Wire Wire Line
	14900 3800 14900 4100
Wire Wire Line
	14900 4100 15100 4100
Wire Wire Line
	9800 2400 10100 2400
Wire Wire Line
	10700 2400 10900 2400
Wire Wire Line
	17000 10000 17500 10000
Wire Wire Line
	17500 10000 18000 10000
Wire Wire Line
	18000 10000 18500 10000
Wire Wire Line
	18500 10000 20200 10000
Wire Wire Line
	17000 11400 17500 11400
Wire Wire Line
	17500 11400 18000 11400
Wire Wire Line
	18000 11400 18500 11400
Wire Wire Line
	18500 11400 20200 11400
Wire Wire Line
	17000 10200 17000 10000
Wire Wire Line
	17000 11400 17000 11200
Wire Wire Line
	17500 10200 17500 10000
Connection ~ 17500 10000
Wire Wire Line
	17500 11200 17500 11400
Connection ~ 17500 11400
Wire Wire Line
	18000 10200 18000 10000
Connection ~ 18000 10000
Wire Wire Line
	18500 10200 18500 10000
Connection ~ 18500 10000
Wire Wire Line
	18500 11200 18500 11400
Connection ~ 18500 11400
Wire Wire Line
	18000 11200 18000 11400
Connection ~ 18000 11400
Wire Wire Line
	17000 10500 17000 10700
Wire Wire Line
	17000 10700 17000 10900
Wire Wire Line
	17500 10500 17500 10700
Wire Wire Line
	17500 10700 17500 10900
Wire Wire Line
	18000 10500 18000 10700
Wire Wire Line
	18000 10700 18000 10900
Wire Wire Line
	18500 10500 18500 10700
Wire Wire Line
	18500 10700 18500 10900
Wire Wire Line
	17000 10700 17500 10700
Wire Wire Line
	17500 10700 18000 10700
Wire Wire Line
	18000 10700 18500 10700
Wire Wire Line
	18500 10700 18900 10700
Connection ~ 17500 10700
Connection ~ 17000 10700
Connection ~ 18000 10700
Connection ~ 18500 10700
Wire Wire Line
	18900 10700 18900 10800
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR013
U 1 1 56D751EB
P 18900 10800
F 0 "#PWR013" H 18900 10550 50  0001 C CNN
F 1 "GND" H 18900 10650 50  0000 C CNN
F 2 "" H 18900 10800 50  0000 C CNN
F 3 "" H 18900 10800 50  0000 C CNN
	1    18900 10800
	1    0    0    -1  
$EndComp
Text Notes 15650 10750 0    60   ~ 0
power decoupling caps\nfor LEM transducers
Wire Wire Line
	9100 11600 8500 11600
Text Label 8500 11600 0    60   ~ 0
P12V0
Text Notes 8800 11300 0    60   ~ 0
(out)
Text Notes 8800 11600 0    60   ~ 0
(in)
Wire Wire Line
	9100 11400 8000 11400
Wire Wire Line
	8000 11400 8000 11500
Wire Wire Line
	8000 11500 8000 11700
Wire Wire Line
	9100 11500 8000 11500
Connection ~ 8000 11500
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR019
U 1 1 56D751EC
P 8000 11700
F 0 "#PWR019" H 8000 11450 50  0001 C CNN
F 1 "GND" H 8000 11550 50  0000 C CNN
F 2 "" H 8000 11700 50  0000 C CNN
F 3 "" H 8000 11700 50  0000 C CNN
	1    8000 11700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 6700 10000 6500
Wire Wire Line
	10000 6500 10250 6500
Text Label 10250 6500 0    60   ~ 0
VBATT+
Text Notes 18300 4600 0    60   ~ 0
48.2mH / 1.8E
Text Notes 7750 2600 0    60   ~ 0
use 80V low \nRDS-on MOSFET\n
Text Notes 19450 3550 0    60   ~ 0
20 wdg.
Text Notes 4650 7500 0    60   ~ 0
Use rail-to-rail in- and output type OPAMP.
Text Notes 16350 5750 0    60   ~ 0
Transformer used with the development model: 240V / 18V - 200VA\nTransformer ratio and power rating may vary depending on the application.\n
Text Notes 16150 1700 0    100  ~ 0
Check the Inverter output phase and amplitude\nbefore closing the Islanding Relay!
Text Notes 20500 15200 0    50   ~ 0
MIT License\nCopyright (c) 2019 Martin Stokroos
$Comp
L openMicroInverter_dev-rescue:Q_POWERMOSFET_GDS-SmartInverter_proto-rescue Q3
U 1 1 56D7517C
P 5900 4100
F 0 "Q3" H 6200 3950 50  0000 R CNN
F 1 "N-CHANNEL" H 5950 4300 50  0001 R CNN
F 2 "" H 6100 4200 50  0000 C CNN
F 3 "" H 5900 4100 50  0000 C CNN
	1    5900 4100
	1    0    0    -1  
$EndComp
Text Notes 16350 5900 0    50   ~ 0
L1 used, is a power factor correction coil from ATX power supply.
Text Notes 17650 11800 0    50   ~ 0
NOTE: Circuit power supplies are not drawn.
Text Notes 15350 7000 0    200  ~ 0
WARNING: High voltages present !\nUse an isolation transformer !
$Comp
L Graphic:Logo_Open_Hardware_Small LOGO1
U 1 1 5EE1BCF2
P 22600 15100
F 0 "LOGO1" H 22600 15375 50  0001 C CNN
F 1 "Logo_Open_Hardware_Small" H 22600 14875 50  0001 C CNN
F 2 "" H 22600 15100 50  0001 C CNN
F 3 "~" H 22600 15100 50  0001 C CNN
	1    22600 15100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 3200 2500 3200
Text Label 2000 3200 0    50   ~ 0
H_BHI
Text Label 2000 4200 0    50   ~ 0
H_AHI
Wire Wire Line
	10500 12000 10700 12000
Text Label 10700 12000 0    50   ~ 0
H_AHI
Wire Wire Line
	10500 11100 10700 11100
Text Label 10700 11100 0    50   ~ 0
H_BHI
Connection ~ 7500 2000
Wire Wire Line
	7500 2000 10300 2000
Connection ~ 7500 4600
Wire Wire Line
	7500 4600 11500 4600
Connection ~ 7000 2000
Wire Wire Line
	7000 2000 7500 2000
Connection ~ 6500 2000
Wire Wire Line
	6500 2000 7000 2000
Wire Wire Line
	6000 2000 6500 2000
Connection ~ 6750 4600
Wire Wire Line
	6750 4600 7500 4600
Wire Wire Line
	6000 4600 6750 4600
$Comp
L openMicroInverter_dev-rescue:C-SmartInverter_proto-rescue C6
U 1 1 5EF760C1
P 9500 14850
F 0 "C6" H 9525 14950 50  0000 L CNN
F 1 "100n" H 9525 14750 50  0000 L CNN
F 2 "" H 9538 14700 50  0000 C CNN
F 3 "" H 9500 14850 50  0000 C CNN
	1    9500 14850
	1    0    0    -1  
$EndComp
$Comp
L openMicroInverter_dev-rescue:GND-SmartInverter_proto-rescue #PWR0101
U 1 1 5EF77AEF
P 9500 15150
F 0 "#PWR0101" H 9500 14900 50  0001 C CNN
F 1 "GND" H 9500 15000 50  0000 C CNN
F 2 "" H 9500 15150 50  0000 C CNN
F 3 "" H 9500 15150 50  0000 C CNN
	1    9500 15150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 15000 9500 15150
Wire Wire Line
	9500 14700 9500 14500
Wire Wire Line
	9500 14500 10000 14500
NoConn ~ 9100 11000
NoConn ~ 9100 11100
NoConn ~ 9100 11200
NoConn ~ 10500 10500
NoConn ~ 10500 10600
NoConn ~ 10500 10700
NoConn ~ 10500 11800
NoConn ~ 10500 11900
NoConn ~ 10500 12200
NoConn ~ 10500 12300
Wire Wire Line
	10500 10800 10700 10800
Text Label 10700 10800 0    50   ~ 0
GND
$EndSCHEMATC
