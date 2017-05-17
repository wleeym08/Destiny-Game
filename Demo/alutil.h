/**
 * File Name:    alutil.h
 * Description:  OpenAL Utility
 * Author:       Zhiying Li
 * Last Update:  2017/05/05
 */

#ifndef ALUTIL_H
#define ALUTIL_H
#include <al.h>
#include <alc.h>

int alInit(void);
void alExit(void);
ALuint bufferWavData(char[]);
ALuint createNormalSource(ALuint);

#endif
