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
                 *  @param listExit list of exit segment
                 */
                DistField(const GeomAPI::Mesh &mesh, std::vector<GeomAPI::Segment> &listExit);
                /** @brief Destructor */
                virtual ~DistField();

                /** @brief Method to set status
                 *  @param node the chosen node
                 *  @param status Status type
                 */
                void setStatus(const GeomAPI::Node &node, Status status);
                /** @brief Method to set status
                 *  @param index index of the chosen node
                 *  @param status Status type
                 */
                void setStatus(int index, Status status);
                /** @brief Method to get status
                 *  @param node the chosen node
                 *  @return status
                 */
                Status getStatus(const GeomAPI::Node &node);
                /** @brief Method to get status
                 *  @param index index of the chosen node
                 *  @return status
                 */
                Status getStatus(int index);

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
                /** @brief Method to compute field of distance 
                 *  @details Fast marching
                 */
                void compute();
                /** @brief Method to interpolate field of distance 
                 *  @param x x coordinate
                 *  @param y y coordinate
                 *  @return value at (x,y)
                 */
                double interpolate(double x, double y);

            private:
                
                /** @brief List of nodes status (frozen/narrow) */  
                std::vector<Status> listStatus_;

        };
    }
}

#endif	/* DISTFIELD_HPP */

