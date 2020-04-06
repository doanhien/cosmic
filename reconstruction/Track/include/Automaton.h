#ifndef Automaton_h
#define Automaton_h

#include <vector>
#include "Segment.h"
#include "ICriterion.h"

class Automaton{

 public:
      
 Automaton(): _nConnections(0){}
      
  /**
   * delete all the segments
   */
  ~Automaton();
      
      
  /** Adds a segment to the automaton.\
   * Take care to set the layer of the segment before adding!
   */
  void addSegment ( Segment* segment );
      
  /**Lengthens the segments by one via adding the first hit of the next segment it is connected to
   * to it.
   * Also connects those longer segments with each other. ( one becomes a parent and one a child )
   * Segments that don't have connected segments to use to get longer, will die here. 
   */
  void lengthenSegments();
      
  /**Adds a criteria to the automaton. So it will be used, when the methods doAutomaton()
   * or cleanBadConnections() are called.
   */
  void addCriterion ( ICriterion* criterion ){ _criteria.push_back( criterion ); }
  void addCriteria ( std::vector< ICriterion* > criteria ){ _criteria.insert( _criteria.end() , criteria.begin() , criteria.end() ); }
  void clearCriteria() { _criteria.clear(); };
      
  /** Does iteration until the states of the segments don't change anymore.
   * 
   * In one iteration all segments are checked, if they have a neighbor.
   * A neighbor:
   * - has the same state
   * - fulfills all the criteria (this is automatically provided, because in lengthenSegments only connections that fullfill the Criteria are made)
   * 
   * If it has a neighbor its state will be raised by one at the end of the iteration.
   * (At the end only in theory: in the program it will be during the iteration, but
   * in a way, that it doesn't affect other segments)
   * 
   * When after an iteration the states didn't change, it stops.
   */
  void doAutomaton();
      
  /** 
   * Erases all segments that don't have a state corresponding to their layer.
   * 
   * After the automaton is performed every segment, that has a neighbor, that has a neighbor, that...
   * ...that reaches layer 0 should have a state equal to its layer. All the others are not connected
   * to layer 0. All those get deleted by this method.
   * (Of course all the connections to them are erased as well)
   */
  void cleanBadStates();
      
  /** 
   * Erase alls connections between segments, that don't satisfy the criteria.
   */
  void cleanBadConnections();
      
  /**Resets all the states of the segmens to 0 by calling the resetState() method of the segment
   * Also sets all segments back to active.
   */
  void resetStates();
      
      
      
  /** Get all the possible tracks in the automaton.
   * 
   * Tracks are built by starting from segments which don't have a parent (and are therefore the begin of a track).
   * For all children they have a new own track is created. The children themselves have children again, so the 
   * tracks split up again.
   * If we have for example a segment with 3 children, which each have 5 children, which each have 7 children,
   * we will get 1*3*5*7=105 tracks.
   * 
   * @return All tracks that are possible with the given segments and their connections. Tracks are returned
   * as a vector of hits. So the output will be a vector of a vector of hits
   * 
   * @param minHits the minimum number of hits that a track needs to have. All possible tracks,
   * that have less won't be considered as tracks and won't be returned.
   * 
   */
  //std::vector < std::vector< IHit* > > getTracks( unsigned minHits = 3 );
  std::vector < std::vector< IHit* > > getTracks( unsigned minHits = 2 ); // YV, 2 mini-vector hits can form a track     
      
  /**Returns all the tracks starting from this segment.
   * It is a recursive method and gets invoked by getTracks.
   */
  //std::vector < std::vector< IHit* > > getTracksOfSegment ( Segment* segment, std::vector< IHit* > hits , unsigned minHits = 3 );
  std::vector < std::vector< IHit* > > getTracksOfSegment ( Segment* segment, std::vector< IHit* > hits , unsigned minHits = 2 );    // YV, 2 mini-vector hits can form a track   
      
  /** 
   * @return All the segments currently saved in the automaton
   */
  //std::vector <const Segment*> getSegments() const;
  std::vector <Segment*> getSegments() const;
      
  unsigned getNumberOfConnections(){ return _nConnections; }
      
 private:
      
  /** Here the segments are stored.
   * The vector corresponds to the layer.
   * The list corresponds to the segments on the layer.
   * _segments[2] is a list with all segments on layer 2.
   * 
   * The segments will be deleted by the Automaton in the destructor
   * 
   */
  std::vector < std::list < Segment* > > _segments;
      
  /** A vector containing all the criteria, that are used in the Automaton
   */
  std::vector < ICriterion* > _criteria;
      
  unsigned _nConnections;
      
      
      
};  
   
#endif
