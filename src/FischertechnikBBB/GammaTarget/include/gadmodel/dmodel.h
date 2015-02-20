#ifndef GAMMA_DMODEL_DMODEL_H__
  #define GAMMA_DMODEL_DMODEL_H__

/**
 * @file
 *
 * This file contains all headers of the GADMODEL Application Programming Interface.
 *
 * <h3> Overview </h3>
 * The following graph shows how the elements (primitive) of the Gamma Data Model
 * are related with each other.
 * <pre>
 *
 * Level 1    Level 2    Level 3    Level 4     Level 5
 *
 * system
 *   |
 *   |------- node [available: l/r] {name: scoped}
 *   |          |
 *   |          |------- memory [available: l/r] {name: scoped}
 *   |                     |
 *   |                     |------- group (has aliases) [available: l/r] {name: scoped}
 *   |                                |
 *   |                                |------- PVArray [available: l/r] {name: scoped)
 *   |
 *   |------- action [available: l/r] {name: scoped}
 *   |
 *   |------- loop [available: l/r] {name: scoped}
 *   |
 *   |------- IO [available: l only] {name: TBD}
 *             |
 *             |------- I/O channel [available: l only] {name: TBD}
 *
 * </pre>
 *
 * The objects of the data model are associated with an alias (name). These
 * aliases have the following restrictions:
 *  - The alias to be added (gd_xxx_addAlias) must be at least a valid C
 *    identifier. In addition it's allowed to use ".". E.g. ".AliasX", "levelX.levelY.objectO"
 *  - To query an object with a name it's required to use a ":" for the
 *    scope (system) of the object. E.g. the PVArray "LevelA.PVArrayA" on the
 *    local system can be either queried via ":LevelA.PVArrayA" or "LocalSystemName:LevelA.PVArrayA"
 *    where "LocalSystemName" is the name of the local system.
 *  - The aliases (and only these - unlike the primitives) exist without a
 *    hierarchy in the data model. Therefore if a memory gets the alias "X"
 *    it's not possible to give a PVArray the alias "X".
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/common.h>
#include <gadmodel/action.h>
#include <gadmodel/dataTypes.h>
#include <gadmodel/group.h>
#include <gadmodel/loop.h>
#include <gadmodel/memory.h>
#include <gadmodel/misc.h>
#include <gadmodel/node.h>
#include <gadmodel/platformDependencies.h>
#include <gadmodel/pv.h>
#include <gadmodel/pvArray.h>

#endif /* GAMMA_DMODEL_DMODEL_H__ */
