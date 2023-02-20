#ifndef _LITESTL_ALGO_HEAP_H_
#define _LITESTL_ALGO_HEAP_H_

// algorithm for heap
// make_heap, push_heap, pop_heap, sort_heap

#include "iterator.h"

namespace mystl
{

/********************************************************************************/
// push_heap
// insert new element at the end of container, and adjust heap
/********************************************************************************/
// ver1: <, max-heap
template <class RIter, class Distance, class T>
void push_heap_ad(RIter first, Distance holeIdx, Distance topIdx, T val)
{
  // percolate up
  auto parent = (holeIdx - 1) / 2;
  while (holeIdx > topIdx && *(first + parent) < val)
  {
    *(first + holeIdx) = *(first + parent);
    holeIdx = parent;
    parent = (holeIdx - 1) / 2;
  }
  *(first + holeIdx) = value;
}

template <class RIter, class Distance>
void push_heap_aux(RIter first, RIter last, Distance*)
{
  mystl::push_heap_ad(first, last - first - 1, static_cast<Distance>(0),
    *(last - 1));
}

template <class RIter>
void push_heap(RIter first, RIter last)
{
  mystl::push_heap_aux(first, last, distance_type(first));
}

// ver2: comp
template <class RIter, class Distance, class T, class Compare>
void push_heap_ad(RIter first, Distance holeIdx, Distance topIdx, T val,
                 Compare comp)
{
  auto parent = (holeIdx - 1) / 2;
  while (holeIdx > topIdx && comp(*(first + parent), val))
  {
    *(first + holeIdx) = *(first + parent);
    holeIdx = parent;
    parent = (holeIdx - 1) / 2;
  }
  *(first + holeIdx) = value;
}

template <class RIter, class Distance, class Compare>
void push_heap_aux(RIter first, RIter last, Distance*, Compare comp)
{
  mystl::push_heap_ad(first, last - first - 1, static_cast<Distance>(0),
    *(last - 1), comp);
}

template <class RIter, class Compare>
void push_heap(RIter first, RIter last, Compare comp)
{
  mystl::push_heap_aux(first, last, distance_type(first), comp);
}

/********************************************************************************/
// pop_heap
// move element at root to the end of container, and adjust heap
/********************************************************************************/
// ver1: <, max-heap
template <class RIter, class Distance, class T>
void pop_heap_ad(RIter first, Distance holeIdx, Distance len, T val)
{
  // percolate down
  auto topIdx = holeIdx;
  auto rchild = 2 * holeIdx + 2;
  while (rchild < len)
  {
    if (*(first + rchild) < *(first + rchild - 1)) --rchild;
    *(first + holeIdx) = *(first + rchild);
    rchild = 2 * rchild + 2;
  }
  if (rchild == len)
  {
    *(first + holeIdx) = *(first + rchild - 1);
    holeIdx = rchild - 1;
  }
  // percolate up
  mystl::push_heap_ad(first, holeIdx, topIdx, val);
}

template <class RIter, class Distance, class T>
void pop_heap_aux(RIter first, RIter last, RIter result, Distance*, T val)
{
  *result = *first;
  mystl::pop_heap_ad(first, static_cast<Distance>(0), last - first, val);
}

template <class RIter>
void pop_heap(RIter first, RIter last)
{
  mystl::pop_heap_aux(first, last - 1, last - 1, distance_type(first),
    *(last - 1));
}

// ver2: comp
template <class RIter, class Distance, class T, class Compare>
void pop_heap_ad(RIter first, Distance holeIdx, Distance len, T val,
                 Compare comp)
{
  // percolate down
  auto topIdx = holeIdx;
  auto rchild = 2 * holeIdx + 2;
  while (rchild < len)
  {
    if (comp(*(first + rchild), *(first + rchild - 1))) --rchild;
    *(first + holeIdx) = *(first + rchild);
    rchild = 2 * rchild + 2;
  }
  if (rchild == len) // if no right child
  {
    *(first + holeIdx) = *(first + rchild - 1);
    holeIdx = rchild - 1;
  }
  // percolate up
  mystl::push_heap_ad(first, holeIdx, topIdx, val, comp);
}

template <class RIter, class Distance, class T, class Compare>
void pop_heap_aux(RIter first, RIter last, RIter result, Distance*, T val,
                  Compare comp)
{
  *result = *first;
  mystl::pop_heap_ad(first, static_cast<Distance>(0), last - first, val,
    comp);
}

template <class RIter, class Compare>
void pop_heap(RIter first, RIter last, Compare comp)
{
  mystl::pop_heap_aux(first, last - 1, last - 1, distance_type(first),
    *(last - 1), comp);
}

/********************************************************************************/
// sort_heap
// do pop_heap operation until last-first==1
/********************************************************************************/
// ver1: <, max-heap
template <class RIter>
void sort_heap(RIter first, RIter last)
{
  while (last - first > 1)
  {
    mystl::pop_heap(first, last--);
  }
}

// ver2: comp
template <class RIter, class Compare>
void sort_heap(RIter first, RIter last, Compare comp)
{
  while (last - first > 1)
  {
    mystl::pop_heap(first, last--, comp);
  }
}

/********************************************************************************/
// make_heap
// make a heap with all elements in container
/********************************************************************************/
// ver1: <, max-heap
template <class RIter, class Distance>
void make_heap_aux(RIter first, RIter last, Distance*)
{
  if (last - first < 2) return;
  auto len = last - first;
  auto holeIdx = (len - 1) / 2;
  while (true)
  {
    mystl::pop_heap_ad(first, holeIdx, len, *(first + holeIdx));
    if (holeIdx == 0) return;
    --holeIdx;
  }
}

template <class RIter>
void make_heap(RIter first, RIter last)
{
  mystl::make_heap_aux(first, last, distance_type(first));
}

// ver2: comp
template <class RIter, class Distance, class Compare>
void make_heap_aux(RIter first, RIter last, Distance*, Compare comp)
{
  if (last - first < 2) return;
  auto len = last - first;
  auto holeIdx = (len - 1) / 2;
  while (true)
  {
    mystl::pop_heap_ad(first, holeIdx, len, *(first + holeIdx), comp);
    if (holeIdx == 0) return;
    --holeIdx;
  }
}

template <class RIter, class Compare>
void make_heap(RIter first, RIter last, Compare comp)
{
  mystl::make_heap_aux(first, last, distance_type(first), comp);
}

} // namespace mystl

#endif // !_LITESTL_ALGO_HEAP_H_