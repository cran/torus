/*****************************************************************************
 *   Copyright (c) 2008 Christophe Dutang									 *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA                  *
 *                                                                           *
 *****************************************************************************/
/*
 *  Torus algorithm to generate quasi random numbers
 *
 *		C functions	
 *  
 *	Many ideas are taken from src/main/RNG.c
 *
 */

#include "torus.h"
#include <time.h>
#include <sys/time.h>

static long seed; 
static int isInit;

/************/
/* constant */
//the first 100 prime numbers
const static int primeNumber[] =
{
	2,      3,      5,      7,     11,     13,     17,     19,     23,     29, 
	31,     37,     41,     43,     47,     53,     59,     61,     67,     71, 
	73,     79,     83,     89,     97,    101,    103,    107,    109,    113, 
    127,    131,    137,    139,    149,    151,    157,    163,    167,    173, 
    179,    181,    191,    193,    197,    199,    211,    223,    227,    229, 
    233,    239,    241,    251,    257,    263,    269,    271,    277,    281, 
    283,    293,    307,    311,    313,    317,    331,    337,    347,    349, 
    353,    359,    367,    373,    379,    383,    389,    397,    401,    409, 
    419,    421,    431,    433,    439,    443,    449,    457,    461,    463, 
    467,    479,    487,    491,    499,    503,    509,    521,    523,    541 
};

/***************************/
/* quasi random generation */

//main function used .Call()
SEXP doTorus(SEXP n, SEXP d)
{
	if (!isNumeric(n) || !isNumeric(d))
		error(_("invalid argument"));
	
	//temporary working variables
	int nb = asInteger( n ); //number of random vectors
	int dim  = asInteger( d ); //dimension of vector
	
	
	//result
	double *u = (double *) R_alloc(nb * dim, sizeof(double));
	SEXP resultinR; //result in R
	PROTECT(resultinR = allocMatrix(REALSXP, nb, dim)); //allocate a n x d matrix
	u = REAL( resultinR ); //plug the C pointer on the R type
	
	R_CheckStack();
	
	//computation step
	torus(u, nb, dim);
	
	UNPROTECT(1);
	
	return resultinR;
}

//compute the vector sequence of the Torus algorithm
void torus(double *u, int nb, int dim)
{
	int i, j;
	
	if (!R_FINITE(nb) || !R_FINITE(dim))
		error(_("non finite argument"));
	
	//sanity check
	if(dim >= 100) error(_("Torus algorithm not yet implemented for dimension %d)"), dim);
	
	if(!isInit) 
		randSetSeed();	
	
	
	//u_ij is the Torus sequence term with n = state + i and s = j + 1
	//u is stored column by column
	for(j = 0; j < dim; j++)
		for(i = 0; i < nb; i++) 
			u[i + j * nb] = fracPart( (seed + i) * sqrt( primeNumber[j] ) ) ;
	
	isInit = 0;		
}

//fractional part
R_INLINE double fracPart(double x)
{
	return x - floor(x);
}


/****************/
/* set the seed */

//main function used .Call()
//seed set by the user
//idea taken from the R internal C function do_setseed
SEXP doSetTorusSeed(SEXP s)
{
	if (!isNumeric(s))
		error(_("invalid argument"));
	
	setTorusSeed( (long) asInteger(s) );
	return R_NilValue;	
}

void setTorusSeed(long s)
{
	if (!R_FINITE(s))
		error(_("non finite seed"));
	
	seed = s;
	isInit = 1;
}

//randomize and set the seed when not initialized
//idea taken from the R internal C function Randomize
void randSetSeed()
{
	
	//seed = (long) time(NULL);
	struct timeval tv;
    gettimeofday (&tv, NULL);
    seed = ((long long) tv.tv_usec << 16) ^ tv.tv_sec;
	/*Rprintf("%.30g \n", tv.tv_usec);	
	 Rprintf("%.30d \n", (uint64_t) tv.tv_usec);		
	 #if HAVE_GETTIMEOFDAY
	 Rprintf("zogzogz\n");
	 #endif			*/
	isInit = 1;
}