#include "MaterialFactory.h"
#include "MessageManager.h"

//#include 
MaterialFactory::MaterialFactory( void )
{
}

MaterialFactory::~MaterialFactory( void )
{
    DeleteMaterials();
}

void MaterialFactory::Initialize( void )
{
    DefineElements ();
    DefineMaterials();
}

void MaterialFactory::DefineElements(void )
{
}

void MaterialFactory::DefineMaterials(void )
{
}

void MaterialFactory::DeleteMaterials( void )
{
    G4MaterialTable *matTable = (G4MaterialTable*)G4Material::GetMaterialTable();
    for( unsigned int i = 0; i < matTable->size(); i++ )
        delete (*(matTable))[i];
    matTable->clear();

    G4ElementTable *elemTable = (G4ElementTable*)G4Element::GetElementTable();
    for( unsigned int i = 0; i < elemTable->size(); i++ )
        delete (*(elemTable))[i];
    elemTable->clear();
}

G4Element *MaterialFactory::GetElement( G4int id )
{
  //G4cout << "Get element whose ID = " << id << G4endl;

    if( !elementMap[id] )
    {
        PError( "Element %d is not defined\n", id );
        return NULL;
    }

    return elementMap[id];
}

G4Material *MaterialFactory::GetMaterial( G4int id )
{ 

  //G4cout << ">>>>>> Material Map size: " << materialMap.size() << G4endl; 

    if( !materialMap[id] )
    {
        PError( "Material %d is not defined\n", id );
        return NULL;
    }

    return materialMap[id]; 
}

int MaterialFactory::SetElement ( G4int id, G4Element  *element  )
{
    if( elementMap[id] ) delete elementMap[id];
    elementMap[id] = element;

    return 0;
}

int MaterialFactory::SetMaterial( G4int id, G4Material *material )
{
    if( materialMap[id] ) delete materialMap[id];
    materialMap[id] = material;

    return 0;
}

int MaterialFactory::AddElement( G4int id, G4Element  *element  )
{
    if( elementMap[id] )
    {
        PWarning( "A element whose ID = %d is already defined\n", id );
        return -1;
    }

    elementMap[id] = element;
    //G4cout << "Done add element whose ID = " << id << G4endl;

    return 0;
}

int MaterialFactory::AddMaterial( G4int id, G4Material *material )
{

  //G4cout << "Add material whose ID = " << id << " G4M: " << material << G4endl;
    if( materialMap[id] )
    {
        PWarning( "A material whose ID = %d is already defined\n", id );
        return -1;
    }

    materialMap[id] = material;

    return 0;
}

void MaterialFactory::Dump( void )
{
    // dump all elements
    PMessage( "Element List: %d elements\n", elementMap.size() );
    for( ELEMENT_ITERATOR ie = elementMap.begin();    
         ie != elementMap.end();
         ie++ )
        PMessage( "  #%03d: %s\n", ie->first, ie->second );
    PMessage( "\n" );

    // dump all materials
    PMessage( "Material List: %d materials\n", materialMap.size() );
    for( MATERIAL_ITERATOR im = materialMap.begin();
         im != materialMap.end();
         im++ )
        PMessage( "  #%03d: %s\n", im->first, im->second );
    PMessage( "\n" );
}

