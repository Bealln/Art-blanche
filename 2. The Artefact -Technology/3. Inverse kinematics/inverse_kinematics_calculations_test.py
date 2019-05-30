import tinyik
import numpy as np
import json

"""
    To do:
        Something is wrong. When the end effector is at a new position (ig, 50,20) and you send it to the same place (x=50, y=20) 
        It does the calculations again! So either position = old position-new position (to calculate the real new position) of the
        endeffector or the new angles - old angles? 

"""


"""""
    PARAMETERS
    
    We will define the arm, which rotates around the z axis. The fist arm is 35 cm and the second 30 cm
    The default starting angles will be 0,0 and the end effector position [65,0,0]
"""


arm = tinyik.Actuator(['z', [35., 0., 0.], 'z', [30., 0., 0.]])
print("Starting angles", arm.angles)
print("Starting end effector possition", arm.ee)
stepperA_resolution= 1.8  #steps = 200
stepperB_resolution = 0.9  #steps = 400

x= [61, 61, 12, 40]
y = [22, 22, 35, 40]

#print(range(len(x)))

print("New position", x,y)

def updatedangles(x=x,y=y): 
    #Desired position in cm - This would be inputed by the Handtracking code
    print("old position", arm.ee)
    p_angles = arm.angles
    arm.ee = [x, y, 0.]

            #I can also specify the position in radians, in which case I dont need to change it to degrees. 
            ## arm.ee = [2 / np.sqrt(2), 2 / np.sqrt(2), 0.]

    #The angles are calculates in radians
    print("Angles in radian", arm.angles)
    d_angles = p_angles - arm.angles
    #This changes radians to degrees
    angles_in_degrees = np.round(np.rad2deg(d_angles))
    #print("Angles in degrees", arm.angles)
    stepperA_angle = angles_in_degrees [0]
    stepperB_angle = angles_in_degrees [1]
    print("New angles, in degrees",stepperA_angle,stepperB_angle)
    
    stepsA = stepperA_angle/stepperA_resolution
    stepsB= stepperB_angle/stepperB_resolution
    print("New steps", stepsA,stepsB)

    print("End effector is now in", arm.ee)

    
for i in range(len(x)):
    print("----------------------")
    print(i)
    updatedangles(x=x[i], y=y[i])
     
