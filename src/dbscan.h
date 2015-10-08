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

			for(int i=0;i<ps.size();i++){
				_noise x;
				_visited y;

				x.resize(ps[i].size(), false);
				y.resize(ps[i].size(), false);

				_noise_matrix.push_back(x);
				_visited_matrix.push_back(y);

			}

		};

		// 
		// The clustering algo
		//
		//void run_cluster() ;

	private:

	// eps radiuus
	// Two points are neighbors if the distance 
	// between them does not exceed threshold value.


		std::vector<double> _eps_matrix;

	//minimum number of points
		unsigned int _minPts;

	// noise vector
	typedef std::vector<bool> _noise;

	std::vector<_noise> _noise_matrix;

	// noise vector
	typedef std::vector<bool> _visited;

	std::vector<_visited> _visited_matrix;

	};
};
#endif
