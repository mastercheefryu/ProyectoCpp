#include "joint.h"


RLeg::RLeg()
{
}
RLeg::~RLeg()
{
}



///Obtiene el angulo real dado por el kinect del movimiento del codo
float RLeg::getHipRoll(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation lhip, rhip, knee;
	
	RLeg finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_HIP,lhip);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_HIP,rhip);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_KNEE,knee);
			
	return (finalAngle.getAngle(lhip.position.position, rhip.position.position, knee.position.position));

}


float RLeg::setHipRoll(float angle){
	
	return (0);

}


float RLeg::getKneePitch(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation hip, knee, ankle;
	
	RLeg finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_HIP,hip);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_KNEE,knee);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_FOOT,ankle);
			
	return (finalAngle.getAngle(knee.position.position, hip.position.position, ankle.position.position));

}


float RLeg::setKneePitch(float angle){
	
	return (0);

}

float RLeg::getAnklePitch(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation knee, ankle, foot;
	
	RLeg finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_KNEE,knee);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_ANKLE,ankle);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_RIGHT_FOOT,foot);
			
	return (finalAngle.getAngle(knee.position.position, ankle.position.position, foot.position.position));

}


float RLeg::setAnklePitch(float angle){
	
	return (0);

}
