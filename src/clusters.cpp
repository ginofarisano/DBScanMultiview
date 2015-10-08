#include "clusters.h"
#include <boost/foreach.hpp>

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

/** Added **/
//2
void myPoint(Points & ps, unsigned int dims,
		//9
		unsigned int num_points){

	int newCluster=0;

	std::cout << "Created point" << std::endl;

	for (unsigned int j = 0; j < num_points; j++)
	{


		Point p(dims);

		/** Added my first feature**/

		for (unsigned int i = 0; i < dims; i++)
		{
			//first feature
			if(i==0){
				if((j%3)==0){
					newCluster++;
					p(i)=newCluster+(0.1*(j%3));
				} else
					p(i)=newCluster+(0.1*(j%3));
			}
			//end first feature

			//second feature
			if(i==0){
				if((j%3)==0){
					newCluster++;
					p(i)=newCluster+(0.1*(j%3));
				} else
					p(i)=newCluster+(0.1*(j%3));
			}
			//end secind feature


			std::cout << p(i) << ' ';
		}

		ps.push_back(p);
		//		std::cout << std::endl;
	}
}


void myPoint2(Points & ps, unsigned int dims,
		//9
		unsigned int num_points){

	//(5 5.2  5.4   5.6  6)  (10   10.4  10.8  11)    eps=0.5

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



}

/** Added **/

// assign each point to a new cluster
void Clusters::uniformPartition()
{
	PointId pid = 0;
	ClusterId cid = 0;
	BOOST_FOREACH(Point p, _ps)
	{
		// create a new cluster for this current point
		Cluster c;
		c.push_back(pid++);
		_clusters.push_back(c);
		_pointId_to_clusterId.push_back(cid++);
	}
}

// findNeighbors(PointId pid, double threshold)
Neighbors Clusters::findNeighbors(PointId pid, double threshold)
{
	Neighbors ne;

	for (unsigned int j=0; j < _sim.size1(); j++)

	{

		std::cout << "La similarità tra " << pid << "e " << j << "è " << (_sim(pid, j)) << std::endl;

		if 	((pid != j ) && (_sim(pid, j)) < threshold)
		{

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

// clusters output
std::ostream& operator<<(std::ostream& o, const Clusters& cs)
{
	ClusterId cid = 1;
	BOOST_FOREACH(Cluster c, cs._clusters)
	{
		o << "c(" << cid++ << ")=";

		BOOST_FOREACH(PointId pid, c)
		{
			o << cs._ps[pid];
		}
		o << std::endl;
	}
	return o;
}


};
