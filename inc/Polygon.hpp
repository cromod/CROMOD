/** 
 * @file Polygon.hpp
 * @brief Header file of Polygon class
 * @author cromod
 * @date june 2015
 */

#ifndef POLYGON_HPP
#define	POLYGON_HPP

#include "Segment.hpp"
#include <map>
#include "Constants.hpp"

namespace Cromod {
    namespace GeomAPI {
        /** @class Polygon Polygon.hpp
         *  @brief Class to define a polygon
         */
        class Polygon {
        
            public:
            
                /** @brief Default constructor */
                Polygon();
                /** @brief Copy constructor */
                Polygon(const Polygon& polygon);
                /** @brief Constructor
                 *  @param listPoints list of points
                 */
                Polygon(const std::vector<Point>& listPoints);
                /** @brief Destructor */
                virtual ~Polygon();
                
                /** @brief Index operator
                 *  @param i index
                 *  @return selected segment
                 */
                Segment& operator[](const unsigned int& i);
                /** @brief Assignment operator
                 *  @param polygon Polygon object
                 *  @return Polygon object
                 */                
                Polygon& operator=(const Polygon &polygon);
                
                /** @brief Method to get size
                 *  @return size
                 */
                unsigned int size() const;
                /** @brief Method to get index
                 *  @param segment Segment object
                 *  @return index
                 */
                unsigned int index(const Segment &segment) const;
                /** @brief Method to add segment
                 *  @param seg Segment object
                 */
                void addSegment(Segment seg);
                /** @brief Method to delete a segment */
                void delSegment();
                /** @brief Method to delete all segments */
                void deleteAll();
                /** @brief Method to add a point
                 *  @param point Point object
                 */
                void addPoint(const Point& point);
                /** @brief Method to get list of segments
                 *  @return list of segments
                 */
                std::vector<Segment> getList();
                /** @brief Method to set a list of segments
                 *  @param listSeg list of segments
                 */
                void setList(const std::vector<Segment>& listSeg);
                
                /** @brief Method to check if polygon is closed
                 *  @return true if closed
                 */
                bool isClosed();
                /** @brief Method to close a polygon */
                void close();
                /** @brief Method to get list of points
                 *  @return list of points
                 */
                std::vector<Point> getPoints();
                /** @brief Method to get a point outside polygon
                 *  @return point outside
                 */
                Point getOutside();
                /** @brief Method to get extrem coordinates of polygon
                 *  @return map of extrem coordinates
                 */
                std::map<Bottom,double> getBottom();
                
                /** @brief Method to check if polygon is crossed
                 *  @return true if crossed
                 */
                bool isSelfIntersect();
                /** @brief Method to get number of intersections
                 *         between a segment and a polygon
                 *  @param segment Segment object
                 *  @return number of intersections
                 */              
                int getNbIntersect(const Segment& segment);
                /** @brief Method to check if a point is on edge of polygon
                 *  @param point Segment point
                 *  @return true if point is on edge
                 */
                bool isOnEdge(const Point& point);
                /** @brief Method to check if a point is inside polygon
                 *  @details http://www.zebulon.fr/questions-reponses/points-interieur-d-un-polygone-149.html
                 *  @param point Point point
                 *  @return true if point is inside
                 */
                bool isInside(const Point& point_in);
            
            private:
                
                /** @brief list of segments */  
                std::vector<Segment> listSeg_;
        };
    }
}
#endif	/* POLYGON_HPP */

