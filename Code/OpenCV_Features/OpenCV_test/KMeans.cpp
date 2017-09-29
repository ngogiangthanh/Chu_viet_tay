#include "KMeans.h"
#include <exception>

int KMeans::getIDNearestCenter(CPoint point)
{
		double sum = 0.0, min_dist;
		int id_cluster_center = 0;
		vector<float> el1 = clusters[0].getCentralValues();
		vector<float> el2 = point.getValues();
		Dynamic_Time_Warping* DTW = new Dynamic_Time_Warping(el1, el2);
		min_dist = DTW->DTWDistance();
		el1.clear();
		el2.clear();

		for (int i = 1; i < K; i++)
		{
				double dist;
				sum = 0.0;

				vector<float> el3 = clusters[i].getCentralValues();
				vector<float> el4 = point.getValues();
				Dynamic_Time_Warping* DTW1 = new Dynamic_Time_Warping(el3, el4);

				el3.clear();
				el4.clear();
				dist = DTW1->DTWDistance();

				if (dist < min_dist)
				{
					min_dist = dist;
					id_cluster_center = i;
				}
			
		}
		return id_cluster_center;

}

KMeans::KMeans(int K, int total_points, int total_values, int max_iterations)
{
	this->K = K;
	this->total_points = total_points;
	this->total_values = total_values;
	this->max_iterations = max_iterations;
}

void KMeans::run(vector<CPoint> points)
{
		if (K > total_points)
			return;

		vector<int> prohibited_indexes;
		// choose K distinct values for the centers of the clusters
		for (int i = 0; i < K; i++)
		{
			while (true)
			{
				int index_point = rand() % total_points;

				if (find(prohibited_indexes.begin(), prohibited_indexes.end(),
					index_point) == prohibited_indexes.end())
				{
					prohibited_indexes.push_back(index_point);
					points[index_point].setCluster(i);
					Cluster cluster(i, points[index_point]);
					clusters.push_back(cluster);
					break;
				}
			}
		}


		int iter = 1;

		while (true)
		{
			bool done = true;

			// associates each point to the nearest center
			for (int i = 0; i < total_points; i++)
			{
				int id_old_cluster = points[i].getCluster();
				int id_nearest_center = getIDNearestCenter(points[i]);
				cout << endl;

				if (id_old_cluster != id_nearest_center)
				{
					if (id_old_cluster != -1)
						clusters[id_old_cluster].removePoint(points[i].getID());

					points[i].setCluster(id_nearest_center);
					clusters[id_nearest_center].addPoint(points[i]);
					done = false;
				}
			}

			// recalculating the center of each cluster
			for (int i = 0; i < K; i++)
			{
				for (int j = 0; j < total_values; j++)
				{
					int total_points_cluster = clusters[i].getTotalPoints();
					double sum = 0.0;

					if (total_points_cluster > 0)
					{
						for (int p = 0; p < total_points_cluster; p++)
							sum += clusters[i].getPoint(p).getValue(j);
						clusters[i].setCentralValue(j, sum / total_points_cluster);
					}
				}
			}

			if (done == true || iter >= max_iterations)
			{
				cout << "Break in iteration " << iter << "\n\n";
				break;
			}

			iter++;
		}

		// shows elements of clusters
		for (int i = 0; i < K; i++)
		{
			int total_points_cluster = clusters[i].getTotalPoints();

			cout << "Cluster " << clusters[i].getID() + 1 << endl;
			for (int j = 0; j < total_points_cluster; j++)
			{
				cout << "Point " << clusters[i].getPoint(j).getID() + 1 << ": ";
				/*for (int p = 0; p < total_values; p++)
					cout << clusters[i].getPoint(j).getValue(p) << " ";*/

				string point_name = clusters[i].getPoint(j).getName();

				if (point_name != "")
					cout << "- " << point_name;

				cout << endl;
			}

			/*cout << "Cluster values: ";

			for (int j = 0; j < total_values; j++)
				cout << clusters[i].getCentralValue(j) << " ";*/

			cout << "\n\n";
		}
}
