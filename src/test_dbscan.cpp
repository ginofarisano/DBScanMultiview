#include "dbscan.h"
#include "distance.h"
#include <iostream>

void withOutSimFile();
void withSimFile();
void withSimFileIterationForMyData(double epsF1,double epsF2,int minPts,ofstream & fileOutput);
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


       ///////////////////////////////////

       eps1=0.11 , eps2=0.7 minPts=2

	    0  1    2      3    4    5      6     7     8

	   (1 1.1  1.2)  (2    2.1  2.2)   (3     3.1   3.2)       eps=0.11

	   Caratteristica2:

	   (5 5.2  5.4   5.6   6)   (10    10.4  10.8  11)    eps=0.7


		0
		0->1

		1
		0->1
		0->2
		0->3

		minPts=3 C1={0}
		da espandere 1,2,3

		0
		1->2

		1
		1->2
		1->3

		minPts=2 C1={0,1}
		da espandere 2,3

		0
		2->/

		1
		2->3
		2->4

		minPts=2 C1={0,1,2}
		da espandere 3,4

		0
		3->4

		1
		3->4

		minPts=1 C1={0,1,2,3}

		(SIAMO SEMPRE NEL CLUSTER1 PERCHé ANCORA C'é da "espandere 4")

		0
		4->5

		1
		4->/
		minPts=1 C1={0,1,2,3,4} CMQ è AGGIUNTO 4

		0
		5->/

		1
		5->6
		5 RUMORE

		0
		6->7

		1
		6->7
		6->8
		minPts=2 C2={6}
		da espandere 7,8

		0
		7->8

		1
		7->8
		minPts=1 C2={6,7}

		8 aggiunto anche se non c'è rimasto Nulla
		C2={6,7,8}



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


	   //////////////////////////



	 */
	int run = 2;

	if(run==0)
		//i have not a sim file
		withOutSimFile();
	else if(run==1)
		//i have a sim file
		withSimFile();
	else if (run==2){

		double eps1From = 0.4;
		double eps1To = 0.99;
		double eps2From = 0.4;
		double eps2To = 0.99;
		int minPtsFrom = 4;
		int minPtsTo = 25;

		std::cout << "Start" << std::endl;

		ofstream fileOutput;
		fileOutput.open ("output.txt");

		for(double epsF1=eps1From;epsF1<=eps1To;epsF1+=0.01){

			for(double epsF2=eps2From;epsF2<=eps2To;epsF2+=0.01){

				for(int minPts=minPtsFrom;minPts<=minPtsTo;minPts++){

					withSimFileIterationForMyData(epsF1,epsF2,minPts,fileOutput);

				}


			}

		}

		fileOutput.close();

	}

	std::cout << "End" << std::endl;
}

void withOutSimFile(){

	using namespace Metrics;

	ofstream fileOutput;
	fileOutput.open ("output.txt");

	//use this structure only if you have not a correlation matrix file
	//numbersOfFeatures is the number of view

	std::cout << "Start" << std::endl;

	//fill this structure only if you have not a correlation matrix file
	Clustering::MultidimensionalPoint multidimensionalPoint;


	int numbersOfFeatures=2;

	for(int i=0;i<numbersOfFeatures;i++){

		Clustering::Points ps;

		multidimensionalPoint.push_back(ps);
	}

	//read function like this for read file with the value
	//after call clusters.computeSimilarity(d) where d is
	//yours similarity function
	Clustering::myPoint(multidimensionalPoint[0]);
	Clustering::myPoint2(multidimensionalPoint[1]);

	// write your distance if you have not a correlation matrix file
	// the Difference distance only works with monodimensional point (modify it)

	std::vector<double> _eps_vector;

	_eps_vector.push_back(0.11);
	_eps_vector.push_back(0.5);

	//is empty if yuo have not a sim matrix
	vector<string> _sim_filename;

	//the 3 value is minPts
	Clustering::DBSCAN clusters(multidimensionalPoint, _eps_vector, 1,_sim_filename);

	Distance<Difference<Clustering::Point> > d;

	clusters.computeSimilarity(d);

	clusters.run_cluster(0);

	clusters.print_cluster(fileOutput);

	std::cout << "\nFine" << std::endl;
}

void withSimFile(){

	ofstream fileOutput;
	fileOutput.open ("output.txt");

	std::cout << "Start" << std::endl;

	//fill this structure only if you have not a correlation matrix file
	Clustering::MultidimensionalPoint multidimensionalPoint;

	//add eps for every view
	std::vector<double> _eps_vector;

	_eps_vector.push_back(0.11);
	_eps_vector.push_back(0.5);

	//initialize this structure with the names
	vector<string> _sim_filename;

	_sim_filename.push_back("UNO.csv");
	_sim_filename.push_back("DUE.csv");


	//the 3 value is minPts
	Clustering::DBSCAN clusters(multidimensionalPoint, _eps_vector, 1,_sim_filename);

	clusters.readSimilarity(_sim_filename,clusters.returnDimension());

	// run clustering (1 union, 0 intersection)
	clusters.run_cluster(0,_sim_filename.size(),clusters.returnDimension());

	clusters.print_cluster(fileOutput);

	//std::cout << clusters;


	std::cout << "\nFine" << std::endl;
}

void withSimFileIterationForMyData(double epsF1,double epsF2,int minPts,ofstream & fileOutput){

	cerr  << "eps1=" << epsF1 << ",eps2=" << epsF2 << ",minPts=" << minPts << endl;

	fileOutput << "eps1=" << epsF1 << ",eps2=" << epsF2 << ",minPts=" << minPts<< ",";
	//fill this structure only if you have not a correlation matrix file

	//fill this structure only if you have not a correlation matrix file
	Clustering::MultidimensionalPoint multidimensionalPoint;

	//add eps for every view
	std::vector<double> _eps_vector;

	_eps_vector.push_back(epsF1);
	_eps_vector.push_back(epsF2);

	//initialize this structure with the names
	vector<string> _sim_filename;

	_sim_filename.push_back("correlation1.csv");
	_sim_filename.push_back("correlation2.csv");


	//the 3 value is minPts
	Clustering::DBSCAN clusters(multidimensionalPoint, _eps_vector, minPts,_sim_filename);

	clusters.readSimilarity(_sim_filename,clusters.returnDimension());

	// run clustering (1 union, 0 intersection)
	clusters.run_cluster(1,_sim_filename.size(),clusters.returnDimension());

	clusters.print_cluster_in_file(fileOutput);

	//std::cout << clusters;

}
