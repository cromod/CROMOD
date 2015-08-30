/** 
 * @file Node.hpp
 * @brief Header file of Node class
 * @author cromod
 * @date july 2015
 */

#ifndef NODE_HPP
#define	NODE_HPP

#include "Vector.hpp"
#include <vector>

namespace Cromod {
    namespace GeomAPI {
        /** @class Node Node.hpp
         *  @brief Class to define a node
         */
        class Node {
            
            public:
                
                /** @brief Default constructor */
                Node();
                /** @brief Copy constructor */
                Node(const Node& node);
                /** @brief Constructor
                 *  @param mesh Mesh object
                 *  @param near true if node is near a polygon edge
                 *  @param inside true if node is inside polygon
                 */
                Node(const Point &point, bool near=false, bool inside=false);
                /** @brief Destructor */
                virtual ~Node();
                
                /** @brief Equality operator
                 *  @param node Node object
                 *  @return true if Node objects are equal
                 */
                virtual bool operator==(const Node &node) const;
                /** @brief Inequality operator
                 *  @param node Node object
                 *  @return true if Node objects are not equal
                 */
                virtual bool operator!=(const Node &node) const;
                /** @brief Assignment operator
                 *  @param fnode FNode object
                 *  @return FNode object
                 */
                virtual Node& operator=(const Node &node);
                
                /** @brief Method to define position
                 *  @param point position
                 */
                void setPosition(const Point &point);
                /** @brief Method to get position
                 *  @return position
                 */
                Point getPosition() const;
                /** @brief Method to define node as near polygon edge
                 *  @param near true if node is near a polygon edge
                 */
                void setNearEdge(bool near);
                /** @brief Method to know if node is near polygon edge
                 *  @return true if node is near polygon edge
                 */
                bool isNearEdge() const;
                /** @brief Method to define node as inside polygon
                 *  @param near true if node is inside polygon
                 */
                void setInside(bool inside);
                /** @brief Method to know if node is inside polygon
                 *  @return true if node is inside polygon
                 */
                bool isInside() const;
                
            protected:
                
                /** @brief Position */  
                Point point_;
                /** @brief Boolean to know if node is near polygon edge */
                bool near_;
                /** @brief Boolean to know if node is inside polygon */
                bool inside_;
        };
    }
}

#endif	/* NODE_HPP */

