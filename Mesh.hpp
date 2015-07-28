/* 
 * File:   Mesh.hpp
 * Author: florent
 *
 * Created on 27 juillet 2015, 20:59
 */

#ifndef MESH_HPP
#define	MESH_HPP

#include <vector>
#include "Node.hpp"
#include "Polygon.hpp"

namespace Cromod {
    namespace GeomAPI {
        /* 
         * Classe Mesh
         * Definition d'un maillage
         */
        class Mesh {
            
            public:
                
                Mesh();
                Mesh(const Mesh& mesh);
                Mesh(const std::vector<Node>& listNode, const Polygon& polygon);
                virtual ~Mesh();
                
            private:
                
                std::vector<Node> listNode_; //liste des noeuds
                Polygon polygon_; //polygone a mailler
                bool init_; //grille initiale
                bool detect_; //noeuds detectes
                double step_; //pas du maillage
                std::vector<double> dim_; //dimensions de la grille initiale
        };
    }
}

#endif	/* MESH_HPP */
