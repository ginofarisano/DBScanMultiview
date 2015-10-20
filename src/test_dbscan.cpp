#include "dbscan.h"
#include "distance.h"
#include <iostream>

int main(){

	/**
	 * The union-method assigns objects to the
	   same cluster, if they are similar in at least one of the representations

	   minPts=2

	    0  1    2      3    4    5      6     7     8

	   (1 1.1  1.2)  (2    2.1  2.2)   (3     3.1   3.2)       eps=0.11

	   Caratteristica2:

	   (5 5.2  5.4   5.6   6)   (10    10.4  10.8  11)    eps=0.5

	   ______

	   C1

	   Prima vista: 0->1
	   Seconda vista:0->1,2
	   minPts=2, da espandere |1|,|2|
	   C1={0}

	   Prima vista: 1->2
	   Seconda vista: 1->2,3
	   minPts=2, da espandere |2|,3
	   C1={0,1}

	   Prima vista: /
	   Seconda vista: 2-> 3,4
	   minPts=2, da aspandere 3,4
	   C1={0,1,2}

	   Prima vista: 3->4
	   Seconda vista: 3->4
	   minPts=1
	   C1={0,1,2,3}

	   C2
	   Prima vista: 4->5
	   Seconda vista: /
	   minPts=1
       RUMORE

       C2
       Prima vista: /
       Seconda vista: 5->6
       minPts=1
       RUMORE

       C2
       Prima vista: 6->7
       Seconda vista: 6->7
       minPts=1
       RUMORE

       C2
       Prima vista: 7->8
       Seconda vista: 7->8
       minPts=1
       RUMORE


       /////////////////////////////////////
       ////////////////////////////////////

       minPts=1

       C1

	   Prima vista: 0->1
	   Seconda vista:0->1,2
	   minPts=2, da espandere 1,2
	   C1={0}

	   Prima vista: 1->2
	   Seconda vista: 1->2,3
	   minPts=2, da espandere 2,3
	   C1={0,1}

	   Prima vista: /
	   Seconda vista: 2-> 3,4
	   minPts=2, da aspandere 3,4
	   C1={0,1,2}

	   Prima vista: 3->4
	   Seconda vista: 3->4
	   minPts=1, da aspandere 4
	   C1={0,1,2,3}

	   Prima vista: 4->5
	   Seconda vista: /
	   minPts=1, da espandere 5
	   C1={0,1,2,3,4}

       Prima vista: /
       Seconda vista: 5->6
       minPts=1, da espandere 6
       C1={0,1,2,3,4,5}

       Prima vista: 6->7
       Seconda vista: 6->7
       minPts=1, da espandere 7
       C1={0,1,2,3,4,5,6}

       Prima vista: 7->8
       Seconda vista: 7->8
       minPts=1, da espandere 8
       C1={0,1,2,3,4,5,6,7}

       Prima vista:
       Seconda vista:
       minPts=0
       C1={0,1,2,3,4,5,6,7,8}
       N.B 8 è in espandiCluster->cmq è aggiunto



	  Intersezione


		minPts=1

	    0  1    2      3    4    5      6     7     8

	   (1 1.1  1.2)  (2    2.1  2.2)   (3     3.1   3.2)       eps=0.11

	   Caratteristica2:

	   (5 5.2  5.4   5.6   6)   (10    10.4  10.8  11)    eps=0.5


	   C1

	   Prima vista: 0->1
	   Seconda vista:0->1,2
	   minPts=1, da espandere |1|,(2 tolto perchè fa parte solo della vista)
	   C1={0}

	   Prima vista: 1->2
	   Seconda vista:1->2,3
	   minPts=1, da espandere 2,(3 tolto perchè fa parte solo della vista)
	   C1={0,1}

	   Prima vista:
	   Seconda vista:2->3
	   minPtd=0
	   C1={0,1,2}
	   Da espandere (3 tolto perchè fa parte solo della vista, N.B 2 non è  rumore perchè
	   siamo in espandiCluster->ergo è aggiunto cmq)

	   C2

	   Prima vista: 3->4
	   Seconda vista:3->4
	   minPts=1, da espandere 4
	   C2={3}

	   Prima vista: 4->5
	   Seconda vista:/
	   minPts=0,
	   C2={3,4}

	   C3

	   Prima vista:
	   Seconda vista:5->6
	   minPts=0
	   RUMORE

	   C3

	   Prima vista: 6->7
	   Seconda vista:6->7
	   minPts=1, da espandere 7
	   C2={6}

	   Prima vista: 7->8
	   Seconda vista:7->8
	   minPts=1, da espandere 7 (che si tira dentro pure 8)
	   C2={6,7,8}






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
	Clustering::DBSCAN clusters(multidimensionalPoint, _eps_matrix, 1);

	// uniform distribution dataset
	//	clusters.uniformPartition();          



	// build similarity  matrix
	Distance<Difference<Clustering::Point> > d;



	clusters.computeSimilarity(d);     



	// run clustering
	clusters.run_cluster();

	clusters.print_cluster();

	//std::cout << clusters;

	std::cout << "\nFine" << std::endl;

	//int test;
	//std::cin >> test;



}
