\name{torus}
\alias{torus}
\alias{setTorusSeed}
\title{Torus algorithm}
\description{
  Torus algorithm for quasi random number generations.
}
\usage{
torus(n, dim)
setTorusSeed(seed)
}
\arguments{
  \item{n}{number of observations. If length(n) > 1, 
  		  the length is taken to be the number required.}
  \item{dim}{dimension of observations (must be <=100)}
  \item{seed}{a single value, interpreted as a positive integer for the seed.}
}
\details{
	The nth term of the Torus algorithm in d dimension is defined by
	    	\deqn{u_n = \left(frac(n \sqrt{p_1}), ..., frac(n \sqrt{p_d}) \right)}{%
			    u_n = (frac(n sqrt(p_1)), ..., frac(n sqrt(p_d)) )}
	where \eqn{p_i} denotes the ith prime number, \eqn{frac} the fractional part
	(i.e. \eqn{frac(x) = x-floor(x)}).	
}
\value{
  \code{torus} generates random deviates, it returns a \eqn{n}x\eqn{dim} matrix.

  \code{setTorusSeed} set the seed.
}
\references{
Planchet F., Jacquemin J. (2003), \emph{L'utilisation de methodes de 
simulation en assurance}. Bulletin Francais d'Actuariat, vol. 6, 11, 3-69.
}
\seealso{
    \code{\link{.Random.seed}}
}
\author{
 C. Dutang
}
\examples{
torus(100,1)

# example of setting the seed
setTorusSeed(1)
torus(5,1)
setTorusSeed(6)
torus(5,1)
#the same
setTorusSeed(1)
torus(10,1)

#tests
u <- torus(1000, 1)
#Kolmogorov Smirnov stat should be 0.0019
ks.test(u, punif) 
#??
chisq.test(u)
	
u <- torus(10000, 1)
#Kolmogorov Smirnov stat should be 0.0003
ks.test(u, punif) 
#??
chisq.test(u)
	
}
\keyword{distribution}
