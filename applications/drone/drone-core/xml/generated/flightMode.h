#ifndef FLIGHT_MODE_H_
#define FLIGHT_MODE_H_
/**
 * \file flightMode.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from physics.xml
 */

/**
 * Helper namespace to hide FlightMode enum from global context.
 */

namespace FlightMode {

/** 
 * \brief Flight Mode 
 * Flight Mode 
 */
enum FlightMode {
    /** 
     * \brief Raw 
     * Raw 
     */
    RAW = 0,
    /** 
     * \brief Stab 
     * Stab 
     */
    STAB = 1,
    /** 
     * \brief Acro 
     * Acro 
     */
    ACRO = 2,
    /** 
     * \brief Althold 
     * Althold 
     */
    ALTHOLD = 3,
    /** 
     * \brief Loiter 
     * Loiter 
     */
    LOITER = 4,
    /** 
     * \brief Last virtual option to run cycles to
     */
    FLIGHT_MODE_LAST
};


static inline const char *getName(const FlightMode &value)
{
    switch (value) 
    {
     case RAW : return "RAW"; break ;
     case STAB : return "STAB"; break ;
     case ACRO : return "ACRO"; break ;
     case ALTHOLD : return "ALTHOLD"; break ;
     case LOITER : return "LOITER"; break ;
     default : return "Not in range"; break ;
     
    }
    return "Not in range";
}

} //namespace FlightMode

#endif  //FLIGHT_MODE_H_
