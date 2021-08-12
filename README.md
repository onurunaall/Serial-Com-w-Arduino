# Serial-Com-w-Arduino

It is possible to control an Arduino Uno connected to a computer using this interface. There are multiple ways of serial communication with Arduino or any device. However, the most efficient of these is to send the data in a package. This has been done in this project. While the data set from the interface is sent to the Arduino, they are automatically packaged by the program. Arduino checks incoming data and executes instructions using these communication packages.

In order to make serial communication, communication must be created between the computer, that is, the main machine and Arduino. This communication is done through COM ports. When any device that will communicate with the computer is connected to the computer, the computer communicates with that device via a COM port. The first thing done in this project was to write the interface for this COM port and the necessary program. Communication with Arduino was established using the COM port selected from the interface. The code for pairing this COM port with the computer and Arduino can be seen under the C code. Then the Baud Rate should be selected. Baud Rate is the communication frequency of the main machine and the machine that communicates with. 1 / (Baud Rate) gives information about how long it takes to transfer 1 bit during communication. Although more than one baud rate can be selected in this study, since communication with Arduino is made, 9600 should be selected at the interface because the microcontroller on the Arduino, Atmega328-PU, is designed to communicate with 9600 Baud Rate and cannot communicate at higher frequencies. However, as will be seen in subsequent studies, the Baud Rate concept cannot be limited to 9600.

In the continuation of the program, after selecting the relevant COM port and Baud Rate, press the Open button to activate the communication channel. In the lower-left dialogue box, there are feedbacks received according to the given directives. In other words, after the communication channel is activated, a message that communication has been activated comes here. LED buttons, on the other hand, are the keys to turn the LEDs connected to the Arduino on and off. For example, when the LED1 button is pressed, the program will prepare the relevant communication package and send it to Arduino on the serial communication channel. Arduino will analyze the incoming package, detect that the package is related to the opening of LED1 and activate the corresponding LED.

Button Status is made to understand whether the program can use the communication channel fully. At this point, it is Arduino, not the computer that sends the orders in communication. Within the scope of the project, there are 5 buttons attached to Arduino. If one of these buttons is activated, the information that the relevant button is active is sent to the computer. The computer processes the incoming data and reflects it to the graphical interface and informs the user which button is activated.

In the last part of this project, a program was written that instantly sends the values of a potentiometer attached to the Arduino. In other words, the value of the potentiometer is sent to the computer whenever it wants. So the voltage on the potentiometer and if desire, the value of the potentiometer can be read from the computer, ie. from the graphic interface. The C code and related C header file related to this work are shared below.

The interface I created for the related project can be seen below;
![image](https://user-images.githubusercontent.com/74546805/129174180-7fd11fd4-c052-44f5-9226-4812485407a5.png)

