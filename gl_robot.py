#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
import time

import zmq



def move():
    # Starts a new node
    rospy.init_node('robot_cleaner', anonymous=True)
    velocity_publisher = rospy.Publisher('cmd_vel_mux/input/navi', Twist, queue_size=10)
    vel_msg = Twist()
    
    #Receiveing the user's input
    print("Let's move  robot")
    speed = 0.2
    distance = 0.8
    isForward = True
    
    #Checking if the movement is forward or backwards
    if(isForward):
        vel_msg.linear.x = abs(speed)
    else:
        vel_msg.linear.x = -abs(speed)
    #Since we are moving just in x-axis
    vel_msg.linear.y = 0
    vel_msg.linear.z = 0
    vel_msg.angular.x = 0
    vel_msg.angular.y = 0
    vel_msg.angular.z = 0
    
    while not rospy.is_shutdown():

        #Setting the current time for distance calculus
        t0 = rospy.Time.now().to_sec()
        current_distance = 0

	print 'inside first while'
        velocity_publisher.publish(vel_msg)

        #Loop to move the turtle in an specified distance
        while(current_distance < distance):
            #Publish the velocity
            velocity_publisher.publish(vel_msg)
            #Takes actual time to velocity calculus
            t1=rospy.Time.now().to_sec()
            #Calculates distancePoseStamped
            current_distance= speed*(t1-t0)
	    print 'second while'
	    print current_distance
	    

            # socket.send("Hello")
            socket.send(str(current_distance))

            # Get the reply.
            message = socket.recv()


        #After the loop, stops the robot
        vel_msg.linear.x = 0
 	print 'after second while'
        #Force the robot to stop
        velocity_publisher.publish(vel_msg)

def moveWithout():
    # Starts a new node
    rospy.init_node('robot_cleaner', anonymous=True)
    velocity_publisher = rospy.Publisher('cmd_vel_mux/input/navi', Twist, queue_size=10)
    vel_msg = Twist()
    
    #Receiveing the user's input
    print("Let's move your robot")
    speed = 0.14
    distance = 0.5
    isForward = True
    
    #Checking if the movement is forward or backwards
    if(isForward):
        vel_msg.linear.x = abs(speed)
    else:
        vel_msg.linear.x = -abs(speed)
    #Since we are moving just in x-axis
    vel_msg.linear.y = 0
    vel_msg.linear.z = 0
    vel_msg.angular.x = 0
    vel_msg.angular.y = 0
    vel_msg.angular.z = 0
    


    #Setting the current time for distance calculus
    t0 = rospy.Time.now().to_sec()
    current_distance = 0

    print 'inside first while'
    velocity_publisher.publish(vel_msg)

    #Loop to move the turtle in an specified distance
    while(current_distance < distance):
        #Publish the velocity
        velocity_publisher.publish(vel_msg)
        #Takes actual time to velocity calculus
        t1=rospy.Time.now().to_sec()
        #Calculates distancePoseStamped
        current_distance= speed*(t1-t0)
	print 'second while'
	print current_distance
        
        #print "Sending request ", request, "..."
        # socket.send("Hello")
        socket.send(str(current_distance))

        # Get the reply.
        message = socket.recv()
    	print "Received reply ", "[", message, "]"


    #After the loop, stops the robot
    vel_msg.linear.x = 0
    print 'after second while'
    #Force the robot to stop
    velocity_publisher.publish(vel_msg)

if __name__ == '__main__':
    try:
        #Testing our function
        #move()
        context = zmq.Context()

        # Socket to talk to server
        print "Connecting to hello world server..."
        socket = context.socket(zmq.REQ)
        socket.connect("tcp://localhost:5555")
    	i = 0
    	while i < 2:
      		moveWithout()
      		time.sleep(5)
      		print(i)
      		i += 1
    except rospy.ROSInterruptException: pass
