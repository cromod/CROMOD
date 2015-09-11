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
         *  @brief Class to define a field of distance
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

                /** @brief Method to set status
                 *  @param status list of 2 booleans
                 */
                void setStatus(const GeomAPI::Node &node, const std::vector<bool> &status);
                /** @brief Method to get status
                 *  @return list of 2 booleans
                 */
                std::vector<bool> getStatus(const GeomAPI::Node &node);

                /** @brief Method to set boundary condition
                 *  @param mesh Mesh object
                 */
                void setBoundaryCondition(GeomAPI::Segment &segment);

                /** @brief Method to build with a mesh
                 *  @param mesh Mesh object
                 */
                void build(const GeomAPI::Mesh &mesh);

                /** @brief Method to initialize field of distance */
                void initialize();
                /** @brief Function to compute relative error
                 *  @param val1 first value
                 *  @param val2 second value
                 *  @return relative error
                 */
                static double computeRelErr(double val1, double val2);
                /** @brief Method to compute field of distance 
                 *  @details Fast marching
                 */
                void compute();
                /** @brief Method to interpolate field of distance 
                 *         thanks to values on mesh
                 *  @details Fast marching
                 */
                void interpolate();

            private:
                
                /** @brief List of nodes status (frozen/narrow) */  
                std::vector< std::vector<bool> > listStatus_;

        };
    }
}

#endif	/* DISTFIELD_HPP */

