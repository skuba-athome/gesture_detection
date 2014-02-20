/****************************************************************************
*                                                                           *
*  OpenNI 1.x Alpha                                                         *
*  Copyright (C) 2011 PrimeSense Ltd.                                       *
*                                                                           *
*  This file is part of OpenNI.                                             *
*                                                                           *
*  OpenNI is free software: you can redistribute it and/or modify           *
*  it under the terms of the GNU Lesser General Public License as published *
*  by the Free Software Foundation, either version 3 of the License, or     *
*  (at your option) any later version.                                      *
*                                                                           *
*  OpenNI is distributed in the hope that it will be useful,                *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             *
*  GNU Lesser General Public License for more details.                      *
*                                                                           *
*  You should have received a copy of the GNU Lesser General Public License *
*  along with OpenNI. If not, see <http://www.gnu.org/licenses/>.           *
*                                                                           *
****************************************************************************/
//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <ros/ros.h>
#include <ros/package.h>
#include "std_msgs/String.h"
#include "geometry_msgs/PointStamped.h"
#include "NiHandViewer.h"

using std::string;
//std::string state ="--";
//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define SAMPLE_XML_PATH "../../../../Data/SamplesConfig.xml"


//---------------------------------------------------------------------------
// Globals
//---------------------------------------------------------------------------
xn::Context		g_context;
xn::ScriptNode	g_scriptNode;

ros::Publisher chatter_pub;


int main(int argc, char* argv[])
{
	XnStatus				rc;
	xn::EnumerationErrors	errors;
   	
	ros::init(argc, argv, "openni_hand_tracker");
    	ros::NodeHandle nh;
	//chatter_pub = nh.advertise<std_msgs::String>("/gesture/point", 1000);
	chatter_pub = nh.advertise<geometry_msgs::PointStamped>("/gesture_raw", 1000);
    	//string configFilename = ros::package::getPath("openni_tracker") + "/openni_tracker.xml";
    	string configFilename = "/home/skuba/skuba_athome/Gesture/SamplesConfig.xml";
	ROS_INFO(configFilename.c_str());
    	rc = g_context.InitFromXmlFile(configFilename.c_str());
 
	// Create a context with default settings
	//rc = g_context.InitFromXmlFile(SAMPLE_XML_PATH, g_scriptNode, &errors);
	if (rc == XN_STATUS_NO_NODE_PRESENT)
	{
		XnChar strError[1024];
		errors.ToString(strError, 1024);
		printf("%s\n", strError);
		return (rc);
	}
	else if (rc != XN_STATUS_OK)
	{
		printf("Open failed: %s\n", xnGetStatusString(rc));
		return (rc);
	}
	ROS_INFO("Init Pass");

	SimpleViewer& viewer = HandViewer::CreateInstance(g_context);

	rc = viewer.Init(argc, argv);
	if (rc != XN_STATUS_OK)
	{
		printf("Viewer init failed: %s\n", xnGetStatusString(rc));
		return 1;
	}

	rc = viewer.Run();
	if (rc != XN_STATUS_OK)
	{
		printf("Viewer run failed: %s\n", xnGetStatusString(rc));
		return 1;
	}
	ros::Rate r(30);
	while(ros::ok()){
		g_context.WaitAndUpdateAll();
		r.sleep();
	}

	return 0;
}
