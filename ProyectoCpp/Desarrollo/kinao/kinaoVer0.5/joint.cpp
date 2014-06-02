
///Esta es la decralarion de la funcionalidad de la clase base "Joint", de aqui se deriban las demas.

#include "joint.h"


Joint::Joint()
{
}
Joint::~Joint()
{
}

float Joint::getAngle(XnVector3D J1, XnVector3D J2, XnVector3D J3)///J2 es la articulacion a la que se va a sacar el angulo
{
	float Real1, Real2, Imag3;
	
	///Se toman los tres vectores y se determina la distancia entre ellos, donde Imag3
	///es la distancia opuesta el J2
	Real1 = sqrt(pow((J1.X-J2.X),2)+pow((J1.Y-J2.Y),2)+pow((J1.Z-J2.Z),2));
	Real2 = sqrt(pow((J3.X-J2.X),2)+pow((J3.Y-J2.Y),2)+pow((J3.Z-J2.Z),2));
	Imag3 = sqrt(pow((J3.X-J1.X),2)+pow((J3.Y-J1.Y),2)+pow((J3.Z-J1.Z),2));
	
	return ((180/PI)*acos((pow(Real1,2)+pow(Real2,2)-pow(Imag3,2))/(2*Real1*Real2)));
	
	}

float Joint::length(float p1[3], float p2[3]){

    return (sqrt(pow((p2[0]-p1[0]),2)+pow((p2[1]-p1[1]),2)+pow((p2[2]-p1[2]),2)));
    ///Determina el vector que va de P1 a P2
}


float Joint::angle(float RL1, float RL2, float IML3){

    return ((180/PI)*acos((pow(RL1,2)+pow(RL2,2)-pow(IML3,2))/(2*RL1*RL2)));///IML3 es el segmento contrario al angulo por determinar, el cual no existe, es IMaginario

}
/*
float** Joint::getCoord(XnUserID user, xn::UserGenerator gUser, skelJoint skel)
{
	//float *toPoint;
	XnSkeletonJointTransformation Point;
	float** allCoord = new float* [24];
	//float allCoord[24][3];//filas, columnas
	//float triadCoord[3][3];
	int j, i;
	
	for(j=0; j<24; j++) allCoord[j] = new float[24];
	
	for(j=0;j<24;j++){
		
			gUser.GetSkeletonCap().GetSkeletonJoint(user,j+1,Point);
            
            allCoord[j][0]=Point.position.position.X;
            allCoord[j][1]=Point.position.position.Y;
            allCoord[j][2]=Point.position.position.Z;					
	}
	
	La matriz anterior, queda organizada de la siguiente manera
	
	XN_SKEL_HEAD			= Fila0,
	XN_SKEL_NECK			= Fila1,
	XN_SKEL_TORSO			= Fila2,
	XN_SKEL_WAIST			= Fila3,

	XN_SKEL_LEFT_COLLAR		= Fila4,
	XN_SKEL_LEFT_SHOULDER	= Fila5,
	XN_SKEL_LEFT_ELBOW		= Fila6,
	XN_SKEL_LEFT_WRIST		= Fila7,
	XN_SKEL_LEFT_HAND		= Fila8,
	XN_SKEL_LEFT_FINGERTIP	=Fila9,

	XN_SKEL_RIGHT_COLLAR	=Fila10,
	XN_SKEL_RIGHT_SHOULDER	=Fila11,
	XN_SKEL_RIGHT_ELBOW		=Fila12,
	XN_SKEL_RIGHT_WRIST		=Fila13,
	XN_SKEL_RIGHT_HAND		=Fila14,
	XN_SKEL_RIGHT_FINGERTIP	=Fila15,

	XN_SKEL_LEFT_HIP		=Fila16,
	XN_SKEL_LEFT_KNEE		=Fila17,
	XN_SKEL_LEFT_ANKLE		=Fila18,
	XN_SKEL_LEFT_FOOT		=Fila19,

	XN_SKEL_RIGHT_HIP		=Fila20,
	XN_SKEL_RIGHT_KNEE		=Fila21,
	XN_SKEL_RIGHT_ANKLE		=Fila22,
	XN_SKEL_RIGHT_FOOT		=Fila23	  
	  
	
	
	
	if(skel == 0){///Coordenadas para el angulo del Neck
		for(i=0; i<3; i++){
			triadCoord[0][i]=allCoord[0][i];///Head
			triadCoord[1][i]=allCoord[1][i];///Neck
			triadCoord[2][i]=allCoord[2][i];///Torso
		}
	}
	if(skel == 1){///Coordenadas para el angulo del Elbow
		for(i=0; i<3; i++){
			triadCoord[5][i]=allCoord[0][i];///Shoulder
			triadCoord[6][i]=allCoord[1][i];///Elbow
			triadCoord[8][i]=allCoord[2][i];///Hand
		}
	}
	
	//toPoint=triadCoord;
	
	return (0);
} */    
	
	

