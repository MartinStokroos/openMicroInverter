/*
 *
 * File: PowerSys.h
 * Purpose:
 * Version: 1.1.1
 * Initial release date: 17-10-2019
 * Date: 01-12-2020
 * URL: https://github.com/MartinStokroos/PowerSys
 * License: MIT License
 *
 *
 * Copyright (c) M.Stokroos 2019
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
*/

#ifndef PowerSys_H_
#define PowerSys_H_

#include "Arduino.h"
#include "avr/pgmspace.h"

#define PHASE_OFFS_90 1073741824UL
#define PHASE_OFFS_120 1431655765UL
#define PHASE_OFFS_240 2863311531UL
#define PHASE_OFFS_270 3221225472UL

// 2pi sin LUT
const int fullwave_lut1024[] PROGMEM = {
		  511, 514, 517, 520, 524, 527, 530, 533,
		  536, 539, 542, 545, 549, 552, 555, 558,
		  561, 564, 567, 570, 574, 577, 580, 583,
		  586, 589, 592, 595, 598, 601, 605, 608,
		  611, 614, 617, 620, 623, 626, 629, 632,
		  635, 638, 641, 644, 647, 650, 653, 656,
		  659, 662, 665, 668, 671, 674, 677, 680,
		  683, 686, 689, 692, 695, 698, 701, 704,
		  707, 709, 712, 715, 718, 721, 724, 727,
		  729, 732, 735, 738, 741, 744, 746, 749,
		  752, 755, 757, 760, 763, 766, 768, 771,
		  774, 776, 779, 782, 784, 787, 790, 792,
		  795, 797, 800, 803, 805, 808, 810, 813,
		  815, 818, 820, 823, 825, 828, 830, 833,
		  835, 838, 840, 842, 845, 847, 849, 852,
		  854, 856, 859, 861, 863, 866, 868, 870,
		  872, 875, 877, 879, 881, 883, 885, 888,
		  890, 892, 894, 896, 898, 900, 902, 904,
		  906, 908, 910, 912, 914, 916, 918, 920,
		  921, 923, 925, 927, 929, 931, 932, 934,
		  936, 938, 939, 941, 943, 944, 946, 948,
		  949, 951, 952, 954, 956, 957, 959, 960,
		  962, 963, 965, 966, 967, 969, 970, 972,
		  973, 974, 976, 977, 978, 979, 981, 982,
		  983, 984, 985, 987, 988, 989, 990, 991,
		  992, 993, 994, 995, 996, 997, 998, 999,
		  1000, 1001, 1002, 1003, 1003, 1004, 1005, 1006,
		  1007, 1007, 1008, 1009, 1010, 1010, 1011, 1012,
		  1012, 1013, 1013, 1014, 1014, 1015, 1016, 1016,
		  1016, 1017, 1017, 1018, 1018, 1019, 1019, 1019,
		  1020, 1020, 1020, 1020, 1021, 1021, 1021, 1021,
		  1021, 1022, 1022, 1022, 1022, 1022, 1022, 1022,
		  1022, 1022, 1022, 1022, 1022, 1022, 1022, 1022,
		  1021, 1021, 1021, 1021, 1021, 1020, 1020, 1020,
		  1020, 1019, 1019, 1019, 1018, 1018, 1017, 1017,
		  1016, 1016, 1016, 1015, 1014, 1014, 1013, 1013,
		  1012, 1012, 1011, 1010, 1010, 1009, 1008, 1007,
		  1007, 1006, 1005, 1004, 1003, 1003, 1002, 1001,
		  1000, 999, 998, 997, 996, 995, 994, 993,
		  992, 991, 990, 989, 988, 987, 985, 984,
		  983, 982, 981, 979, 978, 977, 976, 974,
		  973, 972, 970, 969, 967, 966, 965, 963,
		  962, 960, 959, 957, 956, 954, 952, 951,
		  949, 948, 946, 944, 943, 941, 939, 938,
		  936, 934, 932, 931, 929, 927, 925, 923,
		  921, 920, 918, 916, 914, 912, 910, 908,
		  906, 904, 902, 900, 898, 896, 894, 892,
		  890, 888, 885, 883, 881, 879, 877, 875,
		  872, 870, 868, 866, 863, 861, 859, 856,
		  854, 852, 849, 847, 845, 842, 840, 838,
		  835, 833, 830, 828, 825, 823, 820, 818,
		  815, 813, 810, 808, 805, 803, 800, 797,
		  795, 792, 790, 787, 784, 782, 779, 776,
		  774, 771, 768, 766, 763, 760, 757, 755,
		  752, 749, 746, 744, 741, 738, 735, 732,
		  729, 727, 724, 721, 718, 715, 712, 709,
		  707, 704, 701, 698, 695, 692, 689, 686,
		  683, 680, 677, 674, 671, 668, 665, 662,
		  659, 656, 653, 650, 647, 644, 641, 638,
		  635, 632, 629, 626, 623, 620, 617, 614,
		  611, 608, 605, 601, 598, 595, 592, 589,
		  586, 583, 580, 577, 574, 570, 567, 564,
		  561, 558, 555, 552, 549, 545, 542, 539,
		  536, 533, 530, 527, 524, 520, 517, 514,
		  511, 508, 505, 502, 498, 495, 492, 489,
		  486, 483, 480, 477, 473, 470, 467, 464,
		  461, 458, 455, 452, 448, 445, 442, 439,
		  436, 433, 430, 427, 424, 421, 417, 414,
		  411, 408, 405, 402, 399, 396, 393, 390,
		  387, 384, 381, 378, 375, 372, 369, 366,
		  363, 360, 357, 354, 351, 348, 345, 342,
		  339, 336, 333, 330, 327, 324, 321, 318,
		  315, 313, 310, 307, 304, 301, 298, 295,
		  293, 290, 287, 284, 281, 278, 276, 273,
		  270, 267, 265, 262, 259, 256, 254, 251,
		  248, 246, 243, 240, 238, 235, 232, 230,
		  227, 225, 222, 219, 217, 214, 212, 209,
		  207, 204, 202, 199, 197, 194, 192, 189,
		  187, 184, 182, 180, 177, 175, 173, 170,
		  168, 166, 163, 161, 159, 156, 154, 152,
		  150, 147, 145, 143, 141, 139, 137, 134,
		  132, 130, 128, 126, 124, 122, 120, 118,
		  116, 114, 112, 110, 108, 106, 104, 102,
		  101, 99, 97, 95, 93, 91, 90, 88,
		  86, 84, 83, 81, 79, 78, 76, 74,
		  73, 71, 70, 68, 66, 65, 63, 62,
		  60, 59, 57, 56, 55, 53, 52, 50,
		  49, 48, 46, 45, 44, 43, 41, 40,
		  39, 38, 37, 35, 34, 33, 32, 31,
		  30, 29, 28, 27, 26, 25, 24, 23,
		  22, 21, 20, 19, 19, 18, 17, 16,
		  15, 15, 14, 13, 12, 12, 11, 10,
		  10, 9, 9, 8, 8, 7, 6, 6,
		  6, 5, 5, 4, 4, 3, 3, 3,
		  2, 2, 2, 2, 1, 1, 1, 1,
		  1, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0,
		  1, 1, 1, 1, 1, 2, 2, 2,
		  2, 3, 3, 3, 4, 4, 5, 5,
		  6, 6, 6, 7, 8, 8, 9, 9,
		  10, 10, 11, 12, 12, 13, 14, 15,
		  15, 16, 17, 18, 19, 19, 20, 21,
		  22, 23, 24, 25, 26, 27, 28, 29,
		  30, 31, 32, 33, 34, 35, 37, 38,
		  39, 40, 41, 43, 44, 45, 46, 48,
		  49, 50, 52, 53, 55, 56, 57, 59,
		  60, 62, 63, 65, 66, 68, 70, 71,
		  73, 74, 76, 78, 79, 81, 83, 84,
		  86, 88, 90, 91, 93, 95, 97, 99,
		  101, 102, 104, 106, 108, 110, 112, 114,
		  116, 118, 120, 122, 124, 126, 128, 130,
		  132, 134, 137, 139, 141, 143, 145, 147,
		  150, 152, 154, 156, 159, 161, 163, 166,
		  168, 170, 173, 175, 177, 180, 182, 184,
		  187, 189, 192, 194, 197, 199, 202, 204,
		  207, 209, 212, 214, 217, 219, 222, 225,
		  227, 230, 232, 235, 238, 240, 243, 246,
		  248, 251, 254, 256, 259, 262, 265, 267,
		  270, 273, 276, 278, 281, 284, 287, 290,
		  293, 295, 298, 301, 304, 307, 310, 313,
		  315, 318, 321, 324, 327, 330, 333, 336,
		  339, 342, 345, 348, 351, 354, 357, 360,
		  363, 366, 369, 372, 375, 378, 381, 384,
		  387, 390, 393, 396, 399, 402, 405, 408,
		  411, 414, 417, 421, 424, 427, 430, 433,
		  436, 439, 442, 445, 448, 452, 455, 458,
		  461, 464, 467, 470, 473, 477, 480, 483,
		  486, 489, 492, 495, 498, 502, 505, 508
};



// pi sin LUT
const int halfwave_lut1024[] PROGMEM = {
		0, 2, 3, 5, 6, 8, 9, 11,
		13, 14, 16, 17, 19, 20, 22, 24,
		25, 27, 28, 30, 31, 33, 34, 36,
		38, 39, 41, 42, 44, 45, 47, 49,
		50, 52, 53, 55, 56, 58, 59, 61,
		63, 64, 66, 67, 69, 70, 72, 73,
		75, 77, 78, 80, 81, 83, 84, 86,
		87, 89, 90, 92, 94, 95, 97, 98,
		100, 101, 103, 104, 106, 107, 109, 110,
		112, 113, 115, 117, 118, 120, 121, 123,
		124, 126, 127, 129, 130, 132, 133, 135,
		136, 138, 139, 141, 142, 144, 145, 147,
		148, 150, 151, 153, 154, 156, 157, 159,
		160, 162, 163, 165, 166, 168, 169, 171,
		172, 174, 175, 177, 178, 180, 181, 182,
		184, 185, 187, 188, 190, 191, 193, 194,
		196, 197, 198, 200, 201, 203, 204, 206,
		207, 209, 210, 211, 213, 214, 216, 217,
		218, 220, 221, 223, 224, 226, 227, 228,
		230, 231, 233, 234, 235, 237, 238, 239,
		241, 242, 244, 245, 246, 248, 249, 251,
		252, 253, 255, 256, 257, 259, 260, 261,
		263, 264, 265, 267, 268, 269, 271, 272,
		273, 275, 276, 277, 279, 280, 281, 283,
		284, 285, 286, 288, 289, 290, 292, 293,
		294, 296, 297, 298, 299, 301, 302, 303,
		304, 306, 307, 308, 309, 311, 312, 313,
		314, 316, 317, 318, 319, 321, 322, 323,
		324, 325, 327, 328, 329, 330, 331, 333,
		334, 335, 336, 337, 338, 340, 341, 342,
		343, 344, 345, 347, 348, 349, 350, 351,
		352, 353, 355, 356, 357, 358, 359, 360,
		361, 362, 364, 365, 366, 367, 368, 369,
		370, 371, 372, 373, 374, 375, 377, 378,
		379, 380, 381, 382, 383, 384, 385, 386,
		387, 388, 389, 390, 391, 392, 393, 394,
		395, 396, 397, 398, 399, 400, 401, 402,
		403, 404, 405, 406, 407, 408, 409, 410,
		410, 411, 412, 413, 414, 415, 416, 417,
		418, 419, 420, 420, 421, 422, 423, 424,
		425, 426, 427, 427, 428, 429, 430, 431,
		432, 433, 433, 434, 435, 436, 437, 437,
		438, 439, 440, 441, 441, 442, 443, 444,
		445, 445, 446, 447, 448, 448, 449, 450,
		451, 451, 452, 453, 454, 454, 455, 456,
		456, 457, 458, 459, 459, 460, 461, 461,
		462, 463, 463, 464, 465, 465, 466, 467,
		467, 468, 468, 469, 470, 470, 471, 472,
		472, 473, 473, 474, 474, 475, 476, 476,
		477, 477, 478, 478, 479, 480, 480, 481,
		481, 482, 482, 483, 483, 484, 484, 485,
		485, 486, 486, 487, 487, 488, 488, 489,
		489, 489, 490, 490, 491, 491, 492, 492,
		492, 493, 493, 494, 494, 495, 495, 495,
		496, 496, 496, 497, 497, 498, 498, 498,
		499, 499, 499, 500, 500, 500, 501, 501,
		501, 501, 502, 502, 502, 503, 503, 503,
		503, 504, 504, 504, 505, 505, 505, 505,
		505, 506, 506, 506, 506, 507, 507, 507,
		507, 507, 508, 508, 508, 508, 508, 508,
		509, 509, 509, 509, 509, 509, 509, 509,
		510, 510, 510, 510, 510, 510, 510, 510,
		510, 510, 511, 511, 511, 511, 511, 511,
		511, 511, 511, 511, 511, 511, 511, 511,
		511, 511, 511, 511, 511, 511, 511, 511,
		511, 511, 511, 511, 511, 511, 511, 510,
		510, 510, 510, 510, 510, 510, 510, 510,
		510, 509, 509, 509, 509, 509, 509, 509,
		509, 508, 508, 508, 508, 508, 508, 507,
		507, 507, 507, 507, 506, 506, 506, 506,
		505, 505, 505, 505, 505, 504, 504, 504,
		503, 503, 503, 503, 502, 502, 502, 501,
		501, 501, 501, 500, 500, 500, 499, 499,
		499, 498, 498, 498, 497, 497, 496, 496,
		496, 495, 495, 495, 494, 494, 493, 493,
		492, 492, 492, 491, 491, 490, 490, 489,
		489, 489, 488, 488, 487, 487, 486, 486,
		485, 485, 484, 484, 483, 483, 482, 482,
		481, 481, 480, 480, 479, 478, 478, 477,
		477, 476, 476, 475, 474, 474, 473, 473,
		472, 472, 471, 470, 470, 469, 468, 468,
		467, 467, 466, 465, 465, 464, 463, 463,
		462, 461, 461, 460, 459, 459, 458, 457,
		456, 456, 455, 454, 454, 453, 452, 451,
		451, 450, 449, 448, 448, 447, 446, 445,
		445, 444, 443, 442, 441, 441, 440, 439,
		438, 437, 437, 436, 435, 434, 433, 433,
		432, 431, 430, 429, 428, 427, 427, 426,
		425, 424, 423, 422, 421, 420, 420, 419,
		418, 417, 416, 415, 414, 413, 412, 411,
		410, 410, 409, 408, 407, 406, 405, 404,
		403, 402, 401, 400, 399, 398, 397, 396,
		395, 394, 393, 392, 391, 390, 389, 388,
		387, 386, 385, 384, 383, 382, 381, 380,
		379, 378, 377, 375, 374, 373, 372, 371,
		370, 369, 368, 367, 366, 365, 364, 362,
		361, 360, 359, 358, 357, 356, 355, 353,
		352, 351, 350, 349, 348, 347, 345, 344,
		343, 342, 341, 340, 338, 337, 336, 335,
		334, 333, 331, 330, 329, 328, 327, 325,
		324, 323, 322, 321, 319, 318, 317, 316,
		314, 313, 312, 311, 309, 308, 307, 306,
		304, 303, 302, 301, 299, 298, 297, 296,
		294, 293, 292, 290, 289, 288, 286, 285,
		284, 283, 281, 280, 279, 277, 276, 275,
		273, 272, 271, 269, 268, 267, 265, 264,
		263, 261, 260, 259, 257, 256, 255, 253,
		252, 251, 249, 248, 246, 245, 244, 242,
		241, 239, 238, 237, 235, 234, 233, 231,
		230, 228, 227, 226, 224, 223, 221, 220,
		218, 217, 216, 214, 213, 211, 210, 209,
		207, 206, 204, 203, 201, 200, 198, 197,
		196, 194, 193, 191, 190, 188, 187, 185,
		184, 182, 181, 180, 178, 177, 175, 174,
		172, 171, 169, 168, 166, 165, 163, 162,
		160, 159, 157, 156, 154, 153, 151, 150,
		148, 147, 145, 144, 142, 141, 139, 138,
		136, 135, 133, 132, 130, 129, 127, 126,
		124, 123, 121, 120, 118, 117, 115, 113,
		112, 110, 109, 107, 106, 104, 103, 101,
		100, 98, 97, 95, 94, 92, 90, 89,
		87, 86, 84, 83, 81, 80, 78, 77,
		75, 73, 72, 70, 69, 67, 66, 64,
		63, 61, 59, 58, 56, 55, 53, 52,
		50, 49, 47, 45, 44, 42, 41, 39,
		38, 36, 34, 33, 31, 30, 28, 27,
		25, 24, 22, 20, 19, 17, 16, 14,
		13, 11, 9, 8, 6, 5, 3, 2
};


// pi/2 sin LUT
const int quarterwave_lut1024[] PROGMEM = {
		2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
		2048, 2048, 2048, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047,
		2047, 2046, 2046, 2046, 2046, 2046, 2046, 2046, 2046, 2045, 2045, 2045,
		2045, 2045, 2045, 2044, 2044, 2044, 2044, 2044, 2043, 2043, 2043, 2043,
		2042, 2042, 2042, 2042, 2041, 2041, 2041, 2041, 2040, 2040, 2040, 2040,
		2039, 2039, 2039, 2038, 2038, 2038, 2038, 2037, 2037, 2037, 2036, 2036,
		2036, 2035, 2035, 2034, 2034, 2034, 2033, 2033, 2033, 2032, 2032, 2031,
		2031, 2031, 2030, 2030, 2029, 2029, 2029, 2028, 2028, 2027, 2027, 2026,
		2026, 2025, 2025, 2024, 2024, 2023, 2023, 2022, 2022, 2021, 2021, 2020,
		2020, 2019, 2019, 2018, 2018, 2017, 2017, 2016, 2016, 2015, 2015, 2014,
		2013, 2013, 2012, 2012, 2011, 2010, 2010, 2009, 2009, 2008, 2007, 2007,
		2006, 2006, 2005, 2004, 2004, 2003, 2002, 2002, 2001, 2000, 2000, 1999,
		1998, 1998, 1997, 1996, 1995, 1995, 1994, 1993, 1993, 1992, 1991, 1990,
		1990, 1989, 1988, 1987, 1987, 1986, 1985, 1984, 1984, 1983, 1982, 1981,
		1980, 1980, 1979, 1978, 1977, 1976, 1975, 1975, 1974, 1973, 1972, 1971,
		1970, 1970, 1969, 1968, 1967, 1966, 1965, 1964, 1963, 1963, 1962, 1961,
		1960, 1959, 1958, 1957, 1956, 1955, 1954, 1953, 1952, 1951, 1950, 1950,
		1949, 1948, 1947, 1946, 1945, 1944, 1943, 1942, 1941, 1940, 1939, 1938,
		1937, 1936, 1935, 1934, 1932, 1931, 1930, 1929, 1928, 1927, 1926, 1925,
		1924, 1923, 1922, 1921, 1920, 1919, 1917, 1916, 1915, 1914, 1913, 1912,
		1911, 1910, 1908, 1907, 1906, 1905, 1904, 1903, 1902, 1900, 1899, 1898,
		1897, 1896, 1895, 1893, 1892, 1891, 1890, 1888, 1887, 1886, 1885, 1884,
		1882, 1881, 1880, 1879, 1877, 1876, 1875, 1874, 1872, 1871, 1870, 1868,
		1867, 1866, 1865, 1863, 1862, 1861, 1859, 1858, 1857, 1855, 1854, 1853,
		1851, 1850, 1849, 1847, 1846, 1845, 1843, 1842, 1840, 1839, 1838, 1836,
		1835, 1834, 1832, 1831, 1829, 1828, 1826, 1825, 1824, 1822, 1821, 1819,
		1818, 1816, 1815, 1814, 1812, 1811, 1809, 1808, 1806, 1805, 1803, 1802,
		1800, 1799, 1797, 1796, 1794, 1793, 1791, 1790, 1788, 1787, 1785, 1783,
		1782, 1780, 1779, 1777, 1776, 1774, 1773, 1771, 1769, 1768, 1766, 1765,
		1763, 1761, 1760, 1758, 1757, 1755, 1753, 1752, 1750, 1749, 1747, 1745,
		1744, 1742, 1740, 1739, 1737, 1735, 1734, 1732, 1730, 1729, 1727, 1725,
		1724, 1722, 1720, 1718, 1717, 1715, 1713, 1712, 1710, 1708, 1706, 1705,
		1703, 1701, 1699, 1698, 1696, 1694, 1692, 1691, 1689, 1687, 1685, 1683,
		1682, 1680, 1678, 1676, 1674, 1673, 1671, 1669, 1667, 1665, 1663, 1662,
		1660, 1658, 1656, 1654, 1652, 1651, 1649, 1647, 1645, 1643, 1641, 1639,
		1637, 1636, 1634, 1632, 1630, 1628, 1626, 1624, 1622, 1620, 1618, 1616,
		1615, 1613, 1611, 1609, 1607, 1605, 1603, 1601, 1599, 1597, 1595, 1593,
		1591, 1589, 1587, 1585, 1583, 1581, 1579, 1577, 1575, 1573, 1571, 1569,
		1567, 1565, 1563, 1561, 1559, 1557, 1555, 1553, 1551, 1549, 1547, 1545,
		1543, 1540, 1538, 1536, 1534, 1532, 1530, 1528, 1526, 1524, 1522, 1520,
		1517, 1515, 1513, 1511, 1509, 1507, 1505, 1503, 1500, 1498, 1496, 1494,
		1492, 1490, 1488, 1485, 1483, 1481, 1479, 1477, 1475, 1472, 1470, 1468,
		1466, 1464, 1461, 1459, 1457, 1455, 1453, 1450, 1448, 1446, 1444, 1441,
		1439, 1437, 1435, 1433, 1430, 1428, 1426, 1424, 1421, 1419, 1417, 1414,
		1412, 1410, 1408, 1405, 1403, 1401, 1398, 1396, 1394, 1392, 1389, 1387,
		1385, 1382, 1380, 1378, 1375, 1373, 1371, 1368, 1366, 1364, 1361, 1359,
		1357, 1354, 1352, 1350, 1347, 1345, 1342, 1340, 1338, 1335, 1333, 1331,
		1328, 1326, 1323, 1321, 1319, 1316, 1314, 1311, 1309, 1307, 1304, 1302,
		1299, 1297, 1294, 1292, 1289, 1287, 1285, 1282, 1280, 1277, 1275, 1272,
		1270, 1267, 1265, 1262, 1260, 1258, 1255, 1253, 1250, 1248, 1245, 1243,
		1240, 1238, 1235, 1233, 1230, 1228, 1225, 1223, 1220, 1217, 1215, 1212,
		1210, 1207, 1205, 1202, 1200, 1197, 1195, 1192, 1190, 1187, 1184, 1182,
		1179, 1177, 1174, 1172, 1169, 1166, 1164, 1161, 1159, 1156, 1153, 1151,
		1148, 1146, 1143, 1140, 1138, 1135, 1133, 1130, 1127, 1125, 1122, 1119,
		1117, 1114, 1112, 1109, 1106, 1104, 1101, 1098, 1096, 1093, 1090, 1088,
		1085, 1082, 1080, 1077, 1074, 1072, 1069, 1066, 1064, 1061, 1058, 1056,
		1053, 1050, 1047, 1045, 1042, 1039, 1037, 1034, 1031, 1029, 1026, 1023,
		1020, 1018, 1015, 1012, 1009, 1007, 1004, 1001, 999, 996, 993, 990,
		988, 985, 982, 979, 976, 974, 971, 968, 965, 963, 960, 957,
		954, 952, 949, 946, 943, 940, 938, 935, 932, 929, 926, 924,
		921, 918, 915, 912, 910, 907, 904, 901, 898, 895, 893, 890,
		887, 884, 881, 878, 876, 873, 870, 867, 864, 861, 859, 856,
		853, 850, 847, 844, 841, 839, 836, 833, 830, 827, 824, 821,
		818, 816, 813, 810, 807, 804, 801, 798, 795, 792, 790, 787,
		784, 781, 778, 775, 772, 769, 766, 763, 760, 758, 755, 752,
		749, 746, 743, 740, 737, 734, 731, 728, 725, 722, 719, 717,
		714, 711, 708, 705, 702, 699, 696, 693, 690, 687, 684, 681,
		678, 675, 672, 669, 666, 663, 660, 657, 654, 651, 648, 645,
		642, 639, 636, 633, 630, 627, 624, 622, 619, 616, 613, 610,
		607, 604, 601, 598, 595, 591, 588, 585, 582, 579, 576, 573,
		570, 567, 564, 561, 558, 555, 552, 549, 546, 543, 540, 537,
		534, 531, 528, 525, 522, 519, 516, 513, 510, 507, 504, 501,
		498, 495, 492, 488, 485, 482, 479, 476, 473, 470, 467, 464,
		461, 458, 455, 452, 449, 446, 443, 440, 436, 433, 430, 427,
		424, 421, 418, 415, 412, 409, 406, 403, 400, 396, 393, 390,
		387, 384, 381, 378, 375, 372, 369, 366, 363, 359, 356, 353,
		350, 347, 344, 341, 338, 335, 332, 328, 325, 322, 319, 316,
		313, 310, 307, 304, 301, 297, 294, 291, 288, 285, 282, 279,
		276, 273, 269, 266, 263, 260, 257, 254, 251, 248, 244, 241,
		238, 235, 232, 229, 226, 223, 219, 216, 213, 210, 207, 204,
		201, 198, 194, 191, 188, 185, 182, 179, 176, 173, 169, 166,
		163, 160, 157, 154, 151, 148, 144, 141, 138, 135, 132, 129,
		126, 122, 119, 116, 113, 110, 107, 104, 100, 97, 94, 91,
		88, 85, 82, 79, 75, 72, 69, 66, 63, 60, 57, 53,
		50, 47, 44, 41, 38, 35, 31, 28, 25, 22, 19, 16,
		13, 9, 6, 3
};




class PowerControl
{
public:
	void osgBegin(float _freq, float _deltat);
	void osgUpdate1(unsigned long _phaseInc);
	void osgMaSlUpdate1(unsigned long _phaseInc, unsigned long _phaseOffset);
	void osgMaSlUpdate2(unsigned long _phaseInc, unsigned long _phaseOffset);
	void osgMaSlUpdate3(unsigned long _phaseInc, unsigned long _phaseOffset);
	void osgMaSlUpdate4(unsigned long _phaseInc, unsigned long _phaseOffset);
	void osgMaSlUpdate5(unsigned long _phaseInc, unsigned long _phaseOffset);
	void park(long _alpha, long _beta);
	void ipark(long _d, long _q);

	volatile unsigned long tuningWord;
	int rsin;
	int rcos;
	int rfbk;
	long alpha;
	long beta;
	long d;
	long q;

private:
	volatile unsigned long phaseAccu1;
	volatile unsigned long phaseAccu2;
	volatile unsigned int phaseIdx1;
	volatile unsigned int phaseIdx2;
	volatile unsigned int phaseIdx3;
};

#endif /* PowerSys_H_ */



