//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include <new.h>
#include <stdlib.h>
#include "MT5APISearch.h"
//+------------------------------------------------------------------+
//| Dynamic array base class                                         |
//| For POD data types only!                                         |
//+------------------------------------------------------------------+
class CMTArrayBase
  {
protected:
   UCHAR            *m_data;             // array
   UINT              m_data_total;       // array records total
   UINT              m_data_max;         // array records max
   UINT              m_data_width;       // record size in bytes
   UINT              m_data_step;        // reallocation step

public:
                     CMTArrayBase(const UINT width,const UINT step);
   virtual          ~CMTArrayBase();
   //--- common properties
   UINT              Total(void) const                        { return(m_data_total);      }
   UINT              Width(void) const                        { return(m_data_width);      }
   UINT              Max(void) const                          { return(m_data_max);        }
   UINT              Step(void) const                         { return(m_data_step);       }
   bool              Compare(const CMTArrayBase& array) const;
   //--- global management
   void              Clear(void)                              { m_data_total=0;            }
   bool              Zero(void);
   void              Shutdown(void);
   void              Compact(void);
   bool              Assign(const CMTArrayBase& array);
   void              Swap(CMTArrayBase &arr);
   bool              Reserve(const UINT size);
   bool              Resize(const UINT size);   
   //--- add
   bool              Add(const void *elem)                    { return Add(elem,1);        }
   bool              Add(const void *elem,const UINT total);
   bool              Add(const CMTArrayBase& array);
   bool              AddRange(const CMTArrayBase& array,const UINT from,const UINT to);
   bool              AddEmpty(const UINT total);
   void*             Append(void);
   bool              Insert(const UINT pos,const void *elem)  { return Insert(pos,elem,1); }
   bool              Insert(const UINT pos,const void *elem,const UINT total);
   bool              InsertEmpty(const UINT pos,const UINT total);
   void*             Insert(const void *elem,SMTSearch::SortFunctionPtr sort_function);
   //--- delete
   bool              Delete(const UINT pos);
   bool              Delete(const void *elem);
   bool              DeleteRange(const UINT from,const UINT to);
   bool              Remove(const void *elem,SMTSearch::SortFunctionPtr sort_function);
   //--- modify
   bool              Update(const UINT pos,const void *elem);
   bool              Shift(const UINT pos,const int shift);
   bool              Trim(const UINT size);
   //--- data access
   bool              Next(const UINT pos,void *elem) const;
   void*             Next(const void *elem) const;
   void*             Prev(const void *elem) const;
   const void*       At(const UINT pos) const;
   void*             At(const UINT pos);
   int               Position(const void* ptr) const;
   bool              Range(const UINT from,const UINT to,void* data) const;
   //--- sort & search
   void              Sort(SMTSearch::SortFunctionPtr sort_function);
   void*             Search(const void *key,SMTSearch::SortFunctionPtr sort_function) const;
   void*             SearchGreatOrEq(const void *key,SMTSearch::SortFunctionPtr sort_function) const;
   void*             SearchGreater(const void *key,SMTSearch::SortFunctionPtr sort_function) const;
   void*             SearchLessOrEq(const void *key,SMTSearch::SortFunctionPtr sort_function) const;
   void*             SearchLess(const void *key,SMTSearch::SortFunctionPtr sort_function) const;
   void*             SearchLeft(const void *key,SMTSearch::SortFunctionPtr sort_function) const;
   void*             SearchRight(const void *key,SMTSearch::SortFunctionPtr sort_function) const;

protected:
                     CMTArrayBase(void):m_data(NULL),m_data_total(0),m_data_max(0),m_data_width(0),m_data_step(0){}
   bool              Realloc(const UINT total);
  };
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
inline CMTArrayBase::CMTArrayBase(const UINT width,const UINT step) : m_data(NULL),m_data_total(0),
                                                                  m_data_max(0),m_data_width(width),m_data_step(step)
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
inline CMTArrayBase::~CMTArrayBase(void)
  {
   Shutdown();
  }
//+------------------------------------------------------------------+
//| Zero all elements                                                |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Zero(void)
  {
   if(m_data) ZeroMemory(m_data,m_data_width*m_data_max);
   return(true);
  }
//+------------------------------------------------------------------+
//| Full shutdown with memory free                                   |
//+------------------------------------------------------------------+
inline void CMTArrayBase::Shutdown(void)
  {
//--- clear all
   if(m_data) { delete[] m_data; m_data=NULL; }
//--- zero sizes
   m_data_total=m_data_max=0;
  }
//+------------------------------------------------------------------+
//| Arrays comparison                                                |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Compare(const CMTArrayBase& array) const
  {
//--- check total and with
   if(m_data_width!=array.m_data_width || m_data_total!=array.m_data_total)
      return(false);
//--- check total
   if(Total())
     {
      //--- check data
      if(!m_data || !array.m_data) return(false);
      //--- check record by record
      for(UINT i=0;i<m_data_total;i++)
         if(memcmp(At(i),array.At(i),m_data_width)!=0) return(false);
     }
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Memory check and reallocation to store 'total' records          |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Realloc(const UINT total)
  {
//--- check
   if(total<1 || m_data_step<1)                   return(true);
//--- check size
   if(m_data && (m_data_total+total)<=m_data_max) return(true);
//--- calculate reallocation
   UINT add=((total/m_data_step)+1)*m_data_step;
//--- allocate new buffer
   UCHAR *buffer=new(std::nothrow) UCHAR[(m_data_max+add)*m_data_width];
//--- check
   if(!buffer) return(false);
//--- previous data?
   if(m_data)
     {
      if(m_data_total>0) memcpy(buffer,m_data,m_data_width*m_data_total);
      delete[] m_data;
     }
//--- replace
   m_data     =buffer;
   m_data_max+=add;
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Compact allocated memory                                         |
//+------------------------------------------------------------------+
inline void CMTArrayBase::Compact(void)
  {
   UINT   freespace=m_data_max-m_data_total;
   UCHAR *newdata;
//--- check
   if(!m_data || freespace<=m_data_step) return;
//--- allocate new block
   newdata=new(std::nothrow) UCHAR[(m_data_total+m_data_step)*m_data_width];
//--- check memory
   if(!newdata) return;
//--- copy old data
   memcpy(newdata,m_data,m_data_total*m_data_width);
//--- free old buffer
   delete[] m_data;
//--- replace
   m_data    =newdata;
   m_data_max=m_data_total+m_data_step;
  }
//+------------------------------------------------------------------+
//| Assign from 'array' and                                          |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Assign(const CMTArrayBase& array)
  {
//--- check
   if(this==&array) return(true);
//--- check width
   if(array.m_data_width!=m_data_width) return(false);
//--- clear self
   Clear();
//--- check data
   if(!array.m_data || array.m_data_total<1) return(true);
//--- add
   return(Add(array.m_data,array.m_data_total));
  }
//+------------------------------------------------------------------+
//| Swap arrays content                                              |
//+------------------------------------------------------------------+
inline void CMTArrayBase::Swap(CMTArrayBase &arr)
  {
   UCHAR *data;
   UINT   data_total;
   UINT   data_max;
//--- check
   if(this==&arr) return;
//--- check width
   if(arr.m_data_width!=m_data_width) return;
//--- swap them
   data      =m_data;
   data_total=m_data_total;
   data_max  =m_data_max;
   m_data      =arr.m_data;
   m_data_total=arr.m_data_total;
   m_data_max  =arr.m_data_max;
   arr.m_data      =data;
   arr.m_data_total=data_total;
   arr.m_data_max  =data_max;
  }
//+------------------------------------------------------------------+
//| Reserve free space                                               |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Reserve(const UINT size)
  {
   if(size<=m_data_max) return(true);
   else                 return(Realloc(size-m_data_total));
  }
//+------------------------------------------------------------------+
//| Resize array                                                     |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Resize(const UINT size)
  {
//--- check
   if(!m_data)            return(false);
   if(size==m_data_total) return(true);
//--- resize or realloc
   if(size<m_data_total) m_data_total=size;
   else
      if(size>m_data_total) return(AddEmpty(size-m_data_total));
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Add total records to tail                                       |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Add(const void *elem,const UINT total)
  {
//--- check ptr
   if(!elem)            return(false);
//--- check total
   if(total<1)          return(true);
//--- check and reallocate memory
   if(!Realloc(total))  return(false);
//--- add
   memcpy((char*)m_data+(m_data_width*m_data_total),(const char*)elem,m_data_width*total);
   m_data_total+=total;
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Add array                                                        |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Add(const CMTArrayBase& array)
  {
//--- check
   if(this==&array || !array.m_data || array.m_data_total<1) return(true);
//--- check width
   if(array.m_data_width!=m_data_width) return(false);
//--- add
   return(Add(array.m_data,array.m_data_total));
  }
//+------------------------------------------------------------------+
//| Add records [from,to] from array                                 |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::AddRange(const CMTArrayBase& array,const UINT from,const UINT to)
  {
//--- check
   if(this==&array) return(true);
//--- check width
   if(array.m_data_width!=m_data_width) return(false);
//--- check borders
   if(from>to || to>=array.Total())     return(false);
//--- add
   return(Add((char*)array.m_data+(from*array.m_data_width),(to-from)+1));
  }
//+------------------------------------------------------------------+
//| Add total uninitialized records                                 |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::AddEmpty(const UINT total)
  {
   if(!Realloc(total)) return(false);
   m_data_total+=total;
   return(true);
  }
//+------------------------------------------------------------------+
//| Add new uninitialized record and return pointer to them          |
//+------------------------------------------------------------------+
inline void* CMTArrayBase::Append(void)
  {
//--- check free space
   if(!Realloc(1)) return(NULL);
//--- allocate
   if(m_data_total<m_data_max)
     {
      m_data_total++;
      return((char*)m_data+(m_data_total-1)*m_data_width);
     }
//--- something wrong
   return(NULL);
  }
//+------------------------------------------------------------------+
//| Insert total records into pos position                           |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Insert(const UINT pos,const void *elem,const UINT total)
  {
//--- check
   if(!elem || pos>m_data_total) return(false);
//--- check free space
   if(!Realloc(total)) return(false);
//--- move it if neccessary
   if(pos<m_data_total)
      memmove((char*)m_data+((pos+total)*m_data_width),(char*)m_data+(pos*m_data_width),(m_data_total-pos)*m_data_width);
//--- insert
   memcpy((char*)m_data+(m_data_width*pos),(const char*)elem,m_data_width*total);
   m_data_total+=total;
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Insert total uninitialized records into pos position             |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::InsertEmpty(const UINT pos,const UINT total)
  {
//--- check
   if(pos>m_data_total) return(false);
//--- reallocate
   if(!Realloc(total)) return(false);
//--- move it
   if(pos<m_data_total)
      memmove((char*)m_data+((pos+total)*m_data_width),(char*)m_data+(pos*m_data_width),(m_data_total-pos)*m_data_width);
//--- correct total
   m_data_total+=total;
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Insert new record into sorted array                              |
//| Returns NULL if record already exist or reallocation problem     |
//| Returns inserted record ptr otherwise                            |
//+------------------------------------------------------------------+
inline void* CMTArrayBase::Insert(const void *elem,SMTSearch::SortFunctionPtr sort_function)
  {
   void *result=NULL;
//--- check
   if(!elem || !sort_function) return(result);
//--- reallocate
   if(Realloc(1))
      if((result=SMTSearch::Insert(m_data,elem,m_data_total,m_data_width,sort_function))!=NULL)
         m_data_total++;
//--- result
   return(result);
  }
//+------------------------------------------------------------------+
//| Delete record by position                                        |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Delete(const UINT pos)
  {
//--- check
   if(pos>=m_data_total || !m_data) return(false);
//--- remove
   if((pos+1)<m_data_total)
      memmove((char*)m_data+(pos*m_data_width),(char*)m_data+((pos+1)*m_data_width),((m_data_total-pos)-1)*m_data_width);
   m_data_total--;
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Delete record by pointer                                         |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Delete(const void *elem)
  {
//--- check
   if(!elem || !m_data || elem<m_data || elem>=((char*)m_data+m_data_total*m_data_width)) return(false);
//--- calculate position and delete
   return Delete(((UINT)((const char*)elem-(char*)m_data)/m_data_width));
  }
//+------------------------------------------------------------------+
//| Delete range [from,to]                                           |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::DeleteRange(const UINT from,const UINT to)
  {
//--- check
   if(from>to || to>=m_data_total || !m_data) return(false);
//--- delete
   if(from+1<m_data_total)
      memmove((char*)m_data+(from*m_data_width),
              (char*)m_data+((to+1)*m_data_width),((m_data_total-to)-1)*m_data_width);
//--- correct total
   m_data_total-=((to-from)+1);
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Search and remove record from sorted array                       |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Remove(const void *elem,SMTSearch::SortFunctionPtr sort_function)
  {
   void   *temp;
   UINT64  i;
//--- check
   if(!elem || !sort_function || !m_data || m_data_total<1 || m_data_width<1) return(false);
//--- search it
   if((temp=SMTSearch::Search(elem,m_data,m_data_total,m_data_width,sort_function))==NULL) return(false);
//--- calc position
   i=((UINT64)((char*)temp-(char*)m_data))/m_data_width;
//--- remove it
   if(i<m_data_total-1) memmove(temp,(char *)temp+m_data_width,(size_t)((m_data_total-i)-1)*m_data_width);
   m_data_total--;
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Update record                                                    |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Update(const UINT pos,const void *elem)
  {
//--- check
   if(!elem || pos>=m_data_total || !m_data) return(false);
//--- update
   memcpy((char*)m_data+(pos*m_data_width),(const char*)elem,m_data_width);
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Shift record from pos                                            |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Shift(const UINT pos,const int shift)
  {
   UINT i,newpos=UINT((int)pos+shift);
//--- check
   if(pos>=m_data_total || newpos>=m_data_total || !m_data) return(false);
//--- we need one more record
   if(!Realloc(1)) return(false);
//--- save current
   memcpy((char*)m_data+(m_data_total*m_data_width),(char*)m_data+(pos*m_data_width),m_data_width);
//--- shift record by record
   if(newpos>pos)
      for(i=pos+1;i<=newpos;i++) memcpy((char*)m_data+((i-1)*m_data_width),(char*)m_data+(i*m_data_width),m_data_width);
   else
      for(i=pos;i>newpos;i--)    memcpy((char*)m_data+(i*m_data_width),(char*)m_data+((i-1)*m_data_width),m_data_width);
//--- restore current
   memcpy((char*)m_data+(newpos*m_data_width),(char*)m_data+(m_data_total*m_data_width),m_data_width);
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Remove size first elements                                       |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Trim(const UINT size)
  {
//--- check
   if(!m_data || size>m_data_total) return(false);
//--- trim
   m_data_total-=size;
   memmove((char*)m_data,(char*)m_data+size*m_data_width,m_data_width*m_data_total);
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Next record by position                                          |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Next(const UINT pos,void *elem) const
  {
//--- check
   if(pos>=m_data_total || !elem || !m_data) return(false);
//--- copy and return
   memcpy((char*)elem,(char*)m_data+(pos*m_data_width),m_data_width);
   return(true);
  }
//+------------------------------------------------------------------+
//| Next record by ptr                                               |
//+------------------------------------------------------------------+
inline void* CMTArrayBase::Next(const void *elem) const
  {
//--- check
   if(!elem || !m_data || elem<m_data || elem>=((char*)m_data+(m_data_total-1)*m_data_width)) return(NULL);
//--- return next element
   return((char*)elem+m_data_width);
  }
//+------------------------------------------------------------------+
//| Prev record by ptr                                               |
//+------------------------------------------------------------------+
inline void* CMTArrayBase::Prev(const void *elem) const
  {
//--- check
   if(!elem || !m_data || elem<=m_data || elem>((char*)m_data+(m_data_total-1)*m_data_width)) return(NULL);
//--- return next element
   return((char*)elem-m_data_width);
  }
//+------------------------------------------------------------------+
//| Ptr by position                                                  |
//+------------------------------------------------------------------+
inline const void* CMTArrayBase::At(const UINT pos) const
  {
   return((const char*)m_data+(pos*m_data_width));
  }
//lint –restore
//+------------------------------------------------------------------+
//| Ptr by position                                                  |
//+------------------------------------------------------------------+
inline void* CMTArrayBase::At(const UINT pos)
  {
   return((char*)m_data+(pos*m_data_width));
  }
//+------------------------------------------------------------------+
//| Position by ptr                                                  |
//+------------------------------------------------------------------+
inline int CMTArrayBase::Position(const void* ptr) const
  {
//--- check
   if(!ptr || !m_data || !m_data_width || ptr<m_data || ptr>=(char*)m_data+(m_data_total*m_data_width)) return(-1);
//--- calc offset
   ldiv_t res=ldiv((long)((const char*)ptr-(char*)m_data),(long)m_data_width);
//--- check ptr
   return(res.rem ? -1 : int(res.quot));
  }
//+------------------------------------------------------------------+
//| Receive range                                                    |
//+------------------------------------------------------------------+
inline bool CMTArrayBase::Range(const UINT from,const UINT to,void* data) const
  {
//--- check
   if(from>to || from>=m_data_total || to>=m_data_total || !data || !m_data) return(false);
//--- copy
   memcpy(data,(char*)m_data+(from*m_data_width),((to-from)+1)*m_data_width);
   return(true);
  }
//+------------------------------------------------------------------+
//| Sort array                                                       |
//+------------------------------------------------------------------+
inline void CMTArrayBase::Sort(SMTSearch::SortFunctionPtr sort_function)
  {
   if(m_data && m_data_total>0 && sort_function)
      qsort(m_data,m_data_total,m_data_width,sort_function);
  }
//+------------------------------------------------------------------+
//| Search by key value on sorted array                              |
//+------------------------------------------------------------------+
inline void* CMTArrayBase::Search(const void *key,SMTSearch::SortFunctionPtr sort_function) const
  {
//--- check
   if(key && m_data && m_data_total>0 && sort_function)
      return(SMTSearch::Search(key,m_data,m_data_total,m_data_width,sort_function));
//--- something wrong
   return(NULL);
  }
//+------------------------------------------------------------------+
//| Search great or equal than key value on sorted array             |
//+------------------------------------------------------------------+
inline void* CMTArrayBase::SearchGreatOrEq(const void *key,SMTSearch::SortFunctionPtr sort_function) const
  {
//--- check
   if(key && m_data && m_data_total>0 && sort_function)
      return(SMTSearch::SearchGreatOrEq(key,m_data,m_data_total,m_data_width,sort_function));
//--- something wrong
   return(NULL);
  }
//+------------------------------------------------------------------+
//| Search great than key value on sorted array                      |
//+------------------------------------------------------------------+
inline void* CMTArrayBase::SearchGreater(const void *key,SMTSearch::SortFunctionPtr sort_function) const
  {
//--- check
   if(key && m_data && m_data_total>0 && sort_function)
      return(SMTSearch::SearchGreater(key,m_data,m_data_total,m_data_width,sort_function));
//--- something wrong
   return(NULL);
  }
//+------------------------------------------------------------------+
//| Search less or equal than key value on sorted array              |
//+------------------------------------------------------------------+
inline void* CMTArrayBase::SearchLessOrEq(const void *key,SMTSearch::SortFunctionPtr sort_function) const
  {
//--- check
   if(key && m_data && m_data_total>0 && sort_function)
      return(SMTSearch::SearchLessOrEq(key,m_data,m_data_total,m_data_width,sort_function));
//--- something wrong
   return(NULL);
  }
//+------------------------------------------------------------------+
//| Search less than key value on sorted array                       |
//+------------------------------------------------------------------+
inline void* CMTArrayBase::SearchLess(const void *key,SMTSearch::SortFunctionPtr sort_function) const
  {
//--- check
   if(key && m_data && m_data_total>0 && sort_function)
      return(SMTSearch::SearchLess(key,m_data,m_data_total,m_data_width,sort_function));
//--- something wrong
   return(NULL);
  }
//+------------------------------------------------------------------+
//| Search first element with key equal to key value on sorted array |
//+------------------------------------------------------------------+
inline void* CMTArrayBase::SearchLeft(const void *key,SMTSearch::SortFunctionPtr sort_function) const
  {
//--- check
   if(key && m_data && m_data_total>0 && sort_function)
      return(SMTSearch::SearchLeft(key,m_data,m_data_total,m_data_width,sort_function));
//--- something wrong
   return(NULL);
  }
//+------------------------------------------------------------------+
//| Search last element with key equal to key value on sorted array  |
//+------------------------------------------------------------------+
inline void* CMTArrayBase::SearchRight(const void *key,SMTSearch::SortFunctionPtr sort_function) const
  {
//--- check
   if(key && m_data && m_data_total>0 && sort_function)
      return(SMTSearch::SearchRight(key,m_data,m_data_total,m_data_width,sort_function));
//--- something wrong
   return(NULL);
  }
//+------------------------------------------------------------------+
//| Dynamic array template                                           |
//| For POD data types only!                                         |
//+------------------------------------------------------------------+
template <class T,UINT step=16> class TMTArray : public CMTArrayBase
  {
public:
                     TMTArray() : CMTArrayBase(sizeof(T),step)            {}
   virtual          ~TMTArray(){}
   //--- global management
   void              Swap(TMTArray<T,step> &arr)                          { CMTArrayBase::Swap(arr);                     }
   //--- add
   bool              Add(const T *elem)                                   { return CMTArrayBase::Add(elem);              }
   bool              Add(const T *elem,const UINT total)                  { return CMTArrayBase::Add(elem,total);        }
   bool              Add(const TMTArray<T,step>& arr)                     { return CMTArrayBase::Add(arr);               }
   bool              AddRange(const TMTArray<T,step>& arr,const UINT from,const UINT to)
   { return CMTArrayBase::AddRange(arr,from,to);  }
   T*                Append(void)                                         { return(T*)CMTArrayBase::Append();            }
   bool              Insert(const UINT pos,const T *elem)                 { return CMTArrayBase::Insert(pos,elem);       }
   bool              Insert(const UINT pos,const T *elem,const UINT total){ return CMTArrayBase::Insert(pos,elem,total); }
   T*                Insert(const T *elem,SMTSearch::SortFunctionPtr order) { return(T*)CMTArrayBase::Insert(elem,order);}
   //--- delete
   bool              Delete(const UINT pos)                               { return CMTArrayBase::Delete(pos);            }
   bool              Delete(const T *elem)                                { return CMTArrayBase::Delete(elem);           }
   bool              Remove(const T *elem,SMTSearch::SortFunctionPtr order) { return CMTArrayBase::Remove(elem,order);   }
   //--- modify
   bool              Update(const UINT pos,const T *elem)                 { return CMTArrayBase::Update(pos,elem);       }
   //--- data access
   bool              Next(const UINT pos,T *elem) const                   { return CMTArrayBase::Next(pos,elem);         }
   T*                Next(const T* elem) const                            { return(T*)CMTArrayBase::Next(elem);          }
   T*                Prev(const T* elem)                                  { return(T*)CMTArrayBase::Prev(elem);          }
   T*                First(void)                                          { return(T*)CMTArrayBase::At(0);               }
   int               Position(const T* ptr) const                         { return CMTArrayBase::Position(ptr);          }
   bool              Range(const UINT from,const UINT to,T* data) const   { return CMTArrayBase::Range(from,to,data);    }
   //--- search
   T*                Search(const void *key,SMTSearch::SortFunctionPtr sort_function)          const  { return(T*)CMTArrayBase::Search(key,sort_function);          }
   T*                SearchGreatOrEq(const void *key,SMTSearch::SortFunctionPtr sort_function) const  { return(T*)CMTArrayBase::SearchGreatOrEq(key,sort_function); }
   T*                SearchGreater(const void *key,SMTSearch::SortFunctionPtr sort_function)   const  { return(T*)CMTArrayBase::SearchGreater(key,sort_function);   }
   T*                SearchLessOrEq(const void *key,SMTSearch::SortFunctionPtr sort_function)  const  { return(T*)CMTArrayBase::SearchLessOrEq(key,sort_function);  }
   T*                SearchLess(const void *key,SMTSearch::SortFunctionPtr sort_function)      const  { return(T*)CMTArrayBase::SearchLess(key,sort_function);      }
   T*                SearchLeft(const void *key,SMTSearch::SortFunctionPtr sort_function)      const  { return(T*)CMTArrayBase::SearchLeft(key,sort_function);      }
   T*                SearchRight(const void *key,SMTSearch::SortFunctionPtr sort_function)     const  { return(T*)CMTArrayBase::SearchRight(key,sort_function);     }
   //--- operators
   const T&          operator[](const UINT pos) const                     { return(*(T*)CMTArrayBase::At(pos));          }
   T&                operator[](const UINT pos)                           { return(*(T*)CMTArrayBase::At(pos));          }
   bool              operator==(const TMTArray<T,step>& arr) const        { return(CMTArrayBase::Compare(arr));          }
   bool              operator!=(const TMTArray<T,step>& arr) const        { return(!CMTArrayBase::Compare(arr));         }
   TMTArray<T,step>& operator= (const TMTArray<T,step>& arr)              { if(this!=&arr) Assign(arr); return(*this);   }

private:
                     TMTArray(const TMTArray&) {};
  };
//+------------------------------------------------------------------+
//| Predefined arrays                                                |
//+------------------------------------------------------------------+
typedef TMTArray<UCHAR>   MTByteArray;
typedef TMTArray<wchar_t> MTCharArray;
typedef TMTArray<SHORT>   MTShortArray;
typedef TMTArray<USHORT>  MTUShortArray;
typedef TMTArray<int>     MTIntArray;
typedef TMTArray<UINT>    MTUIntArray;
typedef TMTArray<INT64>   MTInt64Array;
typedef TMTArray<UINT64>  MTUInt64Array;
typedef TMTArray<double>  MTDoubleArray;
//+------------------------------------------------------------------+
