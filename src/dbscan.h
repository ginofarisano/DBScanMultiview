#ifndef DBSCAN_H
#define DBSCAN_H
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>


#include "clusters.h"

namespace Clustering{

	class DBSCAN : public Clusters
	{
	public:
		DBSCAN(MultidimensionalPoint & ps, std::vector<double> eps, unsigned int minPts) :
		  Clusters(ps), _eps_matrix(eps), _minPts(minPts)
		{
			_noise.resize(ps[0].size(), false);
			_visited.resize(ps[0].size(), false);

		};

		//
		// The clustering algo
		//
		void run_cluster(bool UnionOrIntersection=0);
		void print_cluster();

	private:

	// eps radiuus
	// Two points are neighbors if the distance 
	// between them does not exceed threshold value.


	std::vector<double> _eps_matrix;

	//minimum number of points
	unsigned int _minPts;

	// noise vector
	std::vector<bool> _noise;

	public:
		std::vector<bool> _visited;


	};
};
#endif
