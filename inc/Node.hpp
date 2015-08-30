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
                virtual bool operator==(const Node &node) const;
                /* Operateur difference */
                virtual bool operator!=(const Node &node) const;
                /* Operateur affectation */
                virtual Node& operator=(const Node &node);
                
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
                
            protected:
                
                Point point_; // Position
                bool near_; // Noeud pres du bord du polygone
                bool inside_; // Noeud a l'interieur du polygone
        };
    }
}

#endif	/* NODE_HPP */

