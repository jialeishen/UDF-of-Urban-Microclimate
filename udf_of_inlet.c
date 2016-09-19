/**************************************************************************
                                 inlet udf
@author:Jialei Shen
@e-mail:shenjialei1992@163.com
@latest:2016.09.17
This is a UDF file for setting the inlet boundary conditions in Fluent, 
including the following terms:
1  profile term of inlet velocity
2  profile term of inlet k
3  profile term of inlet e
**************************************************************************/

#include "udf.h"

#define UH 4.8                //reference velocity
#define H 20                  //height of buildings
#define DELTA 300             //doundary layer depth; DELTA=15*H
#define A 0.27                //coefficient
#define Utau 0.23             //friction velocity
#define K 0.435               //von Karman constant
#define Cmu 0.09

/*********************profile term of inlet velocity**********************/

DEFINE_PROFILE(velocity_profile,t,i)
{
	real x[ND_ND];
	real h;
	face_t f;

	begin_f_loop(f,t)
    {
		F_CENTROID(x,f,t);
		h=x[1];
      
		if(h<=DELTA && h>=0)
        {
			F_PROFILE(f,t,i)=UH*pow(h/DELTA,A);
        }
        else
        {
			F_PROFILE(f,t,i)=UH;
        }

    }
	end_f_loop(f,t)
}

/************************profile term of inlet k**************************/

DEFINE_PROFILE(k_profile,t,i)
{
	real x[ND_ND];
	real h;
	face_t f;
  
	begin_f_loop(f,t)
    {
		F_CENTROID(x,f,t);
		h=x[1];
      
		if(h<=DELTA)
		{
			F_PROFILE(f,t,i)=((Utau*Utau)/sqrt(Cmu))*(1-h/DELTA);
        }
        else
        {
			F_PROFILE(f,t,i)=0;
        }

    }
	end_f_loop(f,t)
}

/*************************profile term of inlet e**************************/

DEFINE_PROFILE(e_profile,t,i)
{
	real x[ND_ND];
	real h;
	face_t f;
  
	begin_f_loop(f,t)
    {
		F_CENTROID(x,f,t);
		h=x[1];
      
		if(h<=DELTA)
        {
			F_PROFILE(f,t,i)=((Utau*Utau*Utau)/(K*h))*(1-h/DELTA);
        }
        else
        {
			F_PROFILE(f,t,i)=0;
        }

    }
	end_f_loop(f,t)
}
