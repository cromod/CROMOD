/* 
 * File:   Node.hpp
 * Author: florent
 *
 * Created on 6 juillet 2015, 21:21
 */

#ifndef NODE_HPP
#define	NODE_HPP

#include "Vector.hpp"
#include <vector>

namespace Cromod {
    namespace GeomAPI {
        /* 
         * Classe Node
         * Definition d'un noeud du maillage
         */
        class Node {
            
            public:
                
                /* Constructeur par defaut */
                Node();
                /* Constructeur par copie */
                Node(const Node& node);
                /* Constructeur */
                Node(const Point &point, bool near=false, bool inside=false);
                /* Destructeur */
                virtual ~Node();
                
                /* Operateur egal */
                bool operator==(const Node &node) const;
                /* Operateur difference */
                bool operator!=(const Node &node) const;
                /* Operateur affectation */
                Node& operator=(const Node &node);
                
                /* Methode pour definir la position */
                void setPosition(const Point &point);
                /* Methode pour recuperer la position */
                Point getPosition() const;
                /* Methode pour definir le noeud comme pres du bord */
                void setNearEdge(bool near);
                /* Methode pour savoir si le noeud est pres du bord */
                bool isNearEdge() const;
                /* Methode pour definir le noeud a l'interieur du polygone */
                void setInside(bool inside);
                /* Methode pour savoir si le noeud est a l'interieur du polygone */
                bool isInside() const;
		/* Methode pour definir la valeur associee au noeud */
                void setValue(const Vector &value);
                /* Methode pour recuperer la valeur associee au noeud */
                Vector getValue() const;
		/* Methode pour definir le statut de la valeur */
                void setStatus(const std::vector<bool> &status);
                /* Methode pour recuperer le statut de la valeur */
                std::vector<bool> getStatus() const;
                
            private:
                
                Point point_; // Position
                bool near_; // Noeud pres du bord du polygone
                bool inside_; // Noeud a l'interieur du polygone
                Vector value_; // Valeur (scalaire ou vecteur) associee au noeud
                std::vector<bool> status_; // Statut de la valeur (frozen ou narrow)
        };
    }
}

#endif	/* NODE_HPP */

