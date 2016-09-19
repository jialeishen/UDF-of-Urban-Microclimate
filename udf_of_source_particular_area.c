/**************************************************************************
                                 source of particular area
@author:Jialei Shen
@e-mail:shenjialei1992@163.com
@latest:2016.09.19
This UDF file aims to setup a source term in a particular area in the 
computational domain. The UDF file includes the following term:
1  source term
**************************************************************************/

#include "udf.h"
#include "prop.h"

/******************************source term********************************/
DEFINE_SOURCE(udf_source, c, t, dS, eqn)
{
	real x[ND_ND];
	real con,source;

	C_CENTROID(x,c,t);
       
	if(x[0]>1 && x[0]<2 && x[1]>1 &&x[1]<2 && x[2]>1 && x[2]<2)      //coordinates of the particular area
	{
		source=1;
	}
	else
	{
		source=0;
	}

	dS[eqn]=0;
	return source;
}
