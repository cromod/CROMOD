/** 
 * @file Segment.hpp
 * @brief Header file of Segment class
 * @author cromod
 * @date june 2015
 */

#ifndef SEGMENT_HPP
#define	SEGMENT_HPP

#include "Vector.hpp"
#include <vector>

namespace Cromod {
    namespace GeomAPI {
        /** @class Segment Segment.hpp
         *  @brief Class to define a segment
         */
        class Segment {
            
            public:
                
                /** @brief Default constructor */
                Segment();
                /** @brief Copy constructor */
                Segment(const Segment& seg);
                /** @brief Constructor
                 *  @param point1 first point
                 *  @param point2 second point
                 *  @param exit boolean
                 */
                Segment(const Point &point1,
                        const Point &point2, const bool &exit=false);
                /** @brief Destructor */
                virtual ~Segment();
                
                /** @brief Equality operator
                 *  @param seg Segment object
                 *  @return true if Segment objects are equal
                 */
                bool operator==(const Segment &seg) const;
                /** @brief Inequality operator
                 *  @param seg Segment object
                 *  @return true if Segment objects are not equal
                 */
                bool operator!=(const Segment &seg) const;
                /** @brief Assignment operator
                 *  @param seg Segment object
                 *  @return Segment object
                 */
                Segment& operator=(const Segment &seg);
                
                /** @brief Method to define a point as an exit
                 *  @param exit true if it is an exit point
                 */
                void setExit(bool exit);
                /** @brief Method to know a point is an exit
                 *  @return true if it is an exit point
                 */
                bool isExit() const;
                /** @brief Method to define the first point
                 *  @param point1 first point
                 */
                void setOne(Point point1);
                /** @brief Method to get the first point
                 *  @return first point
                 */
                Point getOne() const;
                /** @brief Method to define the second point
                 *  @param point2 second point
                 */
                void setTwo(Point point2);
                /** @brief Method to get the second point
                 *  @return second point
                 */
                Point getTwo() const;
                /** @brief Method to define endpoints
                 *  @param point1 first point
                 *  @param point2 second point
                 */
                void setPoints(Point point1,Point point2);
                /** @brief Method to get endpoints
                 *  @return list of endpoints
                 */
                std::vector<Point> getPoints() const;
                /** @brief Method to get vector
                 *  @return vector between first and second points
                 */
                Vector getVector() const;
                
                /** @brief Method to get the length of segment
                 *  @return length of segment
                 */
                double getLength() const;
                /** @brief Method to know if it is a segment
                 *  @return true if it is a segment
                 */
                bool isSegment() const;
                /** @brief Method to get the minimum distance between point and segment
                 *  @param point Point object
                 *  @return minimum distance between point and segment
                 */
                double getMinDist(const Point &point);
                
                /** @brief Function to determine the orientation of three points
                 *  @details http://en.wikipedia.org/wiki/Curve_orientation
                 *  @param pointA first point
                 *  @param pointB second point
                 *  @param pointC third point
                 *  @return result < 0 -> counterclockwise direction\n
                 *          result = 0 -> points collinear\n
                 *          result > 0 -> clockwise direction
                 */
                static double orientation(const Point &pointA, 
                                          const Point &pointB, 
                                          const Point &pointC);

                /** @brief Method to check intersection
                 *  @details http://algs4.cs.princeton.edu/91primitives/
                 *  @param seg Segment object
                 *  @return true if segments intersect
                 */
                bool checkIntersect(const Segment &seg) const;
                
                /** @brief Method to check parallelism
                 *  @details -> compute cross product
                 *  @param seg Segment object
                 *  @return true if segments are parallel
                 */
                bool checkParallel(const Segment &seg) const;
                
                /** @brief Method to check point inclusion
                 *  @param pointB point
                 *  @return true if point is included
                 *  @details Thales theorem
                 */
                bool checkInclude(const Point &pointB) const;

                /** @brief Method to define a projected point
                 *  @details -> compute scalar product
                 *  @param pointC point
                 *  @return projected point
                 */
                Point findPerPoint(const Point &pointC) const;
                
            private:
                
                /** @brief First point */  
                Point point1_; 
                /** @brief Second point */  
                Point point2_;
                /** @brief Boolean to check if segment is an exit */  
                bool exit_;
                
        };
    }
}

#endif	/* SEGMENT_HPP */

