 # **Voice command**

- Ver em [Português 🇧🇷](./README.md).

![Capturar4](https://user-images.githubusercontent.com/79997705/115067227-fd944d00-9ec6-11eb-877f-e2678627c54f.PNG)

## Project components

- Arduino UNO;
- V3 speech recognition module;
- Relay module 4 channels;
- 400-pin protoboard;
- Jumpers;
- 6 Led's indicators;
- 2 pushbuttons;
- Speaker;
- 330Ω resistors;
- 1kΩ resistors;
- LDR resistor;

  ## Application languages
  
![image](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

## Project's Schematic
![Capturar3](https://user-images.githubusercontent.com/79997705/115067241-008f3d80-9ec7-11eb-8692-587b194c557e.PNG)

## How to use?

It is possible to configure up to seven commands, which can be selected using the white button. Once the command number has been selected, it can be recorded or rewritten by clicking on the green button.

When speaking the command to be recorded, the ideal is to speak normally and clearly. The yellow LED on the module indicates the start of the recording process. The command must be said as soon as the red led is on. The command is spoken only once and then, it waits for the red led to be on again. When the two LEDs flash together, the registration was done correctly.

At the end of a new recording it is necessary to click on the white button for the commands to be loaded. When the commands are loaded, the yellow LED of the module is flashing, indicating that the card is already capturing what the user is saying. If the board recognizes a command, the code snippet for it is executed in Arduino.
  
***
 ![image](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white) 
 
 Visit my [LinkedIn](https://www.linkedin.com/in/nathan-de-souza-silva-firmo/). 


