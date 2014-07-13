///Declaracion de la clase derivada "Head" y su funcionalidad


#include "joint.h"

Head::Head()
{
}
Head::~Head()
{
}

///Obtiene el angulo real dado por el kinect del movimiento frontal de la cabeza
float Head::getHeadPitch(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation head, neck, torso;
	
	Head finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_HEAD,head);
            
   	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_NECK,neck);
	           
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_TORSO,torso);
			
	
	return (finalAngle.getAngle(head.position.position, 
	neck.position.position, torso.position.position));

}

///Establece un limite para el angulo de inclinacion de la cabeza
float Head::setHeadPitch(float angle, float& MIN, float& MAX){
	if (angle>MAX) MAX=angle;
	if (angle<MIN) MIN=angle;
	return (29.5+(angle-MIN)*(-29.5)/(MAX-MIN));
}
