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
         *  @brief Abstract class to define a field
         */
        class Field {
            
            public:
                
                /** @brief Default constructor */
                Field();
                /** @brief Destructor */
                virtual ~Field();
                
                /** @brief Index operator
                 *  @param i index
                 *  @return value on the pointed node
                 */
                GeomAPI::Vector& operator[](const unsigned int& i);
                
                /** @brief Method to get size
                 *  @return size
                 */
                unsigned int size();

                /** @brief Method to get mesh
                 *  @return Mesh object
                 */
                GeomAPI::Mesh getMesh() const;
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
                GeomAPI::Vector getValue(const GeomAPI::Node &node);
                /** @brief Method to know if field is computed
                 *  @return true if computed
                 */
                bool isComputed() const;
                /** @brief Method to get list of value
                 *  @return list of value
                 */
                std::vector<GeomAPI::Vector> getListValue() const;

                /** @brief Method to get nodes around
                 *  @param node central node
                 *  @return map of nodes around
                 */
                std::map<Around,GeomAPI::Node> getNodesAround(const GeomAPI::Node &node);
                /** @brief Method to get nodes around
                 *  @param index index of central node
                 *  @return map of nodes around
                 */
                std::map<Around,int> getNodesAround(int index);
                
                /** @brief Method to build with a mesh
                 *  @param mesh Mesh object
                 *  @param dim dimension of field value
                 */
                virtual void build(const GeomAPI::Mesh &mesh, int dim);
                /** @brief Method to interpolate field of gradient
                 *  @param x x coordinate
                 *  @param y y coordinate
                 *  @return value at (x,y)
                 */
                virtual GeomAPI::Vector interpolate(double x, double y) = 0;

                /** @brief Function to compute relative error
                 *  @param val1 first value
                 *  @param val2 second value
                 *  @return relative error
                 */
                static double computeRelErr(double val1, double val2);
                /** @brief Function to make bilinear interpolation between 4 points
                 *  @details http://en.wikipedia.org/wiki/Bilinear_interpolation
                 *  @param listPts list of points
                 *  @param listVal list of values
                 *  @param point point to interpolate
                 *  @return interpolated value
                 */
                static GeomAPI::Vector bilinearInt(std::vector<GeomAPI::Point> listPts, 
                                                   std::vector<GeomAPI::Vector> listVal,
                                                   GeomAPI::Point point);
                /** @brief Function to make linear interpolation between 3 points
                 *  @param listPts list of points
                 *  @param listVal list of values
                 *  @param point point to interpolate
                 *  @return interpolated value
                 */
                static GeomAPI::Vector linear3DInt(std::vector<GeomAPI::Point> listPts, 
                                                   std::vector<GeomAPI::Vector> listVal,
                                                   GeomAPI::Point point) {};
                /** @brief Function to make linear interpolation between 2 points
                 *  @param listPts list of points
                 *  @param listVal list of values
                 *  @param point point to interpolate
                 *  @return interpolated value
                 */
                static GeomAPI::Vector linear2DInt(std::vector<GeomAPI::Point> listPts, 
                                                   std::vector<GeomAPI::Vector> listVal,
                                                   GeomAPI::Point point) {};
                /** @brief Function to renormalize vector
                 *  @param vec vector
                 *  @return renormalized vector
                 */
                static GeomAPI::Vector renorm(GeomAPI::Vector vec);

            protected:
                
                /** @brief Mesh attribute */  
                GeomAPI::Mesh mesh_; 
                /** @brief List of field nodes */  
                std::vector<GeomAPI::Vector> listValue_;
                /** @brief computed field */  
                bool computed_;
        };
    }
}

#endif	/* FIELD_HPP */

