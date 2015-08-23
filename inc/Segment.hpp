/* 
 * File:   Segment.hpp
 * Author: florent
 *
 * Created on 18 juin 2015, 23:35
 */

#ifndef SEGMENT_HPP
#define	SEGMENT_HPP

#include "Vector.hpp"
#include <vector>

namespace Cromod {
    namespace GeomAPI {
        /* 
         * Classe Segment
         * Definition d'un segment a partir de 2 points
         */
        class Segment {
            
            public:
                
                /* Constructeur par defaut */
                Segment();
                /* Constructeur par copie */
                Segment(const Segment& seg);
                /* Constructeur */
                Segment(const Point &point1,
                        const Point &point2, const bool &exit=false);
                /* Destructeur */
                virtual ~Segment();
                
                /* Operateur egal */
                bool operator==(const Segment &seg) const;
                /* Operateur difference */
                bool operator!=(const Segment &seg) const;
                /* Operateur affectation */
                Segment& operator=(const Segment &seg);
                
                /* Methode pour definir le 1er point */
                void setExit(bool exit);
                /* Methode pour recuperer le 1er point */
                bool isExit() const;
                /* Methode pour definir le 1er point */
                void setOne(Point point1);
                /* Methode pour recuperer le 1er point */
                Point getOne() const;
                /* Methode pour definir le 2e point */
                void setTwo(Point point2);
                /* Methode pour recuperer le 2e point */
                Point getTwo() const;
                /* Methode pour definir les 2 points */
                void setPoints(Point point1,Point point2);
                /* Methode pour recuperer les 2 points */
                std::vector<Point> getPoints() const;
                /* Methode pour recuperer le vecteur du segment */
                Vector getVector() const;
                
                /* Methode pour recuperer la longueur du segment */
                double getLength() const;
                /* Methode pour verifier si les 2 points forment un segment */
                bool isSegment() const;
                /* Methode pour la distance minimale d'un point a un segment */
                double getMinDist(const Point &point);
                
                /* Fonction Orientation pour determiner l'orientation
                 * de l'angle forme par 3 points
                 * resultat < 0 -> sens inverse des aiguilles d'une montre
                 * resultat = 0 -> points colineaires
                 * resultat > 0 -> sens des aiguilles d'une montre
                 * http://en.wikipedia.org/wiki/Curve_orientation
                 */
                static double orientation(const Point &pointA, 
                                          const Point &pointB, 
                                          const Point &pointC);

                /* 
                 * Methode pour verifier l'intersection entre 2 segments
                 * http://algs4.cs.princeton.edu/91primitives/ 
                 */
                bool checkIntersect(const Segment &seg) const;
                
                /* 
                 * Methode pour verifier le parallelisme entre 2 segments
                 * Calcul du produit vectoriel
                 */
                bool checkParallel(const Segment &seg) const;
                
                /* 
                 * Methode pour verifier l'appartenance d'un point a un segment
                 * Utilisation du theoreme de Thales
                 */
                bool checkInclude(const Point &pointB) const;
                
                /* 
                 * Methode pour calculer les coordonnees du pied de la 
                 * perpendiculaire au segment passant par un point quelconque
                 * Utilisation du produit scalaire
                 */
                Point findPerPoint(const Point &pointC) const;
                
            private:
                
                Point point1_; // Point 1
                Point point2_; // Point 2
                bool exit_; // Test pour savoir si le segment est une sortie
                
        };
    }
}

#endif	/* SEGMENT_HPP */

