/* 
 * File:   Mesh.hpp
 * Author: florent
 *
 * Created on 27 juillet 2015, 20:59
 */

#ifndef MESH_HPP
#define	MESH_HPP

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
                
                /* Constructeur par defaut */
                Mesh();
                /* Constructeur par copie */
                Mesh(const Mesh& mesh);
                /* Destructeur */
                virtual ~Mesh();
                
                /* Operateur [] */
                Node& operator[](const unsigned int& i);
                
                /* Methode pour recuperer le nbre de noeuds */
                unsigned int size() const;
		unsigned int index(const Node &node) const;
                /* Methode pour rajouter un noeud */
                void addNode(Node node);
                /* Methode pour supprimer un noeud */
                void deleteNode();
                /* Methode pour supprimer tous les noeuds */
                void deleteAll();
                /* Methode pour savoir si la grille est a l'etat initial */
                bool isInit() const;
                /* Methode pour signaler la grille comme a l'etat initial */
                void setInit(bool init);
                /* Methode pour savoir si les noeuds pres du bord ont ete detectes */
                bool isDetect() const;
                /* Methode pour signaler les noeuds pres du bord comme detectes */
                void setDetect(bool detect);
                /* Methode pour recuperer le polygone du maillage */
                Polygon getPolygon();
                /* Methode pour definir le polygone du maillage */
                void setPolygon(Polygon polygon);
                /* Methode pour recuperer la valeur du pas */
                double getStep();
                /* Methode pour definir la valeur du pas */
                void setStep(double step);
                /* Methode pour recuperer les dimensions du maillage */
                std::vector<int> getDim() const;
                /* Methode pour definir les dimensions du maillage */
                void setDim(std::vector<int> dim);
                
                /* Methode pour construire la grille initiale du maillage */
                void setInitGrid();
                /* 
                 * Methode pour detecter les noeuds interieurs et pres des bords
                 * Calcul de la distance minimale entre les noeuds et les bords
                 */
                void detectNode();
                
                
            private:
                
                std::vector<Node> listNode_; //liste des noeuds
                Polygon polygon_; //polygone a mailler
                bool init_; //grille initiale
                bool detect_; //noeuds detectes
                double step_; //pas du maillage
                std::vector<int> dim_; //dimensions de la grille initiale
        };
    }
}

#endif	/* MESH_HPP */
