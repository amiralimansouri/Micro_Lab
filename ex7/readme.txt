exp:
for the left atmega which has the motor and temperature sensor, as the consoles show if you enter a valid number, the motor starts to spin
and when it reaches the amount which the user has entered, it stops.
also if the user enteres "t" as for temperature, the temp will be shown on the lcd. 
and if the user enters anything else, "invalid input" will be shown on the lcd and the user has to enter another input.
all this has been done using terminals. the data goes throw the d0 and d1 pin of the atmega.
another thing is whatever you type on your keyboard will be visible on the other console of virtual terminal.
the other atmega has the keypad connected to its A port. and the lcd to B port. and in a loop, it changes the amount of declared pins with a 
fast pace, so when you push a button on the keypad... the it will be simultaneous with the change of one pin. so it can know what it should 
print on the lcd. i had some problem sending the data from one atmega to the other. and i think the reason is that i did all the work on the other atmega
first and couldnt adapt everything with another method.
thank you