#include "dbscan.h"
#include <boost/foreach.hpp>

using namespace std;

namespace Clustering
{
	void DBSCAN::run_cluster() 
	{

		ClusterId cid = 1;

		for(int i=0;i<_ps.size();i++){

			Points x = _ps[0];



			for (PointId pid = 0; pid < x.size(); pid++){
				
				_visited y;
				y = _visited_matrix[i];
				// not already visited
				if (!y[pid]){
					y[pid]=true;

					Neighbors ne = findNeighbors(pid, _eps_matrix[i]);


				}


			}


		}



	}

};
