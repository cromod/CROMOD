/* 
 * File:   Individual.hpp
 * Author: florent
 *
 * Created on 18 juin 2015, 22:08
 */

#ifndef INDIVIDUAL_HPP
#define	INDIVIDUAL_HPP

#include <vector>

using namespace std;

namespace Cromod {
    namespace CrowdAPI {
        class Individual {
        
        public:
        
            /* Constructeur */
            Individual();
            /* Constructeur par copie */
            Individual(const Individual& orig);
            /* Destructeur */
            virtual ~Individual();
        
            /* Methode pour definir si l'individu est a l'interieur */
            void setInside(bool inside);
            /* Methode pour savoir si l'individu est a l'interieur */
            bool isInside();
            /* Methode pour definir la masse */
            void setMass(double mass);
            /* Methode pour recuperer la masse */
            double getMass();
            /* Methode pour definir le temps de relaxation */
            void setTRelax(double trelax);
            /* Methode pour recuperer le temps de relaxation */
            double getTRelax();
            /* Methode pour definir le rayon */
            void setRadius(double rad);
            /* Methode pour recuperer le rayon */
            double getRadius();
            
            /* Methode pour definir la position */
            void setPosition(vector<double> position);
            /* Methode pour recuperer la position */
            vector<double> getPosition();
            /* Methode pour definir la vitesse reelle */
            void setSpeed(vector<double> speed);
            /* Methode pour recuperer la vitesse reelle */
            vector<double> getSpeed();
            /* Methode pour definir la vitesse desiree */
            void setWantedSpeed(vector<double> speed);
            /* Methode pour recuperer la vitesse desiree */
            vector<double> getWantedSpeed();
            /* Methode pour calculer la vitesse desiree */
            void computeWantedSpeed(/*GradField gradfield*/);
            /* Methode pour definir la force d'acceleration interieure */
            void setInsideForce(vector<double> force);
            /* Methode pour recuperer la force d'acceleration interieure */
            vector<double> getInsideForce();
            /* Methode pour calculer la force d'acceleration interieure */
            void computeInsideForce();
            /* Methode pour definir la resultante des forces de contact */
            void setContactForce(vector<double> force);
            /* Methode pour recuperer la resultante des forces de contact */
            vector<double> getContactForce();
            
            /* Methode pour calculer la distance entre 2 objets Individual */
            double getDistance(/*Individual individual*/);
            /* Methode pour calculer la distance minimale entre 2 objets Individual */
            double getDistMin(/*Individual individual*/);
            /* Methode pour calculer la distance relative entre 2 objets Individual */
            double getRelDistInd(/*Individual individual*/);
            /* Methode pour calculer la distance relative avec un obstacle */
            double getRelDistWall(/*Segment segment*/);
            /* Methode pour recuperer le vecteur unitaire dirige vers un autre objet Individual */
            vector<double> getDirVectorInd(/*Individual individual*/);
            /* Methode pour recuperer le vecteur unitaire dirige vers un obstacle */
            vector<double> getDirVectorWall(/*Segment segment*/);
        
        private:
        
            double mass_; // Masse de l'individu
            double radius_; // Rayon de l'individu
            double trelax_; // Temps de relaxation pour la force interieure
            bool inside_; // Test pour savoir si l'individu est a l'interieur
            vector<double> position_; // Position de l'individu
            vector<double> speed_; // Vitesse de l'individu
            vector<double> wSpeed_; // Vitesse desiree de l'individu
            vector<double> force_i_; // Force d'acceleration interieure
            vector<double> force_o_; // Resultante des forces de contact
        
        };
    }
}

#endif	/* INDIVIDUAL_HPP */

