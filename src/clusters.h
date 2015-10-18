#include <vector>
#include <cmath>
#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/foreach.hpp>
#include "distance.h"

/**
 * ciao sono io (gino)
 */

namespace Clustering{

// a single point is made up of vector of doubles
typedef boost::numeric::ublas::vector<double> Point;
typedef std::vector<Point> Points;

/** added **/

//struttura per mantenere più viste
typedef std::vector<Points> MultidimensionalPoint;

/** added **/

typedef unsigned int ClusterId;
typedef unsigned int PointId;

// a cluster is a vector of pointid
typedef std::vector<PointId> Cluster;
// a set of Neighbors is a vector of pointid
typedef std::vector<PointId> Neighbors;




void randomInit	(Points & ps, unsigned int dims = 5,
		unsigned int num_points = 10);

void myPoint(Points & ps, unsigned int dims = 5,
		unsigned int num_points = 10);

void myPoint2(Points & ps, unsigned int dims = 5,
		unsigned int num_points = 10);

class Clusters
{
public:
	Clusters (MultidimensionalPoint & ps) : _ps(ps)
{
		_pointId_to_clusterId.resize(_ps[0].size(), 0);


};

	// assign each point to a new cluster
	void uniformPartition();

	// compute similarity
	template <typename Distance_type>
	void computeSimilarity(Distance_type & d)
	{

		unsigned int size = _ps.size();


		for(int i=0;i<size;i++){
			_sim x;
			x.resize(_ps[i].size(),_ps[i].size(),false);
			_sim_matrix.push_back(x);
		}


		for(int z=0;z<size;z++){


			Clustering::Points  p1 = _ps[z];

			unsigned int size2 = p1.size();


			for (unsigned int i=0; i < size2; i++){

				//ogni punto può avere più dimensioi
				Clustering::Point p21 = p1[i];

				for (unsigned int j=i+1; j < size2; j++)
				{


					Clustering::Point p22 = p1[j];


					//std::cout << "Il numero matriciale è " << a << "e " << b << std::endl;


					//lo sto facendo per tutte le dimensioni perchè gli passo il punto che
					//è multidimensionale
					_sim_matrix[z](j, i) = _sim_matrix[z](i, j) = d.similarity(p21, p22);


					std:: cout << "|" <<  j << "," << i << ": " << _sim_matrix[z](j, i) << "| ";


				}


				std::cout << std::endl;
			}



		}

	};

	//
	// findNeighbors(PointId pid, double threshold)
	//
	// this can be implemented with reduced complexity by using R+trees
	//
	Neighbors findNeighbors(PointId pid, double threshold,int view, std::vector<bool> _visited);

protected:
	// the collections of points we are working on
	MultidimensionalPoint& _ps;

	// mapping point_id -> clusterId
	std::vector<ClusterId> _pointId_to_clusterId;





	// the collection of clusters
	std::vector<Cluster> _clusters;

	// simarity_matrix
	typedef boost::numeric::ublas::matrix<double> _sim;

	std::vector<_sim> _sim_matrix;


	friend
	std::ostream& operator << (std::ostream& o, const Clusters& c);
};

}
