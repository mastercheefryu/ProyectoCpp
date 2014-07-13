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


float LArm::setElbowRoll(float angle, float& MIN, float& MAX){//Preguntar como hacer para no pasar esos min y max, sino que siempre se mantengan como algo iniciado
	if (angle>MAX) MAX=angle;								  //Sino tendria que inicializar un MAX y MIN para cada set que haga
	if (angle<MIN) MIN=angle;
	return (-88.5+(angle-MIN)*(-2-88.5)/(MAX-MIN));
}




float LArm::getElbowYaw(XnUserID user, xn::UserGenerator guser)
{
	
	XnSkeletonJointTransformation shoulder, elbow, hand, pastShoulder, pastElbow, pastHand;
	
	LArm varAngle, refAx;
	XnReferenceAxis elbowRefAx;
	XnVector3D elToHand, proyVectorZ, pImag, proyVectorPlane, pProyOverXY, pOverAxY;
	float changeAngle, finalAngle;

	pastShoulder.position.position = shoulder.position.position;
	pastHand.position.position = hand.position.position;
	pastElbow.position.position = elbow.position.position;

	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_SHOULDER,shoulder);
         
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_ELBOW,elbow);
			
	guser.GetSkeletonCap().GetSkeletonJoint(user,XN_SKEL_LEFT_HAND,hand);
	
	
	///Marco de referencia en un momento anterior con punto central sobre el codo
	elbowRefAx = refAx.generateReference(pastHand.position.position, pastElbow.position.position, pastShoulder.position.position);
	
	///Obtenemos el vector elToHand (codo -> mano)
	elToHand.X = hand.position.position.X-elbow.position.position.X;
	elToHand.Y = hand.position.position.Y-elbow.position.position.Y;
	elToHand.Z = hand.position.position.Z-elbow.position.position.Z;
	
	///Obtenemos la proyeccion del vector elToHand sobre el eje Z de la referencia en el codo
	proyVectorZ = getProyectionVector(elToHand, elbowRefAx.NewZ);

	///Obtenemos el punto imaginario
	pImag.X = proyVectorZ.X + elbow.position.position.X;
	pImag.Y = proyVectorZ.Y + elbow.position.position.Y;
	pImag.Z = proyVectorZ.Z + elbow.position.position.Z;
	
	///Obtenemos la proyeccion sobre el plano XY, para ello obtenemos se forma entre la proyeccion y el vector elToHand
	proyVectorPlane.X = hand.position.position.X - pImag.X;
	proyVectorPlane.Y = hand.position.position.Y - pImag.Y;
	proyVectorPlane.Z = hand.position.position.Z - pImag.Z;
	
	///Obtenemos primer punto que es la proyeccion de la mano sobre el plano XY
	pProyOverXY.X = elbow.position.position.X + proyVectorPlane.X;
	pProyOverXY.Y = elbow.position.position.Y + proyVectorPlane.Y;
	pProyOverXY.Z = elbow.position.position.Z + proyVectorPlane.Z;
	
	///Obtenemos el segundo punto sobre nuestro eje Y
	pOverAxY.X = elbow.position.position.X + elbowRefAx.NewY.X;
	pOverAxY.Y = elbow.position.position.Y + elbowRefAx.NewY.Y;
	pOverAxY.Z = elbow.position.position.Z + elbowRefAx.NewY.Z;
	
	///Obtenemos el angulo entre la proyeccion entre el plano XY y el eje Y
	changeAngle = varAngle.getAngle(pProyOverXY, elbow.position.position, pOverAxY);
	
	///Determinamos el signo del angulo para saber si rotamos el codo en sentido horario o antihorario
	///Obtenemos la proyeccion del vector proyVectorPlane sobre el eje X de la referencia en el codo
	if(getProyection(proyVectorPlane,elbowRefAx.NewX) < 0){
	  finalAngle = finalAngle+changeAngle;
	}
	else{
	  finalAngle = finalAngle-changeAngle;
	}
	return(finalAngle);
}


float LArm::setElbowYaw(float angle, float& MIN, float& MAX){
	if (angle>MAX) MAX=angle;
	if (angle<MIN) MIN=angle;
	return (119.5+(angle-MIN)*(-119.5-119.5)/(MAX-MIN));
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


float LArm::setShoulderRoll(float angle, float& MIN, float& MAX){
	if (angle>MAX) MAX=angle;
	if (angle<MIN) MIN=angle;
	return (-18+(angle-MIN)*(76+18)/(MAX-MIN));
}
