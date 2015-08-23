/* 
 * File:   Polygon.hpp
 * Author: florent
 *
 * Created on 25 juin 2015, 20:22
 */

#ifndef POLYGON_HPP
#define	POLYGON_HPP

#include "Segment.hpp"
#include "Vector.hpp"
#include <map>
#include <string>

namespace Cromod {
    namespace GeomAPI {
        /* 
         * Classe Polygon
         * Definition d'un polygone a partir d'une liste d'objets Segment
         */
        class Polygon {
        
            public:
            
                /* Constructeur par defaut */
                Polygon();
                /* Constructeur par copie */
                Polygon(const Polygon& polygon);
                /* Constructeur utilisant une liste de points */
                Polygon(const std::vector<Point>& listPoints);
                /* Destructeur */
                virtual ~Polygon();
                
                /* Operateur [] */
                Segment& operator[](const unsigned int& i);
                /* Operateur affectation */
                Polygon& operator=(const Polygon &polygon);
                
                /* Methode pour recuperer le nbre de cotes */
                unsigned int size();
                /* Methode pour rajouter un segment */
                void addSegment(Segment seg);
                /* Methode pour supprimer un segment */
                void delSegment();
                /* Methode pour supprimer tous les segments */
                void deleteAll();
                /* Methode pour rajouter un point */
                void addPoint(const Point& point);
                /* Methode pour recuperer la liste des segments */
                std::vector<Segment> getList();
                /* Methode pour fournir la liste des segments */
                void setList(const std::vector<Segment>& listSeg);
                
                /* Methode pour savoir si le polygone est ferme */
                bool isClosed();
                /* Methode pour fermer le polygone */
                void close();
                /* Methode pour recuperer la liste de points */
                std::vector<Point> getPoints();
                /* Methode pour recuperer un point hors du polygone */
                Point getOutside();
                /* Methode pour recuperer les coordonnees extremes du polygone */
                std::map<std::string,double> getBottom();
                
                /* Methode pour savoir si le polygone est croise */
                bool isSelfIntersect();
                /* 
                 * Methode pour recuperer le nombre d'intersections entre 
                 * un segment et les cotes du polygone
                 */
                int getNbIntersect(const Segment& segment);
                /* Methode pour verifier si un point est sur un cote du polynome */
                bool isOnEdge(const Point& point);
                /* 
                 * Methode pour verifier si un objet Point est a l'interieur du polygone
                 * http://www.zebulon.fr/questions-reponses/points-interieur-d-un-polygone-149.html
                 */
                bool isInside(const Point& point_in);
            
            private:
                
                std::vector<Segment> listSeg_;
        };
    }
}
#endif	/* POLYGON_HPP */

