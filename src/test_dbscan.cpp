#include "dbscan.h"
#include "distance.h"
#include <iostream>

int main(){

	/**
	 * The union-method assigns objects to the
	   same cluster, if they are similar in at least one of the representations

	   Caratteristica1:

	   1  2    3      4    5    6       7     8     9

	   (1 1.1  1.2)  (2    2.1  2.2)  (3     3.1   3.2)       eps=0.11

	   Caratteristica2:

	   (5 5.2  5.4   5.6  6)  (10   10.4  10.8  11)    eps=0.5

	   ______

	   1 2 3 4 5

	   Primo union core prima caratteristica: 1->1.1 (0->1)
	   Primo union core seconda caratteristica: 5->(5.2, 5.4) (0->(1,2))

	   Da espandere 1.1, 5.2, 5.4
	                 1    1    2 (minPts=2)

	   Secondo union core prima caratteristica: 1.1->1.2 (1->2)
	   Secondo union core seconda caratteristica: 5.2->5.6 (1->3), 5.4->5.6? (1->2)

		(1->2 e 1->3) quindi minPts=2
	   Da espandere 5.6 (gli altri non possono più essere espansi)

	   Secondo union core prima caratteristica: (il 5.6 si è tirato anche il 2) 2->2.1
	   Secondo union core seconda caratteristica: 5.6->6

	  minPts=1 qundi 5.6 e 6 li devo liberare
	   NON CI STA PIU' NIENTE DA ESPANDERE. QUALI SONO ADESSO I PUNTI NOO VISITATI?



	   {2    2.1  2.2 3     3.1   3.2 10   10.4  10.8  11}

	   7 8 9 6

	   Secondo union core prima caratteristica: 3->3.1
	   Secondo union core seconda caratteristica: 11->10.8

	   Da espandere 3.1, 10.8

	   Secondo union core prima caratteristica: 3.1->3.2
	   Secondo union core seconda caratteristica: 10.8->10.4

	   Da espandere 3.2, 10.4

	   Secondo union core prima caratteristica: 3.2->//
	   Secondo union core seconda caratteristica: 10.4->10



	 */

	using namespace Metrics;


	std::cout << "Inizio" << std::endl;



	Clustering::MultidimensionalPoint multidimensionalPoint;

	/** Commented **/

	// random init points dataset (dims, points)
	//Clustering::randomInit(ps, 10, 100);

	/** Commented **/

	/** Added **/

	// prova punti monodimensionali: 9 punti
	//due caratteristiche

	int numbersOfFeatures=2;

	for(int i=0;i<numbersOfFeatures;i++){

		Clustering::Points ps;

		multidimensionalPoint.push_back(ps);
	}

	Clustering::myPoint(multidimensionalPoint[0]);

	Clustering::myPoint2(multidimensionalPoint[1]);


	std::vector<double> _eps_matrix;

	//aggiungo i due eps
	_eps_matrix.push_back(0.11);
	_eps_matrix.push_back(0.5);


	// init: sim threshold, minPts
	Clustering::DBSCAN clusters(multidimensionalPoint, _eps_matrix, 2);

	// uniform distribution dataset
	//	clusters.uniformPartition();          



	// build similarity  matrix
	Distance<Difference<Clustering::Point> > d;



	clusters.computeSimilarity(d);     



	// run clustering
	clusters.run_cluster();

	clusters.print_cluster();

	//std::cout << clusters;

	std::cout << "Fine" << std::endl;

	//int test;
	//std::cin >> test;



}
