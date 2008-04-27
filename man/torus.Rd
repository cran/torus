\name{torus}
\alias{torus}
\alias{setTorusSeed}
\alias{congrurand}
\title{Torus algorithm}
\description{
  Torus algorithm for quasi random number generations and general linear congruential generators for pseudo random number generations.
}
\usage{
torus(n, dim = 1, prime, mixed = FALSE, alpha = 100, usetime = TRUE)
setTorusSeed(seed)
congrurand(n, dim = 1, mod = 2^31-1, mult = 16807, incr = 0, echo)
}
\arguments{
  \item{n}{number of observations. If length(n) > 1, 
  		  the length is taken to be the number required.}
  \item{dim}{dimension of observations (must be <=100, default 1).}
  \item{prime}{a single prime number or a vector of prime numbers to be used
  		 in the Torus sequence. (optional argument).}
  \item{mixed}{a logical to use the mixed Torus algorithm, default FALSE.}
  \item{alpha}{a positive real used in the mixed Torus algorithm, default 100.}
  \item{usetime}{a logical to use the machine time to start the Torus sequence, 
  		   default TRUE. if FALSE, the Torus sequence start from the first term.}
  \item{seed}{a single value, interpreted as a positive integer for the seed.}
  \item{mod}{an integer defining the modulus of the linear congruential generator.}
  \item{mult}{an integer defining the multiplier of the linear congruential generator.}
  \item{incr}{an integer defining the increment of the linear congruential generator.}
  \item{echo}{a logical to plot the seed while computing the sequence.}
}
\details{
	The \eqn{k}th term of the Torus algorithm in d dimension is given by
	    	\deqn{u_k = \left(frac(k \sqrt{p_1}), ..., frac(k \sqrt{p_d}) \right)}{%
			    u_k = (frac(k sqrt(p_1)), ..., frac(k sqrt(p_d)) )}
	where \eqn{p_i} denotes the ith prime number, \eqn{frac} the fractional part
	(i.e. \eqn{frac(x) = x-floor(x)}). The Torus sequence starts from \eqn{k=1} if
	\code{usetime = FALSE} otherwise \eqn{k=(tv.tv_usec << 16) ^ tv.tv_sec}.	
	
	The \eqn{k}th term of a linear congruential generator is defined as
	   \deqn{u_k = \frac{ ( a * u_{k-1} + c ) mod m }{m}}{%
			[ ( a * u_{k-1} + c ) mod m ] / m}
	where \eqn{a} denotes the multiplier, \eqn{c} the increment and \eqn{m} 
	the modulus, with the constraint \eqn{0 <= a < m } and \eqn{0 <= c < m }.
	The default setting is the Park Miller sequence with \eqn{a=16807}, 
	\eqn{m=2^31-1} and \eqn{c=0}.
}
\value{
  \code{torus} and \code{congrurand} generates random variables in ]0,1[ and [0,1[ respectively. It returns a \eqn{n}x\eqn{dim} matrix, when \code{dim}>1 otherwise a vector of length \code{n}.

  \code{setTorusSeed} set the seed of the \code{torus} package 
(i.e. both for the \code{torus} and \code{congrurand} functions).
}
\references{
Planchet F., Jacquemin J. (2003), \emph{L'utilisation de methodes de 
simulation en assurance}. Bulletin Francais d'Actuariat, vol. 6, 11, 3-69. (available on line)

Park S. K., Miller K. W. (1988), \emph{Random number generators: good
ones are hard to find}. Association for Computing Machinery, vol. 31, 10, 1192-2001. 

Wikipedia (2008), \emph{a linear congruential generator}.
}
\seealso{
    \code{\link{.Random.seed}}
}
\author{
 C. Dutang
}
\examples{
torus(100)

# example of setting the seed
setTorusSeed(1)
torus(5)
setTorusSeed(6)
torus(5)
#the same
setTorusSeed(1)
torus(10)

#no use of the machine time
torus(10, use=FALSE)

#tests
u <- torus(1000)
#Kolmogorov Smirnov stat should be 0.0019
ks.test(u, punif) 
	
u <- torus(10000)
#Kolmogorov Smirnov stat should be 0.0003
ks.test(u, punif) 


# Park Miller sequence, i.e. mod = 2^31-1, mult = 16807, incr=0
# the first 10 seeds used in Park Miller sequence
# 16807          1
# 282475249          2
# 1622650073          3
# 984943658          4
# 1144108930          5
# 470211272          6
# 101027544          7
# 1457850878          8
# 1458777923          9
# 2007237709         10
setTorusSeed(1)
congrurand(10, echo=TRUE)

# the 9998+ th terms 
# 925166085       9998
# 1484786315       9999
# 1043618065      10000
# 1589873406      10001
# 2010798668      10002
setTorusSeed(1614852353) #seed for the 9997th term
congrurand(5, echo=TRUE)

	
}
\keyword{distribution}
