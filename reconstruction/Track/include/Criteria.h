#ifndef Criteria_h
#define Criteria_h

/****** include all the criteria *******/
//
//
//
//
//

#include <vector>
#include <set>
#include <string>

class Criteria {
      
 public:

  /** @return a vector of strings that represent all types of criteria stored.
   * For example: "2Hit" or "3Hit" or "4Hit"
   */
  static std::set< std::string > getTypes();
      
            
  /** @return a vector of all Criteria of a certain type
   * 
   * @param type the type of Criteria, that is wanted (e.g. "2Hit")
   */
  static std::set< std::string > getCriteriaNames( std::string type );
      
  /** @return the names of all Criteria in a set
   */
  static std::set< std::string > getAllCriteriaNames();
      
  /** A convenience method to get all the criteria in a vector (gives the same result as getAllCriteriaNames, but
   * instead of a set, returns it as a vector)
   * 
   * @return the names of all Criteria in a vector
   */
  static std::vector< std::string > getAllCriteriaNamesVec();

  /** 
   * Creates a Criterion with the name and the min and max values
   * 
   * @return a "new" Criterion (i.e. needs to be deleted later on)
   */
  static ICriterion* createCriterion( std::string critName , float min=0. , float max=0. )throw (UnknownCriterion) ;


  static void getLeftRight( std::string critName, float & left, float & right );
      
   
      
};

#endif


