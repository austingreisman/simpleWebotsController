# For ticket 6699 on the https://github.com/cyberbotics/webots/issues/6699

This code implements a simple controller that will command a semi-custom Webots Tesla Model 3 vehicle (has a GPS) to move forward at 50 m/s.

This code is to plot the relationship between calculated Wheel Speed to get drive line data vs. using GPS speed.

Here is a sample of the plotted data from the `plotCompareSpeeds.py` file
![image](https://github.com/user-attachments/assets/ca7bb9c8-62e4-422e-a5c9-b7c050458471)

Where TS stands for Timestep.

## How to run
1. Open up your Webots R2023b
2. Open up the world in the world folder
  > It should have loaded the `my_controller` in the TeslaModel
3. You can then run the simulation. Once the robot reaches a steady state, you can pause the simulation and run the `plotCompareSpeeds.py` script to view a comparsion of the speeds between drive line and the gps over time.

I would recommend varying the `basicTimeStep` value in the webots simulation world to re-create the ticket situations.
 > Everytime you change the `basicTimeStep` it will create a new file name, you will need to change the file the Python script looks at each time you do this.
