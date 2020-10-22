/*!*****************************************************************************
 * @file         IComposite.h
 *
 * @copyright    Copyright (c) 2020 by Sourceengineers. All Rights Reserved.
 *
 * @authors      Anselm Fuhrer anselm.fuhrer@sourceengineers.com
 *
 * @brief        Interface to implement the Composite design pattern
 *
 ******************************************************************************/
#ifndef ICOMPOSITE_H_
#define ICOMPOSITE_H_

#include <se-lib-c/definition/SeLibCTypes.h>

/******************************************************************************
 Define interface handle data
******************************************************************************/
typedef struct ICompositeStruct* ICompositeHandle;

/******************************************************************************
 Define interface
******************************************************************************/

typedef struct ICompositeStruct {
    SeLibGenericReferece handle;

    void (* add)(ICompositeHandle composite);
    void (* remove)(ICompositeHandle composite);

    void (* write)(ICompositeHandle composite);
    void (* read)(ICompositeHandle composite);
} IComposite;

// TODO needs to be able to add, remove and getChild

#endif //ICOMPOSITE_H_
