#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_QUITBUTTON                 2       /* control type: command, callback function: QuitCallback */
#define  PANEL_iLBBaudRateList            3       /* control type: listBox, callback function: (none) */
#define  PANEL_iLBComPortList             4       /* control type: listBox, callback function: (none) */
#define  PANEL_iBComPortClose             5       /* control type: command, callback function: OnCloseComPortPressed */
#define  PANEL_iBComPortOpen              6       /* control type: command, callback function: OnOpenComPortPressed */
#define  PANEL_aTBComPortStatus           7       /* control type: textBox, callback function: (none) */
#define  PANEL_iBLed6                     8       /* control type: textButton, callback function: OnLed6Pressed */
#define  PANEL_iBLed4                     9       /* control type: textButton, callback function: OnLed4Pressed */
#define  PANEL_iBLed7                     10      /* control type: textButton, callback function: OnLed7Pressed */
#define  PANEL_iBLed5                     11      /* control type: textButton, callback function: OnLed5Pressed */
#define  PANEL_iBLed3                     12      /* control type: textButton, callback function: OnLed3Pressed */
#define  PANEL_iLED12                     13      /* control type: LED, callback function: (none) */
#define  PANEL_iLED13                     14      /* control type: LED, callback function: (none) */
#define  PANEL_iLED11                     15      /* control type: LED, callback function: (none) */
#define  PANEL_iLED10                     16      /* control type: LED, callback function: (none) */
#define  PANEL_iLED9                      17      /* control type: LED, callback function: (none) */
#define  PANEL_fPotVoltage                18      /* control type: scale, callback function: (none) */
#define  PANEL_DECORATION                 19      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_2               20      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_3               21      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_4               22      /* control type: deco, callback function: (none) */
#define  PANEL_fPotResistance             23      /* control type: scale, callback function: (none) */
#define  PANEL_TEXTMSG                    24      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_2                  25      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_4                  26      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_3                  27      /* control type: textMsg, callback function: (none) */
#define  PANEL_ArduinoMatchingButton      28      /* control type: command, callback function: arduinoMatchingButton */
#define  PANEL_iPotAtoDVal                29      /* control type: string, callback function: (none) */
#define  PANEL_iPotControlClose           30      /* control type: command, callback function: iPotControlPressedClose */
#define  PANEL_iButtonControlOFF          31      /* control type: command, callback function: iButtonStateControlPressedOFF */
#define  PANEL_iButtonStatesControl1      32      /* control type: command, callback function: iButtonStateControlPressedON */
#define  PANEL_iPotControl                33      /* control type: command, callback function: iPotControlPressed */
#define  PANEL_ButtonControlOn            34      /* control type: textMsg, callback function: (none) */
#define  PANEL_ButtonControlClose         35      /* control type: textMsg, callback function: (none) */
#define  PANEL_PotControlOpen_3           36      /* control type: textMsg, callback function: (none) */
#define  PANEL_PotControlOpen_2           37      /* control type: textMsg, callback function: (none) */
#define  PANEL_PotControlOpen             38      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK arduinoMatchingButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK iButtonStateControlPressedOFF(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK iButtonStateControlPressedON(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK iPotControlPressed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK iPotControlPressedClose(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnCloseComPortPressed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnLed3Pressed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnLed4Pressed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnLed5Pressed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnLed6Pressed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnLed7Pressed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnOpenComPortPressed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
