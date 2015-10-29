#include "clusters.h"
#include <boost/foreach.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "boost/algorithm/string.hpp"
#include <algorithm>
using namespace std;



namespace Clustering
{
void randomInit	(Points & ps, unsigned int dims,
		unsigned int num_points)
{
	for (unsigned int j = 0; j < num_points; j++)
	{
		Point p(dims);
		for (unsigned int i = 0; i < dims; i++)
		{
			p(i) = (-1.0 + rand() * (2.0) / RAND_MAX);
			//			std::cout << p(i) << ' ';
		}
		ps.push_back(p);
		//		std::cout << std::endl;
	}
}

void myPoint(Points & ps, unsigned int dims, unsigned int num_points){


	ofstream myfile;
	myfile.open ("output.txt");

	string line;
	ifstream read1 ("kmeans_miRNA_centers.txt");

	int numberOfDimensions=0;
	int numberPatientes=0;

	bool isTheFirst=1;

	//read number of rows
	if (read1.is_open())
	{
		while ( getline (read1,line) )
		{
			if(isTheFirst){
				myfile << "Prima riga " << line  << endl;
				isTheFirst=0;
			} else
				numberOfDimensions++;

		}

		read1.close();
	} else
		cout << "Unable to open file";

	cout << "Number of dimensions (rows) file1 " << numberOfDimensions << endl;

	myfile << "Number of dimensions (row) file1 " << numberOfDimensions << endl;;

	ifstream read2 ("kmeans_miRNA_centers.txt");

	//read a line for split
	int row=0;

	isTheFirst=1;

	//initialize structures
	if (read2.is_open())
	{
		while ( getline (read2,line) )
		{

			istringstream iss(line);

			cout << line << endl;

			//how many columns - numero pazienti???
			if(isTheFirst){

				isTheFirst=0;
				//initialize the structures
				do
				{
					string sub;
					iss >> sub;
					if(sub.size()!=0){
						Point p(numberOfDimensions);

						ps.push_back(p);

						cout << "Paziente: "<< numberPatientes << " :" << sub << endl;

						myfile <<  "Paziente: "<< numberPatientes << " :" << sub << endl;

						numberPatientes++;
					}



				} while (iss);

				cout << "Numero pazienti (prima riga): " << numberPatientes << endl;

				myfile << "Numero pazienti (prima riga): " << numberPatientes << endl;

				continue;
			}



			int column = 0;

			do
			{
				string sub;
				iss >> sub;

				size_t n = std::count(sub.begin(), sub.end(), '\"');
				std::string::size_type sz;     // alias of size_t

				if(n==2){
					cout << "Fake: " << sub << endl;
					myfile <<"Fake: " << sub << endl;

				} else if(sub.size()!=0){

					cout.precision(15);
					myfile.precision(15);

					cout << "Indice colonna: " << column << endl;
					myfile << "Indice colonna: " << column << endl;

					cout << "Stringa letta: " << sub << endl;
					myfile <<"Stringa letta: " << sub << endl;
					try{
						ps[column](row) =  std::stod (sub);

					} catch (const std::invalid_argument&) {
						std::cerr << "Argument is invalid\n";
						myfile <<"Argument is invalid\n" << sub << endl;

						ps[column](row) =  0;
						cout.precision(15);

						cout << "Numero scritto: " << ps[column](row) << endl;


						myfile <<"Numero scritto: " << ps[column](row) << endl;

						continue;

					}


					cout << "Numero scritto: " << ps[column](row) << endl;
					myfile <<"Numero scritto: " << ps[column](row) << endl;

					column ++;
				}


			} while (iss);

			cout << "Riga: " << row << ". Numero di colonne lette: " << column << endl;
			myfile << "Riga: " << row << ". Numero di colonne lette: " << column << endl;

			//row is the dimensions
			row++;
		}
		read2.close();
	} else
		cout << "Unable to open file";


	// LEGGO SE FILE E' STATO LETTO BENE

	Clustering::Points  p1 = ps;

	unsigned int size2 = p1.size();

	cout << "Prova lettura.QUESTA E' LA STRUTTUTA POINTS Numero pazienti: " << size2 << endl;
	myfile << "Prova lettura.QUESTA E' LA STRUTTUTA POINTS Numero pazienti: " << size2 << endl;

	for (unsigned int i=0; i < size2; i++){

		cout << endl;
		//ogni punto può avere più dimensioi
		Clustering::Point p21 = p1[i];

		unsigned int size3 = p21.size();

		for (unsigned int j=0; j < size3; j++){
			cout << "|" << p21(j) << "|";
			myfile << "|" << p21(j) << "|";
		}
	}


	// LEGGO SE FILE E' STATO LETTO BENE


	//versione Ciro NON FUNZIONANTE

	/*
	std::cout << "Created point 1" << std::endl;
		string line;
		  ifstream myfile("kmeans_miRNA_centers.txt");
		  if (myfile.is_open())
		  {


			  	  string sLine;
			  	  int number_patients;
			      getline(myfile, sLine);
			      cout << "number of patients" << endl;
			      istringstream iss(sLine);
			      vector<string> patiences;
			      copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(patiences));
			      number_patients =  patiences.size();
			      string s2;
			      string variabile;
			      ofstream output;
			      output.open("output.txt");
			      int dimensione = 201;
			      float value;
			      float matrix[number_patients][dimensione];
			      Point p(dimensione);
			      for(int i = 0; i < number_patients; i++){
			    	  for(int j = 0; j < dimensione; j++ ){
			    		  myfile >> variabile;
			    		  value = atof(variabile.c_str());
			    		  //prova commit
			    		  //test test s<fdaklf
			    		  //cout << variabile << endl;

			    		  p(j) = value;
			    		  output << p(j) << ' ';


			    	  }
			    	  ps.push_back(p);

			    	  cout << "*************************"+i << endl;
			      }




		    myfile.close();
		  }

		  else cout << "Unable to open file";

			// LEGGO SE FILE E' STATO LETTO BENE
		  ofstream ou;
		  ou.open ("outputMatriceCiro.txt");

			Clustering::Points  p1 = ps;

			unsigned int size2 = p1.size();

			cout << "Prova lettura.QUESTA E' LA STRUTTUTA POINTS Numero pazienti: " << size2 << endl;
			ou << "Prova lettura.QUESTA E' LA STRUTTUTA POINTS Numero pazienti: " << size2 << endl;

			for (unsigned int i=0; i < size2; i++){

				cout << endl;
				//ogni punto può avere più dimensioi
				Clustering::Point p21 = p1[i];

				unsigned int size3 = p21.size();

				for (unsigned int j=0; j < size3; j++){
					cout << "|" << p21(j) << "|";
					ou << "|" << p21(j) << "|";
				}
			}


			// LEGGO SE FILE E' STATO LETTO BENE

	 */
}

void myPoint2(Points & ps, unsigned int dims, unsigned int num_points){


	ofstream myfile;
	myfile.open ("output2.txt");

	string line;
	ifstream read1 ("kmeans_miRNASeq_centers.txt");

	int numberOfDimensions=0;
	int numberPatientes=0;

	bool isTheFirst=1;

	//read number of rows
	if (read1.is_open())
	{
		while ( getline (read1,line) )
		{
			if(isTheFirst){
				myfile << "Prima riga " << line  << endl;
				isTheFirst=0;
			} else
				numberOfDimensions++;

		}

		read1.close();
	} else
		cout << "Unable to open file";

	cout << "Number of dimensions (rows) file1 " << numberOfDimensions << endl;

	myfile << "Number of dimensions (row) file1 " << numberOfDimensions << endl;;

	ifstream read2 ("kmeans_miRNASeq_centers.txt");

	//read a line for split
	int row=0;

	isTheFirst=1;

	//initialize structures
	if (read2.is_open())
	{
		while ( getline (read2,line) )
		{

			istringstream iss(line);

			cout << line << endl;

			//how many columns - numero pazienti???
			if(isTheFirst){

				isTheFirst=0;
				//initialize the structures
				do
				{
					string sub;
					iss >> sub;
					if(sub.size()!=0){
						Point p(numberOfDimensions);

						ps.push_back(p);

						cout << "Paziente: "<< numberPatientes << " :" << sub << endl;

						myfile <<  "Paziente: "<< numberPatientes << " :" << sub << endl;

						numberPatientes++;
					}



				} while (iss);

				cout << "Numero pazienti (prima riga): " << numberPatientes << endl;

				myfile << "Numero pazienti (prima riga): " << numberPatientes << endl;

				continue;
			}



			int column = 0;

			do
			{
				string sub;
				iss >> sub;

				size_t n = std::count(sub.begin(), sub.end(), '\"');
				std::string::size_type sz;     // alias of size_t

				if(n==2){
					cout << "Fake: " << sub << endl;
					myfile <<"Fake: " << sub << endl;

				} else if(sub.size()!=0){

					cout.precision(15);
					myfile.precision(15);

					cout << "Indice colonna: " << column << endl;
					myfile << "Indice colonna: " << column << endl;

					cout << "Stringa letta: " << sub << endl;
					myfile <<"Stringa letta: " << sub << endl;
					try{
						ps[column](row) =  std::stod (sub);

					} catch (const std::invalid_argument&) {
						std::cerr << "Argument is invalid\n";
						myfile <<"Argument is invalid\n" << sub << endl;

						ps[column](row) =  0;
						cout.precision(15);

						cout << "Numero scritto: " << ps[column](row) << endl;


						myfile <<"Numero scritto: " << ps[column](row) << endl;

						continue;

					}


					cout << "Numero scritto: " << ps[column](row) << endl;
					myfile <<"Numero scritto: " << ps[column](row) << endl;

					column ++;
				}


			} while (iss);

			cout << "Riga: " << row << ". Numero di colonne lette: " << column << endl;
			myfile << "Riga: " << row << ". Numero di colonne lette: " << column << endl;

			//row is the dimensions
			row++;
		}
		read2.close();
	} else
		cout << "Unable to open file";

	/************************/
	// LEGGO SE FILE E' STATO LETTO BENE

	Clustering::Points  p1 = ps;

	unsigned int size2 = p1.size();

	cout << "Prova lettura.QUESTA E' LA STRUTTUTA POINTS Numero pazienti: " << size2 << endl;
	myfile << "Prova lettura.QUESTA E' LA STRUTTUTA POINTS Numero pazienti: " << size2 << endl;

	for (unsigned int i=0; i < size2; i++){

		cout << endl;
		//ogni punto può avere più dimensioi
		Clustering::Point p21 = p1[i];

		unsigned int size3 = p21.size();

		for (unsigned int j=0; j < size3; j++){
			cout << "|" << p21(j) << "|";
			myfile << "|" << p21(j) << "|";
		}
	}

	/************************/
	// LEGGO SE FILE E' STATO LETTO BENE


}



//	/** Added **/
//
//	// assign each point to a new cluster
//	void Clusters::uniformPartition()
//	{
//		PointId pid = 0;
//		ClusterId cid = 0;
//		BOOST_FOREACH(Point p, _ps)
//		{
//			// create a new cluster for this current point
//			Cluster c;
//			c.push_back(pid++);
//			_clusters.push_back(c);
//			_pointId_to_clusterId.push_back(cid++);
//		}
//	}

// findNeighbors(PointId pid, double threshold)
Neighbors Clusters::findNeighbors(PointId pid, double threshold,int view, std::vector<bool> _visited)
{

	Neighbors ne;

	_sim sim = _sim_matrix[view];


	for (unsigned int j=0; j <sim.size1(); j++)
	{

		//ho calcolato sono una triangolare
		if 	((pid != j ) &&  (sim(pid, j)) < threshold && !_visited[j] )
		{
			std::cout << "Vista numero " << view << ". La similarità tra " << pid << " e " << j << " è " << (sim(pid, j)) << std::endl;
			ne.push_back(j);
			//std::cout << "sim(" << pid  << "," << j << ")" << _sim(pid, j) << ">" << threshold << std::endl;
		}
	}


	return ne;
};


// single point output
std::ostream& operator<<(std::ostream& o, const Point& p)
{
	o << "{ ";
	BOOST_FOREACH(Point::value_type x, p)
	{
		o << " " << x;
	}
	o << " }, ";

	return o;
}

// single cluster output
std::ostream& operator<<(std::ostream& o, const Cluster& c)
{
	o << "[ ";
	BOOST_FOREACH(PointId pid, c)
	{
		o << " " << pid;
	}
	o << " ]";

	return o;
}

//	// clusters output
//	std::ostream& operator<<(std::ostream& o, const Clusters& cs)
//	{
//		ClusterId cid = 1;
//		BOOST_FOREACH(Cluster c, cs._clusters)
//		{
//			o << "c(" << cid++ << ")=";
//
//			BOOST_FOREACH(PointId pid, c)
//			{
//				o << cs._ps[pid];
//			}
//			o << std::endl;
//		}
//		return o;
//	}


};
