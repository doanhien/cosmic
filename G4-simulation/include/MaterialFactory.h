#ifndef __MATERIAL_FACTORY_H__
#define __MATERIAL_FACTORY_H__

#include "G4Element.hh"
#include "G4Material.hh"

#include <map>

typedef std::map<G4int,G4Element*>            ELEMENT_HASH;
typedef std::map<G4int,G4Material*>           MATERIAL_HASH;
typedef std::map<G4int,G4Element*>::iterator  ELEMENT_ITERATOR;
typedef std::map<G4int,G4Material*>::iterator MATERIAL_ITERATOR;

/**
 * Base class of material factory.
 * This class provides some methods to access and control elements and materials.
 * All elements and materials are not defined at this class.
 * They must be defined at inherit class of this.
 *
 * @author Akira KUSUMOTO
 * @date $Date$
 * @version $Revision$
 */
class MaterialFactory
{
public:
    /// The element numbers
    enum ELEMENTS { E_C  = 1, E_H  = 2, E_N  = 3,  
                    E_O  = 4, E_NB = 5, E_TI = 6,
                    E_CU = 7, E_AL = 8, E_SI = 9 };

    /// The material numbers
    enum MATERIALS {
        M_VACUUM       = 1,  M_AIR          = 2,  M_ALUMINIUM     = 3,
        M_COPPER       = 4,  M_MYLAR        = 5,  M_MAG_CONDUCTOR = 6,
        M_ZYLON        = 7,  M_ROHACELL     = 8,  M_SCINTILATOR   = 9,
        M_IDC_GAS      = 10, M_GFRPG10      = 11, M_GLUE          = 12,
        M_AIREXULTEM   = 13, M_CARBONFORM   = 14, M_GATHERFORM    = 15,
        M_STYROFORM    = 16, M_POLYETHYLENE = 17, M_AGEL          = 18 };

protected:
    ELEMENT_HASH  elementMap;
    MATERIAL_HASH materialMap;

public:
    MaterialFactory( void );
    virtual ~MaterialFactory( void );

    /**
     * Initialize elements and materials.
     * But, this class only calls DefineElements() and DefineMaterials().
     * Definition of elements and materials must be implemented at inherit class of this class.
     */
    void Initialize     ( void );
    /**
     * Delete all defined materials and elements.
     * This methos will be called from destractor.
     */
    void DeleteMaterials( void );

    /**
     * The pure virtual function of elements definition.
     * Implementation of elements definition must be provided by inherit class.
     */
    //virtual void DefineElements ( void ) = 0;
    virtual void DefineElements ( void );
    /**
     * The pure virtual function of material definition.
     * Implementation of materials definition must be provided by inherit class.
     */
    virtual void DefineMaterials( void ) = 0;
    //virtual void DefineMaterials( void );

    /**
     * Get a element.
     * You can specify a element you want by element ID.
     * @param id element id ( MaterialFactory::ELEMENTS )
     * @return G4Element
     */
    G4Element  *GetElement ( G4int id );
    /**
     * Get a material.
     * You can specify a material you want by material ID.
     * @param id material id ( MaterialFactory::MATERIALS )
     * @return G4Material
     */
    G4Material *GetMaterial( G4int id );

    /**
     * Set a element.
     * @param id element ID
     * @param element a element instance
     * @return 0
     */
    int SetElement ( G4int id, G4Element  *element  );
    /**
     * Set a material.
     * @param id material ID
     * @param material a material instance
     * @return 0
     */
    int SetMaterial( G4int id, G4Material *material );

    /**
     * Add a element
     * @param id emement ID
     * @param element a element instance
     * @return flag
     *  - 0 = success
     *  - <0 = failed
     */
    int AddElement ( G4int id, G4Element  *element  );
    /**
     * Add a material
     * @param id material ID
     * @param material a material instance
     * @return flag
     *  - 0 = success
     *  - <0 = failed
     */
    int AddMaterial( G4int id, G4Material *material );

    /**
     * Dump defined element and material information
     */
    void Dump( void );
};

#endif
