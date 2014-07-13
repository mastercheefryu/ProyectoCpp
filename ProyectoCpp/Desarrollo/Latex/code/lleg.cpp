#include "joint.h"

LLeg::LLeg()
{
}
LLeg::~LLeg()
{
}

///Obtiene el angulo real dado por el kinect del movimiento de la cadera
float LLeg::getHipRoll(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation rhip, lhip, knee;
	
	LLeg finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_HIP,rhip);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_HIP,lhip);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_KNEE,knee);
			
	return (finalAngle.getAngle(rhip.position.position, lhip.position.position, knee.position.position));

}


float LLeg::setHipRoll(float angle, float& MIN, float& MAX){
	if (angle>MAX) MAX=angle;
	if (angle<MIN) MIN=angle;
	return (-21.74+(angle-MIN)*(45.29+21.74)/(MAX-MIN));
}

///Aca hacemos lo mismo pero para la rotacion de la rodilla
float LLeg::getKneePitch(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation hip, knee, ankle;
	
	LLeg finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_HIP,hip);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_KNEE,knee);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_FOOT,ankle);
			
	return (finalAngle.getAngle(hip.position.position, knee.position.position, ankle.position.position));

}

float LLeg::setKneePitch(float angle, float& MIN, float& MAX){
	if (angle>MAX) MAX=angle;
	if (angle<MIN) MIN=angle;
	return (121.04+(angle-MIN)*(-5.29-121.04)/(MAX-MIN));
}

///Para el tobillo
float LLeg::getAnklePitch(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation knee, ankle, foot;
	
	LLeg finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_KNEE,knee);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_ANKLE,ankle);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_FOOT,foot);
			
	return (finalAngle.getAngle(knee.position.position, ankle.position.position, foot.position.position));

}

float LLeg::setAnklePitch(float angle, float& MIN, float& MAX){
	if (angle>MAX) MAX=angle;
	if (angle<MIN) MIN=angle;
	return (-68.15+(angle-MIN)*(52.86+68.15)/(MAX-MIN));
}
