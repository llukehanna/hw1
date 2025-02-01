#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::push_back(const std::string& val) {
    // If the list is empty, create a new node.
  if (tail_ == NULL) {
    tail_ = new Item();
    head_ = tail_;
    tail_->first = 0;
    tail_->last = 0;
  }
    // If there's room in the tail's array, add the value there.
  if (tail_->last < ARRSIZE) {
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
  } else {
    // No room in current tail; allocate a new node.
    Item* newItem = new Item();
    newItem->first = 0;
    newItem->last = 0;
    newItem->val[newItem->last] = val;
    newItem->last++;
    // Link the new node.
    tail_->next = newItem;
    newItem->prev = tail_;
    tail_ = newItem;
    size_++;
  }
}

void ULListStr::push_front(const std::string& val) {
  // If the list is empty, create a new node.
  if (head_ == NULL) {
    head_ = new Item();
    tail_ = head_;
    // For push_front in an empty node, we place the value at index ARRSIZE-1.
    head_->first = ARRSIZE - 1;
    head_->last = ARRSIZE;
    head_->val[head_->first] = val;
    size_++;
    return;
  }
    // If there is room before the current first element.
  if (head_->first > 0) {
    head_->first--;
    head_->val[head_->first] = val;
    size_++;
  } else {
    // No room in current head; allocate a new node to become the new head.
    Item* newItem = new Item();
    newItem->first = ARRSIZE - 1;
    newItem->last = ARRSIZE;
    newItem->val[newItem->first] = val;
    newItem->next = head_;
    head_->prev = newItem;
    head_ = newItem;
    size_++;
  }
}

void ULListStr::pop_back() {
  if (empty()) {
    throw std::underflow_error("List is empty");
  }
  // Remove the last element from the tail.
  tail_->last--;
  size_--;
  // If the tail node becomes empty, deallocate it.
  if (tail_->first == tail_->last) {
    Item* temp = tail_;
    if (tail_->prev != NULL) {
      tail_ = tail_->prev;
      tail_->next = NULL;
    } else {
    // Only one node existed.
    head_ = NULL;
    tail_ = NULL;
    }
  delete temp;
  }
}

void ULListStr::pop_front() {
  if (empty()) {
    throw std::underflow_error("List is empty");
  }
  // Remove the first element from the head.
  head_->first++;
  size_--;
  // If the head node becomes empty, deallocate it.
  if (head_->first == head_->last) {
    Item* temp = head_;
    if (head_->next != NULL) {
      head_ = head_->next;
      head_->prev = NULL;
    } else {
      // Only one node existed.
      head_ = NULL;
      tail_ = NULL;
    }
    delete temp;
  }
}

std::string const & ULListStr::back() const {
  if (empty()) {
    throw std::underflow_error("List is empty");
  }
  // The back element is the last element in tail_'s array.
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const {
  if (empty()) {
    throw std::underflow_error("List is empty");
  }
  // The front element is the first element in head_'s array.
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
  // If the location is out of bounds, return NULL.
  if (loc >= size_) {
    return NULL;
  }
  size_t count = 0;
  // Traverse the nodes until we find the node containing the loc-th element.
  for (Item* curr = head_; curr != NULL; curr = curr->next) {
    size_t numElements = curr->last - curr->first;
    if (loc < count + numElements) {
      // Return a pointer to the located element.
      return const_cast<std::string*>(&(curr->val[curr->first + (loc - count)]));
    }
    count += numElements;
  }
  return NULL;  // Should not reach here if loc is valid.
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
