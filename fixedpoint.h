#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H
#define P 17
#define Q 14
#define FRACTION (1 << (Q))


/*fixedpoint in 17.14 format
Operation formulas gotten from pintos pdf
*/
int fixedpoint(int x);

int CONVERT_TO_FP(int n);		//n*f
int CONVERT_TO_INT_ZERO(int x);	//x/f
int CONVERT_TO_INT_NEAREST(int x);	//(x+f/2) x>=0 or (x-f/2) x<=0
int ADD(int x, int y);			//x+y
int ADD_INT(int x, int n);		//x+n
int SUB	(int x, int y);			//x-y
int SUB_INT(int x, int y);
int MULT(int x, int y);	//((int64_t) x)*y/f
int MULT_INT(int x, int n);		//x*n					
int DIV	(int x, int y);		//(int64_t)*f/y
int DIV_INT	(int x, int n);		// x/n


int CONVERT_TO_FP(int n){
return n * FRACTION;
}

CONVERT_TO_INT_ZERO(int x){
	return x / FRACTION;
}

int CONVERT_TO_INT_NEAREST(int x){
	if(x >= 0)		return (x + FRACTION / 2) / FRACTION;
		
	if(x <= 0)		return (x - FRACTION / 2) / FRACTION;
}
int ADD(int x, int y){
	return x + y;
}
int ADD_INT(int x, int n){
	return x + CONVERT_TO_FP(n);
}
int SUB(int x, int y){
	return x - y;
}
int SUB_INT(int x, int n){
	return x- CONVERT_TO_FP(n);
}
int MULT(int x,int n){
	return x * n;
}
int MULT_INT(int x,int y){
	return ((int64_t) x) * y / FRACTION;
}
int DIV(int x,int y){
	return ((int64_t) x)* FRACTION / y;
}
int DIV_INT(int x, int n){
	return x / n;
}

	

















#endif