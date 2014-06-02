#include "joint.h"


RArm::RArm()
{
}
RArm::~RArm()
{
}



///Obtiene el angulo real dado por el kinect del movimiento del codo
float RArm::getElbowRoll(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation shoulder, elbow, hand;
	
	RArm finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_SHOULDER,shoulder);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_ELBOW,elbow);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_HAND,hand);
			
	return (finalAngle.getAngle(shoulder.position.position, elbow.position.position, hand.position.position));

}


float RArm::setElbowRoll(float angle){
	
	return (0);

}



float RArm::getShoulderRoll(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation elbow, shoulder, waist;
	
	RArm finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_ELBOW,elbow);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_SHOULDER,shoulder);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_WAIST,waist);
			
	return (finalAngle.getAngle(elbow.position.position, shoulder.position.position, waist.position.position));

}


float RArm::setShoulderRoll(float angle){
	
	return (0);

}

