
#include "joint.h"

///Definimos un struct XnReferenceAxis para  construir ejes de referencia a partir de  vectores
typedef struct XnReferenceAxis
{
	XnVector3D NewX;
	XnVector3D NewY;
	XnVector3D NewZ;
} XnReferenceAxis;

XnVector3D Joint::getNormalVector(XnVector3D J1, XnVector3D J2, XnVector3D J3)///J2 es el punto de unión de los vectores J2->J1 y J2->J3, a los  cuales se les sacará el vector normal
{
	///Generamos 2 vectores a partir de los cuales calcularemos el producto cruz, Vector1 X Vector2 = VectorNormal
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

XnVector3D Joint::getProyectionVector(XnVector3D Vector1, XnVector3D Vector2)///Calculamos la proyección del Vector1 sobre el Vector2
{
	///Generamos el vector en el cual se va a guardar la proyección resultante

	XnVector3D ProyectionVector;

	///Calculamos el producto  punto entre Vector1 y Vector2
	double PointProduct = (Vector1.X*Vector2.X)+(Vector1.Y*Vector2.Y)+(Vector1.Z*Vector2.Z);
	///Calculamos la norma del Vector2
	double NormVector2 = sqrt(pow(Vector2.X,2)+pow(Vector2.Y,2)+pow(Vector2.Z,2));
	///Ahora calculamos la  constante que multiplica al vector sobre el cual estamos proyectando para generar el nuevo vector proyección
	double Proyection=PointProduct/(pow(NormVector2),2);
	///Calculamos las componentes  del nuevo vector
	ProyectionVector.X=Proyection*Vector2.X;
	ProyectionVector.Y=Proyection*Vector2.Y;
	ProyectionVector.Z=Proyection*Vector2.Z;

	return (ProyectionVector);

	}

XnReferenceAxis Joint::generateReference(XnVector3D J1,XnVector3D J2,XnVector3D J3)///Este método genera un nuevo eje de referencia centrado en un Joint
{
///PointNormal1 es un nuevo Joint para calcular una de las normales que será parte del marco de referencia
	XnVector3D PointNormal1;
///Utilizamos el struct XnReferenceAxis definido previamente para almacenar el nuevo marco de referencia
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







