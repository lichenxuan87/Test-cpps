/*
 * triangleMath.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: peter
 */

#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;

const double PI = 3.14159265;
const double AB = 63;
const double CD = 116.5;
const double angAOB = 2.2435;
const double AD = 692.609;

double toRadian(double degree)
{
    return degree * PI / 180;
}

void help()
{
    cout << "Usage: ./calculateVisibleRange fov" << endl;
}

double calculateVisableRange(double fov)
{
    // Length here are in millimeters
    // Angles here are in degrees
    double angDCF = 90 - fov / 2;

    if (angDCF <= 0)
    {
        cout << "Input FOV is not correct!" << endl;
        return -1;
    }

    double tanAngDCF = tan(toRadian(angDCF));
    double tanAngAOB = tan(toRadian(angAOB));

    // HF = ((DF+AD)tan[angleDCF]*tan[angleAOB] + AB*tan[angleDCF]) /
    //       (1 - tan[angleDCF] * tan[angleAOB])
    // DF = CD * tan[angleDCF]
    double HF = ((CD * tanAngDCF + AD) * tanAngDCF * tanAngAOB + AB * tanAngDCF) /
            (1 - tanAngDCF * tanAngAOB);

    // BG = (AD + CD*tan[angleDCF] + HF) / cos[angleAOB]
    double BG = (AD + CD * tanAngDCF + HF) / cos(toRadian(angAOB));

    return BG;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        help();
        return -1;
    }

    double fov = atof(argv[1]);


    cout << "Blind area distance from eyes: " << calculateVisableRange(fov) << endl;

}
