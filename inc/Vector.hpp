/* 
 * File:   Vector.hpp
 * Author: florent
 *
 * Created on 27 juillet 2015, 19:57
 */

#ifndef VECTOR_HPP
#define	VECTOR_HPP

#include <valarray>

namespace Cromod {
    namespace GeomAPI {
        class Vector: public std::valarray<double>
        {
            public:
                /* Constructeur par defaut */
                Vector();
                /* Constructeur par copie */
                Vector(const valarray<double>& vec);
                /* Constructeurs */
                Vector(const double& val,size_t n);
                Vector(const double* val,size_t n);
                
                /* Operateur egal */
                bool operator==(const Vector& vec) const;
                /* Operateur difference */
                bool operator!=(const Vector& vec) const;
        };
        typedef Vector Point;
    }
}

#endif	/* VECTOR_HPP */

