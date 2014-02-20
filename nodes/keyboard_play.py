#!/usr/bin/env python

'''
        Mealy State Machine
'''

import roslib; roslib.load_manifest('Gesture')
import rospy
import math
import os
import cv

from geometry_msgs.msg import Pose2D,Twist,Vector3
from std_msgs.msg import String

cv.ShowImage('Keyboard',None)
rospy.init_node('keyboard')

send = rospy.Publisher('cmd_vel',Twist)
vel_com = Twist()

vel_x = 0.4
vel_y = 0.4
ang_z = 0.3

try:
	while True:
		temp = cv.WaitKey(100)
	#	print temp
		if(temp == 97 or temp == 65432):
			vel_com.linear.x = 0.0
			vel_com.linear.y = vel_y
			vel_com.angular.z = 0.0
		elif(temp == 119 or temp == 65431):
			vel_com.linear.x = vel_x
			vel_com.linear.y = 0.0
			vel_com.angular.z = 0.0
		elif(temp == 115 or temp == 65437):
			vel_com.linear.x = -vel_x
			vel_com.linear.y = 0.0
			vel_com.angular.z = 0.0
		elif(temp == 100 or temp == 65430):
			vel_com.linear.x = 0.0
			vel_com.linear.y = -vel_y
			vel_com.angular.z = 0.0
		elif(temp == 113 or temp == 65429):
			vel_com.linear.x = 0.0
			vel_com.linear.y = 0.0
			vel_com.angular.z = ang_z
		elif(temp == 101 or temp == 65434):
			vel_com.linear.x = 0.0
			vel_com.linear.y = 0.0
			vel_com.angular.z = -ang_z
		elif(temp == 27):
			exit(0)
		else:
			vel_com.linear.x = 0.0
			vel_com.linear.y = 0.0
			vel_com.angular.z = 0.0
		send.publish(vel_com)
except:
        pass

