import tinyik
import numpy as np
import json

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
Positions = open('hand_position.txt', 'r').readlines()
#IMPORT VALUES IS NOT WORKING
x= 50
y = 20
print(x,y)

def updatedangles(): 
    #Desired position in cm - This would be inputed by the Handtracking code
    arm.ee = [x, y, 0.]

            #I can also specify the position in radians, in which case I dont need to change it to degrees. 
            ## arm.ee = [2 / np.sqrt(2), 2 / np.sqrt(2), 0.]

    #The angles are calculates in radians
    print("Angles in radian", arm.angles)
    #This changes radians to degrees
    arm.angles = np.round(np.rad2deg(arm.angles))
    print("Angles in degrees", arm.angles)
    stepperA_angle = arm.angles[0]
    stepperB_angle = arm.angles[1]
    print(stepperA_angle,stepperB_angle)
    
    stepsA = stepperA_angle/stepperA_resolution
    stepsB= stepperB_angle/stepperB_resolution
    print(stepsA,stepsB)
    
    #f = open('steps.txt', 'wb')
    #f.write("%.2f %.2f" % (stepsA, stepsB)

    steps = stepsA, stepsB
    with open('steps.txt', 'w') as f:  
        json.dump(steps, f)

    #Testing a new position
    #arm.ee = [3, 30, 0.]
    #print("Angles in degrees", arm.angles)




if __name__ == '__main__':

    updatedangles()