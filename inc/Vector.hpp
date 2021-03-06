/** 
 * @file Vector.hpp
 * @brief Header file of Vector class
 * @author cromod
 * @date july 2015
 */

#ifndef VECTOR_HPP
#define	VECTOR_HPP

#include <valarray>

namespace Cromod {
    namespace GeomAPI {
        /** @class Vector Vector.hpp
         *  @brief Class to define a vector
         */
        class Vector: public std::valarray<double>
        {
            public:

                /** @brief Default constructor */
                Vector();

                /** @brief Copy constructor */
                Vector(const valarray<double>& vec);

                /** @brief Constructor with a double
                 *  @param val double value
                 *  @param n size of vector
                 */
                Vector(const double& val,size_t n);

                /** @brief Constructor with a table of double
                 *  @param val table of double
                 *  @param n size of vector
                 */
                Vector(const double* val,size_t n);
                
                /** @brief Equality operator
                 *  @param vec Vector object
                 *  @return true if Vector objects are equal
                 */
                bool operator==(const Vector& vec) const;

                /** @brief Inequality operator
                 *  @param vec Vector object
                 *  @return true if Vector objects are not equal
                 */
                bool operator!=(const Vector& vec) const;
        };

        /** @brief Function to compute cross product
         *  @param vec1 vector 1
         *  @param vec2 vector 2
         *  @return vector
         */
        Vector crossProd(const Vector& vec1, const Vector& vec2);

        /** @brief Function to compute dot product
         *  @param vec1 vector 1
         *  @param vec2 vector 2
         *  @return dot product
         */
        double dotProd(const Vector& vec1, const Vector& vec2);
	
        /** @typedef Point */
        typedef Vector Point;
    }
}

#endif	/* VECTOR_HPP */

