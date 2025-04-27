# Arduino-Car-System-Simulation
![image](https://github.com/user-attachments/assets/4a81278d-a8f3-4a53-b2da-904ed330912a)

Project Overview

This project simulates a smart vehicle interior security and control system using Arduino and Proteus.
It aims to replicate the safety and comfort features found in modern cars on a microcontroller-based platform.
Features

    Engine Start and Seatbelt Check:

        The engine cannot start unless the seatbelt is fastened.

        Buzzer and red LED activate if the seatbelt is unfastened.

        Informative messages are displayed on the LCD.

    Temperature Monitoring and Automatic Air Conditioning:

        When the interior temperature exceeds 25°C, the air conditioning (simulated by a DC motor) is automatically activated.

        Real-time temperature readings are shown on the LCD.

    Automatic Headlight Control:

        Lights (blue LED) turn on automatically in low light conditions detected by an LDR sensor.

        LCD updates with headlight status messages.

    Fuel Level Monitoring:

        Simulated using a potentiometer.

        If fuel level drops below 10%, a yellow LED warns the driver.

        Critical warnings at fuel levels below 5% and complete engine shutdown at 0%.

    Door Status Monitoring:

        If the door is open, the engine will not start.

        Pink LED and LCD alerts notify the driver of the open door.

Components Used

    Microcontroller: Arduino Mega 2560

    Input Components:

        Motor Start Button

        Seatbelt Button

        Temperature Sensor (LM35)

        Light Sensor (LDR)

        Potentiometer (for fuel level simulation)

        Switch (for door status detection)

    Output Components:

        16x2 LCD Display

        LEDs:

            Red LED (Seatbelt warning)

            Blue LED (Headlight indicator)

            Yellow LED (Fuel warning)

            Pink LED (Door open warning using RGB LED)

        Buzzer (Audio alerts)

        DC Motor (Engine and Air Conditioning fan simulation)

Technologies

    Arduino IDE

    Proteus Design Suite

Setup and Installation

    Clone this repository

    Open the .ino file in the Arduino IDE.

    Upload the code to the Arduino Mega 2560 board or launch Proje 2.pdsprj in proteus.

    Link the .hex file to the board and start the simulation.

Usage

    Press the Motor Start button to attempt to start the engine.

    Fasten the seatbelt to allow engine start.

    Monitor temperature, light, fuel, and door status via the LCD screen and indicator LEDs.

License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0) license.
