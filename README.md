# ELEC3607_carparkproject
2017 ELEC3607 project9 (USYD):  

Team members: QISHEN GUAN 450549016  
              MINGYUAN XIA  


Manul: file fsm : code on arduino   
       file schematic: schematic of this project  
       

Project description :  
The prototype will be in 2 parts, Arduino Due board with a Bluetooth shield in slave mode and an android phone as a controller. There are also several hardware components connected to Arduino in order to complete the full features we expected. 

An android phone acts as a controller (An App will be developed for user); it sends and receives data to/from Arduino board, once the phone connected with the board via Bluetooth(BT), the number of available car parking and further instructions will be displayed on the screen. Once the phone sends command to reserve: available car parking will be updated, and a confirmation message will be received as well. When user wants to leave, send “leave” and billing information will be received. After payment has been confirmed, free to go!

The Arduino Due board takes actions upon commands received via BT. A LCD screen is connected to the board to display number of available car parking, the screen is refreshed at a certain frequency to make sure it updates on time. Once the board receives a command of “reserve”, the board sends a message to corresponding servomotor to open the door. Infrared(IR) senor is detecting whether user’s car has come in or not. After user’s car come in, the board control servomotor to close the door and a time counter starts to work to record the time, which will be used to calculate parking fee. When the board receives “leave” command, billing information can be sent via BT and the payment will be made through a push button (not real payment, for demonstration purpose only). Once payment came through, door opens again and the car is free to go! After the door back to close, available car parking updates again.






       
