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


float RArm::setElbowRoll(float angle, float& MIN, float& MAX){
	if (angle>MAX) MAX=angle;								  
	if (angle<MIN) MIN=angle;
	return (-88.5+(angle-MIN)*(-2-88.5)/(MAX-MIN));
}


float RArm::getElbowYaw(XnUserID user, xn::UserGenerator guser)
{
	/*
	XnSkeletonJointTransformation shoulder, elbow, hand;
	
	LArm finalAngle, refAx;
	XnReferenceAxis elbowRefAx;
	XnVector3D elToHand, proyVectorZ, pImag, proyVectorPlane, pastShoulder, pastElbow, pastHand;
	
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_SHOULDER,shoulder);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_ELBOW,elbow);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_HAND,hand);
	
	
	pastShoulder = shoulder;
	
	elbowRefAx = refAx.generateReference(pastShoulder, pastElbow, pastHand);
	
	elToHand.X = hand.position.position.X-elbow.position.position.X;
	elToHand.Y = hand.position.position.Y-elbow.position.position.Y;
	elToHand.Z = hand.position.position.Z-elbow.position.position.Z;
	
	proyVectorZ = getProyectionVector(elToHand, elbowRefAx.NewZ);
	pImag.X = proyVectorZ.X + elbow.position.position.X;
	pImag.Y = proyVectorZ.Y + elbow.position.position.Y;
	pImag.Z = proyVectorZ.Z + elbow.position.position.Z;
	
	proyVectorPlane.X = hand.position.position.X - pImag.X;
	proyVectorPlane.Y = hand.position.position.Y - pImag.Y;
	proyVectorPlane.Z = hand.position.position.Z - pImag.Z;
	
	
	
	return (finalAngle.getAngle(proyVectorZ, elbow.position.position, elbowRefAx.NewX));
*/  return(0);
}


float RArm::setElbowYaw(float angle, float& MIN, float& MAX){
	if (angle>MAX) MAX=angle;
	if (angle<MIN) MIN=angle;
	return (119.5+(angle-MIN)*(-119.5-119.5)/(MAX-MIN));
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


float RArm::setShoulderRoll(float angle, float& MIN, float& MAX){
	if (angle>MAX) MAX=angle;
	if (angle<MIN) MIN=angle;
	return (18+(angle-MIN)*(-76-18)/(MAX-MIN));
}
