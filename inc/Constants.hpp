/** 
 * @file Constants.hpp
 * @brief Header file of constants
 * @author cromod
 * @date june 2015
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

/** @brief Cromod namespace */
namespace Cromod {
    /** @brief Geometric API */
    namespace GeomAPI {
        /** @brief Geometric tolerance */
        const double GEOM_TOLERANCE(1.e-6);
        /** @brief Bottom position */
        enum Bottom {XMIN, XMAX, YMAX, YMIN};
    }
    /** @brief Field API */
    namespace FieldAPI {
        /** @brief Value tolerance */
        const double VAL_TOLERANCE(1.e-6);
        /** @brief Node status */
        enum Status {UNKNOWN, NARROW, FROZEN};
        /** @brief Node around */
        enum Around {UP, DOWN, RIGHT, LEFT};
    }
}

#endif /* CONSTANTS_HPP */