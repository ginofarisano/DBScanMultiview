#ifndef DBSCAN_H
#define DBSCAN_H
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>


#include "clusters.h"

namespace Clustering{

class DBSCAN : public Clusters
{
public:
	DBSCAN(MultidimensionalPoint & ps, std::vector<double> eps, unsigned int minPts,vector<string> _sim_filename) :
		Clusters(ps), _eps_vector(eps), _minPts(minPts)
{

		//the first cell is empty
		int dimension = -1;
		int numFiles = -1;

		//if I have not sim matrix
		if(ps.size()>0){
			_noise.resize(ps[0].size(), false);
			_visited.resize(ps[0].size(), false);
		} else {

			numFiles = _sim_filename.size();

			ifstream read (_sim_filename.at(0));

			string line;

			if(std::getline(read,line))
			{
				std::stringstream  lineStream(line);
				std::string        cell;

				while(std::getline(lineStream,cell,','))
				{
					dimension++;
				}
			}

			read.close();


			_noise.resize(dimension, false);
			_visited.resize(dimension, false);

			this->dimension = dimension;

		}

};

	//
	// The clustering algo
	//
	void run_cluster(bool UnionOrIntersection=0, int dimension=0, int view=0);
	void print_cluster();
	//
	// The clustering algo
	//

	int returnDimension(){
		return dimension;
	}

private:

	// eps radiuus
	// Two points are neighbors if the distance 
	// between them does not exceed threshold value.


	std::vector<double> _eps_vector;

	//minimum number of points
	unsigned int _minPts;

	// noise vector
	std::vector<bool> _noise;

	int dimension;

public:
	std::vector<bool> _visited;


};
};
#endif
