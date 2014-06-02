///Declaracion de la clase derivada "Head" y su funcionalidad


#include "joint.h"

#define MAX_NUM_USERS 15


Head::Head()
{
}
Head::~Head()
{
}

///Obtiene el angulo real dado por el kinect del movimiento frontal de la cabeza
float Head::getHeadPitch()
{
	Head realAngle;///Objeto que se usara para obtener los largos entre las uniones
	float head[3], neck[3], torso[3];///Arrays donde se guardaran las 3 coordenadas de cada parte del cuerpo
	float headToNeck, neckToTorso, imHeadToTorso;///Variables para saber la longitud del skeleton
	
	///Inicializacion para el Kinect
	xn::UserGenerator g_UserGenerator;
	XnSkeletonJointPosition headJoint, neckJoint, torsoJoint;
	XnUInt16 nUsers=MAX_NUM_USERS;
	XnUserID aUsers[MAX_NUM_USERS];
	
	///Se obtienen los valores de los 3 joints requeridos
	for(XnUInt16 i=0; i<nUsers; i++)
        {
            if(g_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i])==FALSE)
                continue;

            g_UserGenerator.GetSkeletonCap().GetSkeletonJoint(aUsers[i],XN_SKEL_TORSO,torsoJoint);
			torso[0]=torsoJoint.position.X;
			torso[1]=torsoJoint.position.Y;
			torso[2]=torsoJoint.position.Z;
			
			g_UserGenerator.GetSkeletonCap().GetSkeletonJoint(aUsers[i],XN_SKEL_HEAD,headJoint);
			head[0]=headJoint.position.X;
			head[1]=headJoint.position.Y;
			head[2]=headJoint.position.Z;
			
			g_UserGenerator.GetSkeletonCap().GetSkeletonJoint(aUsers[i],XN_SKEL_NECK,neckJoint);
			neck[0]=neckJoint.position.X;
			neck[1]=neckJoint.position.Y;
			neck[2]=neckJoint.position.Z;            
                
        }
	

	
	headToNeck = realAngle.length(head, neck);
	neckToTorso = realAngle.length(neck, torso);
	imHeadToTorso = realAngle.length(head, torso);
	
	return (realAngle.angle(headToNeck, neckToTorso, imHeadToTorso));
	///Aqui se podria cambiar a que se pase por referencia, hago que la clase reciba una variable y que esa variable se modifique tambien en el main, para asi retornar un void
	
}


float Head::setHeadPitch(float angle){
	
	return (0);

}
