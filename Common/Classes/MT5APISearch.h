//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Search functions                                                 |
//+------------------------------------------------------------------+
class SMTSearch
  {
public:
   typedef int       (__cdecl *SortFunctionPtr)(const void *, const void *);
public:
   //--- insert
   static char*      Insert(void *base,const void *elem,size_t total,const size_t width,SortFunctionPtr compare);
   //--- quick sort
   template <class T>
   static void       QuickSort(T *base,UINT num,SortFunctionPtr compare);
   //---
   static void*      Search(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare);
   static void*      SearchGreatOrEq(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare);
   static void*      SearchGreater(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare);
   static void*      SearchLessOrEq(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare);
   static void*      SearchLess(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare);
   static void*      SearchLeft(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare);
   static void*      SearchRight(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare);
private:
   template <class T>
   static void       ShortSort (T *lo,T *hi,SortFunctionPtr compare);
   template <class T>
   static void       Swap(T *a,T *b);
  };
//+------------------------------------------------------------------+
//| Returns 0 if record already exist                                |
//| Returns inserted record otherwise                                |
//| Array should contain enough free space for new element           |
//+------------------------------------------------------------------+
inline char* SMTSearch::Insert(void *base,const void *elem,size_t total,const size_t width,SortFunctionPtr compare)
  {
//--- check
   if(base==NULL || elem==NULL || compare==NULL) return(NULL);
//--- first element?
   if(total<1) { memcpy(base,elem,width); return(char*)(base); }
//--- initialize
   register char *lo=(char *)base;
   register char *hi=(char *)base+(total-1)*width,*end=hi;
   register char *mid;
   size_t         half;
   int            result;
//---
   while(total>0)
     {
      half=total/2;
      mid =lo+half*width;
      //--- compare
      if((result=compare(elem,mid))>0) // data[mid]<elem
        {
         lo   =mid+width;
         total=total-half-1;
        }
      else
         if(result<0)                // data[mid]>elem
           {
            total=half;
           }
         else
           {
            // data[mid]==elem
            return(NULL);
           }
     }
//--- insert new
   memmove(lo+width,lo,end-lo+width);
   memcpy(lo,elem,width);
//---
   return(lo);
  }
//+------------------------------------------------------------------+
//| Fast sort                                                        |
//+------------------------------------------------------------------+
template<class T>
inline void SMTSearch::ShortSort (T *lo,T *hi,SortFunctionPtr compare)
  {
   T *p, *maxval;
//--- Note: in assertions below, i and j are alway inside original bound of
//--- array to sort.
//--- While
   while(hi > lo)
     {
      maxval=lo;
      for(p=lo+1; p<=hi; p+=1)
         if (compare(p, maxval) > 0)
         { maxval=p; }
      //---
      Swap(maxval,hi);
      hi-=1;
     }
  }
//+------------------------------------------------------------------+
//| Swap two records                                                 |
//+------------------------------------------------------------------+
template<class T>
inline void SMTSearch::Swap(T *a,T *b)
  {
   T c(*a);
   *a=*b;
   *b=c;
  }
//+------------------------------------------------------------------+
//| Quick sort from CRT                                              |
//+------------------------------------------------------------------+
template<class T>
inline void SMTSearch::QuickSort(T *base,UINT num,SortFunctionPtr compare)
  {
   T *lo, *hi;              /* ends of sub-array currently sorting */
   T *mid;                  /* points to middle of subarray */
   T *loguy, *higuy;        /* traveling pointers for partition step */
   size_t size;             /* size of the sub-array */
   T *lostk[30], *histk[30];
   int stkptr;              /* stack for saving sub-array to be processed */
//---
   if (num < 2) return;
   stkptr=0;                /* initialize stack */
   lo=base;
   hi=base + (num-1);       /* initialize limits */
//---
   recurse:
//---
   size=(hi - lo) + 1;       /* number of el's to sort */
//---
   if (size<=8) ShortSort(lo,hi,compare);
   else
     {
      mid=lo + (size/2);     /* find middle element */
      Swap(mid,lo);          /* swap it to beginning of array */
      //---
      loguy=lo;
      higuy=hi + 1;
      //---
      for(;;)
        {
         //---
         do
           {
            loguy+=1;
           }
         while(loguy<=hi && compare(loguy, lo)<=0);
         //---
         do
           {
            higuy-=1;
           }
         while(higuy > lo && compare(higuy, lo)>=0);
         //---
         if(higuy<loguy) break;
         //---
         Swap(loguy, higuy);
        }
      //---
      Swap(lo, higuy);     /* put partition element in place */
      //---
      if(higuy-1-lo>=hi-loguy)
        {
         if(lo + 1 < higuy)
           {
            lostk[stkptr]=lo;
            histk[stkptr]=higuy - 1;
            ++stkptr;
           }
         if(loguy < hi)
           {
            lo=loguy;
            goto recurse;           /* do small recursion */
           }
        }
      else
        {
         if (loguy < hi)
           {
            lostk[stkptr]=loguy;
            histk[stkptr]=hi;
            ++stkptr;               /* save big recursion for later */
           }
         if(lo + 1 < higuy)
           {
            hi=higuy - 1;
            goto recurse;           /* do small recursion */
           }
        }
     }
//---
   --stkptr;
   if(stkptr>=0)
     {
      lo=lostk[stkptr];
      hi=histk[stkptr];
      goto recurse;           /* pop subarray from stack */
     }
//---
   return;                 /* all subarrays done */
  }
//+------------------------------------------------------------------+
//| Binary search (from CRT)                                         |
//+------------------------------------------------------------------+
inline void* SMTSearch::Search(const void *key,void *base,size_t num,const size_t width,SortFunctionPtr compare)
  {
   char *lo=(char *)base;
   char *hi=(char *)base + (num - 1) * width;
   char *mid;
   size_t half;
   int result;
//--- validation section 
   if(base==NULL || num<1 || width<=0 || compare==NULL) return(NULL);
//---  We allow a NULL key here because it breaks some older code and because we do not dereference
//---  this ourselves so we can't be sure that it's a problem for the comparison function
   while(lo<=hi)
     {
      if((half=num/2)!=0)
        {
         mid=lo + (num & 1 ? half : (half - 1)) * width;
         if((result=(*compare)(key, mid))==0)
            return(mid);
         else
            if (result < 0)
              {
               hi=mid - width;
               num=num & 1 ? half : half-1;
              }
            else
              {
               lo=mid + width;
               num=half;
              }
        }
      else
         if(num)
            return((*compare)(key, lo) ? NULL : lo);
         else
            break;
     }
//---
   return(NULL);
  }
//+------------------------------------------------------------------+
//| Search great or equal key                                        |
//+------------------------------------------------------------------+
inline void* SMTSearch::SearchGreatOrEq(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare)
  {
//--- check
   if(key==NULL || base==NULL || total<1 || compare==NULL) return(NULL);
//--- 
   register char    *lo=(char *)base;
   register char    *end=(char *)base+total*width;
   register char    *mid;
   size_t            half;
//---
   while(total>0)
     {
      half=total/2;
      mid =lo+half*width;
      //--- compare
      if(compare(key,mid)>0) // key>data[mid]
        {
         lo   =mid+width;
         total=total-half-1;
        }
      else total=half;
     }
//--- is exist?
   return(lo==end)?(NULL):(lo);
  }
//+------------------------------------------------------------------+
//| Search great than key                                            |
//+------------------------------------------------------------------+
inline void* SMTSearch::SearchGreater(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare)
  {
//--- check
   if(key==NULL || base==NULL || total<1 || compare==NULL) return(NULL);
//--- 
   register char    *lo=(char *)base;
   register char    *end=(char *)base+total*width;
   register char    *mid;
   size_t            half;
//---
   while(total>0)
     {
      half=total/2;
      mid =lo+half*width;
      //--- compare
      if(compare(key,mid)>=0) // key>=data[mid]
        {
         lo   =mid+width;
         total=total-half-1;
        }
      else total=half;
     }
//--- is exist?
   return(lo==end)?(NULL):(lo);
  }
//+------------------------------------------------------------------+
//| Search less or equal key                                         |
//+------------------------------------------------------------------+
inline void* SMTSearch::SearchLessOrEq(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare)
  {
//--- check
   if(key==NULL || base==NULL || total<1 || compare==NULL) return(NULL);
//--- 
   register char    *lo=(char *)base;
   register char    *beg=(char *)base;
   register char    *mid;
   size_t            half;
//---
   while(total>0)
     {
      half=total/2;
      mid =lo+half*width;
      //--- compare
      if(compare(key,mid)>=0) // key>=data[mid]
        {
         lo   =mid+width;
         total=total-half-1;
        }
      else total=half;
     }
//--- is exist?
   return(lo==beg)?(NULL):(lo-width);
  }
//+------------------------------------------------------------------+
//| Search less than key                                             |
//+------------------------------------------------------------------+
inline void* SMTSearch::SearchLess(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare)
  {
//--- check
   if(key==NULL || base==NULL || total<1 || compare==NULL) return(NULL);
//--- 
   register char    *lo=(char *)base;
   register char    *beg=(char *)base;
   register char    *mid;
   size_t            half;
//---
   while(total>0)
     {
      half=total/2;
      mid =lo+half*width;
      //--- compare
      if(compare(key,mid)>0) // key>data[mid]
        {
         lo   =mid+width;
         total=total-half-1;
        }
      else total=half;
     }
//--- is exist?
   return(lo==beg)?(NULL):(lo-width);
  }
//+------------------------------------------------------------------+
//| Search first equal key                                           |
//+------------------------------------------------------------------+
inline void* SMTSearch::SearchLeft(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare)
  {
//--- check
   if(key==NULL || base==NULL || total<1 || compare==NULL) return(NULL);
//--- search left
   char* start=(char*)SearchLess(key,base,total,width,compare);
//---
   if(start!=NULL)
     {
      //--- go to next
      start+=width;
      //--- check array borders
      if(start>=((char*)base+total*width)) return(NULL);
     }
   else start=(char*)base;
//--- is equal?
   if(!compare(key,start)) return(start);
//--- not found
   return(NULL);
  }
//+------------------------------------------------------------------+
//| Search last equal key                                            |
//+------------------------------------------------------------------+
inline void* SMTSearch::SearchRight(const void *key,void *base,size_t total,const size_t width,SortFunctionPtr compare)
  {
//--- check
   if(key==NULL || base==NULL || total<1 || compare==NULL) return(NULL);
//--- search right
   char* end=(char*)SearchGreater(key,base,total,width,compare);
//---
   if(end!=NULL)
     {
      //--- go to previous
      end-=width;
      //--- check array borders
      if(end<(char*)base) return(NULL);
     }
   else end=(char*)base+(total-1)*width;
//--- is equal?
   if(!compare(key,end)) return(end);
//--- not found
   return(NULL);
  }
//+------------------------------------------------------------------+
