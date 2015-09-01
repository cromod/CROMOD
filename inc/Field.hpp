/** 
 * @file Field.hpp
 * @brief Header file of Field class
 * @author cromod
 * @date august 2015
 */

#ifndef FIELD_HPP
#define	FIELD_HPP

#include "Mesh.hpp"

namespace Cromod {
    namespace FieldAPI {
        /** @class Field Field.hpp
         *  @brief Class to define a field
         */
        class Field {
            
            public:
                
                /** @brief Default constructor */
                Field();
                /** @brief Copy constructor */
                Field(const Field& field);
                /** @brief Constructor
                 *  @param mesh Mesh object
                 */
                Field(const GeomAPI::Mesh &mesh);
                /** @brief Destructor */
                virtual ~Field();
                
                /** @brief Index operator
                 *  @param i index
                 *  @return value on the pointed node
                 */
                GeomAPI::Vector& operator[](const unsigned int& i);
                /** @brief Assignment operator
                 *  @param field Field object
                 *  @return Field object
                 */
                Field& operator=(const Field &field);
                
                /** @brief Method to get size
                 *  @return size
                 */
                unsigned int size();
                /** @brief Method to delete a field node */
                void delValue();
                /** @brief Method to delete every field node */
                void deleteAll();

                /** @brief Method to define mesh
                 *  @param mesh Mesh object
                 */
                void setMesh(const GeomAPI::Mesh &mesh);
                /** @brief Method to get mesh
                 *  @return Mesh object
                 */
                GeomAPI::Mesh getMesh() const;
                /** @brief Method to set step
                 *  @param step mesh step
                 */
                void setStep(double step);
                /** @brief Method to get step
                 *  @return mesh step
                 */
                double getStep() const;
                /** @brief Method to set value on a node
                 *  @param node the chosen node
                 *  @param value value to set
                 */
                void setValue(const GeomAPI::Node &node, const GeomAPI::Vector &value);
                /** @brief Method to get value on a node
                 *  @param node the chosen node
                 *  @return value on the node
                 */
                 GeomAPI::Vector getValue(const GeomAPI::Node &node) const;
                
            private:
                
                /** @brief Mesh attribute */  
                GeomAPI::Mesh mesh_; 
                /** @brief List of field nodes */  
                std::vector<GeomAPI::Vector> listValue_;
        };
    }
}

#endif	/* FIELD_HPP */

