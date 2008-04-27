/**********************************************************************************************
 *   Copyright (c) 2008 Christophe Dutang                                                                    *
 *                                                                                                                                           *
 *   This program is free software; you can redistribute it and/or modify                 *
 *   it under the terms of the GNU General Public License as published by           *
 *   the Free Software Foundation; either version 2 of the License, or                     *
 *   (at your option) any later version.                                                                              *
 *                                                                                                                                           *
 *   This program is distributed in the hope that it will be useful,                               *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   *
 *   GNU General Public License for more details.                                                      *
 *                                                                                                                                           *
 *   You should have received a copy of the GNU General Public License             *
 *   along with this program; if not, write to the                                                             *
 *   Free Software Foundation, Inc.,                                                                                *
 *   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA                               *
 *                                                                                                                                           *
 **********************************************************************************************/
/*
 *  Torus algorithm to generate quasi random numbers
 *  
 *			header file
 *
 */

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <R_ext/Error.h>

#include "locale.h"
#include "mt64.h"

#include <time.h>
#include <sys/time.h>


/* Functions accessed from .Call() */
SEXP doTorus(SEXP n, SEXP d, SEXP p, SEXP ismixed, SEXP a, SEXP timedseed);
SEXP doSetTorusSeed(SEXP s);
SEXP doCongruRand(SEXP n, SEXP d, SEXP modulus, SEXP multiplier, SEXP increment, SEXP echo);

/* utility functions */
void torus(double *u, int nb, int dim, int *prime, int ismixed, double alpha, int usetime);
static R_INLINE double fracPart(double x);
void congrurand(double *u, int nb, int dim, unsigned long long mod, unsigned long long mult, unsigned long long incr, int show);

void setTorusSeed(long s);
static void randSetSeed();
