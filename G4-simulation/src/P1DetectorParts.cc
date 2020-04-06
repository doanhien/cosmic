#include "P1DetectorParts.h"

P1DetectorParts::P1DetectorParts( void )
    : solid          ( NULL ), logical_volume( NULL ),
      physical_volume( NULL ), check_overlap ( false )
{
}

P1DetectorParts::~P1DetectorParts()
{
    if( physical_volume ) delete physical_volume;
    if( logical_volume  ) delete logical_volume;
    if( solid           ) delete solid;
}
