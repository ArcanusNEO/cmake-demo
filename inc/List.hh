#pragma once
#include <iostream>
template <typename T>
class List {
public:
  static T nullObj;
  class Node {
  public:
    T val;
    Node* p[2];
    Node(const T& _val = T(), Node* prev = nullptr, Node* next = nullptr)
      : val(_val) {
      p[0] = prev, p[1] = next;
    }
    Node(const Node& op) { *this = op; }
    Node& operator = (const Node& op) {
      val = op.val, p[0] = op.p[0], p[1] = op.p[1];
      return *this;
    }
    ~Node() {}
  };
  Node* head;
  size_t siz;
  List() : head(nullptr), siz(0) {}
  List(List&& op) {
    head = op.head;
    op.head = nullptr;
    siz = op.siz;
    op.siz = 0;
  }
  List(const List& op) {
    head = nullptr;
    siz = 0;
    (*this) = op;
  }
  List& operator = (const List& op) {
    clear();
    auto x = op.head;
    for (size_t i = 0; i < op.siz; ++i) {
      pushBack(x->val);
      x = x->p[1];
    }
    return *this;
  }
  List& operator = (List&& op) {
    clear();
    head = op.head;
    op.head = nullptr;
    siz = op.siz;
    op.siz = 0;
    return *this;
  }
  void clear() {
    auto x = head;
    while (siz--) {
      auto y = x->p[1];
      delete x;
      x = y;
    }
    head = nullptr;
    siz = 0;
  }
  ~List() { clear(); }
  Node* insert(Node* pos, const T& _val) {
    if (siz == 0 || pos == nullptr) {
      pos = new Node(_val);
      pos->p[0] = pos->p[1] = pos;
    } else {
      pos = new Node(_val, pos->p[0], pos);
      pos->p[0]->p[1] = pos;
      pos->p[1]->p[0] = pos;
    }
    ++siz;
    return pos;
  }
  void pushFront(const T& _val) { head = insert(head, _val); }
  void pushBack(const T& _val) { head = insert(head, _val)->p[1]; }
  Node* __search(const T& val, Node* pos = nullptr) const {
    if (head == nullptr) return nullptr;
    auto ptr = (pos == nullptr ? head : pos);
    for (size_t i = 0; i < siz; ++i) {
      if (ptr->val == val) break;
      ptr = ptr->p[1];
    }
    return (ptr->val == val ? ptr : nullptr);
  }
  bool exist(const T& val) const { return (__search(val) != nullptr); }
  Node* __remove(Node* pos) {
    if (siz == 0 || pos == nullptr) return nullptr;
    auto prev = pos->p[0], next = pos->p[1];
    delete pos;
    --siz;
    if (siz == 0) pos = nullptr;
    else if (siz == 1) {
      pos = next;
      pos->p[0] = pos->p[1] = pos;
    } else {
      prev->p[1] = next;
      next->p[0] = prev;
      pos = next;
    }
    return pos;
  }
  void popFront() { head = __remove(head); }
  void popBack() {
    if (head == nullptr) return;
    head = __remove(head->p[0]);
  }
  T front() const {
    if (head == nullptr) return nullObj;
    return head->val;
  }
  T back() const {
    if (head == nullptr) return nullObj;
    return head->p[0]->val;
  }
  size_t size() const { return siz; }
  bool empty() const { return (siz == 0); }
  class iterator {
  public:
    Node* ptr;
    int64_t counter;
    ~iterator() {}
    iterator(Node* _ptr = nullptr, int64_t _counter = 0) : ptr(_ptr), counter(_counter) {}
    iterator(const iterator& op) : ptr(op.ptr), counter(op.counter) {}
    iterator& operator = (const iterator& op) {
      ptr = op.ptr;
      counter = op.counter;
      return *this;
    }
    iterator& operator ++() {
      if (ptr != nullptr) ptr = ptr->p[1];
      ++counter;
      return *this;
    }
    iterator& operator --() {
      if (ptr != nullptr) ptr = ptr->p[0];
      --counter;
      return *this;
    }
    iterator operator ++(int _arg) {
      auto ret = *this;
      if (ptr != nullptr) ptr = ptr->p[1];
      ++counter;
      return ret;
    }
    iterator operator --(int _arg) {
      auto ret = *this;
      if (ptr != nullptr) ptr = ptr->p[0];
      --counter;
      return ret;
    }
    T& operator *() { return (ptr == nullptr ? nullObj : ptr->val); }
    T operator *() const { return (ptr == nullptr ? nullObj : ptr->val); }
    bool operator == (const iterator& op) const { return (ptr == op.ptr && counter == op.counter); }
    bool operator < (const iterator& op) const { return (ptr != op.ptr && counter < op.counter); }
    bool operator != (const iterator& op) const { return !(*this == op); }
    bool operator <= (const iterator& op) const { return (*this == op || *this < op); }
    bool operator >= (const iterator& op) const { return !(*this < op); }
    bool operator > (const iterator& op) const { return !(*this <= op); }
  };
  iterator begin() { return iterator(head); }
  iterator end() { return iterator(head, siz); }
  const iterator cbegin() const { return iterator(head); }
  const iterator cend() const { return iterator(head, siz); }
  const iterator search(const T& val) const {
    iterator it;
    for (it = cbegin; it != cend; ++it)
      if (*it == val) break;
    return it;
  }
  iterator search(const T& val) { return const_cast<iterator>(((const List&) (*this)).search(val)); }
  void remove(iterator it) {
    auto pos = it.ptr;
    if (pos == nullptr) return;
    pos = __remove(pos);
    if (it.ptr == head) head = pos;
  }
  void remove(const T& val, iterator pos = iterator()) {
    auto ptr = __search(val, pos.ptr);
    auto t = __remove(ptr);
    if (ptr == head) head = t;
  }
};
template<typename T> T List<T>::nullObj = T();
