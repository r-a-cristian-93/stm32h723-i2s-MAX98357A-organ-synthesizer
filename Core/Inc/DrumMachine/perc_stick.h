#ifndef WAV_PERC_STICK_H
#define WAV_PERC_STICK_H

#include <cstdint>

const int16_t wav_perc_stick_length = 1755;
const int16_t wav_perc_stick[1755] = 
{
8, 588, 767, 910, 1043, 684, 421, -210, -483, -43, 
615, 1438, 3199, 8450, 14913, 16139, 7478, -8963, -22679, -28985, 
-25031, -6925, 14159, 25960, 27293, 18079, 553, -16186, -21482, -13553, 
130, 7720, 5237, 3076, 1818, -7731, -21450, -24575, -8995, 11222, 
21322, 23842, 18426, 6641, -4941, -15025, -21440, -21523, -10483, 10377, 
27239, 31216, 20871, 534, -19027, -29925, -31530, -29034, -23675, -12624, 
2188, 14668, 16427, 6891, -4926, -12096, -10968, -1492, 12442, 22982, 
22604, 15648, 10952, 8803, 6219, 5131, 9962, 19402, 25602, 20838, 
4646, -13924, -24016, -23188, -17604, -12767, -8543, -1262, 9702, 17326, 
14950, 3222, -12359, -26190, -32768, -26088, -10212, 4190, 14535, 21395, 
24351, 22734, 15375, 5462, -355, 2834, 12814, 22458, 26005, 20633, 
10125, -425, -10546, -19993, -25992, -23491, -14110, -7045, -5690, -7863, 
-12526, -16984, -17184, -14231, -7570, 6605, 21170, 28274, 30393, 31104, 
29000, 17774, 3113, -524, 5173, 11500, 15159, 15046, 11852, 5892, 
-3204, -13794, -19263, -16929, -13058, -11447, -13507, -19788, -27128, -31563, 
-29791, -22447, -13036, -4294, 3014, 9811, 14109, 13019, 8038, 3959, 
5580, 14905, 26098, 30078, 29742, 30410, 28270, 20728, 7741, -5430, 
-12215, -14001, -11508, -6314, -2597, -2484, -7482, -14689, -19932, -21077, 
-17785, -12263, -5512, -418, 305, -1455, -3761, -5011, -4553, -2664, 
722, 4816, 8289, 10115, 11458, 14368, 18354, 19872, 16596, 10985, 
6172, 4082, 4524, 6216, 9893, 14007, 15742, 14019, 8867, 2194, 
-4818, -11092, -15518, -17711, -17364, -16481, -16048, -15174, -13046, -9104, 
-5541, -3638, -1927, 1338, 5991, 8823, 8955, 7163, 3975, 1715, 
1539, 3857, 7684, 10524, 11615, 9502, 4236, -420, -2858, -4396, 
-5483, -5713, -5449, -5163, -5039, -5246, -5168, -4247, -3085, -2844, 
-3848, -5174, -6397, -7975, -9546, -9799, -8140, -5356, -2799, -1258, 
-154, 1337, 2974, 3974, 4005, 3310, 1524, -1852, -6181, -9926, 
-11453, -10662, -8586, -6308, -4944, -4683, -5568, -7299, -8511, -8156, 
-5694, -2186, 544, 1880, 1564, 213, -1332, -2094, -801, 1462, 
2943, 2756, 255, -3971, -8846, -12858, -14342, -12468, -8060, -3947, 
-1479, -263, -56, -538, -1880, -2894, -2110, -227, 1988, 4218, 
6434, 7939, 7592, 5883, 3755, 2060, 922, 59, 119, 1260, 
3275, 4807, 4157, 1814, -1574, -5519, -9378, -11944, -11373, -8340, 
-5333, -4667, -6523, -8680, -9442, -7504, -3554, 583, 4357, 6793, 
8152, 8848, 8770, 8847, 9577, 11789, 14044, 14497, 14724, 15061, 
14615, 11503, 6041, 2486, 433, -1727, -2831, -2270, 770, 4407, 
6261, 5932, 3090, -1202, -5835, -8680, -8571, -7631, -5908, -2524, 
2275, 6826, 8551, 8828, 9541, 9794, 9428, 8855, 8271, 7722, 
7265, 6797, 5786, 4485, 3425, 2828, 3421, 5558, 7401, 6448, 
2179, -3387, -6042, -4607, -2590, -958, 1865, 5533, 8074, 7547, 
4809, 2571, 1285, 168, -652, -1833, -3397, -3469, -2281, -1011, 
289, 687, 140, -237, 218, 1275, 1594, 753, -192, 223, 
1610, 1802, 998, 733, 1247, 1739, 1541, 1917, 4172, 7656, 
9972, 9159, 6206, 2920, 183, -2479, -5189, -5606, -3190, -279, 
1100, 461, -701, -1338, -2064, -3700, -5871, -7141, -6785, -4337, 
-257, 3438, 5445, 6472, 7943, 9223, 9028, 7060, 3616, 180, 
-3248, -6717, -8496, -7805, -3876, 1901, 6497, 9463, 10944, 11407, 
10910, 8409, 3961, -1469, -5871, -8252, -9180, -8831, -7863, -6559, 
-5551, -5690, -6370, -7310, -7683, -6550, -4303, -1158, 2464, 5839, 
7713, 7232, 5844, 5054, 4572, 3193, 529, -2548, -5226, -6728, 
-6682, -5560, -4521, -5154, -7128, -8289, -8046, -7386, -6563, -5531, 
-5068, -5648, -5870, -3705, -524, 855, 1150, 1713, 2047, 1281, 
-775, -2594, -3282, -3346, -3118, -3420, -4225, -4155, -2332, 626, 
2914, 3464, 2188, -243, -2631, -4610, -6594, -9272, -12096, -13547, 
-13662, -12688, -10353, -7250, -4304, -2157, -446, 1646, 4313, 7281, 
9172, 8997, 7421, 4824, 1976, 403, 248, 446, -387, -2422, 
-4252, -5133, -4426, -1786, 945, 1647, 25, -2139, -2601, -1051, 
1137, 2039, 1114, -178, -602, 324, 1958, 3044, 3901, 4789, 
4593, 3182, 1678, 1488, 3593, 6823, 8964, 8916, 6528, 3101, 
291, -1136, -1043, -1375, -3637, -6343, -7490, -5962, -2954, -270, 
2185, 4092, 5147, 5371, 4824, 4646, 4301, 2791, 1565, 1889, 
3431, 5080, 6309, 6945, 6347, 5058, 4034, 3487, 3078, 1545, 
-1000, -2640, -2385, -706, 919, 1426, 1408, 1594, 1891, 1906, 
1115, 425, 1919, 4424, 4958, 3672, 1400, -1203, -2328, -1980, 
-1036, 352, 1819, 3268, 3523, 2274, 1796, 2248, 2141, 1552, 
954, 682, 493, -226, -1183, -1691, -1780, -2032, -2182, -1290, 
265, 968, 497, -210, -793, -1495, -2480, -2883, -1143, 1502, 
1943, 340, -623, 137, 1627, 2266, 1601, 1194, 1987, 3114, 
2907, 79, -2989, -4262, -5391, -5642, -3539, -541, 780, -615, 
-1840, -1386, -564, 73, 293, 1587, 2941, 1253, -1594, -2757, 
-1804, -324, -376, -1385, -2130, -1864, -361, 2201, 4695, 5206, 
3632, -90, -3641, -4023, -3550, -2671, -7, 3510, 6319, 5972, 
4337, 3503, 1405, -1690, -4533, -5058, -2948, -1577, -1215, -1573, 
-3239, -5383, -6968, -6009, -3340, -1996, -1835, -923, 1626, 4071, 
4567, 4016, 3543, 3139, 2711, 2560, 2973, 3244, 1890, -867, 
-3145, -3713, -1818, 1489, 3631, 3654, 2228, 501, -1352, -2665, 
-1768, 587, 2367, 2270, 936, 234, 236, 817, 1572, 1528, 
588, -1080, -1748, -265, 1923, 2684, 1110, -216, 520, 1429, 
898, -932, -2333, -2359, -2443, -4265, -7183, -8076, -6060, -2752, 
991, 4506, 7175, 7631, 4984, 1114, -1734, -2786, -2524, -2264, 
-2467, -1982, -730, -717, -2781, -5072, -4763, -2136, -611, -1617, 
-3396, -3397, -2221, -1458, 266, 2150, 2534, 2505, 2892, 3908, 
4173, 3215, 2854, 3009, 2690, 1748, 1123, 1023, 357, -456, 
-941, -410, 1083, 1499, 964, 270, -627, -2058, -4528, -6068, 
-4907, -1840, 784, 1268, 1087, 1378, 1830, 2345, 2970, 4049, 
4268, 2620, 465, -414, 593, 1634, 2158, 3615, 5281, 5720, 
4569, 2729, 1476, 761, 278, 172, 461, 217, -1312, -2757, 
-2173, 672, 3320, 3449, 2303, 1578, 1071, 998, 1926, 3275, 
4182, 4257, 3923, 3863, 3731, 3698, 3798, 2894, 1819, 1620, 
1508, 865, -376, -763, -8, -267, -722, 259, 1213, 1537, 
1790, 1864, 2222, 2951, 3532, 3487, 2094, 406, -220, -717, 
-1453, -1739, -1304, -154, 1191, 1982, 1517, 92, -1220, -1929, 
-1626, -52, 2096, 3287, 2327, -551, -3149, -3726, -4244, -5407, 
-5397, -5020, -4666, -3316, -460, 2873, 3346, 1799, 1584, 2069, 
1592, -674, -3178, -3722, -2938, -1858, -1642, -2617, -3617, -4360, 
-4664, -4198, -3248, -2415, -2157, -2690, -3462, -3425, -3248, -2832, 
-1024, 419, 33, -839, -317, 1131, 724, -1510, -2983, -2459, 
-1242, -1550, -2696, -2891, -2333, -2262, -3121, -3098, -961, 1766, 
3004, 1871, -693, -2639, -2672, -1645, -502, 1129, 2619, 2880, 
1816, 369, -72, 670, 1777, 2104, 1320, 280, -546, -805, 
-139, 918, 1257, 742, -136, -1551, -2867, -3574, -3753, -3113, 
-2319, -1138, 726, 2319, 3228, 2173, -6, -272, 1545, 3941, 
5052, 4876, 4925, 4465, 2670, -271, -2701, -2428, -746, 179, 
137, -89, 498, 1598, 1877, 918, -88, -746, -1916, -3057, 
-3194, -2170, -427, 1220, 2341, 1963, 244, -774, -1051, -1159, 
-276, 1234, 2219, 2174, 1627, 1421, 938, 96, -346, -394, 
179, 316, -485, -303, 462, 357, -372, -941, -641, -603, 
-924, -116, 779, 1109, 1632, 1927, 1656, 1281, 1391, 2127, 
3116, 3804, 3839, 3080, 1594, 395, 137, 855, 2125, 2286, 
1233, -40, -1153, -1072, -34, 1490, 3678, 4089, 1078, -2676, 
-3855, -2192, -669, -1004, -1155, -462, -169, 687, 1941, 1608, 
463, -51, 123, 1023, 2333, 3520, 4207, 4394, 4584, 4648, 
3756, 2384, 1458, 187, -1781, -3836, -5369, -5134, -2878, 522, 
3399, 3930, 2699, 1516, 1745, 2365, 1363, 549, 1056, 1067, 
97, -916, -371, 1102, 1502, 1174, 633, 625, 1603, 2361, 
2537, 2084, 1226, 652, 230, 145, 292, 424, 981, 1016, 
-33, -495, 247, 1027, 1427, 2194, 3294, 3301, 1703, -82, 
-635, -261, -302, -719, -553, 239, 887, 420, -340, 72, 
795, 788, 3, -883, -424, 1071, 1573, 272, -1406, -2309, 
-2897, -3168, -2905, -1950, -288, 1042, 1582, 1388, 863, 895, 
1227, 1386, 1330, 1233, 1204, 969, 550, -463, -1384, -1207, 
-1354, -1691, -1369, -1578, -2086, -2273, -2415, -2289, -1730, -694, 
153, 19, -396, -181, 313, 276, -275, -724, -921, -1266, 
-1892, -2273, -1739, -345, 689, 921, 927, 112, -728, 74, 
812, 291, -371, -922, -1472, -2445, -3425, -3107, -2223, -1389, 
71, 1699, 1920, 116, -1148, 50, 1826, 2637, 2347, 1711, 
1574, 1305, 1279, 1766, 1215, -444, -1893, -2135, -979, 395, 
627, -2, -344, -798, -1816, -2211, -1588, -602, 349, 520, 
-543, -1893, -2687, -2636, -1086, 1460, 3656, 4353, 3099, 1609, 
771, 84, 8, 542, 1521, 1981, 1081, 356, 751, 1695, 
1283, -1148, -2778, -3048, -3339, -3076, -1733, 329, 1634, 1366, 
713, 241, -130, -79, 364, 818, 1143, 1683, 2723, 2892, 
1024, -794, -1208, -989, -127, 453, -156, -1332, -2065, -1359, 
-404, -515, -357, 335, 380, 392, 813, 149, -1458, -2501, 
-2594, -1764, -714, 339, 1516, 1961, 1601, 1049, 932, 617, 
-617, -1248, -483, 1692, 4131, 4580, 3412, 1553, -47, -762, 
-1685, -2296, -1915, -1004, -355, -1088, -2153, -2201, -921, 1034, 
1207, -365, -1318, -1304, -1203, -1051, -178, 1162, 1945, 1925, 
1859, 1955, 1753, 1577, 1379, 1317, 2016, 2374, 1598, 305, 
-398, -16, 69, -400, -316, 472, 1392, 1573, 1294, 1329, 
1633, 1170, -898, -2152, -1262, -634, -1024, -1397, -745, 371, 
198, -461, -489, 61, 1069, 1601, 1576, 1477, 1282, 1084, 
1091, 2045, 3754, 4931, 4931, 3785, 2365, 1235, 246, -454, 
-600, 111, 1028, 1249, 1136, 985, 671, 207, -206, -318, 
-330, -267, -161, -301, -278, -43, -566, -1870, -2772, -2665, 
-1350, 925, 2728, 3400, 3233, 2121, 511, -944, -1493, -394, 
1193, 1705, 1359, 839, 379, 362, 952, 1447, 1262, 551, 
-138, -186, 208, 373, 160, -4, 437, 1159, 1352, 687, 
-393, -791, -464, -267, -214, -329, -869, -1345, -1255, -784, 
-26, 1087, 2023, 2295, 1763, 659, 18, 336, 1160, 1661, 
1058, -226, -1290, -1652, -1140, -174, 841, 1444, 1419, 1097, 
160, -991, -1069, -328, 239, 347, 151, -163, -577, -910, 
-830, -482, -384, -542, -813, -1173, -1180, -775, -480, -739, 
-1252, -923, 199, 1089, 1303, 926, 638, 506, -37, -600, 
-538, 214, 927, 816, -44, -1028, -1236, -687, -329, -726, 
-1761, -2260, -1437, -25, 1060, 1368, 1241, 1189, 977, 347, 
-281, -129, 658, 1134, 945, 403, 21, -125, -594, -1605, 
-2251, -1744, -911, -636, -496, 387, 1652, 1478, -20, -876, 
-705, -233, -77, 40, 903, 2046, 2720, 2667, 1811, 821, 
416, 356, 193, 227, 614, 680, -263, -1670, -1940, -880, 
147, 229, -415, -745, -441, 162, 668, 504, 345, 1048, 
2374, 3503, 3408, 2804, 2471, 1524, 305, -34, 639, 1544, 
1782, 1642, 1669, 1609, 986, -255, -1384, -1719, -1353, -886, 
-551, -4, 548, 600, 342, 271, 494, 750, 897, 1177, 
1730, 2056, 1818, 1299, 894, 1061, 1669, 2003, 1817, 1656, 
2226, 2822, 2237, 827, -402, -779, -436, -18, 220, 136, 
-123, -415, -690, -621, -511, -771, -1131, -705, 788, 1749, 
1479, 871, 429, 540, 848, 1091, 1561, 1634, 1252, 739, 
48, -115, 519, 1253, 1322, 629, 103, 99, -33, -489, 
-836, -737, -504, -539, -551, -305, -81, 175, 663, 1293, 
1864, 1989, 1759, 1486, 1194, 1304, 1704, 1610, 1010, 438, 
146, -126, -532, -822, -623, 55, 267, -380, -1081, -1088, 
-333, 443, 742, 600, 530, 955, 785, 59, -16, 61, 
64, 137, 9, -65, -58, -26, 8, -11, -20, -67, 
-34, 54, 45, 0, -46, -50, -33, -27, -9, -3, 
-7, -12, -10, -3, 0
};

#endif // WAVETABLE_H
