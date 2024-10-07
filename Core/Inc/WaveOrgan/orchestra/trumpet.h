#ifndef WAV_TRUMPET_H
#define WAV_TRUMPET_H

#include <cstdint>

const int16_t wav_trumpet[1024] = 
{
-10322, -11040, -11549, -11835, -11664, -11275, -10642, -9640, -8490, -7172, 
-5697, -4187, -2650, -1213, 131, 1335, 2298, 3097, 3654, 3923, 
4035, 3933, 3630, 3223, 2681, 2065, 1422, 769, 167, -387, 
-831, -1151, -1380, -1442, -1379, -1226, -932, -554, -117, 392, 
913, 1440, 1931, 2372, 2771, 3066, 3295, 3463, 3490, 3450, 
3342, 3133, 2891, 2613, 2299, 1985, 1674, 1400, 1157, 954, 
828, 740, 700, 722, 780, 888, 1046, 1222, 1416, 1616, 
1815, 2009, 2175, 2320, 2428, 2495, 2535, 2531, 2496, 2440, 
2352, 2248, 2135, 2015, 1879, 1733, 1580, 1451, 1341, 1275, 
1236, 1217, 1235, 1268, 1314, 1381, 1455, 1538, 1618, 1691, 
1759, 1817, 1867, 1907, 1925, 1930, 1919, 1887, 1848, 1800, 
1739, 1672, 1599, 1534, 1477, 1431, 1391, 1356, 1330, 1313, 
1301, 1298, 1312, 1335, 1368, 1398, 1424, 1440, 1457, 1474, 
1492, 1504, 1512, 1510, 1507, 1501, 1494, 1482, 1466, 1448, 
1434, 1423, 1406, 1387, 1366, 1359, 1353, 1349, 1341, 1345, 
1363, 1378, 1381, 1367, 1357, 1349, 1345, 1335, 1327, 1324, 
1338, 1353, 1364, 1347, 1322, 1291, 1274, 1260, 1246, 1221, 
1196, 1184, 1192, 1204, 1205, 1189, 1168, 1153, 1141, 1133, 
1127, 1126, 1126, 1125, 1124, 1124, 1124, 1119, 1111, 1100, 
1089, 1078, 1064, 1050, 1035, 1024, 1015, 1008, 996, 982, 
965, 950, 938, 930, 922, 915, 907, 907, 909, 910, 
909, 911, 920, 927, 927, 917, 910, 904, 901, 888, 
873, 859, 848, 836, 818, 799, 780, 759, 737, 715, 
696, 678, 660, 637, 615, 592, 576, 562, 550, 532, 
513, 492, 473, 438, 388, 242, 11, -313, -871, -1547, 
-2355, -3321, -4332, -5390, -6415, -7372, -8224, -8835, -9289, -9523, 
-9452, -9206, -8716, -7969, -7093, -6053, -4916, -3745, -2559, -1433, 
-367, 569, 1340, 1994, 2438, 2694, 2819, 2731, 2512, 2204, 
1770, 1279, 755, 244, -232, -677, -1064, -1376, -1621, -1689, 
-1673, -1580, -1348, -1060, -716, -303, 120, 552, 943, 1301, 
1622, 1856, 2033, 2138, 2148, 2113, 2023, 1875, 1704, 1505, 
1268, 1014, 740, 493, 272, 99, -16, -96, -124, -108, 
-63, 26, 143, 277, 431, 588, 744, 887, 1014, 1129, 
1214, 1267, 1294, 1276, 1245, 1205, 1143, 1064, 969, 867, 
770, 679, 592, 506, 421, 370, 343, 342, 361, 387, 
421, 466, 518, 578, 660, 743, 823, 868, 902, 926, 
938, 942, 931, 912, 887, 854, 807, 755, 696, 647, 
606, 579, 552, 527, 502, 483, 469, 465, 470, 480, 
492, 508, 527, 556, 582, 603, 615, 621, 621, 614, 
609, 605, 600, 593, 585, 574, 562, 547, 536, 527, 
519, 515, 509, 502, 487, 472, 460, 457, 455, 452, 
448, 448, 460, 480, 501, 519, 538, 556, 565, 555, 
538, 525, 523, 526, 529, 523, 512, 488, 466, 447, 
439, 429, 419, 417, 427, 448, 466, 474, 474, 478, 
484, 492, 499, 506, 511, 508, 500, 487, 479, 475, 
478, 477, 471, 455, 433, 416, 408, 410, 413, 415, 
412, 408, 403, 406, 413, 425, 433, 438, 438, 436, 
433, 433, 429, 422, 407, 396, 388, 392, 400, 409, 
416, 423, 429, 437, 438, 435, 413, 393, 374, 370, 
369, 373, 380, 388, 397, 405, 412, 419, 432, 479, 
582, 955, 1583, 2606, 4299, 6376, 8992, 12085, 15369, 18838, 
22197, 25381, 28149, 30240, 31838, 32558, 32416, 31696, 30037, 27687, 
24889, 21462, 17759, 13893, 9956, 6179, 2556, -581, -3271, -5583, 
-7069, -8058, -8615, -8374, -7775, -6846, -5439, -3901, -2229, -529, 
1081, 2585, 3750, 4695, 5376, 5589, 5562, 5239, 4518, 3614, 
2488, 1187, -161, -1539, -2831, -4036, -5089, -5905, -6566, -6980, 
-7126, -7111, -6854, -6407, -5850, -5144, -4375, -3581, -2797, -2084, 
-1430, -911, -511, -208, -101, -130, -265, -562, -933, -1366, 
-1879, -2401, -2931, -3421, -3866, -4267, -4547, -4760, -4900, -4902, 
-4840, -4705, -4468, -4195, -3881, -3547, -3213, -2883, -2580, -2307, 
-2080, -1929, -1819, -1768, -1792, -1857, -1976, -2130, -2302, -2494, 
-2690, -2883, -3060, -3205, -3326, -3409, -3456, -3475, -3447, -3395, 
-3326, -3228, -3112, -2985, -2850, -2715, -2580, -2450, -2334, -2230, 
-2165, -2123, -2104, -2123, -2155, -2198, -2260, -2329, -2404, -2476, 
-2544, -2607, -2649, -2678, -2690, -2697, -2699, -2692, -2655, -2607, 
-2545, -2478, -2408, -2331, -2263, -2200, -2150, -2103, -2059, -2024, 
-2005, -1995, -1996, -2005, -2020, -2040, -2059, -2076, -2094, -2116, 
-2141, -2166, -2183, -2192, -2188, -2179, -2164, -2136, -2099, -2052, 
-1988, -1932, -1882, -1857, -1831, -1806, -1778, -1753, -1731, -1716, 
-1698, -1679, -1662, -1652, -1654, -1667, -1683, -1701, -1718, -1731, 
-1737, -1736, -1732, -1727, -1717, -1703, -1678, -1648, -1616, -1586, 
-1553, -1518, -1476, -1439, -1405, -1381, -1363, -1349, -1344, -1344, 
-1347, -1350, -1353, -1355, -1359, -1363, -1367, -1370, -1370, -1370, 
-1372, -1373, -1373, -1359, -1340, -1316, -1298, -1281, -1266, -1251, 
-1241, -1234, -1226, -1214, -1197, -1172, -1141, -1105, -1089, -1083, 
-1092, -1095, -1096, -1095, -1089, -1083, -1076, -1118, -1214, -1437, 
-1818, -2307, -2982, -3790, -4682, -5677, -6687, -7693, -8613, -9388, 
-10040, -10398, -10549, -10526, -10164, -9618, -8913, -7952, -6895, -5749, 
-4525, -3324, -2147, -1101, -151, 690, 1287, 1751, 2054, 2117, 
2064, 1868, 1511, 1094, 611, 98, -412, -907, -1327, -1692, 
-1965, -2121, -2201, -2161, -2004, -1783, -1478, -1120, -731, -307, 
110, 514, 876, 1196, 1480, 1674, 1792, 1854, 1833, 1756, 
1635, 1436, 1213, 971, 722, 489, 272, 121, -2, -99, 
-168, -202, -198, -105, 7, 135, 261, 400, 560, 749, 
925, 1073, 1166, 1235, 1278, 1297, 1301, 1286, 1245, 1191, 
1116, 1028, 935, 837, 738, 644, 565, 508, 464, 445, 
452, 475, 512, 546, 579, 620, 675, 738, 808, 874, 
935, 975, 1004, 1023, 1027, 1023, 1010, 982, 949, 910, 
881, 854, 826, 792, 755, 713, 659, 608, 565, 537, 
517, 504, 512, 530, 559, 587, 610, 624, 639, 654, 
670, 685, 697, 701, 690, 672, 651, 631, 610, 578, 
543, 508, 482, 458, 435, 409, 386, 365, 352, 340, 
331, 326, 323, 323, 318, 307, 290, 282, 277, 274, 
261, 246, 228, 211, 192, 169, 145, 125, 114, 114, 
115, 115, 108, 98, 87, 78, 71, 67, 69, 75, 
84, 82, 70, 41, 15, -9, -30, -45, -56, -52, 
-48, -48, -60, -62, -56, -28, 1, 30, 41, 41, 
33, 28, 33, 48, 83, 107, 121, 85, 47, 5, 
-10, -18, -19, -23, -29, -37, -46, -56, -68, -79, 
-86, -84, -82, -81, -81, -71, -60, -48, -37, -27, 
-19, -16, -12, -3, 0, -1, -14, -21, -25, -26, 
-31, -39, -48, -77, -131, -306, -617, -1046, -1767, -2669, 
-3728, -4999, -6297, -7622
};

#endif // WAVETABLE_H
