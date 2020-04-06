#include <iostream>

#include "Automaton.h"


void Automaton::addSegment ( Segment* segment ){

  if ( segment->getLayer() >= _segments.size() ) { //in case this layer is not included so far
    _segments.resize( segment->getLayer() + 1 ); //resize the vector, so that the layer of the segment is now included

  }

  _segments[ segment->getLayer() ].push_back ( segment );

  _nConnections += segment->getChildren().size();

  //std::cout << "information of this segment: " << segment->getInfo() << std::endl;

}


void Automaton::lengthenSegments(){

  //streamlog_out(DEBUG2) << "Combining the shorter segments to longer ones\n";
  std::cout << "Combining the shorter segments to longer ones\n";

  std::vector < std::list < Segment* > > longerSegments;

  if( _segments.size() > 0 ) longerSegments.resize ( _segments.size() -1 ); //This will have one layer less  

  //----------------------------------------------------------------------------------------------//
  //                                                                                              //
  // next: find all the longer segments and store them in the new vector[][]                      //
  //                                                                                              //
  //----------------------------------------------------------------------------------------------//

  unsigned nLongerSegments=0;
  unsigned nShorterSegments= _segments[0].size();

  for (unsigned layer = 1; layer < _segments.size(); layer++){ //over all layers where there still can be something below

    std::list<Segment*> segments = _segments[layer];

    for ( std::list<Segment*>::iterator iSeg=segments.begin(); iSeg != segments.end(); iSeg++){ //over all segments in this layer

      nShorterSegments++;

      Segment* parent = *iSeg;

      //std::cout << "-------The Layer the parent are on: " << parent->getLayer() << std::endl;

      std::list <Segment*> children = parent->getChildren();

      for ( std::list<Segment*>::iterator iChild=children.begin(); iChild !=children.end(); iChild++){ //over all children of this parent

	Segment* child = *iChild;

	//Combine the parent and the child to form a new longer segment

	//take all the hits from the parent

	std::vector < IHit* > hits = parent->getHits();

	//and also add the inner hit from the child
	hits.insert( hits.begin(), child->getHits().at(0) );


	//make the new (longer) segment
	Segment* newSegment = new Segment ( hits );
	nLongerSegments++;


	//set the layer to the layer of the childsegment
	unsigned newLayer = child->getLayer();
	newSegment->setLayer ( newLayer );

	// Set the skipped layers.
	//std::cout << "checking skipped layers" << std::endl;
	int skippedLayers = parent->getLayer() - child->getLayer() - 1;

	//std::cout << "layer of parent: " << parent->getLayer() << " and of child: " << child->getLayer() << std::endl;
	//if( skippedLayers < 0 ) throw  std::string("skippedLayers can't be < 0!") ;
	if( skippedLayers < 0 ) continue;

	newSegment->setSkippedLayers( unsigned(skippedLayers) );

	std::cout << "Created longer segment: " << parent->getHits().size()
				<< "hits -->" << newSegment->getHits().size()
				<< " hits, layer = " << newLayer
				<< ", skipped layers = " << skippedLayers <<"\n";

	std::cout << "Combined: " << child->getInfo() << "<--with-->" << parent->getInfo() << "\n";


	// Erase the connection from the child to the parent segment and replace it with a link to the new
	// (longer) segment. ( and vice versa ) This way we can connect the longer segments easily after.

	child->deleteParent( parent );
	child->addParent ( newSegment );
	parent->deleteChild ( child );
	parent->addChild ( newSegment );

	//std::cout << "information of each segment : " << newSegment->getInfo() << std::endl;
	//std::cout << "Save the new segment in the new vector[][] " << std::endl;
	// Save the new segment in the new vector[][]
	longerSegments[newLayer].push_back( newSegment );

	//std::cout<< "!!!!!!!!!! finish saving " << std::endl;

      }
      //std::cout << "!!!!!!!!!!!!!child segment" << std::endl;
    }
    //std::cout << "!!!!!!!!! done loop on segment" << std::endl;
  }

  std::cout << " Made " << nLongerSegments << " longer segments from " << nShorterSegments << " shorter segments.\n";

  std::cout << "Next connecting the new longer segments\n";

  unsigned nConnections=0;
  unsigned nPossibleConnections=0;

  for ( unsigned layer = 1; layer + 1 < _segments.size(); layer++ ){ 
    // over all layers (of course the first and the last ones are spared out because there is nothing more above or below

    std::list<Segment*> segments = _segments[layer];

    for ( std::list<Segment*>::iterator iSeg=segments.begin(); iSeg != segments.end(); iSeg++ ){ //over all (short) segments in this layer

      Segment* segment = *iSeg;
      std::list<Segment*> parents = segment->getParents();
      std::list<Segment*> children = segment->getChildren();

      for ( std::list<Segment*>::iterator iParent = parents.begin(); iParent != parents.end(); iParent++ ){ // over all parents of the segment

	Segment* parent = *iParent;

	std::cout << "parent info: " << parent->getInfo() << "\n";
	std::cout << "number of children: " << children.size() << "\n";
	for ( std::list<Segment*>::iterator iChild = children.begin(); iChild != children.end(); iChild++ ){ // over all children of the segment

	  Segment* child = *iChild;

	  // Check if they are compatible
	  bool areCompatible = true;
	  ICriterion* theFailedCrit = NULL; 

	  std::cout << "check all criteria (or at least until one returns false)" << std::endl;
	  for ( unsigned iCrit = 0; iCrit < _criteria.size(); iCrit++ ){

	    std::cout << " Criterion: " << _criteria[iCrit]->getName() << "\n";
	    //std::cout << "is compatible or not: " << _criteria[iCrit]->areCompatible ( parent , child ) << "\n";
	    if ( _criteria[iCrit]->areCompatible ( parent , child ) == false ){

	      areCompatible = false;
	      theFailedCrit = _criteria[iCrit];

	      break;
	    }
	  
	  }

	  if ( areCompatible ){

	    //connect parent and child (i.e. connect the longer segments we previously created)
	    child->addParent( parent );
	    parent->addChild( child );
                
	    nConnections++;

	    std::cout << "Connected: " << child->getInfo() << "<--with-->" << parent->getInfo() << "\n";

	  }

	  else {

	    std::cout << "NOT Connected: " << child->getInfo() << "<--XXXX-->" << parent->getInfo() << "\n";
	    if( theFailedCrit != NULL ) std::cout << "Failed first at criterion: " << theFailedCrit->getName() << "\n";

	  }

	  nPossibleConnections++;

	}

      }

    }

  }

  _nConnections = nConnections;

  std::cout << "Made " << nConnections << " of " << nPossibleConnections
			 << " possible connections \n";


  //----------------------------------------------------------------------------------------------//
  //                                                                                              //
  //   Finally: replace the vector<list<segment*>> of the old segments with the new one           //
  //                                                                                              //
  //----------------------------------------------------------------------------------------------//

  //delete all old Segments:
  for( unsigned i=0; i<_segments.size(); i++){

    std::list<Segment*>& segments = _segments[i];

    for ( std::list<Segment*>::iterator iSeg=segments.begin(); iSeg != segments.end(); iSeg++ ){

      Segment* segment = *iSeg;
      delete segment;
   
    }

    segments.clear();


  }

  // And replace with the newer ones
  _segments = longerSegments;

}


void Automaton::doAutomaton(){

  bool hasChanged = true;
  int nIterations = -1;

  while ( hasChanged == true ){ //repeat this until no more changes happen (this should always be equal or smaller to the number of layers - 1

    hasChanged = false;
    nIterations++;

    //std::cout << ">>>>>>>>>> looping on segment of size: " << _segments.size() << std::endl;
    for ( int layer = _segments.size()-1; layer >= 0; layer--){ //for all layers from outside in

      std::list <Segment*> segments = _segments[layer];
      //std::cout << ">>>>>>>> layer = " << layer << std::endl;
      //std::cout << ">>>>>>>> size of segment for starting automaton: " << segments.size() << std::endl;
      //std::cout << "\n";

      for ( std::list<Segment*>::iterator iSeg=segments.begin(); iSeg!= segments.end(); iSeg++ ){ //for all segments in the layer

	Segment* parent= *iSeg;

	//std::cout << ">>>>>> info of parent before doautomaton: " << parent->getInfo() << std::endl;
	//Simulate skipped layers
	std::vector < int >& state = parent->getState();

	for ( int j= state.size()-1; j>=1; j--){

	  if ( state[j] == state[j-1] ){

	    state[j]++;
	    hasChanged = true; //something changed

	  }

	}

	//std::cout << "checking if parent is activie" << std::endl;
	if ( parent->isActive() ){
	  //std::cout << "!!!!!!!!!!!! parent is active" << std::endl;
	  bool isActive = false;

	  //std::cout << "getting list of chidren segments" << std::endl;
	  //std::cout << "size of children = " << parent->getChildren().size() << std::endl;
	  //std::cout << "infor of parent segment: " << parent->getInfo() << std::endl;
	  //Check if there is a neighbor
	  std::list <Segment*> children = parent->getChildren();

	  //std::cout << "loop on segment of children" << std::endl;

	  for ( std::list<Segment*>::iterator iChild=children.begin(); iChild != children.end(); iChild++ ){// for all children

	    Segment* child = *iChild;

	    if ( child->getOuterState() == parent->getInnerState() ){  //Only if they have the same state

	      parent->raiseState(); //So it has a neighbor --> raise the state


	      hasChanged = true; //something changed
	      isActive = true;

	      break;  //It has a neighbor, we raised the state, so we don't need to check again

	    }

	  }

	  parent->setActive( isActive );

	}

	//std::cout << "is parent active or not! we don't know" << std::endl;
      }

      //std::cout << "done performing on layer: " << layer << std::endl;

    }

  }


  std::cout << "Automaton performed using " << nIterations << " iterations.\n";

}


void Automaton::cleanBadStates(){

  unsigned nErasedSegments = 0;
  unsigned nKeptSegments = 0;

  for( unsigned layer=0; layer < _segments.size(); layer++ ){//for every layer

    std::list <Segment*> & segments = _segments[layer]; // We want to change things in the original list! Therefore the reference operator

    for( std::list<Segment*>::iterator iSeg= segments.begin(); iSeg != segments.end(); iSeg++ ){//over every segment

      Segment* segment = *iSeg;

      if( segment->getInnerState() == (int) layer ){ //the state is alright (equals the layer), this segment is good

	nKeptSegments++;

      }

      else { //state is wrong, delete the segment

	nErasedSegments++;

	//erase it from all its children
	std::list <Segment*> children = segment->getChildren();

	for (std::list<Segment*>::iterator iChild = children.begin(); iChild != children.end(); iChild++ ){

	  (*iChild)->deleteParent ( segment );
	  _nConnections--;

	}

	//erase it from all its parents
	std::list <Segment*> parents = segment->getParents();

	for (std::list<Segment*>::iterator iParent = parents.begin(); iParent!= parents.end(); iParent++){

	  (*iParent)->deleteChild ( segment );
	  _nConnections--;

	}

	//erase from the automaton
	delete *iSeg;
	iSeg = segments.erase( iSeg );  //erase the segment and update the iterator

      }

    }

  }

  std::cout << "Erased segments because of bad states= " << nErasedSegments << "\n";
  std::cout << "Kept segments because of good states= " << nKeptSegments << "\n";

}


void Automaton::resetStates(){

  for ( unsigned layer = 0; layer < _segments.size(); layer++ ){ //over all layers

    std::list<Segment*> segments = _segments[layer];

    for ( std::list<Segment*>::iterator iSeg = segments.begin(); iSeg != segments.end(); iSeg++ ){ //over all segments in the layer

      (*iSeg)->resetState();
      (*iSeg)->setActive( true );

    }

  }

}


void Automaton::cleanBadConnections(){

  unsigned nConnectionsKept = 0;
  unsigned nConnectionsErased = 0;

  for ( int layer = _segments.size()-1 ; layer >= 1 ; layer-- ){ 
    //over all layers from outside in. And there's no need to check layer 0, as it has no children.

    std::list<Segment*> segments = _segments[layer];

    for ( std::list<Segment*>::iterator iSeg = segments.begin(); iSeg!=segments.end(); iSeg++ ){ // over all segments in the layer

      Segment* parent = *iSeg;
      std::list < Segment* > children = parent->getChildren();

      for ( std::list<Segment*>::iterator iChild = children.begin(); iChild != children.end(); iChild++ ){ //over all children the segment has got

	Segment* child = *iChild;

	bool areCompatible = true; //whether segment and child are compatible

	//check all criteria (or at least until the first false pops up)
	for ( unsigned iCrit=0; iCrit < _criteria.size() ; iCrit++ ){

	  if ( _criteria[iCrit]->areCompatible( parent , child ) == false ){

	    areCompatible = false;
	    break; //no need to continue, now that we know, they're not compatible

	  }

	}

	if ( areCompatible == false ){ // they are not compatible --> erase the connection

	  nConnectionsErased++;
	  _nConnections--;
               
	  //erase the connection:
	  parent->deleteChild ( child );
	  child->deleteParent ( parent );

	}

	else {

	  nConnectionsKept++;

	}

      }

    }

  }

  std::cout << "Erased bad connections= " << nConnectionsErased << "\n";
  std::cout << "Kept good connections= " << nConnectionsKept << "\n";

}

std::vector < std::vector< IHit* > > Automaton::getTracksOfSegment ( Segment* segment, std::vector< IHit*> hits , unsigned minHits ){

  std::vector < std::vector< IHit* > > tracks; //the vector of the tracks to be returned
  std::vector <IHit*> segHits = segment->getHits(); // the hits of the segment


  //add the outer hit
  if ( segHits.back()->isVirtual() == false ) hits.push_back ( segHits.back() );  //Of course add only real hits to the track

  std::list <Segment*> children = segment->getChildren();

  if ( children.empty() ){ //No more children --> we are at the bottom --> start a new Track here

    //add the rest of the hits to the vector
    for ( int i = segHits.size()-2 ; i >= 0; i--){
         
      if ( segHits[i]->isVirtual() == false ) hits.push_back ( segHits[i] );

    }

    if ( hits.size() >= minHits ){

      //add this to the tracks
      tracks.push_back ( hits );

    }

  }

  else { // there are still children below --> so just take all their tracks and do it again

    for ( std::list<Segment*>::iterator iChild=children.begin(); iChild!= children.end(); iChild++){ //for all children

      std::vector < std::vector< IHit* > > newTracks = getTracksOfSegment( *iChild , hits );

      for (unsigned int j=0; j < newTracks.size(); j++){//for all the tracks of the child

	tracks.push_back ( newTracks[j] );

      }

    }

  }

  return tracks;

}


std::vector < std::vector< IHit* > > Automaton::getTracks( unsigned minHits ){

  std::vector < std::vector< IHit* > > tracks;
  std::vector <IHit*> emptyHitVec;

  std::cout << " segment size of automaton: " << _segments.size() << std::endl;
  for ( unsigned layer = 0 ; layer < _segments.size() ; layer++ ){ //over all layers

    std::list<Segment*> segments = _segments[layer];

    int count = 0;
    for ( std::list<Segment*>::iterator iSeg = segments.begin(); iSeg != segments.end(); iSeg++ ){ //over all segments
      count++;
      Segment* segment = *iSeg;


      std::cout  << "segment information: " << segment->getInfo() << "\n";
      //get the tracks from the segment
      std::vector < std::vector< IHit* > > newTracks = getTracksOfSegment( segment , emptyHitVec , minHits );

      //and add them to the vector of all tracks
      tracks.insert( tracks.end() , newTracks.begin() , newTracks.end() );

    }

    // std::cout << "number of segment of each layer: " << count << std::endl;
  }

  return tracks;

}

/*
std::vector <const Segment*> Automaton::getSegments() const{

  std::vector <const Segment*> segments;
   
  for( unsigned layer=0; layer < _segments.size(); layer++ ){

    segments.insert( segments.end() , _segments[layer].begin() , _segments[layer].end() );

  }

  for ( std::vector <const Segment*>::iterator iSeg=segments.begin(); iSeg!= segments.end(); iSeg++ ){

    std::cout << "-------->>>>>>>>  hit information " << (*iSeg)->getInfo() << std::endl;

  }

  return segments; 

}
*/

std::vector <Segment*> Automaton::getSegments() const{

  std::vector <Segment*> segments;
   
  for( unsigned layer=0; layer < _segments.size(); layer++ ){

    segments.insert( segments.end() , _segments[layer].begin() , _segments[layer].end() );

    std::list <Segment*> segmentsT = _segments[layer];

    for ( std::list<Segment*>::iterator iSeg=segmentsT.begin(); iSeg!= segmentsT.end(); iSeg++ ){

      std::cout << "-------->>>>>>>>  hit information " << (*iSeg)->getInfo() << std::endl;

    }

  }

  //for ( std::vector <Segment*>::iterator iSeg=segments.begin(); iSeg!= segments.end(); iSeg++ ){
  //std::cout << "-------->>>>>>>>  hit information " << (*iSeg)->getInfo() << std::endl;
  //}

  return segments; 

}


Automaton::~Automaton(){

  //delete segments
  for( unsigned layer=0; layer < _segments.size(); layer++){ //over all layers

    std::list<Segment*> segments = _segments[layer];

    for( std::list<Segment*>::iterator iSeg = segments.begin(); iSeg!=segments.end(); iSeg++ ){ //over all segments

      delete *iSeg;

    }

  }

}




