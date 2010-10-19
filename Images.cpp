#include "StdAfx.h"
#include "Images.h"

CImages::CImages(void)
{
	src = new SDL_Rect();
	
	splashscreen = new CImg("splashscreen.png");
	black = new CImg("black.png");
	// start all images with NULL, needed to make smooth loading screen
	titlescreen = NULL;
	cake[0] = cake[1] = cake[2] = bird[0] = bird[1] = bird[2] = bird[3] = bird[4] = bird[5] = NULL;
	for (int i = 0; i < 20; i++) {
		particles[i] = NULL;
	}
	for (int i = 0; i < 8; i++) {
		levelselect[i] = NULL;
	}
	levelselectgrid= NULL;
	 background = levelselecttext =
	 gameboard = pausemenu = turnonsound = turnoffsound= 
	 ending = blocks = background2 = background3 = background4 = background5 = background6 = background7 = background8 =
	 levelselectgameboards =
	 fonts[0] = fonts[1] = fonts[2]= fonts[3] = fonts[4] = fonts[5] = 
	 smallblocks =
	 levelselectionbox =
	 particles[0] = particles[1] = particles[2] = particles[3] =
	 congratulations =
	 tutorialpage1 = tutorialpage2 = tutorialpage3 =
	 blackoverlay =
	 tutorial[0] = tutorial[1] = tutorial[2] = tutorial[3] = tutorial[4] =
	 blackoverlaygameboard =
	 turnoncolorblindmode = turnoffcolorblindmode =
	 colorblindblue = colorblindred = colorblindpurple = colorblindcyan = colorblindgreen = NULL;
	smallblocks = NULL;
	fonts[2] = new CImg("micro10silver.png");
	smallblocks = new CImg("smallblocks.png");
	titlescreen = new CImg("title.png");
	sprintf(characters,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~`!@#$ %^&*()-_=+[{]};:\'\",<.>/?°¢£•ß©Æø¿¡¬√ƒ≈∆«»… ÀÃÕŒœ–—“”‘’÷ÿŸ⁄€‹›ﬂ‡·‚„‰ÂÊÁËÈÍÎÏÌÓÔÒÚÛÙıˆ¯˘˙˚¸˝ˇ");
	for (int i = 0; i < 256;i ++) 
		characterMapping[i] = 0;
	for (int i = 0; i < 91; i++) {
		//if (characters[i] == '\'')
		//	printf("%d-%d-%c ", i, characters[i],characters[i]);
		characterMapping[characters[i]] = i;
	}

	//printf("%d ", characterMapping['\'']);
	int rectangles[160][4] = { {   0,  0, 28, 34}, {  29,  0, 23, 34}, {  53,  0, 22, 34}, {  76,  0, 24, 34},
   { 101,  0, 22, 34}, { 124,  0, 22, 34}, { 147,  0, 25, 34}, { 173,  0, 25, 34},
   { 199,  0, 15, 34}, { 215,  0, 20, 34}, { 236,  0, 25, 34}, { 262,  0, 21, 34},
   { 284,  0, 27, 34}, { 312,  0, 26, 34}, { 339,  0, 26, 34}, { 366,  0, 22, 34},
   { 389,  0, 28, 34}, { 418,  0, 23, 34}, { 442,  0, 20, 34}, { 463,  0, 25, 34},
   { 489,  0, 24, 34}, { 514,  0, 27, 34}, { 542,  0, 31, 34}, { 574,  0, 26, 34},
   { 601,  0, 26, 34}, { 628,  0, 23, 34}, { 652,  0, 22, 34}, { 675,  0, 22, 34},
   { 698,  0, 19, 34}, { 718,  0, 23, 34}, { 742,  0, 21, 34}, { 764,  0, 18, 34},
   { 783,  0, 22, 34}, { 806,  0, 22, 34}, { 829,  0, 16, 34}, { 846,  0, 20, 34},
   { 867,  0, 22, 34}, { 890,  0, 15, 34}, { 906,  0, 29, 34}, { 936,  0, 22, 34},
   { 959,  0, 22, 34}, { 982,  0, 22, 34}, {1005,  0, 22, 34}, {1028,  0, 18, 34},
   {1047,  0, 18, 34}, {1066,  0, 18, 34}, {1085,  0, 22, 34}, {1108,  0, 23, 34},
   {1132,  0, 30, 34}, {1163,  0, 23, 34}, {1187,  0, 23, 34}, {1211,  0, 19, 34},
   {1231,  0, 22, 34}, {1254,  0, 17, 34}, {1272,  0, 22, 34}, {1295,  0, 22, 34},
   {1318,  0, 23, 34}, {1342,  0, 21, 34}, {1364,  0, 22, 34}, {1387,  0, 22, 34},
   {1410,  0, 22, 34}, {1433,  0, 22, 34}, {1456,  0, 20, 34}, {1477,  0, 15, 34},
   {1493,  0, 15, 34}, {1509,  0, 26, 34}, {1536,  0, 24, 34}, {1561,  0, 20, 34},
   {1582,  0, 28, 34}, {1611,  0, 21, 34}, {1633,  0, 25, 34}, {1659,  0, 18, 34},
   {1678,  0, 16, 34}, {1695,  0, 15, 34}, {1711,  0, 16, 34}, {1728,  0, 20, 34},
   {1749,  0, 22, 34}, {1772,  0, 21, 34}, {1794,  0, 17, 34}, {1812,  0, 17, 34},
   {1830,  0, 17, 34}, {1848,  0, 17, 34}, {1866,  0, 17, 34}, {1884,  0, 15, 34},
   {1900,  0, 12, 34}, {1913,  0, 16, 34}, {1930,  0, 16, 34}, {1947,  0, 19, 34},
   {1967,  0, 15, 34}, {1983,  0, 20, 34}, {2004,  0, 22, 34}, {2027,  0, 20, 34},
   {2048,  0, 15, 34}, {2064,  0, 20, 34}, {2085,  0, 23, 34}, {2109,  0, 24, 34},
   {2134,  0, 21, 34}, {2156,  0, 26, 34}, {2183,  0, 26, 34}, {2210,  0, 20, 34},
   {2231,  0, 28, 34}, {2260,  0, 28, 34}, {2289,  0, 28, 34}, {2318,  0, 28, 34},
   {2347,  0, 28, 34}, {2376,  0, 28, 34}, {2405,  0, 30, 34}, {2436,  0, 22, 34},
   {2459,  0, 22, 34}, {2482,  0, 22, 34}, {2505,  0, 22, 34}, {2528,  0, 22, 34},
   {2551,  0, 16, 34}, {2568,  0, 17, 34}, {2586,  0, 17, 34}, {2604,  0, 18, 34},
   {2623,  0, 25, 34}, {2649,  0, 26, 34}, {2676,  0, 26, 34}, {2703,  0, 26, 34},
   {2730,  0, 26, 34}, {2757,  0, 26, 34}, {2784,  0, 26, 34}, {2811,  0, 26, 34},
   {2838,  0, 24, 34}, {2863,  0, 24, 34}, {2888,  0, 24, 34}, {2913,  0, 24, 34},
   {2938,  0, 26, 34}, {2965,  0, 22, 34}, {2988,  0, 22, 34}, {3011,  0, 22, 34},
   {3034,  0, 22, 34}, {3057,  0, 22, 34}, {3080,  0, 22, 34}, {3103,  0, 22, 34},
   {3126,  0, 29, 34}, {3156,  0, 19, 34}, {3176,  0, 21, 34}, {3198,  0, 21, 34},
   {3220,  0, 21, 34}, {3242,  0, 21, 34}, {3264,  0, 16, 34}, {3281,  0, 16, 34},
   {3298,  0, 17, 34}, {3316,  0, 18, 34}, {3335,  0, 22, 34}, {3358,  0, 22, 34},
   {3381,  0, 22, 34}, {3404,  0, 22, 34}, {3427,  0, 22, 34}, {3450,  0, 22, 34},
   {3473,  0, 22, 34}, {3496,  0, 22, 34}, {3519,  0, 22, 34}, {3542,  0, 22, 34},
   {3565,  0, 22, 34}, {3588,  0, 22, 34}, {3611,  0, 23, 34}, {3635,  0, 23, 34}};


	for (int i = 0; i < 160; i++) {
		for (int j = 0; j < 4; j++) {
			micro12rectangles[i][j][0] = rectangles[i][j];
			micro12rectangles[i][j][1] = rectangles[i][j];
		}
	}
	int rectangles2[160][4] =  { {   0,  0, 18, 22}, {  19,  0, 18, 22}, {  38,  0, 18, 22}, {  57,  0, 18, 22},
   {  76,  0, 18, 22}, {  95,  0, 18, 22}, { 114,  0, 18, 22}, { 133,  0, 18, 22},
   { 152,  0, 12, 22}, { 165,  0, 17, 22}, { 183,  0, 18, 22}, { 202,  0, 17, 22},
   { 220,  0, 20, 22}, { 241,  0, 18, 22}, { 260,  0, 18, 22}, { 279,  0, 18, 22},
   { 298,  0, 18, 22}, { 317,  0, 18, 22}, { 336,  0, 18, 22}, { 355,  0, 18, 22},
   { 374,  0, 18, 22}, { 393,  0, 18, 22}, { 412,  0, 20, 22}, { 433,  0, 18, 22},
   { 452,  0, 18, 22}, { 471,  0, 18, 22}, { 490,  0, 18, 22}, { 509,  0, 18, 22},
   { 528,  0, 18, 22}, { 547,  0, 18, 22}, { 566,  0, 18, 22}, { 585,  0, 18, 22},
   { 604,  0, 18, 22}, { 623,  0, 18, 22}, { 642,  0, 12, 22}, { 655,  0, 17, 22},
   { 673,  0, 18, 22}, { 692,  0, 17, 22}, { 710,  0, 20, 22}, { 731,  0, 18, 22},
   { 750,  0, 18, 22}, { 769,  0, 18, 22}, { 788,  0, 18, 22}, { 807,  0, 18, 22},
   { 826,  0, 18, 22}, { 845,  0, 18, 22}, { 864,  0, 18, 22}, { 883,  0, 18, 22},
   { 902,  0, 20, 22}, { 923,  0, 18, 22}, { 942,  0, 18, 22}, { 961,  0, 18, 22},
   { 980,  0, 18, 22}, { 999,  0, 13, 22}, {1013,  0, 18, 22}, {1032,  0, 18, 22},
   {1051,  0, 18, 22}, {1070,  0, 18, 22}, {1089,  0, 18, 22}, {1108,  0, 17, 22},
   {1126,  0, 18, 22}, {1145,  0, 18, 22}, {1164,  0, 18, 22}, {1183,  0, 13, 22},
   {1197,  0, 12, 22}, {1210,  0, 18, 22}, {1229,  0, 20, 22}, {1250,  0, 18, 22},
   {1269,  0, 20, 22}, {1290,  0, 16, 22}, {1307,  0, 21, 22}, {1329,  0, 18, 22},
   {1348,  0, 13, 22}, {1362,  0, 13, 22}, {1376,  0, 15, 22}, {1392,  0, 18, 22},
   {1411,  0, 16, 22}, {1428,  0, 16, 22}, {1445,  0, 13, 22}, {1459,  0, 15, 22},
   {1475,  0, 13, 22}, {1489,  0, 16, 22}, {1506,  0, 12, 22}, {1519,  0, 12, 22},
   {1532,  0, 12, 22}, {1545,  0, 16, 22}, {1562,  0, 12, 22}, {1575,  0, 16, 22},
   {1592,  0, 12, 22}, {1605,  0, 16, 22}, {1622,  0, 16, 22}, {1639,  0, 18, 22},
   {1658,  0, 14, 22}, {1673,  0, 22, 22}, {1696,  0, 21, 22}, {1718,  0, 22, 22},
   {1741,  0, 15, 22}, {1757,  0, 18, 22}, {1776,  0, 18, 22}, {1795,  0, 22, 22},
   {1818,  0, 22, 22}, {1841,  0, 22, 22}, {1864,  0, 22, 22}, {1887,  0, 22, 22},
   {1910,  0, 22, 22}, {1933,  0, 22, 22}, {1956,  0, 24, 22}, {1981,  0, 22, 22},
   {2004,  0, 22, 22}, {2027,  0, 22, 22}, {2050,  0, 22, 22}, {2073,  0, 22, 22},
   {2096,  0, 14, 22}, {2111,  0, 14, 22}, {2126,  0, 14, 22}, {2141,  0, 14, 22},
   {2156,  0, 24, 22}, {2181,  0, 24, 22}, {2206,  0, 22, 22}, {2229,  0, 22, 22},
   {2252,  0, 22, 22}, {2275,  0, 22, 22}, {2298,  0, 22, 22}, {2321,  0, 22, 22},
   {2344,  0, 22, 22}, {2367,  0, 22, 22}, {2390,  0, 22, 22}, {2413,  0, 22, 22},
   {2436,  0, 22, 22}, {2459,  0, 22, 22}, {2482,  0, 22, 22}, {2505,  0, 22, 22},
   {2528,  0, 22, 22}, {2551,  0, 22, 22}, {2574,  0, 22, 22}, {2597,  0, 22, 22},
   {2620,  0, 24, 22}, {2645,  0, 22, 22}, {2668,  0, 22, 22}, {2691,  0, 22, 22},
   {2714,  0, 22, 22}, {2737,  0, 22, 22}, {2760,  0, 14, 22}, {2775,  0, 14, 22},
   {2790,  0, 14, 22}, {2805,  0, 14, 22}, {2820,  0, 22, 22}, {2843,  0, 22, 22},
   {2866,  0, 22, 22}, {2889,  0, 22, 22}, {2912,  0, 22, 22}, {2935,  0, 22, 22},
   {2958,  0, 22, 22}, {2981,  0, 22, 22}, {3004,  0, 22, 22}, {3027,  0, 22, 22},
   {3050,  0, 22, 22}, {3073,  0, 22, 22}, {3096,  0, 22, 22}, {3119,  0, 22, 22}};

	for (int i = 0; i < 160; i++) {
		for (int j = 0; j < 4; j++) {
			micro12rectangles[i][j][2] = rectangles2[i][j];
			micro12rectangles[i][j][3] = rectangles2[i][j];
		}
	}

	int rectangles3[160][4] =  { {   0,  0, 24, 33}, {  25,  0, 24, 33}, {  50,  0, 24, 33}, {  75,  0, 24, 33},
   { 100,  0, 24, 33}, { 125,  0, 24, 33}, { 150,  0, 24, 33}, { 175,  0, 24, 33},
   { 200,  0, 24, 33}, { 225,  0, 24, 33}, { 250,  0, 24, 33}, { 275,  0, 24, 33},
   { 300,  0, 27, 33}, { 328,  0, 24, 33}, { 353,  0, 24, 33}, { 378,  0, 24, 33},
   { 403,  0, 24, 33}, { 428,  0, 24, 33}, { 453,  0, 24, 33}, { 478,  0, 24, 33},
   { 503,  0, 24, 33}, { 528,  0, 24, 33}, { 553,  0, 27, 33}, { 581,  0, 24, 33},
   { 606,  0, 24, 33}, { 631,  0, 24, 33}, { 656,  0, 24, 33}, { 681,  0, 24, 33},
   { 706,  0, 24, 33}, { 731,  0, 24, 33}, { 756,  0, 24, 33}, { 781,  0, 24, 33},
   { 806,  0, 24, 33}, { 831,  0, 24, 33}, { 856,  0, 15, 33}, { 872,  0, 24, 33},
   { 897,  0, 24, 33}, { 922,  0, 24, 33}, { 947,  0, 27, 33}, { 975,  0, 24, 33},
   {1000,  0, 24, 33}, {1025,  0, 24, 33}, {1050,  0, 24, 33}, {1075,  0, 24, 33},
   {1100,  0, 24, 33}, {1125,  0, 24, 33}, {1150,  0, 24, 33}, {1175,  0, 24, 33},
   {1200,  0, 27, 33}, {1228,  0, 24, 33}, {1253,  0, 24, 33}, {1278,  0, 24, 33},
   {1303,  0, 24, 33}, {1328,  0, 15, 33}, {1344,  0, 24, 33}, {1369,  0, 24, 33},
   {1394,  0, 24, 33}, {1419,  0, 24, 33}, {1444,  0, 24, 33}, {1469,  0, 24, 33},
   {1494,  0, 24, 33}, {1519,  0, 24, 33}, {1544,  0, 27, 33}, {1572,  0, 15, 33},
   {1588,  0, 15, 33}, {1604,  0, 27, 33}, {1632,  0, 23, 33}, {1656,  0, 24, 33},
   {1681,  0, 27, 33}, {1709,  0, 24, 33}, {1734,  0, 24, 33}, {1759,  0, 21, 33},
   {1781,  0, 20, 33}, {1802,  0, 20, 33}, {1823,  0, 24, 33}, {1848,  0, 24, 33},
   {1873,  0, 24, 33}, {1898,  0, 24, 33}, {1923,  0, 20, 33}, {1944,  0, 23, 33},
   {1968,  0, 20, 33}, {1989,  0, 23, 33}, {2013,  0, 15, 33}, {2029,  0, 15, 33},
   {2045,  0, 15, 33}, {2061,  0, 20, 33}, {2082,  0, 15, 33}, {2098,  0, 24, 33},
   {2123,  0, 15, 33}, {2139,  0, 24, 33}, {2164,  0, 24, 33}, {2189,  0, 24, 33},
   {2214,  0, 17, 33}, {2232,  0, 30, 33}, {2263,  0, 30, 33}, {2294,  0, 30, 33},
   {2325,  0, 30, 33}, {2356,  0, 30, 33}, {2387,  0, 30, 33}, {2418,  0, 30, 33},
   {2449,  0, 30, 33}, {2480,  0, 30, 33}, {2511,  0, 30, 33}, {2542,  0, 30, 33},
   {2573,  0, 30, 33}, {2604,  0, 30, 33}, {2635,  0, 33, 33}, {2669,  0, 30, 33},
   {2700,  0, 30, 33}, {2731,  0, 30, 33}, {2762,  0, 30, 33}, {2793,  0, 30, 33},
   {2824,  0, 30, 33}, {2855,  0, 30, 33}, {2886,  0, 30, 33}, {2917,  0, 30, 33},
   {2948,  0, 33, 33}, {2982,  0, 33, 33}, {3016,  0, 30, 33}, {3047,  0, 30, 33},
   {3078,  0, 30, 33}, {3109,  0, 30, 33}, {3140,  0, 30, 33}, {3171,  0, 30, 33},
   {3202,  0, 30, 33}, {3233,  0, 30, 33}, {3264,  0, 30, 33}, {3295,  0, 30, 33},
   {3326,  0, 30, 33}, {3357,  0, 30, 33}, {3388,  0, 30, 33}, {3419,  0, 30, 33},
   {3450,  0, 30, 33}, {3481,  0, 30, 33}, {3512,  0, 30, 33}, {3543,  0, 30, 33},
   {3574,  0, 33, 33}, {3608,  0, 30, 33}, {3639,  0, 30, 33}, {3670,  0, 30, 33},
   {3701,  0, 30, 33}, {3732,  0, 30, 33}, {3763,  0, 17, 33}, {3781,  0, 17, 33},
   {3799,  0, 17, 33}, {3817,  0, 17, 33}, {3835,  0, 30, 33}, {3866,  0, 30, 33},
   {3897,  0, 30, 33}, {3928,  0, 30, 33}, {3959,  0, 30, 33}, {3990,  0, 30, 33},
   {4021,  0, 30, 33}, {4052,  0, 30, 33}, {4083,  0, 30, 33}, {4114,  0, 30, 33},
   {4145,  0, 30, 33}, {4176,  0, 30, 33}, {4207,  0, 30, 33}, {4238,  0, 30, 33}};

	for (int i = 0; i < 160; i++) {
		for (int j = 0; j < 4; j++) {
			micro12rectangles[i][j][4] = rectangles3[i][j];
		}
	}

	int rectangles4[160][4] = { {   0,  0, 20, 25}, {  21,  0, 19, 25}, {  41,  0, 19, 25}, {  61,  0, 19, 25},
   {  81,  0, 19, 25}, { 101,  0, 19, 25}, { 121,  0, 19, 25}, { 141,  0, 19, 25},
   { 161,  0, 19, 25}, { 181,  0, 19, 25}, { 201,  0, 19, 25}, { 221,  0, 19, 25},
   { 241,  0, 21, 25}, { 263,  0, 19, 25}, { 283,  0, 19, 25}, { 303,  0, 19, 25},
   { 323,  0, 19, 25}, { 343,  0, 19, 25}, { 363,  0, 19, 25}, { 383,  0, 19, 25},
   { 403,  0, 19, 25}, { 423,  0, 19, 25}, { 443,  0, 21, 25}, { 465,  0, 19, 25},
   { 485,  0, 19, 25}, { 505,  0, 19, 25}, { 525,  0, 20, 25}, { 546,  0, 19, 25},
   { 566,  0, 19, 25}, { 586,  0, 19, 25}, { 606,  0, 19, 25}, { 626,  0, 19, 25},
   { 646,  0, 19, 25}, { 666,  0, 19, 25}, { 686,  0, 13, 25}, { 700,  0, 19, 25},
   { 720,  0, 19, 25}, { 740,  0, 19, 25}, { 760,  0, 21, 25}, { 782,  0, 19, 25},
   { 802,  0, 19, 25}, { 822,  0, 19, 25}, { 842,  0, 19, 25}, { 862,  0, 19, 25},
   { 882,  0, 19, 25}, { 902,  0, 19, 25}, { 922,  0, 19, 25}, { 942,  0, 19, 25},
   { 962,  0, 21, 25}, { 984,  0, 19, 25}, {1004,  0, 19, 25}, {1024,  0, 19, 25},
   {1044,  0, 19, 25}, {1064,  0, 13, 25}, {1078,  0, 19, 25}, {1098,  0, 19, 25},
   {1118,  0, 19, 25}, {1138,  0, 19, 25}, {1158,  0, 19, 25}, {1178,  0, 19, 25},
   {1198,  0, 19, 25}, {1218,  0, 19, 25}, {1238,  0, 21, 25}, {1260,  0, 13, 25},
   {1274,  0, 13, 25}, {1288,  0, 21, 25}, {1310,  0, 19, 25}, {1330,  0, 19, 25},
   {1350,  0, 21, 25}, {1372,  0, 19, 25}, {1392,  0, 19, 25}, {1412,  0, 17, 25},
   {1430,  0, 16, 25}, {1447,  0, 16, 25}, {1464,  0, 19, 25}, {1484,  0, 19, 25},
   {1504,  0, 19, 25}, {1524,  0, 19, 25}, {1544,  0, 16, 25}, {1561,  0, 18, 25},
   {1580,  0, 16, 25}, {1597,  0, 18, 25}, {1616,  0, 13, 25}, {1630,  0, 13, 25},
   {1644,  0, 13, 25}, {1658,  0, 16, 25}, {1675,  0, 13, 25}, {1689,  0, 19, 25},
   {1709,  0, 13, 25}, {1723,  0, 19, 25}, {1743,  0, 19, 25}, {1763,  0, 19, 25},
   {1783,  0, 22, 25}, {1806,  0, 22, 25}, {1829,  0, 22, 25}, {1852,  0, 22, 25},
   {1875,  0, 22, 25}, {1898,  0, 22, 25}, {1921,  0, 22, 25}, {1944,  0, 22, 25},
   {1967,  0, 22, 25}, {1990,  0, 22, 25}, {2013,  0, 22, 25}, {2036,  0, 22, 25},
   {2059,  0, 22, 25}, {2082,  0, 22, 25}, {2105,  0, 25, 25}, {2131,  0, 22, 25},
   {2154,  0, 22, 25}, {2177,  0, 22, 25}, {2200,  0, 22, 25}, {2223,  0, 22, 25},
   {2246,  0, 22, 25}, {2269,  0, 22, 25}, {2292,  0, 22, 25}, {2315,  0, 22, 25},
   {2338,  0, 22, 25}, {2361,  0, 22, 25}, {2384,  0, 22, 25}, {2407,  0, 22, 25},
   {2430,  0, 22, 25}, {2453,  0, 22, 25}, {2476,  0, 22, 25}, {2499,  0, 22, 25},
   {2522,  0, 22, 25}, {2545,  0, 22, 25}, {2568,  0, 22, 25}, {2591,  0, 22, 25},
   {2614,  0, 22, 25}, {2637,  0, 22, 25}, {2660,  0, 22, 25}, {2683,  0, 22, 25},
   {2706,  0, 22, 25}, {2729,  0, 22, 25}, {2752,  0, 22, 25}, {2775,  0, 22, 25},
   {2798,  0, 22, 25}, {2821,  0, 22, 25}, {2844,  0, 22, 25}, {2867,  0, 22, 25},
   {2890,  0, 22, 25}, {2913,  0, 22, 25}, {2936,  0, 22, 25}, {2959,  0, 22, 25},
   {2982,  0, 22, 25}, {3005,  0, 22, 25}, {3028,  0, 22, 25}, {3051,  0, 22, 25},
   {3074,  0, 22, 25}, {3097,  0, 22, 25}, {3120,  0, 22, 25}, {3143,  0, 22, 25},
   {3166,  0, 22, 25}, {3189,  0, 22, 25}, {3212,  0, 22, 25}, {3235,  0, 22, 25},
   {3258,  0, 22, 25}, {3281,  0, 22, 25}, {3304,  0, 22, 25}, {3327,  0, 22, 25}};

	for (int i = 0; i < 160; i++) {
		for (int j = 0; j < 4; j++) {
			micro12rectangles[i][j][5] = rectangles4[i][j];
		}
	}

	int rectangles5[160][4] =   { {   0,  0,  9, 13}, {  11,  0,  9, 13}, {  22,  0,  9, 13}, {  33,  0,  9, 13},
   {  44,  0,  9, 13}, {  55,  0,  9, 13}, {  66,  0,  9, 13}, {  77,  0,  9, 13},
   {  88,  0,  9, 13}, {  99,  0,  9, 13}, { 110,  0,  9, 13}, { 121,  0,  9, 13},
   { 132,  0, 11, 13}, { 145,  0,  9, 13}, { 156,  0,  9, 13}, { 167,  0,  9, 13},
   { 178,  0,  9, 13}, { 189,  0,  9, 13}, { 200,  0,  9, 13}, { 211,  0,  9, 13},
   { 222,  0,  9, 13}, { 233,  0,  9, 13}, { 244,  0, 10, 13}, { 256,  0,  9, 13},
   { 267,  0,  9, 13}, { 278,  0,  9, 13}, { 289,  0,  9, 13}, { 300,  0,  9, 13},
   { 311,  0,  9, 13}, { 322,  0,  9, 13}, { 333,  0,  9, 13}, { 344,  0,  9, 13},
   { 355,  0,  9, 13}, { 366,  0,  9, 13}, { 377,  0,  3, 13}, { 382,  0,  9, 13},
   { 393,  0,  9, 13}, { 404,  0,  9, 13}, { 415,  0, 11, 13}, { 428,  0,  9, 13},
   { 439,  0,  9, 13}, { 450,  0,  9, 13}, { 461,  0,  9, 13}, { 472,  0,  9, 13},
   { 483,  0,  9, 13}, { 494,  0,  9, 13}, { 505,  0,  9, 13}, { 516,  0,  9, 13},
   { 527,  0, 11, 13}, { 540,  0,  9, 13}, { 551,  0,  9, 13}, { 562,  0,  9, 13},
   { 573,  0,  9, 13}, { 584,  0,  4, 13}, { 590,  0,  9, 13}, { 601,  0,  9, 13},
   { 612,  0,  9, 13}, { 623,  0,  9, 13}, { 634,  0,  9, 13}, { 645,  0,  9, 13},
   { 656,  0,  9, 13}, { 667,  0,  9, 13}, { 678,  0, 11, 13}, { 691,  0,  4, 13},
   { 697,  0,  4, 13}, { 703,  0, 11, 13}, { 716,  0,  9, 13}, { 727,  0,  9, 13},
   { 738,  0, 11, 13}, { 751,  0,  9, 13}, { 762,  0,  9, 13}, { 773,  0,  7, 13},
   { 782,  0,  6, 13}, { 790,  0,  7, 13}, { 799,  0,  9, 13}, { 810,  0,  9, 13},
   { 821,  0,  9, 13}, { 832,  0,  9, 13}, { 843,  0,  6, 13}, { 851,  0,  8, 13},
   { 861,  0,  6, 13}, { 869,  0,  8, 13}, { 879,  0,  3, 13}, { 884,  0,  3, 13},
   { 889,  0,  3, 13}, { 894,  0,  6, 13}, { 902,  0,  4, 13}, { 908,  0,  9, 13},
   { 919,  0,  4, 13}, { 925,  0,  9, 13}, { 936,  0,  9, 13}, { 947,  0,  9, 13},
   { 958,  0, 11, 13}, { 971,  0, 11, 13}, { 984,  0, 11, 13}, { 997,  0, 11, 13},
   {1010,  0, 11, 13}, {1023,  0, 11, 13}, {1036,  0, 11, 13}, {1049,  0, 11, 13},
   {1062,  0, 11, 13}, {1075,  0, 11, 13}, {1088,  0, 11, 13}, {1101,  0, 11, 13},
   {1114,  0, 11, 13}, {1127,  0, 11, 13}, {1140,  0, 15, 13}, {1157,  0, 11, 13},
   {1170,  0, 11, 13}, {1183,  0, 11, 13}, {1196,  0, 11, 13}, {1209,  0, 11, 13},
   {1222,  0, 11, 13}, {1235,  0, 11, 13}, {1248,  0, 11, 13}, {1261,  0, 11, 13},
   {1274,  0, 11, 13}, {1287,  0, 11, 13}, {1300,  0, 11, 13}, {1313,  0, 11, 13},
   {1326,  0, 11, 13}, {1339,  0, 11, 13}, {1352,  0, 11, 13}, {1365,  0, 11, 13},
   {1378,  0, 11, 13}, {1391,  0, 11, 13}, {1404,  0, 11, 13}, {1417,  0, 11, 13},
   {1430,  0, 11, 13}, {1443,  0, 11, 13}, {1456,  0, 11, 13}, {1469,  0, 11, 13},
   {1482,  0, 11, 13}, {1495,  0, 11, 13}, {1508,  0, 11, 13}, {1521,  0, 11, 13},
   {1534,  0, 11, 13}, {1547,  0, 11, 13}, {1560,  0, 11, 13}, {1573,  0, 11, 13},
   {1586,  0, 11, 13}, {1599,  0, 11, 13}, {1612,  0, 11, 13}, {1625,  0, 11, 13},
   {1638,  0, 11, 13}, {1651,  0, 11, 13}, {1664,  0, 11, 13}, {1677,  0, 11, 13},
   {1690,  0, 11, 13}, {1703,  0, 11, 13}, {1716,  0, 11, 13}, {1729,  0, 11, 13},
   {1742,  0, 11, 13}, {1755,  0, 11, 13}, {1768,  0, 11, 13}, {1781,  0, 11, 13},
   {1794,  0, 11, 13}, {1807,  0, 11, 13}, {1820,  0, 11, 13}, {1833,  0, 11, 13}};

	for (int i = 0; i < 160; i++) {
		for (int j = 0; j < 4; j++) {
			micro12rectangles[i][j][6] = rectangles5[i][j];
		}
	}

}

CImages::~CImages(void)
{
}
void CImages::RenderText(int x, int y, int font,char *text, int alpha) {
	if (font == 6) {
		RenderTextCustom(x,y,font,text,alpha);
		return;
	}
	int addY = 0;/*
	switch(font) {
		case 0:
			addY= 360+44+52;
			break;
		case 1:
			addY= 360+44;
			break;
		case 2:
			addY= 360;
			break;
		case 3:
			addY= 624;
			break;
		case 4:
			addY= 558;
			break;
		case 5:
			addY = 508;
			break;
	}*/
	int cursor = 0;
	for (int i = 0; i < strlen(text); i++) {
		if (text[i] == ' ') {
			if (font == 5)
				cursor += 10;
			else
				cursor += 20;
			continue;
		} else {
			src->x = micro12rectangles[characterMapping[text[i]]][0][font]+0;
			src->y = 0+addY;
			if (font == 5)
				src->w = micro12rectangles[characterMapping[text[i]]][2][font]-5;
			else
				src->w = micro12rectangles[characterMapping[text[i]]][2][font]-4;
			src->h = micro12rectangles[0][3][font];
			if (characterMapping[text[i]] >= 50) {
				src->y = micro12rectangles[0][3][font]+addY;
				src->x -= micro12rectangles[characterMapping['x']][0][font];
			}
			fonts[font]->Render(x + (cursor),y,alpha,*src);
			cursor+= src->w-4;
		}
	}
}
void CImages::LoadImages() {
	if (levelselectgrid == NULL) {
		levelselectgrid = new CImg("levelselectgrid.png");
		return;
	}
	if (background == NULL) {
		background = new CImg("levelselect.png");
		return;
	}
	if (levelselecttext == NULL) {
		levelselecttext = new CImg("levelselecttext.png");
		return;
	}
	if (gameboard == NULL) {
		gameboard = new CImg("gameboard.png");
		return;
	}
	if (pausemenu == NULL) {
		pausemenu = new CImg("pausemenu.png");
		return;
	}
	if (turnonsound == NULL) {
		turnonsound = new CImg("turnonsound.png");
		return;
	}
	if (turnoffsound == NULL) {
		turnoffsound = new CImg("turnoffsound.png");
		return;
	}
	if (blocks == NULL) {
		blocks = new CImg("blocks.png");
		return;
	}
	if (background2 == NULL) {
		background2 = new CImg("background2.png");
		return;
	}
	if (fonts[0] == NULL) {
		fonts[0]= new CImg("erasbold.png");
		return;
	}
	if (fonts[1] == NULL) {
		fonts[1]= new CImg("micro12green.png");
		return;
	}
	if (fonts[3] == NULL) {
		fonts[3] = new CImg("micro9.png");
		return;
	}
	if (fonts[4] == NULL) {
		fonts[4] = new CImg("corpulentcaps18.png");
		return;
	}
	if (fonts[5] == NULL) {
		fonts[5] = new CImg("corpulentcaps12.png");
		return;
	}
	if (fonts[6] == NULL) {
		fonts[6] = new CImg("caps10.png");
		return;
	}
	if (particles[0]  == NULL) {
		particles[0] = new CImg("starparticle.png");
		return;
	}
	if (particles[1]  == NULL) {
		particles[1] = new CImg("particlesparkle.png");
		return;
	}
	if (particles[2]  == NULL) {
		particles[2] = new CImg("star2.png");
		return;
	}
	if (particles[3] == NULL) {
		particles[3] = new CImg("particlebubble.png");
		return;
	}

	if (congratulations == NULL) {
		congratulations= new CImg("congratulations.png");
		return;
	}
	if (levelselectionbox == NULL) {
		levelselectionbox = new CImg("levelselectionbox.png");
		return;
	}
	if (levelselectgameboards == NULL) {
		levelselectgameboards = new CImg("levelselectgameboards.png");
		return;
	}
	if (tutorialpage1 == NULL) {
		tutorialpage1 = new CImg("tutorialpage1.png");
		return;
	}
	if (tutorialpage2 == NULL) {
		tutorialpage2 = new CImg("tutorialpage2.png");
		return;
	}
	if (tutorialpage3 == NULL) {
		tutorialpage3= new CImg("tutorialpage3.png");
		return;
	}
	if (blackoverlay == NULL) {
		blackoverlay = new CImg("blackoverlay.png");
		return;
	}
	if (tutorial[0] == NULL) {
		tutorial[0] = new CImg("tutorial1.png");
		return;
	}
	if (tutorial[1] == NULL) {
		tutorial[1] = new CImg("tutorial2.png");
		return;
	}
	if (tutorial[2] == NULL) {
		tutorial[2] = new CImg("tutorial3.png");
		return;
	}
	if (tutorial[3] == NULL) {
		tutorial[3] = new CImg("tutorial4.png");
		return;
	}
	if (tutorial[4] == NULL) {
		tutorial[4] = new CImg("tutorial5.png");
		return;
	}
	if (colorblindblue == NULL) {
		colorblindblue = new CImg("colorblindb.png");
		return;
	}
	if (colorblindred == NULL) {
		colorblindred = new CImg("colorblindr.png");
		return;
	}
	if (colorblindpurple == NULL) {
		colorblindpurple = new CImg("colorblindp.png");
		return;
	}
	if (colorblindgreen == NULL) {
		colorblindgreen = new CImg("colorblindg.png");
		return;
	}
	if (colorblindcyan == NULL) {
		colorblindcyan = new CImg("colorblindc.png");
		return;
	}
	if (turnoncolorblindmode == NULL) {
		turnoncolorblindmode= new CImg("turnoncolorblindmode.png");
		return;
	}
	if (turnoffcolorblindmode == NULL) {
		turnoffcolorblindmode = new CImg("turnoffcolorblindmode.png");
		return;
	}
	if (background3 == NULL) {
		background3 = new CImg("background3.png");
		return;
	}
	if (background4 == NULL) {
		background4 = new CImg("background4.png");
		return;
	}
	if (background5 == NULL) {
		background5 = new CImg("background5.png");
		return;
	}
	if (background6 == NULL) {
		background6 = new CImg("background6.png");
		return;
	}
	if (background7 == NULL) {
		background7 = new CImg("background7.png");
		return;
	}
	if (background8 == NULL) {
		background8 = new CImg("background8.png");
		return;
	}
	if (particles[5] == NULL) {
		particles[5] = new CImg("leaf1.png");
		return;
	}
	if (particles[6] == NULL) {
		particles[6] = new CImg("leaf2.png");
		return;
	}
	if (cake[0] == NULL) {
		cake[0] = new CImg("cake1.png");
		return;
	}
	if (cake[1] == NULL) {
		cake[1] = new CImg("cake2.png");
		return;
	}
	if (ending == NULL) {
		ending = new CImg("ending.png");
		return;
	}
	if (particles[7] == NULL) {
		particles[7] = new CImg("leaf3.png");
		return;
	}
	if (particles[8] == NULL) {
		particles[8] = new CImg("snow1.png");
		return;
	}
	if (particles[9] == NULL) {
		particles[9] = new CImg("snow2.png");
		return;
	}
	if (particles[10] == NULL) {
		particles[10] = new CImg("snow3.png");
		return;
	}
	if (particles[11] == NULL) {
		particles[11] = new CImg("butterfly1.png");
		return;
	}
	if (particles[12] == NULL) {
		particles[12] = new CImg("butterfly2.png");
		return;
	}
	if (particles[13] == NULL) {
		particles[13] = new CImg("butterfly3.png");
		return;
	}
	if (particles[14] == NULL) {
		particles[14] = new CImg("butterfly4.png");
		return;
	}
	if (particles[15] == NULL) {
		particles[15] = new CImg("butterfly5.png");
		return;
	}
	if (particles[16] == NULL) {
		particles[16] = new CImg("butterfly6.png");
		return;
	}if (particles[17] == NULL) {
		particles[17] = new CImg("leaf4.png");
		return;
	}
	if (particles[18] == NULL) {
		particles[18] = new CImg("leaf5.png");
		return;
	}
	if (particles[19] == NULL) {
		particles[19] = new CImg("leaf6.png");
		return;
	}
	if (bird[0] == NULL) {
		bird[0] = new CImg("bird1.png");
		return;
	}
	if (bird[1] == NULL) {
		bird[1] = new CImg("bird2.png");
		return;
	}
	if (bird[2] == NULL) {
		bird[2] = new CImg("bird3.png");
		return;
	}
	if (bird[3] == NULL) {
		bird[3] = new CImg("bird4.png");
		return;
	}
	if (bird[4] == NULL) {
		bird[4] = new CImg("bird5.png");
		return;
	}
	if (bird[5] == NULL) {
		bird[5] = new CImg("bird6.png");
		return;
	}
	if (cake[2] == NULL) {
		cake[2] = new CImg("cake3.png");
		return;
	}
	if (levelselect[0] == NULL) {
		levelselect[0] = new CImg("levelselect1.png");
		return;
	}
	if (levelselect[1] == NULL) {
		levelselect[1] = new CImg("levelselect2.png");
		return;
	}
	if (levelselect[2] == NULL) {
		levelselect[2] = new CImg("levelselect3.png");
		return;
	}
	if (levelselect[3] == NULL) {
		levelselect[3] = new CImg("levelselect4.png");
		return;
	}
	if (levelselect[4] == NULL) {
		levelselect[4] = new CImg("levelselect5.png");
		return;
	}
	if (levelselect[5] == NULL) {
		levelselect[5] = new CImg("levelselect6.png");
		return;
	}
	if (levelselect[6] == NULL) {
		levelselect[6] = new CImg("levelselect7.png");
		return;
	}
	if (levelselect[7] == NULL) {
		levelselect[7] = new CImg("levelselect8.png");
		return;
	}
	if (blackoverlaygameboard == NULL) {
		blackoverlaygameboard= new CImg("blackoverlaygameboard.png");
		return;
	}
}
void CImages::RenderTextCustom(int x, int y, int font,char *text, int alpha) {
		int cursor = 0;
	for (int i = 0; i < strlen(text); i++) {
		if (text[i] == ' ') {
			if (font == 5)
				cursor += 10;
			else
				cursor += 10;
			continue;
		} else {
			src->x = micro12rectangles[characterMapping[text[i]]][0][font];
			src->y = 0;
			src->w = micro12rectangles[characterMapping[text[i]]][2][font]+1;
			src->h = micro12rectangles[0][3][font];
			if (characterMapping[text[i]] >= 50) {
				src->y = micro12rectangles[0][3][font];
				src->x -= micro12rectangles[characterMapping['x']][0][font];
			}
			fonts[font]->Render(x + (cursor),y,alpha,*src);
			cursor+= src->w;
		}
	}
}