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


	//(1 1.1 1.2) (2 2.1 2.2) (3 3.1 3.2)


	std::cout << "Created point 1" << std::endl;


	Point p1(1);

	p1(0)=1;

	std::cout << p1(0) << ' ';

	ps.push_back(p1);


	Point p2(1);

	p2(0)=1.1;

	std::cout << p2(0) << ' ';

	ps.push_back(p2);


	Point p3(1);

	p3(0)=1.2;

	std::cout << p3(0) << ' ';

	ps.push_back(p3);


	Point p4(1);

	p4(0)=2;

	std::cout << p4(0) << ' ';

	ps.push_back(p4);


	Point p5(1);

	p5(0)=2.1;

	std::cout << p5(0) << ' ';

	ps.push_back(p5);


	Point p6(1);

	p6(0)=2.2;

	std::cout << p6(0) << ' ';

	ps.push_back(p6);


	Point p7(1);

	p7(0)=3;

	std::cout << p7(0) << ' ';

	ps.push_back(p7);


	Point p8(1);

	p8(0)=3.1;

	std::cout << p8(0) << ' ';

	ps.push_back(p8);


	Point p9(1);

	p9(0)=3.2;

	std::cout << p9(0) << ' ';

	ps.push_back(p9);


	std::cout << std::endl;
}


void myPoint2(Points & ps, unsigned int dims, unsigned int num_points){


	//(5 5.2 5.4 5.6 6) (10 10.4 10.8 11) eps=0.5


	std::cout << "Created point 2" << std::endl;


	Point p1(1);

	p1(0)=5;

	std::cout << p1(0) << ' ';

	ps.push_back(p1);


	Point p2(1);

	p2(0)=5.2;

	std::cout << p2(0) << ' ';

	ps.push_back(p2);


	Point p3(1);

	p3(0)=5.4;

	std::cout << p3(0) << ' ';

	ps.push_back(p3);


	Point p4(1);

	p4(0)=5.6;

	std::cout << p4(0) << ' ';

	ps.push_back(p4);


	Point p5(1);

	p5(0)=6;

	std::cout << p5(0) << ' ';

	ps.push_back(p5);


	Point p6(1);

	p6(0)=10;

	std::cout << p6(0) << ' ';

	ps.push_back(p6);


	Point p7(1);

	p7(0)=10.4;

	std::cout << p7(0) << ' ';

	ps.push_back(p7);


	Point p8(1);

	p8(0)=10.8;

	std::cout << p8(0) << ' ';

	ps.push_back(p8);


	Point p9(1);

	p9(0)=11;

	std::cout << p9(0) << ' ';

	ps.push_back(p9);


	std::cout << std::endl;
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
		if 	((pid != j ) &&  (sim(pid, j)) > threshold && !_visited[j] )
		{
			//std::cout << "Vista numero " << view << ". La similarità tra " << pid << " e " << j << " è " << (sim(pid, j)) << std::endl;
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
