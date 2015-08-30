/** 
 * @file FNode.hpp
 * @brief Header file of FNode class
 * @author cromod
 * @date august 2015
 */

#ifndef FNODE_HPP
#define	FNODE_HPP

#include "Node.hpp"

using namespace Cromod::GeomAPI;

namespace Cromod {
    namespace FieldAPI {
        /** @class FNode FNode.hpp
         *  @brief Class to define a field node
         */
        class FNode: public Cromod::GeomAPI::Node
        {
            
            public:
                
                /** @brief Default constructor */
                FNode();
                /** @brief Copy constructor */
                FNode(const FNode& fnode);
                /** @brief Constructor
                 *  @param node Node object
                 */
                FNode(const Node &node);
                /** @brief Destructor */
                virtual ~FNode();
                
                /** @brief Equality operator
                 *  @param fnode FNode object
                 *  @return true if FNode objects are equal
                 */
                bool operator==(const FNode &fnode) const;
                /** @brief Inequality operator
                 *  @param fnode FNode object
                 *  @return true if FNode objects are not equal
                 */
                bool operator!=(const FNode &fnode) const;
                /** @brief Assignment operator
                 *  @param fnode FNode object
                 *  @return FNode object
                 */
                FNode& operator=(const FNode &fnode);

                /** @brief Method to define value
                 *  @param value value of field node
                 */
                void setValue(const Vector &value);
                /** @brief Method to get value
                 *  @return value of field node
                 */
                Vector getValue() const;
                /** @brief Method to define status
                 *  @param status status of field node (frozen,narrow)
                 */
                void setStatus(const std::vector<bool> &status);
                /** @brief Method to get status
                 *  @return status of field node
                 */
                std::vector<bool> getStatus() const;

            private:
                
                /** @brief Value of field node (scalar or vector) */                 
                Vector value_;
                /** @brief Status of field node (frozen,narrow) */  
                std::vector<bool> status_;
        };
    }
}

#endif	/* FNODE_HPP */

