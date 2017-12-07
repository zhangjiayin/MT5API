//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Class of memory block                                            |
//+------------------------------------------------------------------+
class CMTMemPack
  {
private:
   //--- constants
   enum
     {
      REALLOC_STEP  =1024                  // buffer reallocation step
     };

private:
   //--- data
   char             *m_buffer;             // data
   UINT              m_buffer_len;         // data length
   UINT              m_buffer_max;         // maximum number of bytes in buffer

public:
   //--- constructor/destructor
                     CMTMemPack();
                    ~CMTMemPack();
   //--- correct the length in block
   void              Clear()         { m_buffer_len=0; }
   void              Shutdown();
   bool              Reallocate(UINT growsize);
   //--- add unformatted data
   bool              Add(const void *buf,UINT len);
   //--- swap array contents
   void              Swap(CMTMemPack &pack);
   //--- buffer access
   char*             Buffer()        { return(m_buffer);     }
   const UINT        Len() const     { return(m_buffer_len); }
   void              Len(UINT val)   { if(val<=m_buffer_max) m_buffer_len=val; }
   UINT              Max() const     { return(m_buffer_max); }
  };
//+------------------------------------------------------------------+
//| Constructor with memory pre-allocation                           |
//+------------------------------------------------------------------+
inline CMTMemPack::CMTMemPack()
   : m_buffer(NULL),
     m_buffer_len(0),
     m_buffer_max(0)
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
inline CMTMemPack::~CMTMemPack()
  {
   Shutdown();
  }
//+------------------------------------------------------------------+
//| Add data to buffer                                               |
//+------------------------------------------------------------------+
inline bool CMTMemPack::Add(const void *buf,UINT len)
  {
//--- check
   if(!buf)
      return(false);
//--- check for exceeding buffer size
   if(m_buffer==NULL || (len+m_buffer_len)>m_buffer_max)
      if(!Reallocate(len+m_buffer_len+REALLOC_STEP))
         return(false);
//--- append data to buffer
   memcpy(&m_buffer[m_buffer_len],buf,len);
   m_buffer_len+=len;
//---
   return(true);
  }
//+------------------------------------------------------------------+
//| Swap buffer contents                                             |
//+------------------------------------------------------------------+
inline void CMTMemPack::Swap(CMTMemPack &pack)
  {
   char *buffer;             // buffer
   UINT  buffer_len;         // data length
   UINT  buffer_max;         // maximum number of bytes in buffer
//--- check
   if(this==&pack)
      return;
//--- swap, remember own buffer
   buffer    =m_buffer;
   buffer_len=m_buffer_len;
   buffer_max=m_buffer_max;
//--- replace buffer with received one
   m_buffer    =pack.m_buffer;
   m_buffer_len=pack.m_buffer_len;
   m_buffer_max=pack.m_buffer_max;
//--- return own buffer
   pack.m_buffer    =buffer;
   pack.m_buffer_len=buffer_len;
   pack.m_buffer_max=buffer_max;
  }
//+------------------------------------------------------------------+
//|  Deallocate memory in MemPack                                    |
//+------------------------------------------------------------------+
inline void CMTMemPack::Shutdown()
  {
   if(m_buffer) { delete[] m_buffer; m_buffer=NULL; }
   m_buffer_max=0;
   m_buffer_len=0;
  }
//+------------------------------------------------------------------+
//| Reallocate data block                                            |
//+------------------------------------------------------------------+
inline bool CMTMemPack::Reallocate(UINT growsize)
  {
   char *newbuf;
//--- check sizes
   if(growsize<=m_buffer_max) return(true);
//--- try to allocate block of greater size
   if((newbuf=new(std::nothrow) char[growsize])==NULL)
      return(false);
//--- copy values from old buffer
   if(m_buffer)
     {
      if(m_buffer_len>0) memcpy(newbuf,m_buffer,m_buffer_len);
      delete[] m_buffer;
     }
   m_buffer    =newbuf;
   m_buffer_max=growsize;
//---
   return(true);
  }
//+------------------------------------------------------------------+
