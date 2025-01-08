#include <initializer_list>
#include <iostream>
#include <cassert>

/**********************************************************************************
 * README 
 * ********************************************************************************
 * This starter code is a skeleton of the Set and Node classes.
 * You can modify this code to create your project_5 submission.
 * Any main() function or output will be ignoed by testing software.
 * A testing main() can be found on Learn.
 * 
 * From Project 5 Specification: 2.1 Development Stratigies
 * "First, implement the node class and all of its member functions. This should be
 *  straight-forward from the course notes, as they are the sam member functions as 
 *  for a linked list.
 * 
 *  Second, start with a skeleton, where each member function is defined, but where
 *  the default values of the return type is returned. ..."
 * 
 * The skeleton has been povided (below) for you to modify.
*/

class Set;
class Node;
std::ostream &operator<<( std::ostream &out, Set const &rhs );
 
  /////////////////////////////
 /// Set class declaration ///
/////////////////////////////
class Set {
  public:
    Set( std::initializer_list<int> initial_values );
   ~Set();
 
    // The instructions will describe exactly what to do
    Set( Set const &orig );
    Set( Set      &&orig );
 
    // The instructions will describe exactly what to do
    Set &operator=( Set const &orig );
    Set &operator=( Set      &&orig );
 
    // Size operations
    bool        empty() const;
    std::size_t size()  const;
 
    // Clear all items out of the set
    void clear();
 
    // Find the value item in the set
    //  - Return the address of the node if found,
    //    and nullptr otherwise.
    Node *find( int const &item ) const;
 
    // Insert the item into the set if it
    // is not already in the set.
    //  - Return 1 if the item is new,
    //    and 0 otherwise.
    std::size_t insert( int const &item );
 
    // Insert all the items in the array
    // from array[begin] to array[end - 1]
    // that are not already in the set.
    //  - Return the number of items inserted
    //    into the set.
    std::size_t insert( int         const array[],
                        std::size_t const begin,
                        std::size_t const end );
 
    // Remove the item from the set and
    // return the number of items removed.
    std::size_t erase( int const &item );
 
    // Move any items from 'other', whose values
    // do not appear in 'this', to 'this'
    // Leave any items that already appear
    // in 'this' and 'other' in 'other'. 
    std::size_t merge( Set &other );

 
    // Set operations
    Set &operator|=( Set const &other );
    Set &operator&=( Set const &other );
    Set &operator^=( Set const &other );
    Set &operator-=( Set const &other );
 
    Set operator|( Set const &other ) const;
    Set operator&( Set const &other ) const;
    Set operator^( Set const &other ) const;
    Set operator-( Set const &other ) const;
 
    // Returns 'true' if the 'other' set
    // is a subset of 'this' set; that is,
    // all entries in the 'other' set are
    // also in this set.
    bool operator<=( Set const &other ) const;
    bool operator>=( Set const &other ) const;
    bool operator<( Set const &other ) const;
    bool operator>( Set const &other ) const;
 
    bool operator==( Set const &other ) const;
    bool operator!=( Set const &other ) const;
   
  private:
    Node *p_head_;
 
  friend std::ostream &operator<<( std::ostream &out, Set const &rhs );
};


  ///////////////////////////////
 /// Node class declaration  ///
///////////////////////////////
class Node {
  public:
    Node( int new_value, Node *new_next );
    int   value() const;
    Node *next()  const;
 
  private:
    int   value_;
    Node *p_next_;

  // Allow any member function in the class
  // 'Set' to access or modify the member
  // variables of any instance of this class.
  friend class Set;
};

 
  ///////////////////////////////
 /// Node class Definition   ///
///////////////////////////////

// Node constructor

//IS THIS CORRECT
Node::Node( int new_value, Node *new_next ) : value_{new_value}, p_next_{new_next} {
  
}
 
int Node::value() const {
  return value_;
}

Node *Node::next() const {
  return p_next_;
}


  ///////////////////////////////
 /// Set class definition    ///
///////////////////////////////

// Initializing constructor
Set::Set( std::initializer_list<int> initial_values) : p_head_{nullptr} {
  // std::cout<<"Creating"<<std::endl;
  for(int const &element : initial_values){//why const ref
    insert(element);
  }
}

// Destructor
Set::~Set() {
  // std::cout<<"Calling ~Set() on "<<*this<<std::endl;
  clear();
  // std::cout<<"Done clear, returned to ~Set()"<<std::endl;
  //what is a sentinel for a linked list?
}
 
// Copy constructor
Set::Set( Set const &orig ) : p_head_{nullptr} {
  for(Node* p_current_node{orig.p_head_}; p_current_node != nullptr; p_current_node = p_current_node->next()){
    insert(p_current_node->value());
  }
}

// Move constructor
Set::Set( Set &&orig ) : p_head_{nullptr} {
  std::swap(p_head_, orig.p_head_);
}
 
// Copy assignment
Set &Set::operator=( Set const &orig ) {
  if(this == &orig) return *this;
  clear();
  for(Node* p_current_node{orig.p_head_}; p_current_node != nullptr; p_current_node = p_current_node->p_next_){
    insert(p_current_node->value());
  }
  return *this;
}

// Move assignment
Set &Set::operator=( Set &&orig ) {
  std::swap(p_head_, orig.p_head_);
  return *this;
}
 
// Empty
bool Set::empty() const {
  return (p_head_ == nullptr) ? true : false;
}

// Size
size_t Set::size() const {
  size_t len{0};
  Node* p_current_node = p_head_;
  while(p_current_node != nullptr){
    len++;
    p_current_node = p_current_node->p_next_;
  }
  return len;
}
 
 
// Clear
void Set::clear() {
  // std::cout<<"Calling clear() on "<<*this<<std::endl;
  Node* p_current_node = p_head_;
  while (p_current_node != nullptr) {
    Node* p_next_node = p_current_node->next();
    // std::cout<<p_current_node<<" "<<p_next_node<<std::endl;

    //delete node
    p_current_node->value_ = 0;
    p_current_node->p_next_ = nullptr;
    delete p_current_node; //can i do this?

    p_current_node = p_next_node;

    // p_next_node = nullptr; // set to nullptr just in case this is that last loop iteration. Is this peferred?
  }
  
  p_head_ = nullptr;
  // std::cout<<"Done clear"<<std::endl;
  return;
}
 
// Find
Node *Set::find( int const &item ) const {
  // std::cout<<"In find"<<std::endl;
  Node* p_current_node = p_head_; //create a pointer to the current node
  // std::cout<<"In find: created current node: "<<p_current_node<<std::endl;
  while((p_current_node != nullptr) && (p_current_node->value_ != item)) { //Note: the comparison to nullptr needs to come first because we cannot dereference nullptr
    // std::cout<<"finding..."<<std::endl;
    p_current_node = p_current_node->p_next_;
  } //while the value at a node isn't == item, keep going
  // std::cout<<"In find: about to return"<<std::endl;
  return p_current_node; //return the pointer to the current node. If it is the last node, this will be nullptr and the value was not found
}
 
// Insert the item into the set

//the instructions say that the value returned is the number of items inserted into the set. Does that mean the length?
std::size_t Set::insert( int const &item ) {
  // std::cout<<"In insert"<<std::endl;
  //check if item is already in the set
  if(find(item) != nullptr) return 0; //is it best practice to add an else after this?
  p_head_ = new Node{item, p_head_}; //create a new node which points to the next node and has value of item and then update the head
  return 1;
}
 
// Insert all the items in the array
std::size_t Set::insert( int         const array[],
                         std::size_t const begin,
                         std::size_t const end ) {

  std::size_t n_inserted_vals{0};
  for(std::size_t index{begin}; index < end; index++){
    n_inserted_vals += insert(array[index]);
  }    
  return n_inserted_vals;
}

 
// Remove the item from the set and
// return the number of items removed.
std::size_t Set::erase( int const &item ) {
  Node* p_item = find(item);
  if(p_item == nullptr) return 0; //if the item is not in the set, then return 0

  if(p_item == p_head_){
    //the first item is the one we want to delete
    //point p_head to the entry after the one we are deleting
    p_head_ = p_item->next();

    //delete the item
    p_item->value_ = 0;
    p_item->p_next_ = nullptr;
    delete p_item;
    p_item = nullptr;
    return 1;
  }
  
  //we do not have to check if p_prev_node is nullptr because the item is garanteed to be in the list
  Node* p_prev_node{p_head_};
  for(p_prev_node; p_prev_node->next() != p_item; p_prev_node = p_prev_node->next());
  p_prev_node->p_next_ = p_item->next(); //point the previous item to the item after the deleted node
  
  //now we delete the item
  p_item->value_ = 0;
  p_item->p_next_ = nullptr;
  delete p_item; 
  p_item = nullptr;
  return 1;
}
 
// Move any items from 'other', whose values
// do not appear in 'this', to 'this'.
// Leave any items that already appear
// in both sets, in both sets. 
std::size_t Set::merge( Set &other ) {

  //first, we loop through the other set, one node at a time
  std::size_t n_merged{0};
  Node* p_prev{nullptr};

  for(Node* p_current{other.p_head_}; p_current != nullptr; p_prev = p_current, p_current = p_current->next()){
    //now, we check if that element is already in our set

    //if it is not in the set, we move it
    if(find(p_current->value()) == nullptr){

      Node* p_old_next = p_current->next(); //we first store the next node in the other linked list

      //We make the node point to the first node in set1 and then make the head point to this node
      p_current->p_next_ = p_head_;
      p_head_ = p_current;

      //next, we need to make the prev node in other point to the next one
      //we will assign p_current to the node before the node we deleted
      if(p_prev == nullptr){
        //if the previous pointer is null ptr, we just removed the first entry. 
        //this means we point the head of the other set to the old next
        other.p_head_ = p_old_next;
        //and set the current node to the head of the other list
        p_current = other.p_head_;
      }
      else{
        //if we are not at the start of the list
        //we fix the linked list
        p_prev->p_next_ = p_old_next;
        //and update the current node
        p_current = p_prev;
      }

      n_merged++;
    }
    //otherwise, we just don't do anything
  }
  // std::cout<<"About to return"<<std::endl;
  return n_merged;
}

  //////////////////////
 /// Set operations ///
//////////////////////
Set &Set::operator|=( Set const &other ) {
  for(Node* p_current{other.p_head_}; p_current != nullptr; p_current = p_current->next()){
    insert(p_current->value());
  }
  return *this;
}
 
Set &Set::operator&=( Set const &other ) {
  // std::cout<<"In &="<<std::endl;
  //loop through first set
  // if(p_head_ == nullptr) std::cout<<"AHHHHHHHH NULLPTR"<<std::endl;
  // std::cout<<p_head_<<std::endl;

  for(Node* p_current{p_head_}; p_current != nullptr; ){
    // if(p_current == nullptr) std::cout<<"AHHHHHHHH NULLPTR"<<std::endl;
    //if the value is not in the other set, delete it from the first set
    // std::cout<<"IN LOOP "<<p_current->value();
    if(other.find(p_current->value()) == nullptr){
      Node* p_next = p_current->next();
      // std::cout<<"  Erase: "<<p_current->value();
      erase(p_current->value());
      p_current = p_next;
    }else{
      p_current = p_current->next();
    }
    //otherwise do nothing
  }
  // std::cout<<*this<<std::endl;
  return *this;
}

// Set &Set::operator&=( Set const &other)
// {}

Set &Set::operator^=( Set const &other ) {
  // std::cout<<"in operator^="<<std::endl;
  for(Node* p_current{other.p_head_}; p_current != nullptr; ){
    //if the value is found in the other set, delete it from the first set
    if(find(p_current->value()) != nullptr){
      Node* p_next = p_current->next();
      erase(p_current->value());
      p_current = p_next;
    }
    else if(find(p_current->value()) == nullptr){
      insert(p_current->value());
      p_current = p_current->next();
    }
    
  }
  return *this;
}
 
Set &Set::operator-=( Set const &other ) {
  // std::cout<<"in operator-="<<std::endl;
  for(Node* p_current{p_head_}; p_current != nullptr;){
    //if the value is found in the other set, delete it from the first set
    if(other.find(p_current->value()) != nullptr){
      Node* p_next = p_current->next();
      erase(p_current->value());
      p_current = p_next;
    }
    else{
      p_current = p_current->next();
    }
    //otherwise do nothing
  }
  return *this;
}
 
Set Set::operator|( Set const &other ) const {

  Set result{*this};
  result |= other;
  return result;
}
 
Set Set::operator&( Set const &other ) const {
  Set result{*this};
  result &= other;
  return result;
}
 
Set Set::operator^( Set const &other ) const {
  Set result{*this};
  result ^= other;
  return result;
}
 
Set Set::operator-( Set const &other ) const {
  Set result{*this};
  result -= other;
  return result;
}
 
// Returns 'true' if the 'other' set
// is a subset of 'this' set; that is,
// all entries in the 'other' set are
// also in this set.
bool Set::operator>=( Set const &other ) const {
  for(Node* p_current{other.p_head_}; p_current != nullptr; p_current = p_current->next()){
    if(find(p_current->value()) == nullptr) return false;
  }
  return true;
}
 
bool Set::operator<=( Set const &other ) const {
  return other >= *this;
}
 
bool Set::operator>( Set const &other ) const {
  if(size() == other.size()) return 0;
  return *this >= other;
}
 
bool Set::operator<( Set const &other ) const {
  return other > *this;
}
 
bool Set::operator==( Set const &other ) const {
  return ((*this >= other) && (*this <= other));
}
 
bool Set::operator!=( Set const &other ) const {
  return !(*this == other);
}


  ////////////////////////////////////////////
 /// Supplied Code for print Set objects  ///
////////////////////////////////////////////
/// @brief Overloads the << operator allowing the print of Set objects
/// @param out The ostream to print to (e.g. std::cout <<)
/// @param rhs The Set to print (e.g. << set_A)
/// @note You do not need to edit or alter this code
std::ostream &operator<<( std::ostream &out, Set const &rhs ) {
  out << "{";
  if ( !rhs.empty() ) {
    out << rhs.p_head_->value();   
    for ( Node *ptr{ rhs.p_head_->next() }; ptr != nullptr; ptr = ptr->next() ) {
      out << ", " << ptr->value();
    }
  }
  out << "}";
 
  return out;
}
//debug
// std::ostream &operator<<( std::ostream &out, Set const &rhs ) {
//   out << "{ head: ("<<&rhs.p_head_<<") ["<<rhs.p_head_<<"] --> ";
//   if ( !rhs.empty() ) {
//     out << rhs.p_head_->value()<<" ("<<rhs.p_head_<<")  ["<<rhs.p_head_->next()<<"]";   
//     for ( Node *ptr{ rhs.p_head_->next() }; ptr != nullptr; ptr = ptr->next() ) {
//       out << " --> " << ptr->value()<<" ("<<ptr<<") ["<<ptr->next()<<"]";
//     }
//   }
//   out << "}";
 
//   return out;
// }

// int main(){
//   Set my_data_1{ 1, 3, 5, 2, 4, 8, 5, 3, 1 };
//   // This should print '6'
//   std::cout << my_data_1.size() << std::endl;
//   // This should print '0' ('false')
//   std::cout << my_data_1.empty() << std::endl;
//   assert( my_data_1.find( 0 ) == nullptr );
//   assert( my_data_1.find( 1 )->value() == 1 );
//   assert( my_data_1.find( 5 )->value() == 5 );
//   assert( my_data_1.find( 6 ) == nullptr );
//   assert( my_data_1.find( 8 )->value() );

// }