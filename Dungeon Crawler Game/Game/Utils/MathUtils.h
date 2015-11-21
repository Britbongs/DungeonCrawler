
#ifndef MATH_H
#define MATH_H 

class MathUtils
{
public:
	MathUtils();
	~MathUtils();
	//Param: current time, start value, change in value, duration of the linearTween
	static float LinearTween(float, float, float, float); 
};



#endif 