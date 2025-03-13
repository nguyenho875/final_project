## Secure Elevator Control System: 
James Dwyer, Nguyen Ho

## System Behavior:
The Security-Enhanced Elevator System ensures secure access within residential buildings by using personalized PIN codes assigned uniquely to each resident and authorized individual. 
When a user presses the elevator request button, the elevator returns to the first floor if it isn't already there, and an LCD display prompts the user to enter their PIN. 
Upon successful entry, verified against pre-stored codes, the user's name and designated floor appear on the LCD, the green LED activates, and the elevator moves to the corresponding floor. 
If the entered PIN is incorrect, a red LED indicates failure, and after three unsuccessful attempts, the system temporarily locks out further input for one minute. 
This approach enhances security by eliminating risks associated with traditional keys or cards, while providing ease of use and peace of mind for residents.

## Design Alternatives:
In the development of our elevator security system, we faced several critical design decisions regarding motor selection and user authentication methods. 
We chose a gear motor instead of a positional or continuous servo motor due to the gear motor's strength and reliability in lifting the elevator box vertically between floors. 
While positional servo motors offer precise angular positioning and continuous servos facilitate simple speed adjustments, neither provided sufficient torque and linear movement simplicity needed for our elevator mechanism. 
Ultimately, the gear motor's robust lifting capability and straightforward integration outweighed the precision angular control provided by servos. 
<br/>
Another key decision involved user authentication; we selected a keypad entry system over a fingerprint scanner due to practical constraints. 
Although fingerprint scanners provide enhanced security through biometric verification, our selected fingerprint scanner lacked an existing Mbed-compatible library. 
Integrating it would have required either extensive modifications to convert existing libraries or implementing an additional microcontroller, increasing both complexity and potential points of failure. 
The keypad solution provided seamless integration with our existing Mbed-based system, offering sufficient security without the added complexity.

![image](https://github.com/user-attachments/assets/210d9014-db3d-400b-82c3-6084077cbcb5)
![image](https://github.com/user-attachments/assets/4c90974b-b36b-4c09-9bb0-1bf34446c235)


## Modular design:
The code consists of modules for all compoenents in the system such as LEDs, motor, button, matrix keypad and LCD display, and two additional modules, namely user interface and elevator systme. The fully functional elevator system module was broken up based on the order of operation and interaction of the user with system, which include everything that happends before the user is requried to enter their code through the matrix keypad to authorize access, the authorization process, and everything after authorization is over, varying based on the result. The entire authorization process is performed by the matrix keypad module (most importantly the keypadUpdate() function), while the operation of the rest of the system (LEDs, motor, display, button) before and after authorization is controlled by the user interface module. The LCD display is involved to communicate with the user across all steps, so functions from this module are called from both the user intereface and matrix keypad modules. 
<br/> <br/>
![IMG_C9B084701AB8-1](https://github.com/user-attachments/assets/bd9deab0-9252-4e85-a208-1407cdbd69ea)



