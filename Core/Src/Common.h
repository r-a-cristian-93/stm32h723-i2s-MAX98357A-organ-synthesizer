#ifndef COMMON_H
#define COMMON_H

#define M_2PI 6.28318530717958647692
#define DRAWBARS_COUNT 9
#define MIDI_NOTES_COUNT 128
#define PARAM_LOWEST_VALUE 0.0001


extern double g_time;
extern double g_amplitude;

double note_frequency[MIDI_NOTES_COUNT][DRAWBARS_COUNT] = {
    {4.09, 8.18, 12.25, 16.35, 24.51, 32.70, 41.21, 49.02, 65.41},
    {4.33, 8.66, 12.98, 17.32, 25.97, 34.65, 43.66, 51.93, 69.30},
    {4.59, 9.18, 13.75, 18.35, 27.51, 36.71, 46.26, 55.02, 73.42},
    {4.86, 9.72, 14.57, 19.45, 29.15, 38.89, 49.01, 58.29, 77.78},
    {5.15, 10.30, 15.44, 20.60, 30.88, 41.20, 51.93, 61.76, 82.41},
    {5.46, 10.91, 16.36, 21.83, 32.71, 43.65, 55.01, 65.43, 87.30},
    {5.78, 11.56, 17.33, 23.12, 34.66, 46.25, 58.28, 69.32, 92.50},
    {6.13, 12.25, 18.36, 24.50, 36.72, 49.00, 61.75, 73.44, 98.00},
    {6.49, 12.98, 19.45, 25.96, 38.90, 51.91, 65.42, 77.81, 103.82},
    {6.88, 13.75, 20.61, 27.50, 41.22, 55.00, 69.31, 82.44, 110.00},
    {7.28, 14.57, 21.83, 29.14, 43.67, 58.27, 73.44, 87.34, 116.54},
    {7.72, 15.43, 23.13, 30.87, 46.27, 61.74, 77.80, 92.53, 123.47},
    {8.18, 16.35, 24.51, 32.70, 49.02, 65.41, 82.43, 98.04, 130.82},
    {8.66, 17.32, 25.97, 34.65, 51.93, 69.30, 87.33, 103.86, 138.59},
    {9.18, 18.35, 27.51, 36.71, 55.02, 73.42, 92.52, 110.04, 146.83},
    {9.72, 19.45, 29.14, 38.89, 58.29, 77.78, 98.02, 116.58, 155.56},
    {10.30, 20.60, 30.88, 41.20, 61.76, 82.41, 103.85, 123.52, 164.82},
    {10.91, 21.83, 32.71, 43.65, 65.43, 87.31, 110.03, 130.86, 174.62},
    {11.56, 23.13, 34.66, 46.25, 69.32, 92.50, 116.57, 138.64, 185.00},
    {12.25, 24.50, 36.72, 49.00, 73.44, 98.00, 123.50, 146.88, 196.00},
    {12.98, 25.96, 38.90, 51.91, 77.81, 103.83, 130.85, 155.62, 207.66},
    {13.75, 27.50, 41.22, 55.00, 82.44, 110.00, 138.63, 164.87, 220.00},
    {14.57, 29.14, 43.67, 58.27, 87.34, 116.54, 146.87, 174.67, 233.08},
    {15.43, 30.87, 46.27, 61.74, 92.53, 123.47, 155.60, 185.06, 246.94},
    {16.35, 32.70, 49.02, 65.41, 98.03, 130.81, 164.85, 196.06, 261.62},
    {17.32, 34.65, 51.93, 69.30, 103.86, 138.59, 174.66, 207.72, 277.18},
    {18.35, 36.71, 55.02, 73.42, 110.04, 146.83, 185.04, 220.08, 293.66},
    {19.45, 38.89, 58.29, 77.78, 116.58, 155.56, 196.05, 233.16, 311.13},
    {20.60, 41.20, 61.76, 82.41, 123.51, 164.81, 207.70, 247.02, 329.62},
    {21.83, 43.65, 65.43, 87.31, 130.86, 174.62, 220.06, 261.72, 349.23},
    {23.12, 46.25, 69.32, 92.50, 138.64, 185.00, 233.14, 277.28, 369.99},
    {24.50, 49.00, 73.44, 98.00, 146.88, 196.00, 247.00, 293.76, 391.99},
    {25.96, 51.91, 77.81, 103.83, 155.62, 207.65, 261.69, 311.23, 415.30},
    {27.50, 55.00, 82.44, 110.00, 164.87, 220.00, 277.25, 329.74, 440.00},
    {29.14, 58.27, 87.34, 116.54, 174.67, 233.08, 293.74, 349.35, 466.16},
    {30.87, 61.74, 92.53, 123.47, 185.06, 246.94, 311.20, 370.12, 493.88},
    {32.70, 65.41, 98.03, 130.81, 196.06, 261.62, 329.71, 392.13, 523.25},
    {34.65, 69.30, 103.86, 138.59, 207.72, 277.18, 349.32, 415.45, 554.37},
    {36.71, 73.42, 110.04, 146.83, 220.08, 293.66, 370.09, 440.15, 587.33},
    {38.89, 77.78, 116.58, 155.56, 233.16, 311.13, 392.09, 466.33, 622.26},
    {41.20, 82.41, 123.51, 164.81, 247.03, 329.63, 415.41, 494.05, 659.26},
    {43.65, 87.31, 130.86, 174.61, 261.72, 349.23, 440.11, 523.43, 698.46},
    {46.25, 92.50, 138.64, 185.00, 277.28, 370.00, 466.28, 554.56, 739.99},
    {49.00, 98.00, 146.88, 196.00, 293.77, 392.00, 494.01, 587.53, 783.99},
    {51.91, 103.83, 155.62, 207.65, 311.23, 415.30, 523.38, 622.47, 830.61},
    {55.00, 110.00, 164.87, 220.00, 329.74, 440.00, 554.50, 659.48, 880.00},
    {58.27, 116.54, 174.67, 233.08, 349.35, 466.16, 587.48, 698.70, 932.33},
    {61.74, 123.47, 185.06, 246.94, 370.12, 493.88, 622.41, 740.24, 987.77},
    {65.41, 130.81, 196.07, 261.63, 392.13, 523.25, 659.42, 784.26, 1046.50},
    {69.30, 138.59, 207.72, 277.18, 415.45, 554.36, 698.63, 830.89, 1108.73},
    {73.42, 146.83, 220.08, 293.66, 440.15, 587.33, 740.17, 880.30, 1174.66},
    {77.78, 155.56, 233.16, 311.13, 466.32, 622.25, 784.18, 932.65, 1244.50},
    {82.41, 164.81, 247.03, 329.63, 494.05, 659.26, 830.82, 988.11, 1318.51},
    {87.31, 174.61, 261.72, 349.23, 523.43, 698.46, 880.22, 1046.86, 1396.91},
    {92.50, 185.00, 277.28, 369.99, 554.56, 739.99, 932.56, 1109.11, 1479.98},
    {98.00, 196.00, 293.77, 392.00, 587.53, 783.99, 988.01, 1175.07, 1567.98},
    {103.83, 207.65, 311.23, 415.30, 622.47, 830.61, 1046.76, 1244.93, 1661.22},
    {110.00, 220.00, 329.74, 440.00, 659.48, 880.00, 1109.01, 1318.96, 1760.00},
    {116.54, 233.08, 349.35, 466.16, 698.70, 932.33, 1174.95, 1397.40, 1864.66},
    {123.47, 246.94, 370.12, 493.88, 740.24, 987.77, 1244.82, 1480.49, 1975.54},
    {130.81, 261.63, 392.13, 523.25, 784.26, 1046.50, 1318.84, 1568.52, 2093.01},
    {138.59, 277.18, 415.45, 554.37, 830.90, 1108.73, 1397.26, 1661.79, 2217.46},
    {146.83, 293.67, 440.15, 587.33, 880.30, 1174.66, 1480.35, 1760.61, 2349.32},
    {155.56, 311.13, 466.32, 622.25, 932.65, 1244.51, 1568.37, 1865.30, 2489.02},
    {164.81, 329.63, 494.05, 659.26, 988.11, 1318.51, 1661.64, 1976.22, 2637.02},
    {174.61, 349.23, 523.43, 698.46, 1046.86, 1396.91, 1760.44, 2093.72, 2793.82},
    {185.00, 369.99, 554.56, 739.99, 1109.11, 1479.98, 1865.12, 2218.22, 2959.95},
    {196.00, 392.00, 587.53, 783.99, 1175.06, 1567.98, 1976.02, 2350.13, 3135.96},
    {207.65, 415.31, 622.47, 830.61, 1244.94, 1661.22, 2093.53, 2489.88, 3322.44},
    {220.00, 440.00, 659.48, 880.00, 1318.96, 1760.00, 2218.01, 2637.93, 3520.00},
    {233.08, 466.16, 698.70, 932.33, 1397.40, 1864.66, 2349.91, 2794.79, 3729.31},
    {246.94, 493.88, 740.24, 987.77, 1480.49, 1975.53, 2489.64, 2960.97, 3951.06},
    {261.63, 523.25, 784.26, 1046.50, 1568.52, 2093.00, 2637.68, 3137.04, 4186.01},
    {277.18, 554.37, 830.90, 1108.73, 1661.79, 2217.46, 2794.52, 3323.58, 4434.92},
    {293.67, 587.33, 880.30, 1174.66, 1760.61, 2349.32, 2960.70, 3521.22, 4698.64},
    {311.13, 622.25, 932.65, 1244.51, 1865.30, 2489.02, 3136.75, 3730.60, 4978.03},
    {329.63, 659.26, 988.11, 1318.51, 1976.21, 2637.02, 3323.27, 3952.43, 5274.04},
    {349.23, 698.46, 1046.86, 1396.91, 2093.72, 2793.82, 3520.88, 4187.45, 5587.65},
    {369.99, 739.99, 1109.11, 1479.98, 2218.23, 2959.96, 3730.24, 4436.45, 5919.91},
    {392.00, 783.99, 1175.06, 1567.98, 2350.13, 3135.96, 3952.05, 4700.26, 6271.93},
    {415.30, 830.61, 1244.94, 1661.22, 2489.87, 3322.44, 4187.05, 4979.75, 6644.87},
    {440.00, 880.00, 1318.96, 1760.00, 2637.93, 3520.00, 4436.03, 5275.86, 7040.00},
    {466.16, 932.33, 1397.40, 1864.66, 2794.79, 3729.31, 4699.81, 5589.58, 7458.62},
    {493.88, 987.77, 1480.49, 1975.53, 2960.98, 3951.07, 4979.28, 5921.95, 7902.14},
    {523.25, 1046.50, 1568.52, 2093.00, 3137.04, 4186.01, 5275.36, 6274.09, 8372.02},
    {554.37, 1108.73, 1661.79, 2217.46, 3323.58, 4434.92, 5589.05, 6647.17, 8869.85},
    {587.33, 1174.66, 1760.61, 2349.32, 3521.21, 4698.64, 5921.39, 7042.43, 9397.27},
    {622.25, 1244.51, 1865.30, 2489.02, 3730.60, 4978.03, 6273.49, 7461.19, 9956.06},
    {659.26, 1318.51, 1976.21, 2637.02, 3952.43, 5274.04, 6646.53, 7904.86, 10548.08},
    {698.46, 1396.91, 2093.73, 2793.83, 4187.45, 5587.65, 7041.76, 8374.90, 11175.30},
    {739.99, 1479.98, 2218.23, 2959.96, 4436.45, 5919.91, 7460.48, 8872.90, 11839.82},
    {783.99, 1567.98, 2350.13, 3135.96, 4700.26, 6271.93, 7904.11, 9400.51, 12543.86},
    {830.61, 1661.22, 2489.87, 3322.44, 4979.75, 6644.88, 8374.11, 9959.50, 13289.75},
    {880.00, 1760.00, 2637.93, 3520.00, 5275.86, 7040.00, 8872.06, 10551.72, 14080.00},
    {932.33, 1864.66, 2794.79, 3729.31, 5589.58, 7458.62, 9399.62, 11179.16, 14917.24},
    {987.77, 1975.53, 2960.98, 3951.07, 5921.95, 7902.13, 9958.55, 11843.90, 15804.26},
    {1046.50, 2093.01, 3137.05, 4186.01, 6274.09, 8372.02, 10550.72, 12548.18, 16744.04},
    {1108.73, 2217.46, 3323.58, 4434.92, 6647.17, 8869.84, 11178.09, 13294.33, 17739.69},
    {1174.66, 2349.32, 3521.21, 4698.64, 7042.43, 9397.27, 11842.77, 14084.85, 18794.54},
    {1244.51, 2489.02, 3730.60, 4978.03, 7461.19, 9956.06, 12546.98, 14922.38, 19912.13},
    {1318.51, 2637.02, 3952.43, 5274.04, 7904.86, 10548.08, 13293.06, 15809.71, 21096.16},
    {1396.91, 2793.83, 4187.45, 5587.65, 8374.90, 11175.30, 14083.51, 16749.81, 22350.61},
    {1479.98, 2959.96, 4436.45, 5919.91, 8872.90, 11839.82, 14920.96, 17745.80, 23679.64},
    {1567.98, 3135.96, 4700.26, 6271.93, 9400.51, 12543.85, 15808.21, 18801.02, 25087.70},
    {1661.22, 3322.44, 4979.75, 6644.88, 9959.50, 13289.75, 16748.21, 19918.99, 26579.50},
    {1760.00, 3520.00, 5275.86, 7040.00, 10551.72, 14080.00, 17744.11, 21103.44, 28160.00},
    {1864.66, 3729.31, 5589.58, 7458.62, 11179.16, 14917.24, 18799.23, 22358.31, 29834.48},
    {1975.53, 3951.07, 5921.95, 7902.13, 11843.90, 15804.26, 19917.09, 23687.80, 31608.53},
    {2093.00, 4186.01, 6274.09, 8372.02, 12548.18, 16744.04, 21101.43, 25096.36, 33488.07},
    {2217.46, 4434.92, 6647.17, 8869.84, 13294.33, 17739.69, 22356.18, 26588.66, 35479.38},
    {2349.32, 4698.64, 7042.43, 9397.27, 14084.85, 18794.54, 23685.55, 28169.70, 37589.09},
    {2489.02, 4978.03, 7461.19, 9956.06, 14922.38, 19912.13, 25093.97, 29844.77, 39824.26},
    {2637.02, 5274.04, 7904.86, 10548.08, 15809.71, 21096.16, 26586.13, 31619.43, 42192.33},
    {2793.83, 5587.65, 8374.90, 11175.30, 16749.81, 22350.61, 28167.03, 33499.62, 44701.22},
    {2959.96, 5919.91, 8872.90, 11839.82, 17745.80, 23679.64, 29841.92, 35491.61, 47359.29},
    {3135.96, 6271.93, 9400.51, 12543.85, 18801.02, 25087.71, 31616.42, 37602.05, 50175.42},
    {3322.44, 6644.88, 9959.50, 13289.75, 19918.99, 26579.50, 33496.42, 39837.98, 53159.00},
    {3520.00, 7040.00, 10551.72, 14080.00, 21103.44, 28160.00, 35488.23, 42206.87, 56320.00},
    {3729.31, 7458.62, 11179.16, 14917.24, 22358.31, 29834.48, 37598.46, 44716.62, 59668.96},
    {3951.07, 7902.13, 11843.90, 15804.27, 23687.81, 31608.53, 39834.19, 47375.61, 63217.06},
    {4186.01, 8372.02, 12548.18, 16744.04, 25096.36, 33488.07, 42202.85, 50192.71, 66976.14},
    {4434.92, 8869.84, 13294.33, 17739.69, 26588.66, 35479.38, 44712.36, 53177.32, 70958.75},
    {4698.64, 9397.27, 14084.85, 18794.55, 28169.71, 37589.09, 47371.10, 56339.42, 75178.18},
    {4978.03, 9956.06, 14922.38, 19912.13, 29844.76, 39824.25, 50187.93, 59689.53, 79648.50},
    {5274.04, 10548.08, 15809.71, 21096.16, 31619.42, 42192.32, 53172.25, 63238.84, 84384.64},
    {5587.65, 11175.30, 16749.80, 22350.60, 33499.61, 44701.20, 56334.03, 66999.21, 89402.40},
    {5919.91, 11839.82, 17745.80, 23679.64, 35491.60, 47359.28, 59683.84, 70983.20, 94718.56},
    {6271.93, 12543.85, 18801.02, 25087.70, 37602.04, 50175.40, 63232.81, 75204.07, 100350.80}
};

#endif
