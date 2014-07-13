#ifndef JOINT_H
#define JOINT_H

#include "kinao_global.h"

#define PI 3.14159265358979323846


///Aqui se describe la clase base "Joint"
class Joint
{
private:

public:
    Joint();///Constructor del Objeto
    virtual ~Joint(void);///Destructor del Objeto

    ///Determina el vector que va de P1 a P2
    virtual float length (float[3], float[3]);/// P1[3],P2[3]
	///Determina el angulo entre 3 puntos dadas las 3 lineas descritas por estos puntos
	///El angulo a determinar viene dado por la linea imaginaria que esta opuesta a este angulo
    virtual float angle(float, float, float);///L1,L2,L3(L3 es el opuesto del angulo a determinar)
    
    ///Aunque se podria, no se crea una funcion getAngle aqui porque se necesitan pasar los parametros que usa el kinect para
    ///cada una de las posiciones, lo que se quiere es simplemente decir head.getAngle y que se obtenga el de la cabeza. Se pordria
    ///hacer, pero inicializando todos los joints y que se esten actualizando en tiempo real en la clasd Joint, para luego simplemente
    ///llamarlos desde las respectivas subclases igualando el valor actual del Joint en x,y,z a mi variable dentro de la subclase, luego
    ///como el objeto es de tipo Head, entonces el automaticamente sabe que las variables que debe pasar son las corerspondientes a los puntos
    ///que describen el angulo del cuello. Por ahora queda como mejora
    
    ///Determina directamente el angulo que hay en el segundo vector
    virtual float getAngle(XnVector3D, XnVector3D, XnVector3D);
    
       
    ///Genera el vector resultante de realizar el producto cruz entre los 2 vectores coplanares
	virtual XnVector3D getNormalVector(XnVector3D, XnVector3D, XnVector3D);
	
	///Obtiene el vector resultante de proyectar un vector sobre otro
	virtual XnVector3D getProyectionVector(XnVector3D , XnVector3D );
	
	///Obtiene la constante de la proyeccion
	virtual XnFloat getProyection(XnVector3D Vector1, XnVector3D Vector2);
	
	///Construye un nuevo eje de coordenadas a partir de 3 vectores otrtogonales
	virtual XnReferenceAxis generateReference(XnVector3D, XnVector3D, XnVector3D );
    
    
    
    
    
    ///
    ///virtual float** getCoord(XnUserID, xn::UserGenerator, skelJoint);
    
};



///Aqui se describe la clase derivada "Head"
class Head: public Joint
{
private:
public:
	Head();///Constructor del Objeto
	virtual ~Head(void);///Destructor del Objeto
	///Obtiene el angulo que se determina a partir del kinect
	virtual float getHeadPitch(XnUserID, xn::UserGenerator);
	///Genera el angulo necesario para mover el NAO
	virtual float setHeadPitch(float, float&, float&);

			
};


///Esta es la clase que describe el comportamiento para los brazos
class LArm: public Joint
{
private:
public:
	LArm();
	virtual ~LArm(void);
	
	///Obtiene el angulo que se determina a partir del kinect del codo
	virtual float getElbowRoll(XnUserID, xn::UserGenerator);
	///Genera el angulo necesario para mover el NAO
	virtual float setElbowRoll(float, float&, float&);
	
	///Obtiene el angulo que se determina a partir del kinect del hombro
	virtual float getShoulderRoll(XnUserID, xn::UserGenerator);
	///Genera el angulo necesario para mover el NAO
	virtual float setShoulderRoll(float, float&, float&);
	
	virtual float getElbowYaw(XnUserID, xn::UserGenerator);
	virtual float setElbowYaw(float, float&, float&);

	};	
	
class RArm: public Joint
{
public:
	RArm();
	virtual ~RArm(void);
	
	///Obtiene el angulo que se determina a partir del kinect del codo
	virtual float getElbowRoll(XnUserID, xn::UserGenerator);
	///Genera el angulo necesario para mover el NAO
	virtual float setElbowRoll(float, float&, float&);
	
	///Obtiene el angulo que se determina a partir del kinect del hombro
	virtual float getShoulderRoll(XnUserID, xn::UserGenerator);
	///Genera el angulo nececsario para mover el NAO
	virtual float setShoulderRoll(float, float&, float&);
	
	virtual float getElbowYaw(XnUserID, xn::UserGenerator);
	virtual float setElbowYaw(float, float&, float&);
	
	};
	

class LLeg: public Joint
{
public:
	LLeg();
	virtual ~LLeg(void);
	
	///Obtiene el angulo que se determina a partir del kinect del hombro
	virtual float getHipRoll(XnUserID, xn::UserGenerator);
	///Genera el angulo necesario para mover el NAO
	virtual float setHipRoll(float, float&, float&);
	
	///Obtiene el angulo que se determina a partir del kinect
	virtual float getKneePitch(XnUserID, xn::UserGenerator);
	///Genera el angulo necesario para mover el NAO
	virtual float setKneePitch(float, float&, float&);

	///Obtiene el angulo que se determina a partir del kinect
	virtual float getAnklePitch(XnUserID, xn::UserGenerator);
	///Genera angulo para mover NAO
	virtual float setAnklePitch(float, float&, float&);
	
	};
	
class RLeg: public Joint
{
public:
	RLeg();
	virtual ~RLeg(void);
	
	
	///Obtiene el angulo que se determina a partir del kinect del hombro
	virtual float getHipRoll(XnUserID, xn::UserGenerator);
	///Genera el angulo necesario para mover el NAO
	virtual float setHipRoll(float, float&, float&);
	
	///Obtiene el angulo que se determina a partir del kinect
	virtual float getKneePitch(XnUserID, xn::UserGenerator);
	///Genera el angulo necesario para mover el NAO
	virtual float setKneePitch(float, float&, float&);
	
	///Obtiene el angulo que se determina a partir del kinect
	virtual float getAnklePitch(XnUserID, xn::UserGenerator);
	///Genera angulo para mover NAO
	virtual float setAnklePitch(float, float&, float&);
	

	
	};
	

#endif /// JOINT_H
