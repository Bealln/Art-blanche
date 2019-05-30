# Art-blanche

This project contains the Art Blanche project code:
============
Technological aspect: Development of an articulated 2DOF robot which follows a spectator. Contains processing code in Python (Hand tracking, inverse kinematics) annd actuation code in C++.

Project overview:Study of user experience and tangible representations of human interactions with interactive installations. 

The work presented has been developed from October 2018 - May 2019.

Note the processing section of the code runs in Python 3.X and uses multiple libraries which should be imported for a correct functioning of the code - including numpy, scipy, matplotlib and opencv. The actuation section of the code runs in C++.

Contents
----------
The 2.The Artefact Technology contains four files, User input, kinematics, actuation and a folder of non used code, which contains code tested but disregarded. 

[User input](https://github.com/Bealln/Art-blanche/tree/master/2.%20The%20Artefact%20-Technology/1.%20User%20input) Contains the relevant documentation to track the spectators' hand position, exporting it as an x,y coordinate. The code used is the Handtracking foler. The original code was developed by Sasha Gaz(Link: https://github.com/Bealln/Hand_Detection) 


[Inverse kinematics](https://github.com/Bealln/Art-blanche/tree/master/2.%20The%20Artefact%20-Technology/3.%20Inverse%20kinematics) This folder multiple code files with inverse kinematics testing. The file (Art_blache_kinematics_code.py) contains the code combination of the user input and handtracking code, as well as the transformation of the angles calculated by the inverse kinematics into steps and the procedure to send the code to an Arduino through a serial port monitor. For the inverse kinamtics code, the library tinyk was used. (Link:https://github.com/lanius/tinyik)

[Actuation](https://github.com/Bealln/Art-blanche/tree/master/2.%20The%20Artefact%20-Technology/4.%20Actuation%20-%20Arduino%20)  This folder contains multiple files Arduino files including running a stepper motor or serial port monitor test. The folder Art_blanche_actuation contains the final code, which runs the motors obtaining the number of steps through a serial port communication. Also, it sets an LED to turn on when the Arduino receives a message.

