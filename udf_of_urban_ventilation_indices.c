/**************************************************************************
				UDF of inlet profiles & ventilation indices
@author:Jialei Shen
@e-mail:shenjialei1992@163.com
@latest:2016.09.17
This is an UDF file of urban ventilation simulation in CFD, including the 
following terms: 
1  Profile term of inlet velocity;
2  Profile term of inlet k;
3  Profile term of inlet e;
4  Pollutant source term;
5  Volume of domain of interest (DOI);
6  Purging flow rate (PFR) term;
7  Local mean age of air (LMAA) term;
8  Mean residence time (Tau_R) term;
9  Visitation frequency (VF) term;
10 Average residence time (TP) term;
11 Flow rate (Q) term;
12 Turn-over time (Tau_N) term;
13 Air change rate (ACH) term;
14 Air exchange efficiency (Ea) term;
**************************************************************************/

#include "udf.h"
#include "sg.h"

#define UH 7.84            //reference velocity (m/s)
#define H 18.              //height of buildings (m)
#define DELTA 250.         //doundary layer depth (m)
#define ALPHA 0.25         //coefficient
#define Utau 0.305272      //friction velocity (m/s)
#define K 0.4              //von Karman constant
#define Cmu 0.09
#define M 0.00001          //pollutant emmision rate (kg/m3*s)
#define RHO 1.29           //density of air (kg/m3)
#define VOL 6220.8

real PFR;    //define global variables
real vol;
real VF;
real LMAA;
real Tau_R;
real Tau_N;
real Q;

/**********************Profile term of inlet velocity**********************/

DEFINE_PROFILE(velocity_profile,t,i)
{
	real x[ND_ND];
	real h;
	face_t f;

	begin_f_loop(f,t)
    {
		F_CENTROID(x,f,t);
		h=x[2];
      
		if(h<=DELTA && h>=0)
        {
			F_PROFILE(f,t,i)=UH*pow(h/DELTA,ALPHA);
        }
        else
        {
			F_PROFILE(f,t,i)=UH;
        }

    }
	end_f_loop(f,t)
}

/************************Profile term of inlet k**************************/

DEFINE_PROFILE(k_profile,t,i)
{
	real x[ND_ND];
	real h;
	face_t f;
  
	begin_f_loop(f,t)
    {
		F_CENTROID(x,f,t);
		h=x[2];
      
		if(h<=DELTA)
        {
			F_PROFILE(f,t,i)=(Utau*Utau)/sqrt(Cmu);
        }
        else
        {
			F_PROFILE(f,t,i)=(Utau*Utau)/sqrt(Cmu);
        }

    }
	end_f_loop(f,t)
}

/************************Profile term of inlet e**************************/

DEFINE_PROFILE(e_profile,t,i)
{
	real x[ND_ND];
	real h;
	face_t f;
  
	begin_f_loop(f,t)
    {
		F_CENTROID(x,f,t);
		h=x[2];
      
		if(h<=DELTA)
        {
			F_PROFILE(f,t,i)=(Utau*Utau*Utau)/(K*h);
        }
        else
        {
			F_PROFILE(f,t,i)=(Utau*Utau*Utau)/(K*DELTA);
        }

    }
	end_f_loop(f,t)
}

/*************************Pollutant source term**************************/

DEFINE_SOURCE(Pullation_1,c,t,dS,eqn)
{
	real x[ND_ND];
	real source;
	C_CENTROID(x,c,t);
	
	if(x[0]>=151.2 && x[0]<=158.4 && x[1]>=81.0 && x[1]<=105.0 && x[2]<=18. && x[2]>=0.)
	{
		source = M;
	}
	else
	{
		source = 0;
	}
	
	dS[eqn]=0;
	return source;
}

/*****************************volume of DOI******************************/

DEFINE_ON_DEMAND(vol_udf)
{
	Domain *domain;
	Thread *t;
	cell_t c;
	real x[ND_ND];
	FILE *fp_vol;
	fp_vol=fopen("vol.txt","a");
	domain=Get_Domain(1);
	
	thread_loop_c(t,domain)
	{
		begin_c_loop(c,t)
		{
			C_CENTROID(x,c,t);
			if(x[0]>=151.2 && x[0]<=158.4 && x[1]>=81.0 && x[1]<=105.0 && x[2]<=18. && x[2]>=0.)
			{
				vol=vol+C_VOLUME(c,t);
			}
		}
		end_c_loop(c,t)
	}
	fprintf(fp_vol,"%g\n",vol);
	fclose(fp_vol);
}

/*******************************PFR term********************************/

DEFINE_ON_DEMAND(PFR_1_udf)
{
	Domain *domain;
	Thread *t;
	cell_t c;
	real x[ND_ND];
	real cpt=0;
	real cpa;
	FILE *fp_pfr;
	fp_pfr=fopen("PFR.txt","a");
	domain=Get_Domain(1);
	
	thread_loop_c(t,domain)
	{
		begin_c_loop(c,t)
		{
			C_CENTROID(x,c,t);
			if(x[0]>=151.2 && x[0]<=158.4 && x[1]>=81.0 && x[1]<=105.0 && x[2]<=18. && x[2]>=0.)
			{
				cpt=cpt+C_YI(c,t,0)*C_VOLUME(c,t);
			}
		}
		end_c_loop(c,t)
	}
	cpa=cpt/vol;
	PFR=(M*vol)/(cpa*RHO);
	fprintf(fp_pfr,"%g\n",PFR);
	fclose(fp_pfr);
}

/*******************************LMAA term********************************/

DEFINE_ON_DEMAND(LMAA_1_udf)
{
	Domain *domain;
	Thread *t;
	cell_t c;
	real x[ND_ND];
	real cpt=0;
	real cpa;
	FILE *fp_lmaa;
	fp_lmaa=fopen("LMAA.txt","a");
	domain=Get_Domain(1);
	
	thread_loop_c(t,domain)
	{
		begin_c_loop(c,t)
		{
			C_CENTROID(x,c,t);
			if(x[0]>=151.2 && x[0]<=158.4 && x[1]>=81.0 && x[1]<=105.0 && x[2]<=18. && x[2]>=0.)
			{
				cpt=cpt+C_YI(c,t,0)*C_VOLUME(c,t);
			}
		}
		end_c_loop(c,t)
	}
	cpa=cpt/vol;
	LMAA=cpa/M;
	fprintf(fp_lmaa,"%g\n",LMAA);
	fclose(fp_lmaa);
}

/*****************************Tau_R term******************************/

DEFINE_ON_DEMAND(Tau_R_1_udf)
{
	FILE *fp_tau_r;
	fp_tau_r=fopen("Tau_R.txt","a");
	
	Tau_R=2*LMAA;

	fprintf(fp_tau_r,"%g\n",Tau_R);
	fclose(fp_tau_r);
}

/*******************************VF term********************************/

DEFINE_ON_DEMAND(VF_1_udf)
{
	Domain *domain;
	Thread *t;
	face_t f;
	Thread *t0,*t1=NULL;
	cell_t c0,c1=-1;
	real delta_qp,qp;
	real x[ND_ND];
	real NV_VEC(A);
	real a;
	real u,v,w;
	real y;
	real rho;
	real xxx,yyy,zzz;
	real xx,yy,zz;
	FILE *fp_vf;
	fp_vf=fopen("VF.txt","a");
	domain=Get_Domain(1);
	
	thread_loop_f(t,domain)
	{
		begin_f_loop(f,t)
		{
			c0=F_C0(f,t);
			t0=F_C0_THREAD(f,t);
			F_AREA(A,f,t);
			a=NV_MAG(A);
			F_CENTROID(x,f,t);
			xxx=ROUND(x[0]*10.0);
			yyy=ROUND(x[1]*10.0);
			zzz=ROUND(x[2]*10.0);
			xx=xxx/10.0;
			yy=yyy/10.0;
			zz=zzz/10.0;
			
			if(xx==151.2 && yy>=81.0 && yy<=105.0 && zz>=0.0 && zz<=18.0)
			{
				if(BOUNDARY_FACE_THREAD_P(t))
				{
					if(NNULLP(THREAD_STORAGE(t,SV_Y)) && NNULLP(THREAD_STORAGE(t,SV_U)) && NNULLP(THREAD_STORAGE(t,SV_DENSITY)))
					{
						u=F_U(f,t);
						y=F_YI(f,t,0);
						rho=F_R(f,t);
					}
					else
					{
						u=C_U(c0,t0);
						y=C_YI(c0,t0,0);
						rho=C_R(c0,t0);
					}
				}
				else
				{
					c1 = F_C1(f,t);
					t1 = F_C1_THREAD(f,t);
					u=(C_U(c0,t0)+C_U(c1,t1))/2;
					y=(C_YI(c0,t0,0)+C_YI(c1,t1,0))/2;
					rho=(C_R(c0,t0)+C_R(c1,t1))/2;
				}
				delta_qp=delta_qp+rho*a*((fabs(u)+u)/2)*y;
			}
			if(xx==158.4 && yy>=81.0 && yy<=105.0 && zz>=0.0 && zz<=18.0)
			{
				if(BOUNDARY_FACE_THREAD_P(t))
				{
					if(NNULLP(THREAD_STORAGE(t,SV_Y)) && NNULLP(THREAD_STORAGE(t,SV_U)) && NNULLP(THREAD_STORAGE(t,SV_DENSITY)))
					{
						u=F_U(f,t);
						y=F_YI(f,t,0);
						rho=F_R(f,t);
					}
					else
					{
						u=C_U(c0,t0);
						y=C_YI(c0,t0,0);
						rho=C_R(c0,t0);
					}
				}
				else
				{
					c1 = F_C1(f,t);
					t1 = F_C1_THREAD(f,t);
					u=(C_U(c0,t0)+C_U(c1,t1))/2;
					y=(C_YI(c0,t0,0)+C_YI(c1,t1,0))/2;
					rho=(C_R(c0,t0)+C_R(c1,t1))/2;
				}
				delta_qp=delta_qp+rho*a*((fabs(u)-u)/2)*y;
			}
			if(xx>=151.2 && xx<=158.4 && yy==81.0 && zz>=0.0 && zz<=18.0)
			{
				if(BOUNDARY_FACE_THREAD_P(t))
				{
					if(NNULLP(THREAD_STORAGE(t,SV_Y)) && NNULLP(THREAD_STORAGE(t,SV_V)) && NNULLP(THREAD_STORAGE(t,SV_DENSITY)))
					{
						v=F_V(f,t);
						y=F_YI(f,t,0);
						rho=F_R(f,t);
					}
					else
					{
						v=C_V(c0,t0);
						y=C_YI(c0,t0,0);
						rho=C_R(c0,t0);
					}
				}
				else
				{
					c1 = F_C1(f,t);
					t1 = F_C1_THREAD(f,t);
					v=(C_V(c0,t0)+C_V(c1,t1))/2;
					y=(C_YI(c0,t0,0)+C_YI(c1,t1,0))/2;
					rho=(C_R(c0,t0)+C_R(c1,t1))/2;
				}
				delta_qp=delta_qp+rho*a*((fabs(v)+v)/2)*y;
			}
			if(xx>=151.2 && xx<=158.4 && yy==105.0 && zz>=0.0 && zz<=18.0)
			{
				if(BOUNDARY_FACE_THREAD_P(t))
				{
					if(NNULLP(THREAD_STORAGE(t,SV_Y)) && NNULLP(THREAD_STORAGE(t,SV_V)) && NNULLP(THREAD_STORAGE(t,SV_DENSITY)))
					{
						v=F_V(f,t);
						y=F_YI(f,t,0);
						rho=F_R(f,t);
					}
					else
					{
						v=C_V(c0,t0);
						y=C_YI(c0,t0,0);
						rho=C_R(c0,t0);
					}
				}
				else
				{
					c1 = F_C1(f,t);
					t1 = F_C1_THREAD(f,t);
					v=(C_V(c0,t0)+C_V(c1,t1))/2;
					y=(C_YI(c0,t0,0)+C_YI(c1,t1,0))/2;
					rho=(C_R(c0,t0)+C_R(c1,t1))/2;
				}
				delta_qp=delta_qp+rho*a*((fabs(v)-v)/2)*y;
			}
			if(xx>=151.2 && xx<=158.4 && yy>=81.0 && yy<=105.0 && zz==18.0)
			{
				if(BOUNDARY_FACE_THREAD_P(t))
				{
					if(NNULLP(THREAD_STORAGE(t,SV_Y)) && NNULLP(THREAD_STORAGE(t,SV_W)) && NNULLP(THREAD_STORAGE(t,SV_DENSITY)))
					{
						w=F_W(f,t);
						y=F_YI(f,t,0);
						rho=F_R(f,t);
					}
					else
					{
						w=C_W(c0,t0);
						y=C_YI(c0,t0,0);
						rho=C_R(c0,t0);
					}
				}
				else
				{
					c1 = F_C1(f,t);
					t1 = F_C1_THREAD(f,t);
					w=(C_W(c0,t0)+C_W(c1,t1))/2;
					y=(C_YI(c0,t0,0)+C_YI(c1,t1,0))/2;
					rho=(C_R(c0,t0)+C_R(c1,t1))/2;
				}
				delta_qp=delta_qp+rho*a*((fabs(w)-w)/2)*y;
			}
		}
		end_f_loop(f,t)
	}
	qp=vol*M;
	VF=1+(delta_qp/qp);
	fprintf(fp_vf,"%g\n",VF);
	fclose(fp_vf);
}

/*******************************TP term********************************/

DEFINE_ON_DEMAND(TP_1_udf)
{
	real TP;
	FILE *fp_tp;
	fp_tp=fopen("TP.txt","a");
	
	TP=vol/(PFR*VF);
	
	fprintf(fp_tp,"%g\n",TP);
	fclose(fp_tp);
}

/*******************************Q term********************************/

DEFINE_ON_DEMAND(Q_1_udf)
{
	Domain *domain;
	Thread *t;
	face_t f;
	Thread *t0,*t1=NULL;
	cell_t c0,c1=-1;
	real delta_qp;
	real x[ND_ND];
	real NV_VEC(A);
	real a;
	real u,v,w;
	real xxx,yyy,zzz;
	real xx,yy,zz;
	FILE *fp_q;
	fp_q=fopen("Q.txt","a");
	domain=Get_Domain(1);
	
	thread_loop_f(t,domain)
	{
		begin_f_loop(f,t)
		{
			c0=F_C0(f,t);
			t0=F_C0_THREAD(f,t);
			F_AREA(A,f,t);
			a=NV_MAG(A);
			F_CENTROID(x,f,t);
			xxx=ROUND(x[0]*10.0);
			yyy=ROUND(x[1]*10.0);
			zzz=ROUND(x[2]*10.0);
			xx=xxx/10.0;
			yy=yyy/10.0;
			zz=zzz/10.0;
			
			if(xx==151.2 && yy>=81.0 && yy<=105.0 && zz>=0.0 && zz<=18.0)
			{
				if(BOUNDARY_FACE_THREAD_P(t))
				{
					if(NNULLP(THREAD_STORAGE(t,SV_U)))
					{
						u=F_U(f,t);
					}
					else
					{
						u=C_U(c0,t0);
					}
				}
				else
				{
					c1 = F_C1(f,t);
					t1 = F_C1_THREAD(f,t);
					u=(C_U(c0,t0)+C_U(c1,t1))/2;
				}
				delta_qp=delta_qp+a*((fabs(u)+u)/2);
			}
			if(xx==158.4 && yy>=81.0 && yy<=105.0 && zz>=0.0 && zz<=18.0)
			{
				if(BOUNDARY_FACE_THREAD_P(t))
				{
					if(NNULLP(THREAD_STORAGE(t,SV_U)))
					{
						u=F_U(f,t);
					}
					else
					{
						u=C_U(c0,t0);
					}
				}
				else
				{
					c1 = F_C1(f,t);
					t1 = F_C1_THREAD(f,t);
					u=(C_U(c0,t0)+C_U(c1,t1))/2;
				}
				delta_qp=delta_qp+a*((fabs(u)-u)/2);
			}
			if(xx>=151.2 && xx<=158.4 && yy==81.0 && zz>=0.0 && zz<=18.0)
			{
				if(BOUNDARY_FACE_THREAD_P(t))
				{
					if(NNULLP(THREAD_STORAGE(t,SV_V)))
					{
						v=F_V(f,t);
					}
					else
					{
						v=C_V(c0,t0);
					}
				}
				else
				{
					c1 = F_C1(f,t);
					t1 = F_C1_THREAD(f,t);
					v=(C_V(c0,t0)+C_V(c1,t1))/2;
				}
				delta_qp=delta_qp+a*((fabs(v)+v)/2);
			}
			if(xx>=151.2 && xx<=158.4 && yy==105.0 && zz>=0.0 && zz<=18.0)
			{
				if(BOUNDARY_FACE_THREAD_P(t))
				{
					if(NNULLP(THREAD_STORAGE(t,SV_V)))
					{
						v=F_V(f,t);
					}
					else
					{
						v=C_V(c0,t0);
					}
				}
				else
				{
					c1 = F_C1(f,t);
					t1 = F_C1_THREAD(f,t);
					v=(C_V(c0,t0)+C_V(c1,t1))/2;
				}
				delta_qp=delta_qp+a*((fabs(v)-v)/2);
			}
			if(xx>=151.2 && xx<=158.4 && yy>=81.0 && yy<=105.0 && zz==18.0)
			{
				if(BOUNDARY_FACE_THREAD_P(t))
				{
					if(NNULLP(THREAD_STORAGE(t,SV_W)))
					{
						w=F_W(f,t);
					}
					else
					{
						w=C_W(c0,t0);
					}
				}
				else
				{
					c1 = F_C1(f,t);
					t1 = F_C1_THREAD(f,t);
					w=(C_W(c0,t0)+C_W(c1,t1))/2;
				}
				delta_qp=delta_qp+a*((fabs(w)-w)/2);
			}
		}
		end_f_loop(f,t)
	}
	Q=delta_qp;
	fprintf(fp_q,"%g\n",Q);
	fclose(fp_q);
}

/*****************************Tau_N term******************************/

DEFINE_ON_DEMAND(Tau_N_1_udf)
{
	FILE *fp_tau_n;
	fp_tau_n=fopen("Tau_N.txt","a");
	
	Tau_N=vol/Q;

	fprintf(fp_tau_n,"%g\n",Tau_N);
	fclose(fp_tau_n);
}

/*******************************ACH term********************************/

DEFINE_ON_DEMAND(ACH_1_udf)
{
	real ACH;
	FILE *fp_ach;
	fp_ach=fopen("ACH.txt","a");
	
	ACH=3600/Tau_N;
	
	fprintf(fp_ach,"%g\n",ACH);
	fclose(fp_ach);
}

/*******************************Ea term********************************/

DEFINE_ON_DEMAND(Ea_1_udf)
{
	real Ea;
	FILE *fp_ea;
	fp_ea=fopen("Ea.txt","a");
	
	Ea=Tau_N/Tau_R;
	
	fprintf(fp_ea,"%g\n",Ea);
	fclose(fp_ea);
}
