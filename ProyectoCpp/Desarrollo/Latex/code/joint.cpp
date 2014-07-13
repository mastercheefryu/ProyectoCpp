///Esta es la declaracion de la funcionalidad de la clase base "Joint".
///De aqui se derivan las demas.

#include "joint.h"

Joint::Joint()
{
}
Joint::~Joint()
{
}

float Joint::getAngle(XnVector3D J1, XnVector3D J2, XnVector3D J3)
///J2 es la articulacion a la que se va a sacar el angulo
{
	float Real1, Real2, Imag3;
	
	///Se toman los tres vectores y se determina la distancia entre ellos, donde Imag3
	///es la distancia opuesta del J2
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

    return ((180/PI)*acos((pow(RL1,2)+pow(RL2,2)-pow(IML3,2))/(2*RL1*RL2)));
    ///IML3 es el segmento contrario al angulo por determinar, el cual no existe, es imaginario

}

XnVector3D Joint::getNormalVector(XnVector3D J1, XnVector3D J2, XnVector3D J3)
///J2 es el punto de union de los vectores J2->J1 y J2->J3, 
///a los cuales se les sacara el vector normal
{
	///Generamos 2 vectores a partir de los cuales calcularemos 
	///el producto cruz, Vector1 X Vector2 = VectorNormal
	XnVector3D Vector1, Vector2, NormalVector;
	///Para Vector1 = J2->J1
	Vector1.X=J1.X-J2.X;
	Vector1.Y=J1.Y-J2.Y;
	Vector1.Z=J1.Z-J2.Z;
	///Para Vector2 = J2->J3
	Vector2.X=J3.X-J2.X;
	Vector2.Y=J3.Y-J2.Y;
	Vector2.Z=J3.Z-J2.Z;
	///Generamos el vector ortogonal VectorNormal
	NormalVector.X=(Vector1.Y*Vector2.Z)-(Vector2.Y*Vector1.Z);
	NormalVector.Y=(Vector2.X*Vector1.Z)-(Vector1.X*Vector2.Z);
	NormalVector.Z=(Vector1.X*Vector2.Y)-(Vector2.X*Vector1.Y);

	return (NormalVector);
	
	}

XnVector3D Joint::getProyectionVector(XnVector3D Vector1, XnVector3D Vector2)
///Calculamos la proyeccion del Vector1 sobre el Vector2
{
	///Generamos el vector en el cual se va a guardar 
	///la proyeccion resultante

	XnVector3D ProyectionVector;

	///Calculamos el producto  punto entre Vector1 y Vector2
	XnFloat PointProduct = (Vector1.X*Vector2.X)+(Vector1.Y*Vector2.Y)+(Vector1.Z*Vector2.Z);
	///Calculamos la norma del Vector2
	XnFloat NormVector2 = sqrt(pow(Vector2.X,2)+pow(Vector2.Y,2)+pow(Vector2.Z,2));

	XnFloat Proyection=PointProduct/(pow(NormVector2,2));

	ProyectionVector.X=Proyection*Vector2.X;
	ProyectionVector.Y=Proyection*Vector2.Y;
	ProyectionVector.Z=Proyection*Vector2.Z;

	return (ProyectionVector);

	}
	
XnFloat Joint::getProyection(XnVector3D Vector1, XnVector3D Vector2)
///Calculamos la proyeccion del Vector1 sobre el Vector2
{
	///Generamos el vector en el cual se va a guardar la proyeccion resultante
	XnVector3D ProyectionVector;

	///Calculamos el producto  punto entre Vector1 y Vector2
	XnFloat PointProduct = (Vector1.X*Vector2.X)+(Vector1.Y*Vector2.Y)+(Vector1.Z*Vector2.Z);
	///Calculamos la norma del Vector2
	XnFloat NormVector2 = sqrt(pow(Vector2.X,2)+pow(Vector2.Y,2)+pow(Vector2.Z,2));
	///Ahora calculamos la  constante que multiplica al vector 
	///sobre el cual estamos proyectando para generar el nuevo vector proyeccion
	XnFloat Proyection=PointProduct/(pow(NormVector2,2));

	return (Proyection);

	}	
	
XnReferenceAxis Joint::generateReference(XnVector3D J1,XnVector3D J2,XnVector3D J3)
///Este metodo genera un nuevo eje de referencia centrado en un Joint
{
///PointNormal1 es un nuevo Joint para calcular una de las normales 
///que sera parte del marco de referencia
	XnVector3D PointNormal1;
///Utilizamos el struct XnReferenceAxis definido previamente para 
///almacenar el nuevo marco de referencia
	XnReferenceAxis NewAxis;
	
	NewAxis.NewX=Joint::getNormalVector(J1,J2,J3);
	
	PointNormal1.X=J2.X+NewAxis.NewX.X;
	PointNormal1.Y=J2.Y+NewAxis.NewX.Y;
	PointNormal1.Z=J2.Z+NewAxis.NewX.Z;
	
	NewAxis.NewY=Joint::getNormalVector(J1,J2,PointNormal1);
	
	NewAxis.NewZ.X=J1.X-J2.X;
	NewAxis.NewZ.Y=J1.Y-J2.Y;
	NewAxis.NewZ.Z=J1.Z-J2.Z;
	
	return (NewAxis);
}
