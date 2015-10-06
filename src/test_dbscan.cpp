#include "dbscan.h"
#include "distance.h"
#include <iostream>

int main(){

	using namespace Metrics;


	std::cout << "Inizio" << std::endl;

	Clustering::Points ps;

	/** Commented **/

	// random init points dataset (dims, points)
	//Clustering::randomInit(ps, 10, 100);

	/** Commented **/

	/** Added **/

	// prova punti monodimensionali: tre cluster da 3 punti
	Clustering::myPoint(ps, 1, 9);

	/** Added **/


	// init: sim threshold, minPts
	Clustering::DBSCAN clusters(ps, 0.11, 2);

	// uniform distribution dataset
	//	clusters.uniformPartition();          

	// build similarity  matrix
	Distance<Difference<Clustering::Point> > d;
	clusters.computeSimilarity(d);     

	// run clustering
	clusters.run_cluster();

	std::cout << clusters;

	std::cout << "Fine" << std::endl;

	int test;
	std::cin >> test;

}
