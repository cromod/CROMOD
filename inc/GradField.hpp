/** 
 * @file GradField.hpp
 * @brief Header file of GradField class
 * @author cromod
 * @date september 2015
 */

#ifndef GRADFIELD_HPP
#define GRADFIELD_HPP

#include "DistField.hpp"

namespace Cromod {
    namespace FieldAPI {
        /** @class GradField GradField.hpp
         *  @brief Class to define a field of gradient
         */
        class GradField: public Field {
            
            public:

                /** @brief Default constructor */
                GradField();
                /** @brief Copy constructor */
                GradField(const GradField& gradfield);
                /** @brief Constructor
                 *  @param mesh Mesh object
                 */
                GradField(const DistField &distfield);
                /** @brief Destructor */
                virtual ~GradField();

                /** @brief Method to build with a field of distance
                 *  @param distfield DistField object
                 */
                void build(const DistField &distfield);

                /** @brief Method to compute
                 *  @param listValue list of distance value
                 */
                void compute(const std::vector<GeomAPI::Vector>& listValue);

                /** @brief Method to interpolate field of gradient
                 *  @param x x coordinate
                 *  @param y y coordinate
                 *  @return value at (x,y)
                 */
                GeomAPI::Vector interpolate(double x, double y);

        };
    }
}

#endif	/* DISTFIELD_HPP */

