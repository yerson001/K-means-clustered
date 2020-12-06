#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <fstream>
using namespace std;
using namespace sf;
#define Ancho 1000
#define Largo 1000

class Clusters : public Drawable
{

	vector<CircleShape> clusters;
	int cnum;
	bool clusters_stable;

public:
	Clusters(int cluster_num) : cnum(cluster_num), clusters_stable(false)
	{
		for (int c = 0; c < cnum; c++)
		{
			clusters.push_back(sf::CircleShape(10));
			clusters[c].setPosition(std::rand() % Ancho, std::rand() % Largo);
			clusters[c].setFillColor(sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255));
		};
	};

	void draw(sf::RenderTarget &w, sf::RenderStates states = sf::RenderStates::Default) const
	{
		for (int i = 0; i < cnum; i++)
			w.draw(clusters[i], states);
	};

	void Init(std::vector<sf::CircleShape> &points)
	{
		std::vector<std::vector<sf::CircleShape *> *> elems;
		for (int i = 0; i < cnum; i++)
		{
			elems.push_back(new std::vector<sf::CircleShape *>);
		};

		if (!clusters_stable)
		{
			for (unsigned int p = 0; p < points.size(); p++)
			{
				float distance = 999999;
				int aprox = 0;

				//std::cout << points[p].getPosition().x << " " << points[p].getPosition().y << " ";
				for (int c = 0; c < cnum; c++)
				{

					float distancia = sqrt(pow(clusters[c].getPosition().x - points[p].getPosition().x, 2) + pow(clusters[c].getPosition().y - points[p].getPosition().y, 2));
					//std::cout << distancia << std::endl;
					if (distancia < distance)
					{
						distance = distancia;
						aprox = c;
					};
				};
				elems[aprox]->push_back(&points[p]);
			};

			bool It = true;
			for (int c = 0; c < cnum; c++)
			{
				sf::Vector2f newpos(0.f, 0.f);

				for (unsigned int p = 0; p < elems[c]->size(); p++)
				{
					newpos += (*elems[c])[p]->getPosition();

					(*elems[c])[p]->setFillColor(clusters[c].getFillColor() + sf::Color(20, 20, 20));
				};

				newpos /= (float)elems[c]->size();

				if (!(It = It && (clusters[c].getPosition() == newpos)))
					clusters[c].setPosition(newpos);
			};
			clusters_stable = It;
		};
		//while(elems.size()!=0) elems.pop_back();
		/*for (int i = 0; i < elems.size(); i++)
			std::cout << elems[i]->size() << " ";
		std::cout << "\n";
		*/
	};

	void recet_data(int cluster_num)
	{
		clusters_stable = false;

		int onum = clusters.size();
		if (cluster_num <= cnum)
		{
			for (int i = 0; i < cnum - onum; i++)
				clusters.pop_back();

			cnum = cluster_num;
		}
		else
		{
			while (cnum != cluster_num)
			{
				clusters.push_back(sf::CircleShape(10));
				cnum++;
			};
		};

		for (int c = 0; c < cnum; c++)
		{
			clusters[c].setPosition(std::rand() % Ancho, std::rand() % Largo);
			clusters[c].setFillColor(sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255));
		};
	};

	const std::vector<sf::CircleShape> &getClusters()
	{
		return clusters;
	};

	bool clustersStable() { return clusters_stable; };
};

int pressedDigit(sf::Event e)
{
	sf::Keyboard::Key num = e.key.code;
	if ((num >= sf::Keyboard::Num0) && (num <= sf::Keyboard::Num9))
		return num - sf::Keyboard::Num0;
	else if ((num >= sf::Keyboard::Numpad0) && (num <= sf::Keyboard::Numpad9))
		return num - sf::Keyboard::Numpad0;
	else
		return -1;
};

int main(int argc, char **argv)
{
        //===============READ FILE=================
	ifstream ip("yellow_tripdata_2015-01-06.csv");
        if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';
        int start,numpoint = 7291;
        string A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S;
        //===========================================

	sf::RenderWindow win(sf::VideoMode(Ancho, Largo, 32), "K-Means algorithm visualization");
	win.setFramerateLimit(5);
	sf::Event mainloop;
	std::vector<sf::CircleShape> points;
	std::srand(time(NULL));

	
	start = 0;
	while(ip.good() && start<numpoint)
	{
		getline(ip,A,',');getline(ip,B,',');getline(ip,C,',');
        getline(ip,D,',');getline(ip,E,',');getline(ip,F,',');
		getline(ip,G,',');getline(ip,H,',');getline(ip,I,',');
		getline(ip,J,',');getline(ip,K,',');getline(ip,L,',');
		getline(ip,M,',');getline(ip,N,',');getline(ip,O,',');
		getline(ip,P,',');getline(ip,Q,',');getline(ip,R,',');
		getline(ip,S,'\n');
		cout<<F<< " "<<G<<endl;
		  
		points.push_back(sf::CircleShape(5));
		points[start].setPosition((-1)*(std::atof(F.c_str()))+rand()%Ancho,
				                std::atof(G.c_str())+rand()%Largo);
		//points[start].setPosition(std::rand() % 1000, std::rand() % 1000);
		points[start].setFillColor(sf::Color::White);start++;
		//cout<<start<<endl;
	}

	int numc = 100;// grupos num-1
	Clusters clu(numc);

	while (win.isOpen())
	{
		win.clear();
		while (win.pollEvent(mainloop))
		{
			if (mainloop.type == sf::Event::Closed)
				win.close();

			if (mainloop.type == sf::Event::KeyPressed)
			{
				int pressed = pressedDigit(mainloop);
				if (pressed != -1 || pressed != 0 || pressed != 1)
					numc = pressed;
			};
		};

		if (clu.clustersStable())
		{
			//std::cout << numc << "\n";
			clu.recet_data(numc);
		}

		clu.Init(points);

		for (unsigned int i = 0; i < points.size(); i++)
		{
			win.draw(points[i]);
		};
		win.draw(clu);
		win.display();
	};
	cout<<"END"<<endl;

	return 0;
}