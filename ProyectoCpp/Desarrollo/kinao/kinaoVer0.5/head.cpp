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
	//XnFloat headPosition[3], neckPosition[3], torsoPosition[3];
	Head finalAngle;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_HEAD,head);
            
   // headPosition[0]=head.position.position.X;
    //headPosition[1]=head.position.position.Y;
    //headPosition[2]=head.position.position.Z;			
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_NECK,neck);
			
	//neckPosition[0]=neck.position.position.X;
    //neckPosition[1]=neck.position.position.Y;
    //neckPosition[2]=neck.position.position.Z;			
            
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_TORSO,torso);
			
	//torsoPosition[0]=torso.position.position.X;
    //torsoPosition[1]=torso.position.position.Y;
    //torsoPosition[2]=torso.position.position.Z;		
    
    //return (finalAngle.getAngle(headPosition,neckPosition,torsoPosition));
	return (finalAngle.getAngle(head.position.position, neck.position.position, torso.position.position));

}


float Head::setHeadPitch(float angle){
	
	return (0);

}
