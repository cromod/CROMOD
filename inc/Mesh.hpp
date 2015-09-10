/** 
 * @file Mesh.hpp
 * @brief Header file of Mesh class
 * @author cromod
 * @date july 2015
 */

#ifndef MESH_HPP
#define	MESH_HPP

#include "Node.hpp"
#include "Polygon.hpp"

namespace Cromod {
    namespace GeomAPI {
        /** @class Mesh Mesh.hpp
         *  @brief Class to define a mesh
         */
        class Mesh {
            
            public:
                
                /** @brief Default constructor */
                Mesh();
                /** @brief Copy constructor */
                Mesh(const Mesh& mesh);
                /** @brief Destructor */
                virtual ~Mesh();
                
                /** @brief Index operator
                 *  @param i index
                 *  @return the pointed node
                 */
                Node& operator[](const unsigned int& i);
                
                /** @brief Method to get size
                 *  @return size
                 */
                unsigned int size() const;
                /** @brief Method to get index
                 *  @param Node object
                 *  @return index
                 */
                unsigned int index(const Node &node) const;
                /** @brief Method to add node
                 *  @param node Node object
                 */
                void addNode(Node node);
                /** @brief Method to delete a node */
                void deleteNode();
                /** @brief Method to delete every node */
                void deleteAll();
                
                /** @brief Method to check if mesh is initialized
                 *  @return true if initialized
                 */
                bool isInit() const;
                /** @brief Method to define mesh as initialized
                 *  @param init true if initialized
                 */
                void setInit(bool init);
                /** @brief Method to check if mesh is detected
                 *  @return true if detected
                 */
                bool isDetect() const;
                /** @brief Method to define mesh as detected
                 *  @param detect true if detected
                 */
                void setDetect(bool detect);
                /** @brief Method to get polygon
                 *  @return Polygon object
                 */
                Polygon getPolygon();
                /** @brief Method to set polygon
                 *  @param polygon Polygon object
                 */
                void setPolygon(Polygon polygon);
                /** @brief Method to get step
                 *  @return mesh step
                 */
                double getStep();
                /** @brief Method to set step
                 *  @param step mesh step
                 */
                void setStep(double step);
                /** @brief Method to get dimensions
                 *  @return list of dimensions
                 */
                std::vector<int> getDim() const;
                /** @brief Method to set dimensions
                 *  @param dim list of dimensions
                 */
                void setDim(std::vector<int> dim);
                
                /** @brief Method to set the initial grid of mesh */
                void setInitGrid();
                /** @brief Method to detect nodes inside polygon and near edges
                 *  @details Compute minimum distance between nodes and edges
                 */
                void detectNode();

            private:
                
                /** @brief list of nodes */  
                std::vector<Node> listNode_;
                /** @brief polygon */  
                Polygon polygon_;
                /** @brief initialisation boolean */ 
                bool init_;
                /** @brief detection boolean */ 
                bool detect_;
                 /** @brief mesh step */                
                double step_;
                 /** @brief list of dimensions */ 
                std::vector<int> dim_;
        };
    }
}

#endif	/* MESH_HPP */
