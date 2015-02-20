#ifndef GAMMA_DMODEL_DATA_TYPES_H__
    #define GAMMA_DMODEL_DATA_TYPES_H__
/**
 * @file
 *
 * Contains all GADMODEL-specific data types.
 *
 * @author  (C)opyright since 2003 by RST Industrie-Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/dataTypes.h>


/******************************************************************************
 * Object Types
 ******************************************************************************/
/**
 * Identification of the Gamma Data Model objects for performing the aliasing
 * operations #gd_addAlias and #gd_removeAlias.
 */
typedef enum gd_AliasTypeID
{
    gd_ALIAS_TYPE_ID_NODE,      ///< Only perform operation on node types.
    gd_ALIAS_TYPE_ID_ACTION,    ///< Only perform operation on action types.
    gd_ALIAS_TYPE_ID_LOOP,      ///< Only perform operation on loop types.
    gd_ALIAS_TYPE_ID_MEMORY,    ///< Only perform operation on memory types.
    gd_ALIAS_TYPE_ID_GROUP,     ///< Only perform operation on group types.
    gd_ALIAS_TYPE_ID_PV_ARRAY,  ///< Only perform operation on PV Array types.
    gd_ALIAS_TYPE_ID_FIFO,      ///< Only perform operation on Fifo types
} gd_AliasTypeID;


/**
 * The default scope to apply if the user did not explicitly quote one.
 */
typedef enum gd_DefaultScope
{
    /**
     * This scope does always add a 'local scope' prefix (":") to the alias if
     * the user did not specify any other scope.
     *
     * The following table shows some examples:
     * user input:       result:            remarks:
     * "actionX"         ":actionX"         automatically applied
     * ":actionX"        ":actionX"         no manipulation - scope already existing
     * "*:actionX"       "*:actionX"        no manipulation - scope already existing
     */
    gd_DEFAULT_SCOPE_LOCAL,

    /**
     * This scope does always add a 'global scope' prefix ("*:") to the alias if
     * the user did not specify any other scope.
     *
     * The following table shows some examples:
     * user input:       result:            remarks:
     * "actionX"         "*:actionX"        automatically applied
     * ":actionX"        ":actionX"         no manipulation - scope already existing
     * "*:actionX"       "*:actionX"        no manipulation - scope already existing
     */
    gd_DEFAULT_SCOPE_GLOBAL,
} gd_DefaultScope;

/**
 * Validates the value of the given gd_DefaultScope variable.
 */
#define gd_DefaultScope_isValid( scope ) \
    (gd_DEFAULT_SCOPE_LOCAL == (scope) || \
     gd_DEFAULT_SCOPE_GLOBAL == (scope) )


#endif /* GAMMA_DMODEL_DATA_TYPES_H__ */

