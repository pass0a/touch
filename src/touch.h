/*
 *  Created on: 2016-03-03
 *  Author: Yangchao
 */
#ifndef  LINUX_EVENTHAND_H_
#define LINUX_EVENTHAND_H_
#include "stdint.h"


#ifdef __cplusplus
extern "C" {
#endif

	typedef enum OPERATION
	{
		Press = 0,
		Release,
		Slide,
		Move,
	}OPERAT;


	typedef struct POSDATA
	{
		OPERAT ope;
		unsigned int pos_x1;
		unsigned int pos_y1;
		unsigned int pos_x2;
		unsigned int pos_y2;

	}TOUCHPOSDATA;
    int reportMouse(uint16_t type, uint16_t code, int32_t value);
	int reportEvent(TOUCHPOSDATA *data);
	int setDevice(const char* path);
#ifdef __cplusplus
}
#endif
#endif
