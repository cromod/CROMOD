/** 
 * @file DistField.hpp
 * @brief Header file of DistField class
 * @author cromod
 * @date september 2015
 */

#ifndef DISTFIELD_HPP
#define	DISTFIELD_HPP

#include "Field.hpp"

namespace Cromod {
    namespace FieldAPI {
        /** @class DistField DistField.hpp
         *  @brief Class to define a field
         */
        class DistField: public Field {
            
            public:
                
                /** @brief Default constructor */
                DistField();
                /** @brief Copy constructor */
                DistField(const DistField& distfield);
                /** @brief Constructor
                 *  @param mesh Mesh object
                 */
                DistField(const GeomAPI::Mesh &mesh);
                /** @brief Destructor */
                virtual ~DistField();

                /** @brief Method to set boundary condition
                 *  @param mesh Mesh object
                 */
               void setBoundaryCondition(GeomAPI::Segment &segment);



        };
    }
}

#endif	/* DISTFIELD_HPP */

