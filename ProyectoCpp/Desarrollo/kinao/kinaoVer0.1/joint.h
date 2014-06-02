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
};

///Aqui se describe la clase derivada "Head"
class Head: public Joint
{
private:
public:
	Head();///Constructor del Objeto
	virtual ~Head(void);///Destructor del Objeto
	///Obtiene el angulo que se determina a partir del kinect
	virtual float getHeadPitch();
	///Genera el angulo necesario para mover el NAO
	virtual float setHeadPitch(float);
			
};
/*
class Arm: public Join
{
	}
*/
#endif /// JOINT_H
