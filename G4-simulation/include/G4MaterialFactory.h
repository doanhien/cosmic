#ifndef __G4_MATERIAL_FACTORY_H__
#define __G4_MATERIAL_FACTORY_H__

#include "MaterialFactory.h"

/**
 * Material factory class.
 * This class creates materials which are same as g3lib
 * 
 * @author Akirar KUSUMOTO
 * @date $Date$
 * @version $Revision$
 */
class G4MaterialFactory : public MaterialFactory
{
public:
    G4MaterialFactory( void ){}
    ~G4MaterialFactory( void ){}

    /**
     * Define elements.
     * You can get these elements by MaterialFactory::GetElement().
     */
    //virtual void DefineElements ( void );
    void DefineElements ( void );
    /**
     * Define materials.
     * You can get these materials by MaterialFactory::GetMaterial().
     */
    //virtual void DefineMaterials( void );
    void DefineMaterials( void );
};

#endif
