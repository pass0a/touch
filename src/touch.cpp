
#include <linux/input.h> 
#include <fcntl.h>  
#include <unistd.h>  
#include <stdint.h>  
#include <stdio.h>  
#include <stdlib.h> 
#include "touch.h"
#include <time.h>
#include <string.h>

#define  SILDING_STEP 6
#define  SILDING_DELAY 10000

int fd=0;
char gpath[250]="/dev/input/event0";
int setDevice(const char* path){
	strcpy(gpath,path);
	return 0;
}
int openEventdevice()
{	
	fd = open(gpath, O_RDWR); 
    if (fd < 0)
	{  
        printf("Open input device failed !\r\n");  
        return -1;  
    } 
	printf("open %s scuessful!!\r\n",gpath);
	return fd;
}

int closeEventdevice()
{
	close(fd);
	return 0;
}
int reportkey(int fd, uint16_t type, uint16_t code, int32_t value)  
{  
    struct input_event event;  
  
    event.type = type;  
    event.code = code;  
    event.value = value;  
  
    gettimeofday(&event.time, 0);  
    printf("reportkey:%d,%d,%d\r\n",event.type, event.code, event.value);
    if (write(fd, &event, sizeof(struct input_event)) < 0) {  
        printf("report key error!\n");  
		close(fd);
        return -1;  
    }  
  
	return 0;  
}  

int  reportSildingEvent(int fd,int sx,int sy,int ex,int ey )
{
	
	int nextPosX,nextPosY;
	printf("Siding from Point(%d,%d) to Point(%d,%d),\n",sx,sy, ex, ey);
	
	if(ex == sx && ey==sy) // the same two points
	{
		reportkey(fd,EV_ABS,ABS_X,sx);
		reportkey(fd,EV_ABS,ABS_Y,sy); //report position x,y

		reportkey(fd,EV_ABS,ABS_PRESSURE,1); //report preeusre 1
		reportkey(fd,EV_KEY,330,1); //report touch preesed event

		reportkey(fd,EV_SYN,2,0);
		reportkey(fd,EV_SYN,0,0); 

		reportkey(fd,EV_ABS,ABS_X,sx);
		reportkey(fd,EV_ABS,ABS_Y,sy); //report position x,y
        
		reportkey(fd,EV_KEY,330,0);    //report touch release event
		reportkey(fd,EV_ABS,ABS_PRESSURE,0);  //report preeusre 0
        
		reportkey(fd,EV_SYN,2,0);
		reportkey(fd,EV_SYN,0,0); 	//report syn signal , finish the curent event!
		return 0;
	}
	
	/**Report pressed-down event START----*/
	
	reportkey(fd,EV_ABS,ABS_X,sx);
	reportkey(fd,EV_ABS,ABS_Y,sy); //report position x,y
    	
	reportkey(fd,EV_ABS,ABS_PRESSURE,200); //report preeusre 200
	reportkey(fd,EV_KEY,BTN_TOUCH,1); //report touch preesed event
    		
	reportkey(fd,EV_SYN,2,0);
	reportkey(fd,EV_SYN,0,0);
	usleep(SILDING_DELAY);
	/**Report pressed-down event END----*/	
	
	nextPosX = sx;
	nextPosY = sy;
	if(ex == sx) // vertical Line
	{
		nextPosY = ey > sy ? (nextPosY + SILDING_STEP) : (nextPosY - SILDING_STEP);
		while (abs(nextPosY-sy)< abs(ey-sy)) 
		{
	
			reportkey(fd,EV_ABS,ABS_X,ex);
			//usleep(10000);
			reportkey(fd,EV_ABS,ABS_Y,nextPosY); //report position x,y
			//usleep(10000);
			reportkey(fd,EV_SYN,2,0);
			reportkey(fd,EV_SYN,0,0);
			usleep(SILDING_DELAY);
			nextPosY = ey > sy ? (nextPosY + SILDING_STEP) : (nextPosY - SILDING_STEP);
		}
	
		reportkey(fd,EV_ABS,ABS_X,ex);
		reportkey(fd,EV_ABS,ABS_Y,ey); //report position x,y			
		reportkey(fd,EV_ABS,ABS_PRESSURE,0);	//report preeusre 0
		reportkey(fd,EV_KEY,BTN_TOUCH,0);    //report touch release event
		reportkey(fd,EV_SYN,2,0);
		reportkey(fd,EV_SYN,0,0);
		
		return 0;
	}
	
	if(ey == sy) // 	horizontal Line
	{
		nextPosX = ex > sx ? (nextPosX + SILDING_STEP) : (nextPosX - SILDING_STEP);
		while (abs(nextPosX-sx)< abs(ex-sx))
		{
			reportkey(fd,EV_ABS,ABS_X,nextPosX);
			reportkey(fd,EV_ABS,ABS_Y,ey); //report position x,y			
			reportkey(fd,EV_SYN,2,0);
			reportkey(fd,EV_SYN,0,0);
			usleep(SILDING_DELAY);
			nextPosX = ex > sx ? (nextPosX + SILDING_STEP) : (nextPosX - SILDING_STEP);
		}
		reportkey(fd,EV_ABS,ABS_X,ex);
		reportkey(fd,EV_ABS,ABS_Y,ey); //report position x,y			
		reportkey(fd,EV_ABS,ABS_PRESSURE,0);	//report preeusre 0
		reportkey(fd,EV_KEY,BTN_TOUCH,0);    //report touch release event
		reportkey(fd,EV_SYN,2,0);
		reportkey(fd,EV_SYN,0,0);
		return 0;
	}
	
	printf("Siding from Point(%d,%d) to Point(%d,%d), this is A Oblique Line.\n",sx,sy, ex, ey);
	/*		
	
	
	//nextPosY = sy;
	nextPosX = ex > sx ? nextPosX + SILDING_STEP : nextPosX - SILDING_STEP;
	if (abs(nextPosX-sx)>= abs(ex-sx))
	{
	printf("(%d,%d) ",ex,nextPosY);
	nextPosY = ey > sy ? nextPosY + SILDING_STEP : nextPosY - SILDING_STEP;
				
	nextPosY = ((nextPosX - sx ) * (ey - sy) /(ex - sx) ) + sy ;
	}
	else
	{
	nextPosY = ((nextPosX - sx ) * (ey - sy) /(ex - sx) ) + sy ;	 
		
	}
	*/
	return 0;
}
int reportMouse(uint16_t type, uint16_t code, int32_t value) {
    if (!fd) {
        if (-1 == openEventdevice()) return -1;
    }
    return reportkey(fd, type, code, value);
}
int reportEvent(TOUCHPOSDATA *data)
{
	if (!data) {
		return closeEventdevice();
	}
	else {
		if (!fd) {
			if(-1==openEventdevice()) return -1;
		}
	}
	unsigned int ope = data->ope;
	unsigned int x1 = data->pos_x1;
	unsigned int y1 = data->pos_y1;
	unsigned int x2 = data->pos_x2;
	unsigned int y2 = data->pos_y2;
	printf("report (type:%d) (%d,%d) to Point(%d,%d),\n",ope,x1,y1, x2, y2);
	switch(ope)
	{
	case Press:
	{
		reportkey(fd,EV_ABS,ABS_X,x1);
		reportkey(fd,EV_ABS,ABS_Y,y1); //report position x,y

		reportkey(fd,EV_ABS,ABS_PRESSURE,1); //report preeusre 1
		reportkey(fd,EV_KEY,BTN_LEFT,1); //report touch preesed event 330 - BTN_TOUCH
		reportkey(fd,EV_SYN,2,0);
		reportkey(fd,EV_SYN,0,0); 
	}
	break;
	case Release:
	{
		reportkey(fd,EV_ABS,ABS_X,x1);
		reportkey(fd,EV_ABS,ABS_Y,y1); //report position x,y

		reportkey(fd,EV_KEY,BTN_LEFT,0);    //report touch release event
		reportkey(fd,EV_ABS,ABS_PRESSURE,0);  //report preeusre 0
	
		reportkey(fd,EV_SYN,2,0);
		reportkey(fd,EV_SYN,0,0);
	}
	break;
	case Slide:
	{ 
		reportSildingEvent(fd,x1,y1,x2,y2);
	}
	break;
	default:
		break;
	}
	return 0;
}

