#include "dbscan.h"
#include <boost/foreach.hpp>
#include <map>

using namespace std;

namespace Clustering{

ClusterId cid;

void DBSCAN::run_cluster(bool UnionOrIntersection, int views, int dimension){

	cid = 0;

	// foreach pid...ho messo _ps[0] perchè il numero di individui
	// è lo stesso per ogni vista

	int size;
	int size_v;

	if(_ps.size()>0){
		//numero di individui
		size=_ps[0].size();
		//numero di viste
		size_v=_ps.size();
	} else {
		//numero di individui
		size=dimension;
		//numero di viste
		size_v=views;
	}

	for (PointId pid = 0; pid < size; pid++){

		if (!_visited[pid]){
			_visited[pid] = true;
		} else
			continue;

		//std::cout <<"New: " << pid << std::endl;

		//inizializzato per ogni PID
		Neighbors* neighbors_array = new Neighbors[size_v];
		//inizializzato per ogni PID
		map <PointId, int> map_view;

		//**// PER OGNI VISTA INIZIO

		for(int i=0;i<size_v;i++){

			// ottiene i vicini per ogni vista
			neighbors_array[i] = findNeighbors(pid, _eps_vector[i],i,_visited);

			int neighbords_size=neighbors_array[i].size();

			//a quante viste appartiene il mio punto?
			//nel caso dell'unione ne basta una, nel caso dell'intersezione = numero viste

			for(int n=0;n<neighbords_size;n++){
				PointId point_id=neighbors_array[i][n];
				//std::cout << pid << "->" << point_id <<  std::endl;
				map_view[point_id]++;
				//std::cout << map_view[point_id] <<  std::endl;
			}

		}


		//**// PER OGNI VISTA FINE

		//**// UNIONE O INTERSEZIONE INIZIO

		//quanti vicini? Mi scorro la mappa e: nel caso dell'unione vedo la taglia della mappa
		//nel caso dell'intersezione calcolo aggiungo uno solamente se il valore associato al point_id
		//è esattamente il numero delle viste
		int neighbors_size=0;

		//nell'intersezione un punto potrebbe essere locale ma non globale
		Neighbors global_neighbors;

		int sizet=0;

		if(UnionOrIntersection){
			neighbors_size=map_view.size();
		} else {

			std::map<PointId, int>::iterator i = map_view.begin();

			while (i != map_view.end()) {
				//cout << "La taglia è " << map_view.size() << endl;
				if ((i->second)==size_v) {
					neighbors_size++;
					++i;
				} else {
					//std::cout << "Point i=" << pid << ". " << i->first << " locale ma non globale. Presente in solo " << i->second  << " view/s"<< std::endl;// = true;
					std::map<PointId, int>::iterator toErase = i;
					++i;
					map_view.erase(toErase);

				}
			}

		}

		//cout << "La taglia è " << map_view.size() << endl;
		//**// UNIONE O INTERSEZIONE FINE
		sizet=map_view.size();

		//std::cout << "Point i=" << pid << ". Numero di vicini " << neighbors_size << std::endl;

		// not enough support -> mark as noice
		if (neighbors_size < _minPts)
		{
			_noise[pid] = true;
			continue;
		}
		else
		{
			//std::cout << "Point i=" << pid << " can be expanded " << std::endl;// = true;

			// Add p to current cluster
			cid++;
			Cluster c;              // a new cluster
			c.push_back(pid);   	// assign pid to cluster
			_pointId_to_clusterId[pid]=cid;


			//**// SECONDA PARTE ALGORITMO - ESPANDO I VICINI INIZIO

			// go to neighbors
			for (map <PointId, int>::const_iterator i = map_view.begin(); i != map_view.end(); ++i){

				//std::cout << i->first << std::endl;


				//inizializzato per ogni vicino
				Neighbors* neighbors_array2 = new Neighbors[size_v];

				//inizializzato per ogni vicino
				map <PointId, int> map_view2;

				PointId nPid = i->first;

				if (!_visited[nPid]){
					_visited[nPid] = true;
				} else
					continue;

				for(int i=0;i<size_v;i++){
					// not already visited

					// ottiene i vicino per ogni vista

					neighbors_array2[i] = findNeighbors(nPid, _eps_vector[i],i,_visited);

					int neighbords_size2=neighbors_array2[i].size();

					//a quante viste appartiene il mio punto?
					//nel caso dell'unione ne basta una, nel caso dell'intersezione = numero viste

					for(int n=0;n<neighbords_size2;n++){
						PointId point_id=neighbors_array2[i][n];
						//std::cout << nPid << "->" << point_id <<  std::endl;
						map_view2[point_id]++;
						//std::cout << map_view[point_id] <<  std::endl;
					}

				}
				//quanti vicini? Mi scorro la mappa e: nel caso dell'unione vedo la taglia della mappa
				//nel caso dell'intersezione calcolo aggiungo uno solamente se il valore associato al point_id
				//è esattamente il numero delle viste
				int neighbors_size2=0;

				int sizet=0;

				if(UnionOrIntersection){
					neighbors_size2=map_view2.size();

				} else {

					std::map<PointId, int>::iterator i = map_view2.begin();

					while (i != map_view2.end()) {
						if ((i->second)==size_v) {
							neighbors_size2++;
							++i;
						} else {
							//std::cout << "Point i=" << pid << ". " << i->first << " locale ma non globale. Presente in solo " << i->second  << " view/s"<< std::endl;// = true;
							std::map<PointId, int>::iterator toErase = i;
							++i;
							map_view2.erase(toErase);
						}
					}


				}

				sizet=map_view2.size();

				if(neighbors_size2 >= _minPts){

					//std::cout << "\t Expanding to pid=" << nPid << std::endl;

					// join
					for (map <PointId, int>::const_iterator i = map_view2.begin(); i != map_view2.end(); ++i){
						{
							// join neighbord
							map_view[i->first]=i->second;
							//std::cerr << "\tPushback pid=" << i << std::endl;
						}

					}

				}

				// not already assigned to a cluster
				if (!_pointId_to_clusterId[i->first]){
					//std::cout << "\tadding pid=" << i->first << std::endl;
					c.push_back(i->first);
					_pointId_to_clusterId[i->first]=cid;
				}




			}



		}

	}

}

void DBSCAN::print_cluster(ofstream &fileOutput){
	for(int i=1;i<=cid;i++)
	{
		//std::cout << endl << "Cluster " << i << ":";
		fileOutput << std::endl << "Cluster " << i << ":";
		for(int j=0;j<_pointId_to_clusterId.size();j++){
			if(_pointId_to_clusterId[j]==i){
				//std::cout << " " << j;
				fileOutput << " " << j;
			}
		}
	}

}

void DBSCAN::print_cluster_in_file(ofstream &fileOutput){

	for(int j=0;j<_pointId_to_clusterId.size();j++){
		fileOutput << _pointId_to_clusterId[j] << " ";
	}

	fileOutput << endl;
}
};



