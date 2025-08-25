/*
 * fuzzy.c
 *
 *  Created on: Aug 20, 2025
 *      Author: Admin
 */

#include "fuzzy.h"

// membership for temperature
static float low_temp, mid_temp, high_temp, very_high_temp;

// membership for humidity
static float very_low_hum, low_hum, mid_hum, high_hum, very_high_hum;

// For presence
static int detection;

// rules
static float R1,R2,R3,R4,R5,R6,R7,R8,R9,R10;
static float R11,R12,R13,R14,R15,R16,R17,R18,R19,R20;
static float R21,R22,R23,R24,R25,R26,R27,R28,R29,R30;
static float R31,R32,R33,R34,R35,R36,R37,R38,R39,R40;

// Speed membership
static float speed_very_low, speed_low, speed_middle, speed_fast, speed_very_fast;

// defuzz result
static int dcog;

// -------- FUZZIFICATION ------------
void find_temp(float temp)
{
    if (temp >= 18 && temp < 21.5f) {
        low_temp = -0.2857f * (temp - 18) + 1;
        mid_temp = 0.2857f * (temp - 18);
        high_temp = 0;
        very_high_temp = 0;
    }
    else if (temp >= 21.5f && temp < 25) {
        low_temp = 0;
        mid_temp = -0.2857f * (temp - 21.5f) + 1;
        high_temp = 0.2857f * (temp - 21.5f);
        very_high_temp = 0;
    }
    else if (temp >= 25 && temp < 28.5f) {
        low_temp = 0;
        mid_temp = 0;
        high_temp = -0.2857f * (temp - 25) + 1;
        very_high_temp = 0.2857f * (temp - 25);
    }
    else if (temp >= 28.5f) {
        low_temp = 0;
        mid_temp = 0;
        high_temp = 0;
        very_high_temp = 1;
    }
}

void find_hum(float hum)
{
    if (hum >= 50 && hum < 62.5f) {
        very_low_hum = -0.08f * (hum - 50) + 1;
        low_hum = 0.08f * (hum - 50);
        mid_hum = 0;
        high_hum = 0;
        very_high_hum = 0;
    }
    else if (hum >= 62.5f && hum < 75) {
        very_low_hum = 0;
        low_hum = -0.08f * (hum - 62.5f) + 1;
        mid_hum = 0.08f * (hum - 62.5f);
        high_hum = 0;
        very_high_hum = 0;
    }
    else if (hum >= 75 && hum < 87.5f) {
        very_low_hum = 0;
        low_hum = 0;
        mid_hum = -0.08f * (hum - 75) + 1;
        high_hum = 0.08f * (hum - 75);
        very_high_hum = 0;
    }
    else if (hum >= 87.5f && hum <= 99) {
        very_low_hum = 0;
        low_hum = 0;
        mid_hum = 0;
        high_hum = -0.08f * (hum - 87.5f) + 1;
        very_high_hum = 0.08f * (hum - 87.5f);
    }
}

void motion_detection(int presence)
{
    detection = (presence == 1) ? 1 : 0;
}

// -------- RULE EVALUATION ----------
void rule_evaluation(void)
{
    // Clear all rules
    R1=R2=R3=R4=R5=R6=R7=R8=R9=R10=0;
    R11=R12=R13=R14=R15=R16=R17=R18=R19=R20=0;
    R21=R22=R23=R24=R25=R26=R27=R28=R29=R30=0;
    R31=R32=R33=R34=R35=R36=R37=R38=R39=R40=0;

    if (detection == 0) {
        R1  = fminf(low_temp, very_low_hum);
        R3  = fminf(low_temp, low_hum);
        R5  = fminf(low_temp, mid_hum);
        R7  = fminf(low_temp, high_hum);
        R9  = fminf(low_temp, very_high_hum);
        R11 = fminf(mid_temp, very_low_hum);
        R13 = fminf(mid_temp, low_hum);
        R15 = fminf(mid_temp, mid_hum);
        R17 = fminf(mid_temp, high_hum);
        R19 = fminf(mid_temp, very_high_hum);
        R21 = fminf(high_temp, very_low_hum);
        R23 = fminf(high_temp, low_hum);
        R25 = fminf(high_temp, mid_hum);
        R27 = fminf(high_temp, high_hum);
        R29 = fminf(high_temp, very_high_hum);
        R31 = fminf(very_high_temp, very_low_hum);
        R33 = fminf(very_high_temp, low_hum);
        R35 = fminf(very_high_temp, mid_hum);
        R37 = fminf(very_high_temp, high_hum);
        R39 = fminf(very_high_temp, very_high_hum);
    }
    else {
        R2  = fminf(low_temp, very_low_hum);
        R4  = fminf(low_temp, low_hum);
        R6  = fminf(low_temp, mid_hum);
        R8  = fminf(low_temp, high_hum);
        R10 = fminf(low_temp, very_high_hum);
        R12 = fminf(mid_temp, very_low_hum);
        R14 = fminf(mid_temp, low_hum);
        R16 = fminf(mid_temp, mid_hum);
        R18 = fminf(mid_temp, high_hum);
        R20 = fminf(mid_temp, very_high_hum);
        R22 = fminf(high_temp, very_low_hum);
        R24 = fminf(high_temp, low_hum);
        R26 = fminf(high_temp, mid_hum);
        R28 = fminf(high_temp, high_hum);
        R30 = fminf(high_temp, very_high_hum);
        R32 = fminf(very_high_temp, very_low_hum);
        R34 = fminf(very_high_temp, low_hum);
        R36 = fminf(very_high_temp, mid_hum);
        R38 = fminf(very_high_temp, high_hum);
        R40 = fminf(very_high_temp, very_high_hum);
    }
}

// -------- MAXIMUM ------------
void maximum(void)
{
	speed_very_low  = fmaxf(R1, fmaxf(R3, fmaxf(R11, fmaxf(R12, fmaxf(R13, fmaxf(R21, fmaxf(R22, fmaxf(R23, fmaxf(R24, fmaxf(R31, fmaxf(R32, fmaxf(R33, R34))))))))))));
	speed_low       = fmaxf(R2, fmaxf(R4, fmaxf(R14, fmaxf(R25, R35))));
	speed_middle    = fmaxf(R5, fmaxf(R6, fmaxf(R15, fmaxf(R17, fmaxf(R26, fmaxf(R27, fmaxf(R29, fmaxf(R36, R37))))))));
	speed_fast      = fmaxf(R7, fmaxf(R8, fmaxf(R9, fmaxf(R16, fmaxf(R18, fmaxf(R19, fmaxf(R28, fmaxf(R38, R39))))))));
	speed_very_fast = fmaxf(R10, fmaxf(R20, fmaxf(R30, R40)));
}

// -------- DEFUZZIFICATION -----
void centre(void)
{
    float dsvl = 25 * speed_very_low;
    float dsl  = 25 * speed_low;
    float dsm  = 25 * speed_middle;
    float dsf  = 25 * speed_fast;
    float dsvf = 25 * speed_very_fast;

    float wsvl = dsvl * 0;
    float wsl  = dsl  * 25;
    float wsm  = dsm  * 50;
    float wsf  = dsf  * 75;
    float wsvf = dsvf * 100;

    float num = wsvl + wsl + wsm + wsf + wsvf;
    float den = dsvl + dsl + dsm + dsf + dsvf;

    if (den == 0) dcog = 0;
    else dcog = (int)(num / den);
}

int crisp_output(void)
{
    return (int)((dcog * 1023.0f) / 99.0f);
}

// -------- MAIN ENTRY ----------
int fuzzy_init(float temp_rcv, float hum_rcv, int presence_rcv)
{
    if (temp_rcv < 18 || hum_rcv < 50) {
        dcog = 0;
        return 0;
    } else {
        find_temp(temp_rcv);
        find_hum(hum_rcv);
        motion_detection(presence_rcv);
        rule_evaluation();
        maximum();
        centre();
        return crisp_output();
    }
}

