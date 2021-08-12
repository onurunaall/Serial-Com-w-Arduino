// Include files
#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
#include "arduino.h"
#include "toolbox.h"
#include <rs232.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

// Static global variables
static int panelHandle;
static int iOpenedComPort;
static int iOpenedBaudRate;
static int iOpenComPortStatus=0;
static int iButtonState; 
static int counter=0;
static int interrupt=0;
static int button_interrupt=0;

//==============================================================================
void ComPortReceiveCallback(int portNumber, int eventMask, void *callbackdata);
void ParseData(char *inBuffer);
void ParseButton(char *inBuffer);
void ParsePot(char *inBuffer);

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
    int error = 0;
    
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "User Interface Applicationhbihijm,.uir", PANEL));
    
    /* display the panel and run the user interface */
    errChk (DisplayPanel (panelHandle));
    errChk (RunUserInterface ());

Error:
    /* clean up */
    DiscardPanel (panelHandle);
    return 0;
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.

int CVICALLBACK panelCB (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
	}
	return 0;
}

int CVICALLBACK QuitCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface(0);
			break;
	}
	return 0;
}

int CVICALLBACK OnOpenComPortPressed (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int iSelectedComPort=0;
	int iSelectedBaudRate=0;
	int iComPortOpenError=0;
	char* fail_error1;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(PANEL,PANEL_iLBBaudRateList,&iSelectedBaudRate);
			for(int i=1;i<=60;i++){
				iSelectedComPort=i;
				iComPortOpenError=OpenComConfig (iSelectedComPort,"",iSelectedBaudRate,0,8,1,512,512);	
			
				if(iComPortOpenError>=0){
					//success
					SetCtrlVal(PANEL,PANEL_aTBComPortStatus,"COM Port has been opened succesfully.\r\n");
					SetCtrlVal(PANEL,PANEL_aTBComPortStatus,"Selected Baud Rate has been opened succesfully.\r\n");
					iOpenComPortStatus=1;
					SetCtrlAttribute(PANEL,PANEL_iBComPortOpen,ATTR_DIMMED,1);
					SetCtrlAttribute(PANEL,PANEL_iBComPortClose,ATTR_DIMMED,0);
					iOpenedComPort=iSelectedComPort;
					iOpenedBaudRate=iSelectedBaudRate;
					break;
				}
				else{
					SetCtrlVal(PANEL,PANEL_aTBComPortStatus,"Failed to Open Selected COM Port\r\n");
					iOpenComPortStatus=0;
					fail_error1=GetRS232ErrorString (iComPortOpenError);
					SetCtrlVal(PANEL,PANEL_aTBComPortStatus,fail_error1);
					break;
				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnCloseComPortPressed (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int iCloseComPortError=0;
	char* fail_error2;
	switch (event)
	{
		case EVENT_COMMIT:
			if(iOpenComPortStatus==1){
				iCloseComPortError=CloseCom(iOpenedComPort);
				if(iCloseComPortError>=0){
					//success
					iOpenComPortStatus=0;
					SetCtrlVal(PANEL,PANEL_aTBComPortStatus,"Selected COM Port Has Been Closed Succesfully\r\n");
					SetCtrlAttribute(PANEL,PANEL_iBComPortOpen,ATTR_DIMMED,0);
					SetCtrlAttribute(PANEL,PANEL_iBComPortClose,ATTR_DIMMED,1);
					iOpenedComPort=0;
					iOpenedBaudRate=0;
				}
				else{
					SetCtrlVal(PANEL,PANEL_aTBComPortStatus,"Failed to Close Selected Com Port\r\n");
					fail_error2=GetRS232ErrorString (iCloseComPortError);
					SetCtrlVal(PANEL,PANEL_aTBComPortStatus,fail_error2);
				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK arduinoMatchingButton (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int m;
	int n;
	char sentinfo;
	char readBuf;
	char startMarker='<';
	char endMarker='>';
	switch (event)
	{
		case EVENT_COMMIT:
			
			if(iOpenComPortStatus==1){
				FlushInQ(iOpenedComPort);
				sentinfo='a'; 
				m=ComWrt(iOpenedComPort,sentinfo,1);
				n=ComRd(iOpenedComPort,readBuf,1);
				if(readBuf=='b'){
				SetCtrlVal(PANEL,PANEL_aTBComPortStatus,"Arduino and Sender Machine Has Been Matched.");
				}
				else{
				SetCtrlVal(PANEL,PANEL_aTBComPortStatus,"Arduino and Sender Machine Cannot Be Matched.");
				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnLed3Pressed (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	iButtonState=0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(PANEL,PANEL_iBLed3,&iButtonState);
			if(iOpenComPortStatus==1){
				if(iButtonState==1){
					ComWrt(iOpenedComPort,'3',1);
				}
				else{
					ComWrt(iOpenedComPort,'8',1);
				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnLed4Pressed (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	iButtonState=0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(PANEL,PANEL_iBLed4,&iButtonState);
			if(iOpenComPortStatus==1){
				if(iButtonState==1){
					ComWrt(iOpenedComPort,'4',1);
				}
				else{
					ComWrt(iOpenedComPort,'9',1);
				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnLed5Pressed (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	iButtonState=0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(PANEL,PANEL_iBLed5,&iButtonState);
			if(iOpenComPortStatus==1){
				if(iButtonState==1){
					ComWrt(iOpenedComPort,'5',1);
				}
				else{
					ComWrt(iOpenedComPort,'0s',1);
				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnLed6Pressed (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	iButtonState=0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(PANEL,PANEL_iBLed6,&iButtonState);
			if(iOpenComPortStatus==1){
				if(iButtonState==1){
					ComWrt(iOpenedComPort,"Hello World",13);
				}
				else{
					ComWrt(iOpenedComPort,'2',1);
				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnLed7Pressed (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	iButtonState=0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(PANEL,PANEL_iBLed7,&iButtonState);
			if(iOpenComPortStatus==1){
				if(iButtonState==1){
					ComWrt(iOpenedComPort,'7',1);
				}
				else{
					ComWrt(iOpenedComPort,'1',1);
				}
			}
			break;
	}
	return 0;
}						  
																				
int CVICALLBACK iPotControlPressed (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char receivedInfo[5];										   
	char* sPotVal;
	char startMarker='<';
	char endMarker='>';
	char* iPotAtoDValue;
	double iPotVal=0;
	int potPotPot;
	
	switch (event)
	{
		case EVENT_COMMIT:
				if(iOpenComPortStatus==1){
					FlushInQ(iOpenedComPort);	
					while(1){
						iPotAtoDValue=0;
						potPotPot=ComRd(iOpenedComPort,receivedInfo,5);
						iPotAtoDValue=receivedInfo;
						
						if(iPotAtoDValue[0]==startMarker && iPotAtoDValue[4]==endMarker){
							SetCtrlVal(PANEL,PANEL_iPotAtoDVal,"%c%c%c",iPotAtoDValue[1],iPotAtoDValue[2],iPotAtoDValue[3]);
							
							for(int w=1;w<=3;w++){
								sPotVal[w]=iPotAtoDValue[w];
							}
							iPotVal=atof(sPotVal);
							SetCtrlVal(PANEL,PANEL_fPotVoltage,(((double)5/(double)1024)*iPotVal));
							SetCtrlVal(PANEL,PANEL_fPotResistance,(((double)100000/(double)1024)*iPotVal));
						}
						
						if(interrupt==1){
							iPotAtoDValue="0";
							iPotVal=0;
							FlushInQ(iOpenedComPort);
							FlushOutQ(iOpenedComPort);
							break;
						}
						else
							continue;
					}
				}
				break;
	}
	return 0;
}


int CVICALLBACK iPotControlPressedClose (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(iOpenComPortStatus==1){
					interrupt==1;
				}
			break;
	}
	return 0;
}

int CVICALLBACK iButtonStateControlPressedON (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	int k=0,t=0;
	int whichButtonNumber;
	char buttonStartMark='t';
	switch (event)
	{
		case EVENT_COMMIT:
			if(iOpenComPortStatus==1 && button_interrupt==0){
				FlushInQ(iOpenedComPort);
				k=ComWrt(iOpenedComPort,buttonStartMark,1);
				t=ComRd(iOpenedComPort,whichButtonNumber,sizeof(whichButtonNumber));
				if(whichButtonNumber==9 && button_interrupt==0){
					SetCtrlVal(PANEL,PANEL_iLED9,1);
				}
				else if(whichButtonNumber==10 && button_interrupt==0){
					SetCtrlVal(PANEL,PANEL_iLED10,1);
				}
				else if(whichButtonNumber==11 && button_interrupt==0){
					SetCtrlVal(PANEL,PANEL_iLED11,1);
				}
				else if(whichButtonNumber==12 && button_interrupt==0){
					SetCtrlVal(PANEL,PANEL_iLED12,1);
				}
				else if(whichButtonNumber==13 && button_interrupt==0){
					SetCtrlVal(PANEL,PANEL_iLED13,1);
				}
			}
			
			break;
	}
	return 0;
}

int CVICALLBACK iButtonStateControlPressedOFF (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(iOpenComPortStatus==1){
					button_interrupt=1;
				}
			break;
	}
	return 0;
}
	
void ComPortReceiveCallback(int portNumber, int eventMask, void *callbackdata){
	char inBuffer[100];
	int iComPortReadError=0;
	int strLen;
	
	switch(eventMask){
		case LWRS_RECEIVE:
			{
				iComPortReadError=ComRd(portNumber,inBuffer,6);
				if(iComPortReadError==6){
					
					if(ParseData(inBuffer[5]==10)){
						ParseData(inBuffer);
					}
				}
				else{
					FlushInQ(portNumber);
				}
				break;			  
		    }
		default:
		case LWRS_ERR:
			{
				FlushInQ(portNumber);
				break;
			}
}
	
void ParseData(char *inBuffer){
   switch(inBuffer[0]){
	   case 'I':
			{
			ParseButton(inBuffer);
			break;
			}
	   case 'P'
			{
			ParsePot(inBuffer);
			break;
			}
		}
	}
}

void ParseButton(char *inBuffer){
	 switch(inBuffer[1])
	 {
	 	case '0':
			{
				switch(inBuffer[2])
				{
					case '9':
						{
						 switch(inBuffer[3])
							 {
							 	case 'N':
									{
										SetCtrlVal(PANEL,PANEL_iLED9,1);
										break;
									}
								case 'F':
									{
										SetCtrlVal(PANEL,PANEL_iLED9,0);
										break;
									}
							 }
						 
						 break;
						}
				}
				break;
			}
		case '1':
			{
				switch(inBuffer[2])
				{
					case '0':
						{
						 switch(inBuffer[3])
							 {
							 	case 'N':
									{
										SetCtrlVal(PANEL,PANEL_iLED10,1);
										break;
									}
								case 'F':
									{
										SetCtrlVal(PANEL,PANEL_iLED10,0);
										break;
									}
							 }
						 
						 break;
						}
					case '1':
						{
						 switch(inBuffer[3])
							 {
							 	case 'N':
									{
										SetCtrlVal(PANEL,PANEL_iLED11,1);
										break;
									}
								case 'F':
									{
										SetCtrlVal(PANEL,PANEL_iLED11,0);
										break;
									}
							 }
						 
						 break;
						}
					case '2':
						{
						 switch(inBuffer[3])
							 {
							 	case 'N':
									{
										SetCtrlVal(PANEL,PANEL_iLED12,1);
										break;
									}
								case 'F':
									{
										SetCtrlVal(PANEL,PANEL_iLED12,0);
										break;
									}
							 }
						 
						 break;
						}
					case '3':
						{
						 switch(inBuffer[3])
							 {
							 	case 'N':
									{
										SetCtrlVal(PANEL,PANEL_iLED13,1);
										break;
									}
								case 'F':
									{
										SetCtrlVal(PANEL,PANEL_iLED13,0);
										break;
									}
							 }
						 
						 break;
						}
				}
			
				break;
			}
	 }
}


void ParsePot(char *inBuffer){
	char sHexConvert[30];
	int iPotAtoDValue=0;
	
	sHexConvert[0]='0';
	sHexConvert[1]='x';
	sHexConvert[2]=inBuffer[1];
	sHexConvert[3]=inBuffer[2];
	sHexConvert[4]=inBuffer[3];
	sHexConvert[5]=0;
	
	sscanf(buf,"%x",&iPotAtoDValue);
	
	SetCtrlVal(PANEL,PANEL_iPotAtoDVal,iPotAtoDValue);
	SetCtrlVal(PANEL,PANEL_fPotVoltage,(((float)5/(float)1024)*(float)iPotAtoDValue);
	SetCtrlVal(PANEL,PANEL_fPotResistance,(((float)100000/(float)1024)*(float)iPotAtoDValue));
	
}
