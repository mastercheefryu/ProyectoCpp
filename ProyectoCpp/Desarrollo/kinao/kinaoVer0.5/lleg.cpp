#include "joint.h"


LLeg::LLeg()
{
}
LLeg::~LLeg()
{
}



///Obtiene el angulo real dado por el kinect del movimiento del codo
float LLeg::getHipRoll(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation rhip, lhip, knee;
	
	LLeg finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_HIP,rhip);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_HIP,lhip);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_KNEE,knee);
			
	return (finalAngle.getAngle(rhip.position.position, lhip.position.position, knee.position.position));

}


float LLeg::setHipRoll(float angle){
	
	return (0);

}


float LLeg::getKneePitch(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation hip, knee, ankle;
	
	LLeg finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_HIP,hip);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_KNEE,knee);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_FOOT,ankle);
			
	return (finalAngle.getAngle(hip.position.position, knee.position.position, ankle.position.position));

}


float LLeg::setKneePitch(float angle){
	
	return (0);

}

float LLeg::getAnklePitch(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation knee, ankle, foot;
	
	LLeg finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_KNEE,knee);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_ANKLE,ankle);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_FOOT,foot);
			
	return (finalAngle.getAngle(knee.position.position, ankle.position.position, foot.position.position));

}


float LLeg::setAnklePitch(float angle){
	
	return (0);

}

