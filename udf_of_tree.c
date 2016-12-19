/**************************************************************************
                                 TREE model
@author:Jialei Shen
@e-mail:shenjialei1992@163.com
@latest:2016.09.19
This is an UDF file used to simulate the air flow around a tree model,
including the following terms:
1  source term of X momentum
2  source term of Y momentum
3  source term of Z momentum
4  source term of turbulent k (turbulent kinetic energy)
5  source term of turbulent e (turbulent dissiption rate)
6  profile term of inlet velocity
7  profile term of inlet k
8  profile term of inlet e
**************************************************************************/

#include "udf.h"
#define W(U,V,W) (sqrt((U)*(U)+(V)*(V)+(W)*(W)))   //average velocity
#define Cdf 0.2
#define H 1.0
#define Lm 36.01
#define Zm 0.6
#define B 1./6.
#define KAR 0.435
#define Z0 0.0025
#define Cmu 0.09
#define WW 5.0
#define L 25.0
#define V 1.5e-5

/***********************source term of X momentum**************************/
DEFINE_SOURCE(x_momentum_source,c,t,dS,eqn)
{
	real x[ND_ND];
	real source,lad,n;

	C_CENTROID(x,c,t);

	if(x[1]<Zm && x[1]>=0)
	{
		n=6;
		lad=Lm*pow(((H-Zm)/(H-x[1])),n)*exp(n*(1-((H-Zm)/(H-x[1]))));
	}
	else if(x[1]>=Zm && x[1]<H)
	{
		n=0.5;
		lad=Lm*pow(((H-Zm)/(H-x[1])),n)*exp(n*(1-((H-Zm)/(H-x[1]))));
	}
	else
	{
		lad=0;
	}

	source=-Cdf*lad*W(C_U(c,t),C_V(c,t),C_W(c,t))*C_U(c,t);
	dS[eqn]=-Cdf*lad*W(C_U(c,t),C_V(c,t),C_W(c,t));
	return source;
}

/***********************source term of Y momentum**************************/
DEFINE_SOURCE(y_momentum_source,c,t,dS,eqn)
{
	real x[ND_ND];
	real source,lad,n;

	C_CENTROID(x,c,t);

	if(x[1]<Zm && x[1]>=0)
	{
		n=6;
		lad=Lm*pow(((H-Zm)/(H-x[1])),n)*exp(n*(1-((H-Zm)/(H-x[1]))));
	}
	else if(x[1]>=Zm && x[1]<H)
	{
		n=0.5;
		lad=Lm*pow(((H-Zm)/(H-x[1])),n)*exp(n*(1-((H-Zm)/(H-x[1]))));
	}
	else
	{
		lad=0;
	}

	source=-Cdf*lad*W(C_U(c,t),C_V(c,t),C_W(c,t))*C_V(c,t);
	dS[eqn]=-Cdf*lad*W(C_U(c,t),C_V(c,t),C_W(c,t));
	return source;
}

/***********************source term of Z momentum**************************/
DEFINE_SOURCE(z_momentum_source,c,t,dS,eqn)
{
	real x[ND_ND];
	real source,lad,n;

	C_CENTROID(x,c,t);

	if(x[1]<Zm && x[1]>=0)
	{
		n=6;
		lad=Lm*pow(((H-Zm)/(H-x[1])),n)*exp(n*(1-((H-Zm)/(H-x[1]))));
	}
	else if(x[1]>=Zm && x[1]<H)
	{
		n=0.5;
		lad=Lm*pow(((H-Zm)/(H-x[1])),n)*exp(n*(1-((H-Zm)/(H-x[1]))));
	}
	else
	{
		lad=0;
	}

	source=-Cdf*lad*W(C_U(c,t),C_V(c,t),C_W(c,t))*C_W(c,t);
	dS[eqn]=-Cdf*lad*W(C_U(c,t),C_V(c,t),C_W(c,t));
	return source;
}

/**********************source term of turbulence k*************************/
DEFINE_SOURCE(k_source,c,t,dS,eqn)
{
	real x[ND_ND];
	real source,lad,n;

	C_CENTROID(x,c,t);

	if(x[1]<Zm && x[1]>=0)
	{
		n=6;
		lad=Lm*pow(((H-Zm)/(H-x[1])),n)*exp(n*(1-((H-Zm)/(H-x[1]))));
	}
	else if(x[1]>=Zm && x[1]<H)
	{
		n=0.5;
		lad=Lm*pow(((H-Zm)/(H-x[1])),n)*exp(n*(1-((H-Zm)/(H-x[1]))));
	}
	else
	{
		lad=0;
	}

	source=Cdf*lad*pow(W(C_U(c,t),C_V(c,t),C_W(c,t)),3)-4*Cdf*lad*W(C_U(c,t),C_V(c,t),C_W(c,t))*C_K(c,t);
	dS[eqn]=-4*Cdf*lad*W(C_U(c,t),C_V(c,t),C_W(c,t));
	return source;
}

/**********************source term of turbulence e*************************/
DEFINE_SOURCE(e_source,c,t,dS,eqn)
{
	real x[ND_ND];
	real source,lad,n;

	C_CENTROID(x,c,t);

	if(x[1]<Zm && x[1]>=0)
	{
		n=6;
		lad=Lm*pow(((H-Zm)/(H-x[1])),n)*exp(n*(1-((H-Zm)/(H-x[1]))));
	}
	else if(x[1]>=Zm && x[1]<H)
	{
		n=0.5;
		lad=Lm*pow(((H-Zm)/(H-x[1])),n)*exp(n*(1-((H-Zm)/(H-x[1]))));
	}
	else
	{
		lad=0;
	}

	source=1.5*Cdf*lad*pow(W(C_U(c,t),C_V(c,t),C_W(c,t)),3)-6*Cdf*lad*W(C_U(c,t),C_V(c,t),C_W(c,t))*C_D(c,t);
	dS[eqn]=-6*Cdf*lad*W(C_U(c,t),C_V(c,t),C_W(c,t));
	return source;
}

/*********************profile term of inlet velocity************************/
DEFINE_PROFILE(velocity_profile,t,i)
{
	real x[ND_ND];
	real h;
	real ufree=6;
	real del=10;
	face_t f;

	begin_f_loop(f,t)
	{
		F_CENTROID(x,f,t);
		h=x[1];
      
		if(h<=del)
        	{
			F_PROFILE(f,t,i)=ufree*pow(h/del,B);
        	}
        	else
        	{
			F_PROFILE(f,t,i)=ufree;
        	}

	}
	end_f_loop(f,t)
}

/************************profile term of inlet k***************************/
DEFINE_PROFILE(k_profile,t,i)
{
	real x[ND_ND];
	real h;
	real Re,ff,utau;
	real ufree=6;
	face_t f;
  
	Re=(ufree*L)/V;
	ff=0.074/(pow(Re,0.2));
	utau=sqrt(ff*ufree*ufree*0.5);

	begin_f_loop(f,t)
	{
		F_CENTROID(x,f,t);
		h=x[1];
      
		if(h<=WW)
        	{
			F_PROFILE(f,t,i)=(pow(utau,2)*pow((1-h/WW),2))/(sqrt(Cmu));
        	}
        	else
        	{
			F_PROFILE(f,t,i)=0;
        	}

	}
	end_f_loop(f,t)
}

/************************profile term of inlet e***************************/
DEFINE_PROFILE(e_profile,t,i)
{
	real x[ND_ND];
	real h;
	real Re,ff,utau;
	real ufree=6;
	face_t f;
  
	Re=(ufree*L)/V;
	ff=0.074/(pow(Re,0.2));
	utau=sqrt(ff*ufree*ufree*0.5);

	begin_f_loop(f,t)
	{
		F_CENTROID(x,f,t);
		h=x[1];
      
		if(h<=WW)
        	{
			F_PROFILE(f,t,i)=((pow(utau,3)*pow((1-h/WW),2))/(KAR*(h+Z0)))*(1+5.75*(h/Z0));
        	}
        	else
        	{
			F_PROFILE(f,t,i)=0;
        	}

	}
	end_f_loop(f,t)
}
