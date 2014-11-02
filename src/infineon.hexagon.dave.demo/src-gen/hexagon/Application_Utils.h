/**
 * @author generated by eTrice
 *
 * Utils File of ActorClass Application
 * 
 */

#ifndef _HEXAGON_APPLICATION_UTILS_H_
#define _HEXAGON_APPLICATION_UTILS_H_

#include "hexagon/Application.h"

/*
 * access macros for ports, operations and attributes
*/

/* simple event ports */
#define blinkyPort_start() PBlinkyControlConjPort_start(&self->constData->blinkyPort)
#define blinkyPort_stop() PBlinkyControlConjPort_stop(&self->constData->blinkyPort)
#define buttonControlPort_setInstance(data) PButtonControlProtocollConjPort_setInstance(&self->constData->buttonControlPort, data)
#define buttonPort_setInstance(data) PButtonProtocollConjPort_setInstance(&self->constData->buttonPort, data)
#define adcControlPort_setInstance(data) PAdcControlProtocollConjPort_setInstance(&self->constData->adcControlPort, data)
#define adcControlPort_start() PAdcControlProtocollConjPort_start(&self->constData->adcControlPort)
#define adcControlPort_stop() PAdcControlProtocollConjPort_stop(&self->constData->adcControlPort)

/* data receive ports */

/* data send ports */

/* saps */

/* replicated event ports */

/* services */

/* operations */

/* attributes */

#endif /* _HEXAGON_APPLICATION_UTILS_H_ */

