
///Esta es la decralarion de la funcionalidad de la clase base "Joint", de aqui se deriban las demas.

#include "joint.h"


Joint::Joint()
{
}
Joint::~Joint()
{
}

float Joint::length(float p1[3], float p2[3]){

    return (sqrt(pow((p2[0]-p1[0]),2)+pow((p2[1]-p1[1]),2)+pow((p2[2]-p1[2]),2)));
    ///Determina el vector que va de P1 a P2
}


float Joint::angle(float RL1, float RL2, float IML3){

    return ((180/PI)*acos((pow(RL1,2)+pow(RL2,2)-pow(IML3,2))/(2*RL1*RL2)));///IML3 es el segmento contrario al angulo por determinar, el cual no existe, es IMaginario

}
