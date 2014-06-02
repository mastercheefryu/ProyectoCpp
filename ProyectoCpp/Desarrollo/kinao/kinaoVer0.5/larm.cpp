#include "joint.h"


LArm::LArm()
{
}
LArm::~LArm()
{
}



///Obtiene el angulo real dado por el kinect del movimiento del codo
float LArm::getElbowRoll(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation shoulder, elbow, hand;
	
	LArm finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_SHOULDER,shoulder);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_ELBOW,elbow);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_HAND,hand);
			
	return (finalAngle.getAngle(shoulder.position.position, elbow.position.position, hand.position.position));

}


float LArm::setElbowRoll(float angle){
	
	return (0);

}


float LArm::getShoulderRoll(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation elbow, shoulder, waist;
	
	LArm finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_ELBOW,elbow);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_SHOULDER,shoulder);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_WAIST,waist);
			
	return (finalAngle.getAngle(elbow.position.position, shoulder.position.position, waist.position.position));

}


float LArm::setShoulderRoll(float angle){
	
	return (0);

}
