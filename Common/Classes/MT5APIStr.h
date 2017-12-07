//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include <new.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <winnls.h>
//+------------------------------------------------------------------+
//| String base class                                                |
//+------------------------------------------------------------------+
class CMTStr
  {
protected:
   wchar_t          *m_str;                 // string body
   UINT              m_str_len;             // string length
   const UINT        m_str_max;             // string buffer max size

public:
                     CMTStr(wchar_t *buf,const UINT size):m_str(buf),m_str_len(0),m_str_max(size) { if(m_str) m_str[0]=0; }
   virtual          ~CMTStr()                   { m_str=NULL; m_str_len=0;                   }
   //--- base functionality
   void              Clear()                    { m_str_len=0; if(m_str) m_str[0]=0;         }
   bool              Empty() const              { return(m_str_len<1 || m_str==NULL || m_str[0]==0); }
   UINT              Len()   const              { return(m_str_len);                         }
   static UINT       Len(LPCWSTR str)           { return(str ? (UINT)wcslen(str):0);         }
   UINT              Max()   const              { return(m_str_max);                         }
   const wchar_t*    Str()   const              { return(m_str);                             }
   wchar_t*          Buffer()                   { return(m_str);                             }
   void              Refresh()                  { m_str_len=(m_str ? (UINT)wcsnlen(m_str,m_str_max):0);  }
   const wchar_t     operator[](UINT ind) const { return((ind<m_str_len && m_str) ? m_str[ind] : L'\0'); }
   bool              operator!() const          { return(m_str_len==0);                                  }
   CMTStr&           operator= (const CMTStr& src) { if(this!=&src) Assign(src); return(*this);          }
   //--- assign
   void              Assign(const CMTStr &from);
   void              Assign(LPCWSTR from);
   void              Assign(LPCWSTR from,const UINT from_len);
   void              Assign(LPCSTR from);
   void              Assign(LPCSTR from,const UINT from_len);
   //--- operations
   int               Format(LPCWSTR fmt,...);
   void              ToLower();
   void              ToUpper();
   void              Trim(UINT len);
   void              TrimSpaces();
   static void       TrimSpaces(LPWSTR str);
   void              ReplaceChar(wchar_t findchar,wchar_t repchar);
   void              Replace(wchar_t *findstr,const wchar_t *repstr);
   void              Delete(UINT pos,UINT len);
   template <UINT dstsize>
   static void       Delete(wchar_t (&dst)[dstsize],UINT pos,UINT len) { Delete(dst,dstsize,pos,len); }
   static void       Delete(LPWSTR dst,UINT dstsize,UINT pos,UINT len);
   static void       ToLower(LPWSTR str,UINT size);
   static void       ToUpper(LPWSTR str,UINT size);
   template <UINT size>
   static void       ToLower(wchar_t (&str)[size]) { ToLower(str,size); }
   template <UINT size>
   static void       ToUpper(wchar_t (&str)[size]) { ToUpper(str,size); }
   template <UINT strsize>
   static int        FormatStr(wchar_t (&str)[strsize],LPCWSTR fmt,...);
   static int        FormatStr(LPWSTR str,UINT size,LPCWSTR fmt,...);
   template <UINT strsize>
   static void       Terminate(wchar_t (&str)[strsize]) { str[strsize-1]=L'\0'; }
   //--- append
   void              Append(LPCWSTR appstring);
   void              Append(const CMTStr &appstring);
   void              Append(wchar_t appchar);
   template <UINT dstsize>
   static void       Append(wchar_t (&dst)[dstsize],LPCWSTR src) { Append(dst,dstsize,src); }
   static void       Append(LPWSTR dst,UINT dstsize,LPCWSTR src);
   //--- insert
   void              Insert(UINT pos,LPCWSTR insstring);
   void              Insert(UINT pos,const CMTStr &insstring);
   void              Insert(UINT pos,wchar_t inschar);
   //--- copy
   void              Copy(LPWSTR string,UINT maxlen) const;
   void              Copy(LPSTR string,UINT maxlen) const;
   template <UINT dstsize>
   static void       Copy(wchar_t (&dst)[dstsize],LPCWSTR src)               { Copy(dst,dstsize,src);          }
   template <UINT dstsize>
   static void       Copy(wchar_t (&dst)[dstsize],LPCWSTR src,UINT srccount) { Copy(dst,dstsize,src,srccount); }
   static void       Copy(LPWSTR dst,UINT dstsize,LPCWSTR src);
   static void       Copy(LPWSTR dst,UINT dstsize,LPCWSTR src,UINT srccount);
   template <UINT dstsize>
   static void       Copy(char (&dst)[dstsize],LPCWSTR src)    { Copy(dst,dstsize,src); }
   static void       Copy(LPSTR dst,UINT dstsize,LPCWSTR src);
   static void       Copy(LPWSTR dst,UINT dstsize,LPCSTR src);
   static void       CopyCodePage(LPWSTR dst,UINT dstsize,LPCSTR src,UINT codepage);
   //--- compare
   int               Compare(LPCWSTR str) const;
   int               Compare(LPCWSTR str,UINT count) const;
   int               Compare(const CMTStr& str) const;
   static int        Compare(LPCWSTR str1,LPCWSTR str2);
   static int        Compare(LPCWSTR str1,LPCWSTR str2,UINT count);
   //--- compare no case
   int               CompareNoCase(LPCWSTR str) const;
   int               CompareNoCase(LPCWSTR str,UINT count) const;
   int               CompareNoCase(const CMTStr& str) const;
   static int        CompareNoCase(LPCWSTR str1,LPCWSTR str2);
   static int        CompareNoCase(LPCWSTR str1,LPCWSTR str2,UINT count);
   //--- check groups mask
   static bool       CheckGroupMask(LPCWSTR groupsmask,LPCWSTR group);
   //--- find symbol & substring
   int               Find(LPCWSTR substring,UINT startpos) const;
   int               Find(LPCWSTR substring) const;
   int               FindNoCase(LPCWSTR substring,UINT startpos) const;
   int               FindNoCase(LPCWSTR substring) const { return FindNoCase(substring,(UINT)0); }
   int               FindR(LPCWSTR substring) const;
   int               FindChar(const wchar_t character) const;
   int               FindRChar(const wchar_t character) const;
   static int        Find(LPCWSTR str,LPCWSTR substr);
   static int        FindNoCase(LPCWSTR str,LPCWSTR substr);
   static int        FindR(LPCWSTR str,LPCWSTR substr);
   static int        FindChar(LPCWSTR str,wchar_t character);
   static int        FindRChar(LPCWSTR str,wchar_t character);
   //--- error description method
   LPCWSTR           ErrorMsg(const DWORD error);

protected:
                     CMTStr();
                     CMTStr(const CMTStr &from);
   CMTStr(LPWSTR buf,const UINT size,LPCWSTR from):m_str(buf),m_str_len(0),m_str_max(size)
     {
      if(m_str) m_str[0]=0;
      Assign(from);
     }
private:
   static bool        CheckGroupTemplate(LPWSTR expr,LPCWSTR group);
  };
//+------------------------------------------------------------------+
//| Stack string template                                            |
//+------------------------------------------------------------------+
template <UINT buflen> class TMTStrStatic : public CMTStr
  {
   wchar_t           m_buffer[buflen];
public:
                     TMTStrStatic()                       : CMTStr(m_buffer,buflen)      {}
                     TMTStrStatic(LPCWSTR from)           : CMTStr(m_buffer,buflen,from) {}
                     TMTStrStatic(const TMTStrStatic& from) : CMTStr(m_buffer,buflen) { Assign(from); }
                     TMTStrStatic(const CMTStr&       from) : CMTStr(m_buffer,buflen) { Assign(from); }
  };
//+------------------------------------------------------------------+
//| Stack strings types                                              |
//+------------------------------------------------------------------+
typedef TMTStrStatic<16>   CMTStr16;
typedef TMTStrStatic<32>   CMTStr32;
typedef TMTStrStatic<64>   CMTStr64;
typedef TMTStrStatic<128>  CMTStr128;
typedef TMTStrStatic<256>  CMTStr256;
typedef TMTStrStatic<260>  CMTStrPath;
typedef TMTStrStatic<512>  CMTStr512;
typedef TMTStrStatic<1024> CMTStr1024;
typedef TMTStrStatic<2048> CMTStr2048;
typedef TMTStrStatic<4096> CMTStr4096;
//+------------------------------------------------------------------+
//| Assign from CMTStr                                               |
//+------------------------------------------------------------------+
inline void CMTStr::Assign(const CMTStr &from)
  {
//--- check
   if(m_str)
     {
      UINT newlen=from.Len();
      //--- calc new length
      if(newlen>=m_str_max) newlen=m_str_max-1;
      memcpy(m_str,from.Str(),newlen*sizeof(wchar_t));
      m_str_len=newlen;
      //--- terminate
      m_str[m_str_len]=0;
     }
//---
  }
//+------------------------------------------------------------------+
//| Assign from ptr                                                  |
//+------------------------------------------------------------------+
inline void CMTStr::Assign(LPCWSTR from)
  {
//--- check
   if(m_str)
     {
      //--- check empty string
      if(!from) m_str_len=0;
      else
        {
         UINT newlen=(UINT)wcsnlen(from,m_str_max);
         //--- calculate new length and copy
         if(newlen>=m_str_max) newlen=m_str_max-1;
         memcpy(m_str,from,newlen*sizeof(wchar_t));
         m_str_len=newlen;
        }
      //--- terminate string
      m_str[m_str_len]=0;
     }
  }
//+------------------------------------------------------------------+
//| Assign from ptr with len                                         |
//+------------------------------------------------------------------+
inline void CMTStr::Assign(LPCWSTR from,const UINT from_len)
  {
//--- check
   if(m_str)
     {
      //--- check empty string
      if(!from) m_str_len=0;
      else
        {
         UINT newlen=(UINT)wcsnlen(from,(from_len<m_str_max)?(from_len):(m_str_max));
         //--- calculate new length and copy
         if(newlen>=m_str_max) newlen=m_str_max-1;
         memcpy(m_str,from,newlen*sizeof(wchar_t));
         m_str_len=newlen;
        }
      //--- terminate string
      m_str[m_str_len]=0;
     }
  }
//+------------------------------------------------------------------+
//| Assign from one-byte string                                      |
//+------------------------------------------------------------------+
inline void CMTStr::Assign(LPCSTR from)
  {
//--- check
   if(m_str)
     {
      //--- check empty string
      if(!from) m_str[0]=0;
      else
        {
         //--- copy string
         int len=::MultiByteToWideChar(CP_ACP,0,from,-1,m_str,int(m_str_max-1));
         //--- check result
         if(len==0 && GetLastError()==ERROR_INSUFFICIENT_BUFFER) m_str[m_str_max-1]=0;
         else
           {
            //--- len must be greater or equal than 0
            len=(0>len)?(0):(len);
            //--- limit len
            len=(len<((int)m_str_max-1))?(len):((int)m_str_max-1);
            //--- terminate string
            m_str[len]=0;
           }
        }
      //--- refresh
      Refresh();
     }
  }
//+------------------------------------------------------------------+
//| Assign from one-byte string with length                          |
//+------------------------------------------------------------------+
inline void CMTStr::Assign(LPCSTR from,const UINT from_len)
  {
//--- check
   if(m_str)
     {
      //--- check empty string
      if(!from) m_str[0]=0;
      else
        {
         //--- copy string
         int len=::MultiByteToWideChar(CP_ACP,0,from,int(from_len),m_str,int(m_str_max-1));
         //--- check result
         if(len==0 && GetLastError()==ERROR_INSUFFICIENT_BUFFER) m_str[m_str_max-1]=0;
         else
           {
            //--- len must be greater or equal than 0
            len=(0>len)?(0):(len);
            //--- limit len
            len=(len<((int)m_str_max-1))?(len):((int)m_str_max-1);
            //--- terminate string
            m_str[len]=0;
           }
        }
      //--- refresh
      Refresh();
     }
  }
//+------------------------------------------------------------------+
//| Copy from ptr with len                                           |
//+------------------------------------------------------------------+
inline void CMTStr::Copy(LPWSTR string,UINT maxlen) const
  {
   if(string && maxlen>0 && m_str) wcsncpy_s(string,maxlen,m_str,_TRUNCATE);
  }
//+------------------------------------------------------------------+
//| Copy from one-byte string with len                               |
//+------------------------------------------------------------------+
inline void CMTStr::Copy(LPSTR string,UINT maxlen) const
  {
   if(string && maxlen>0 && m_str)
      ::WideCharToMultiByte(CP_ACP,0,m_str,-1,string,int(maxlen),NULL,NULL);
  }
//+------------------------------------------------------------------+
//| Static copy from string with len                                 |
//+------------------------------------------------------------------+
inline void CMTStr::Copy(LPWSTR dst,UINT dstsize,LPCWSTR src)
  {
   if(dst && src && dstsize>0)
     {
      //--- copy string
      wcsncpy_s(dst,dstsize,src,_TRUNCATE);
      //--- remove trash symbols from CRT in Debug
      #ifdef _DEBUG
      for(UINT pos=Len(dst)+1;pos<dstsize;pos++) dst[pos]=(wchar_t)0;
      #endif
     }
  }
//+------------------------------------------------------------------+
//| Static copy from string with len                                 |
//+------------------------------------------------------------------+
inline void CMTStr::Copy(LPWSTR dst,UINT dstsize,LPCWSTR src,UINT srccount)
  {
   if(dst && src && dstsize>0 && srccount>0)
     {
      //--- copy string
      wcsncpy_s(dst,dstsize,src,dstsize>srccount ? srccount:_TRUNCATE);
      //--- remove trash symbols from CRT in Debug
      #ifdef _DEBUG
      for(UINT pos=Len(dst)+1;pos<dstsize;pos++) dst[pos]=(wchar_t)0;
      #endif
     }
  }
//+------------------------------------------------------------------+
//| Copy from one-byte to unicode string                             |
//+------------------------------------------------------------------+
inline void CMTStr::Copy(LPSTR dst,UINT dstsize,LPCWSTR src)
  {
   if(dst && src && dstsize>0)
      ::WideCharToMultiByte(CP_ACP,0,src,-1,dst,int(dstsize),NULL,NULL);
  }
//+------------------------------------------------------------------+
//| Copy from unicode to one-byte string                             |
//+------------------------------------------------------------------+
inline void CMTStr::Copy(LPWSTR dst,UINT dstsize,LPCSTR src)
  {
   if(dst && src)
      ::MultiByteToWideChar(CP_ACP,0,src,-1,dst,int(dstsize));
  }
//+------------------------------------------------------------------+
//| Copy from unicode to one-byte string with codepage               |
//+------------------------------------------------------------------+
inline void CMTStr::CopyCodePage(LPWSTR dst,UINT dstsize,LPCSTR src,UINT codepage)
  {
   if(dst && src)
      ::MultiByteToWideChar(codepage,0,src,-1,dst,int(dstsize));
  }
//+------------------------------------------------------------------+
//| String format                                                    |
//+------------------------------------------------------------------+
inline int CMTStr::Format(LPCWSTR fmt,...)
  {
   int len=-1;
//---
   if(fmt && m_str)
     {
      va_list marker;
      //--- format text
      va_start(marker,fmt);
      len=_vsnwprintf_s(m_str,m_str_max,_TRUNCATE,fmt,marker);
      va_end(marker);
      //--- check result
      if(len>=0) m_str_len=UINT(len);
      else       m_str_len=(UINT)wcsnlen(m_str,m_str_max);
     }
//---
   return(len);
  }
//+------------------------------------------------------------------+
//| Convert to lower case                                            |
//+------------------------------------------------------------------+
inline void CMTStr::ToLower()
  {
   if(m_str) _wcslwr_s(m_str,m_str_max);
  }
//+------------------------------------------------------------------+
//| Convert to upper case                                            |
//+------------------------------------------------------------------+
inline void CMTStr::ToUpper()
  {
   if(m_str) _wcsupr_s(m_str,m_str_max);
  }
//+------------------------------------------------------------------+
//| Trim symbols from right                                          |
//+------------------------------------------------------------------+
inline void CMTStr::Trim(UINT len)
  {
   if(m_str && len<m_str_len)
     {
      m_str_len=len;
      m_str[m_str_len]=0;
     }
  }
//+------------------------------------------------------------------+
//| Trim spaces                                                      |
//+------------------------------------------------------------------+
inline void CMTStr::TrimSpaces()
  {
   UINT pos;
//--- check
   if(m_str_len==0 || !m_str) return;
//--- remove lead spaces
   for(pos=0;m_str[pos]==L' ';) pos++;
   if(pos>0)
     {
      memmove(&m_str[0],&m_str[pos],(m_str_len-pos+1)*sizeof(m_str[0]));
      m_str_len-=pos;
     }
//--- remove last spaces
   for(pos=m_str_len;pos>0;pos--)
     {
      if(m_str[pos-1]==L' ') m_str[pos-1]=L'\0';
      else break;
     }
//--- refresh length
   m_str_len=pos;
  }
//+------------------------------------------------------------------+
//| Trim spaces                                                      |
//+------------------------------------------------------------------+
inline void CMTStr::TrimSpaces(LPWSTR str)
  {
   size_t len,pos;
//--- check
   if(!str || (len=wcslen(str))==0) return;
//--- remove lead spaces
   for(pos=0;str[pos]==L' ';) pos++;
   if(pos>0)
     {
      memmove(&str[0],&str[pos],(len-pos+1)*sizeof(str[0]));
      len-=pos;
     }
//--- remove last spaces
   for(pos=len;pos>0;pos--)
      if(str[pos-1]==L' ') str[pos-1]=L'\0';
      else break;
  }
//+------------------------------------------------------------------+
//| Replace symbol                                                   |
//+------------------------------------------------------------------+
inline void CMTStr::ReplaceChar(wchar_t findchar,wchar_t repchar)
  {
//--- check
   if(m_str_len==0 || !m_str) return;
//--- replace
   for(UINT pos=0;pos<m_str_len;pos++)
      if(m_str[pos]==findchar) m_str[pos]=repchar;
  }
//+------------------------------------------------------------------+
//| Replace substring                                                |
//+------------------------------------------------------------------+
inline void CMTStr::Replace(wchar_t *findstr,const wchar_t *repstr)
  {
//--- check
   if(findstr && repstr && m_str)
     {
      wchar_t *from=m_str;
      wchar_t *cp;
      size_t   newsize=0,findstr_len=wcslen(findstr);
      wchar_t *newstr =NULL;
      //--- search
      while((cp=wcsstr(from,findstr))!=NULL)
        {
         //--- buffer allocated?
         if(!newstr)
           {
            newsize=m_str_max;
            newstr =new(std::nothrow) wchar_t[newsize];
            //--- fail
            if(newstr==NULL) break;
           }
         *cp=0;
         m_str_len=_snwprintf_s(newstr,newsize,_TRUNCATE,L"%s%s%s",m_str,repstr,cp+findstr_len);
         //--- copy
         if(m_str_len>=m_str_max) m_str_len=m_str_max-1;
         memcpy(m_str,newstr,m_str_len*sizeof(wchar_t));
         m_str[m_str_len]=0;
         //--- next position
         from=m_str+(cp-m_str)+wcslen(repstr);
        }
      //--- free buffer
      if(newstr)
        {
         delete[] newstr;
         newstr=NULL;
        }
     }
  }
//+------------------------------------------------------------------+
//| Delete len symbols from pos position                             |
//+------------------------------------------------------------------+
inline void CMTStr::Delete(UINT pos,UINT len)
  {
//--- check
   if(pos>=m_str_len || len==0 || !m_str) return;
//--- remove
   if(pos+len>m_str_len) len=m_str_len-pos;
   if(pos+len<m_str_len)
      for(UINT i=pos;i<m_str_len-len;i++)
         m_str[i]=m_str[i+len];
   m_str_len-=len;
   m_str[m_str_len]=L'\0';
  }
//+------------------------------------------------------------------+
//| Delete len symbols from pos position                             |
//+------------------------------------------------------------------+
inline void CMTStr::Delete(LPWSTR dst,UINT dstsize,UINT pos,UINT len)
  {
   UINT dstlen;
//--- check
   if(!dst || dstsize==0) return;
   dstlen=Len(dst);
   if(pos>=dstlen-1)      return;
//--- remove
   if(pos+len>dstlen) len=dstlen-pos;
   if(pos+len<dstlen)
      for(UINT i=pos;i<dstlen-len;i++)
         dst[i]=dst[i+len];
   dst[dstlen-len]=L'\0';
  }
//+------------------------------------------------------------------+
//| Convert to lower case                                            |
//+------------------------------------------------------------------+
inline void CMTStr::ToLower(LPWSTR str,UINT size)
  {
   if(str && size>0) _wcslwr_s(str,size);
  }
//+------------------------------------------------------------------+
//| Convert to upper case                                            |
//+------------------------------------------------------------------+
inline void CMTStr::ToUpper(LPWSTR str,UINT size)
  {
   if(str && size>0) _wcsupr_s(str,size);
  }
//+------------------------------------------------------------------+
//| Static string format                                             |
//+------------------------------------------------------------------+
template<UINT strsize>
inline int CMTStr::FormatStr(wchar_t (&str)[strsize],LPCWSTR fmt,...)
  {
   int len=-1;
//---
   if(str && strsize>1 && fmt)
     {
      va_list marker;
      //--- format text
      va_start(marker,fmt);
      len=_vsnwprintf_s(str,strsize,_TRUNCATE,fmt,marker);
      va_end(marker);
      //--- check
      if(len>0) str[len]=L'\0';
     }
//---
   return(len);
  }
//+------------------------------------------------------------------+
//| Static string format                                             |
//+------------------------------------------------------------------+
inline int CMTStr::FormatStr(LPWSTR str,UINT size,LPCWSTR fmt,...)
  {
   int len=-1;
//---
   if(str && size>1 && fmt)
     {
      va_list marker;
      //--- format text
      va_start(marker,fmt);
      len=_vsnwprintf_s(str,size,_TRUNCATE,fmt,marker);
      va_end(marker);
      //--- check
      if(len>0) str[len]=L'\0';
     }
//---
   return(len);
  }
//+------------------------------------------------------------------+
//| Append to end                                                    |
//+------------------------------------------------------------------+
inline void CMTStr::Append(LPCWSTR appstring)
  {
   UINT len;
//--- check appstring
   if(m_str && appstring && (len=(UINT)wcslen(appstring))>0 && (len+m_str_len)<m_str_max)
     {
      memcpy(&m_str[m_str_len],appstring,len*sizeof(m_str[0]));
      m_str_len+=len;
      m_str[m_str_len]=0;
     }
  }
//+------------------------------------------------------------------+
//| Append to end                                                    |
//+------------------------------------------------------------------+
inline void CMTStr::Append(const CMTStr &appstring)
  {
//--- check appstring
   if(m_str && appstring.Len()>0 && (appstring.Len()+m_str_len)<m_str_max)
     {
      memcpy(&m_str[m_str_len],appstring.Str(),appstring.Len()*sizeof(m_str[0]));
      m_str_len+=appstring.Len();
      m_str[m_str_len]=0;
     }
  }
//+------------------------------------------------------------------+
//| Append symbol to end                                             |
//+------------------------------------------------------------------+
inline void CMTStr::Append(wchar_t appchar)
  {
//--- check appchar
   if(m_str && appchar!=L'\0' && (m_str_len+1)<m_str_max)
     {
      m_str[m_str_len]=appchar;
      m_str[++m_str_len]=L'\0';
     }
  }
//+------------------------------------------------------------------+
//| Append to end                                                    |
//+------------------------------------------------------------------+
inline void CMTStr::Append(LPWSTR dst,UINT dstsize,LPCWSTR src)
  {
   if(dst && src) wcscat_s(dst,dstsize,src);
  }
//+------------------------------------------------------------------+
//| Substring insert                                                 |
//+------------------------------------------------------------------+
inline void CMTStr::Insert(UINT pos,LPCWSTR insstring)
  {
   UINT len;
//--- check insstring
   if(m_str && insstring && (len=(UINT)wcslen(insstring))>0 && (len+m_str_len)<m_str_max)
     {
      memmove(&m_str[pos+len],&m_str[pos],(m_str_len-pos)*sizeof(m_str[0]));
      memcpy(&m_str[pos],insstring,len*sizeof(m_str[0]));
      m_str_len+=len;
      m_str[m_str_len]=L'\0';
     }
  }
//+------------------------------------------------------------------+
//| Substring insert                                                 |
//+------------------------------------------------------------------+
inline void CMTStr::Insert(UINT pos,const CMTStr &insstring)
  {
//--- check insstring
   if(m_str && insstring.Len()>0 && (insstring.Len()+m_str_len)<m_str_max)
     {
      memmove(&m_str[pos+insstring.Len()],&m_str[pos],(m_str_len-pos)*sizeof(m_str[0]));
      memcpy(&m_str[pos],insstring.Str(),insstring.Len()*sizeof(m_str[0]));
      m_str_len+=insstring.Len();
      m_str[m_str_len]=L'\0';
     }
  }
//+------------------------------------------------------------------+
//| Symbol insert                                                    |
//+------------------------------------------------------------------+
inline void CMTStr::Insert(UINT pos,wchar_t inschar)
  {
//--- check inschar
   if(m_str && inschar!=L'\0' && (m_str_len+1)<m_str_max)
     {
      memmove(&m_str[pos+1],&m_str[pos],(m_str_len-pos)*sizeof(m_str[0]));
      m_str[pos]=inschar;
      m_str[++m_str_len]=L'\0';
     }
  }
//+------------------------------------------------------------------+
//| Compare                                                          |
//+------------------------------------------------------------------+
inline int CMTStr::Compare(LPCWSTR str) const
  {
   if(m_str && str) return wcscmp(m_str,str);
   return(m_str_len<1 ? 0 : 1);
  }
//+------------------------------------------------------------------+
//| Compare                                                          |
//+------------------------------------------------------------------+
inline int CMTStr::Compare(LPCWSTR str,UINT count) const
  {
   if(m_str && str) return wcsncmp(m_str,str,count);
   return(m_str_len<1 ? 0 : 1);
  }
//+------------------------------------------------------------------+
//| Compare                                                          |
//+------------------------------------------------------------------+
inline int CMTStr::Compare(const CMTStr& str) const
  {
   return(m_str ? wcscmp(m_str,str.Str()) : -1);
  }
//+------------------------------------------------------------------+
//| Compare                                                          |
//+------------------------------------------------------------------+
inline int CMTStr::Compare(LPCWSTR str1,LPCWSTR str2)
  {
   return wcscmp(str1,str2);
  }
//+------------------------------------------------------------------+
//| Compare                                                          |
//+------------------------------------------------------------------+
inline int CMTStr::Compare(LPCWSTR str1,LPCWSTR str2,UINT count)
  {
   return wcsncmp(str1,str2,count);
  }
//+------------------------------------------------------------------+
//| Compare no case                                                  |
//+------------------------------------------------------------------+
inline int CMTStr::CompareNoCase(LPCWSTR str) const
  {
   if(m_str && str) return _wcsicmp(m_str,str);
   return(m_str_len<1 ? 0 : 1);
  }
//+------------------------------------------------------------------+
//| Compare no case                                                  |
//+------------------------------------------------------------------+
inline int CMTStr::CompareNoCase(LPCWSTR str,UINT count) const
  {
   if(m_str && str) return _wcsnicmp(m_str,str,count);
   return(m_str_len<1 ? 0 : 1);
  }
//+------------------------------------------------------------------+
//| Compare no case                                                  |
//+------------------------------------------------------------------+
inline int CMTStr::CompareNoCase(const CMTStr& str) const
  {
   if(m_str && str.m_str) return _wcsicmp(m_str,str.m_str);
   return(m_str_len<1 ? 0 : 1);
  }
//+------------------------------------------------------------------+
//| Compare no case                                                  |
//+------------------------------------------------------------------+
inline int CMTStr::CompareNoCase(LPCWSTR str1,LPCWSTR str2)
  {
   return _wcsicmp(str1,str2);
  }
//+------------------------------------------------------------------+
//| Compare no case                                                  |
//+------------------------------------------------------------------+
inline int CMTStr::CompareNoCase(LPCWSTR str1,LPCWSTR str2,UINT count)
  {
   return _wcsnicmp(str1,str2,count);
  }
//+------------------------------------------------------------------+
//| Check group correspondence to groups mask list                   |
//+------------------------------------------------------------------+
inline bool CMTStr::CheckGroupMask(LPCWSTR groupsmask,LPCWSTR group)
  {
   const wchar_t *tok_start;
   wchar_t        mask[256]={0};
   bool           found=false;
   int            pos;
//--- check
   if(!groupsmask || !group) return(false);
//--- look through groupmask
   for(tok_start=groupsmask;*tok_start;tok_start++)
     {
      //--- skip spaces and commas
      if(*tok_start==L' ' || *tok_start==L',') continue;
      //--- copy mask
      for(pos=0; *tok_start && *tok_start!=L',' && pos<255; tok_start++,pos++) mask[pos]=*tok_start;
      //--- skip spaces and commas
      while(pos>0 && (mask[pos-1]==L' ' || mask[pos-1]==L',')) pos--;
      mask[pos]=0;
      //--- check
      if(mask[0]=='!' && CheckGroupTemplate(mask,group)) return(false);
      else
         if(CheckGroupTemplate(mask,group)) found=true;
      //--- template over
      if(!*tok_start) break;
     }
//--- return result
   return(found);
  }
//+------------------------------------------------------------------+
//| Find substring                                                   |
//+------------------------------------------------------------------+
inline int CMTStr::Find(LPCWSTR substring,UINT startpos) const
  {
   if(substring && m_str && m_str_len>0)
      if(startpos<m_str_len)
        {
         wchar_t *position=wcsstr(m_str+startpos,substring);
         if(position) return int(position-m_str);
        }
   return(-1);
  }
//+------------------------------------------------------------------+
//| Find substring                                                   |
//+------------------------------------------------------------------+
inline int CMTStr::Find(LPCWSTR substring) const
  {
   if(substring && m_str && m_str_len>0)
     {
      wchar_t *position=wcsstr(m_str,substring);
      if(position)
        {
         return int(position-m_str);
        }
     }
   return(-1);
  }
//+------------------------------------------------------------------+
//| Find substring no case                                           |
//+------------------------------------------------------------------+
inline int CMTStr::FindNoCase(LPCWSTR substring,UINT startpos) const
  {
   UINT sublen=0;
//---
   if(substring && (sublen=(UINT)wcslen(substring))>0 && m_str && m_str_len>0)
      if(startpos<m_str_len)
         for(UINT pos=startpos;m_str_len-pos>=sublen;pos++)
            if(_wcsnicmp(m_str+pos,substring,sublen)==0)
               return int(pos);
   return(-1);
  }
//+------------------------------------------------------------------+
//| Find substring reverse                                           |
//+------------------------------------------------------------------+
inline int CMTStr::FindR(LPCWSTR substring) const
  {
   int pos=0,end=0,beg=-1;
//--- check
   if(substring && m_str && m_str_len>0 && Len(substring)>0)
     {
      //--- find from end
      while((pos=CMTStr::Find(&m_str[end],substring))>=0)
        {
         beg=end+pos;
         end+=pos+1;
        }
     }
//--- result
   return(beg);
  }
//+------------------------------------------------------------------+
//| Find symbol                                                      |
//+------------------------------------------------------------------+
inline int CMTStr::FindChar(const wchar_t character) const
  {
   if(m_str && m_str_len>0)
     {
      wchar_t *ptr=wcschr(m_str,character);
      if(ptr) return int(ptr-m_str);
     }
   return(-1);
  }
//+------------------------------------------------------------------+
//| Find symbol reverse                                              |
//+------------------------------------------------------------------+
inline int CMTStr::FindRChar(const wchar_t character) const
  {
   if(m_str && m_str_len>0)
     {
      wchar_t *ptr=wcsrchr(m_str,character);
      if(ptr) return int(ptr-m_str);
     }
   return(-1);
  }
//+------------------------------------------------------------------+
//| Find substring                                                   |
//+------------------------------------------------------------------+
inline int CMTStr::Find(LPCWSTR str,LPCWSTR substr)
  {
   if(str && substr && substr[0]!=L'\0')
     {
      LPCWSTR ptr=wcsstr(str,substr);
      if(ptr) return int(ptr-str);
     }
   return(-1);
  }
//+------------------------------------------------------------------+
//| Find substring no case                                           |
//+------------------------------------------------------------------+
inline int CMTStr::FindNoCase(LPCWSTR str,LPCWSTR substr)
  {
   UINT len=0,sublen=0;
//---
   if(str && substr && (len=(UINT)wcslen(str))>0 && (sublen=(UINT)wcslen(substr))>0)
      for(UINT pos=0;len-pos>=sublen;pos++)
         if(_wcsnicmp(str+pos,substr,sublen)==0)
            return int(pos);
   return(-1);
  }
//+------------------------------------------------------------------+
//| Find substring reverse                                           |
//+------------------------------------------------------------------+
inline int CMTStr::FindR(LPCWSTR str,LPCWSTR substr)
  {
   int pos=0,end=0,beg=-1;
//--- check
   if(str && substr && Len(str)>0 && Len(substr)>0)
     {
      //--- find
      while((pos=CMTStr::Find(&str[end],substr))>=0)
        {
         beg=end+pos;
         end+=pos+1;
        }
     }
//--- result
   return(beg);
  }
//+------------------------------------------------------------------+
//| Find char                                                        |
//+------------------------------------------------------------------+
inline int CMTStr::FindChar(LPCWSTR str,wchar_t character)
  {
   if(str)
     {
      LPCWSTR ptr=wcschr(str,character);
      if(ptr) return int(ptr-str);
     }
   return(-1);
  }
//+------------------------------------------------------------------+
//| Find symbol reverse                                              |
//+------------------------------------------------------------------+
inline int CMTStr::FindRChar(LPCWSTR str,wchar_t character)
  {
   if(str)
     {
      LPCWSTR ptr=wcsrchr(str,character);
      if(ptr) return int(ptr-str);
     }
   return(-1);
  }
//+------------------------------------------------------------------+
//| Check group by expression                                        |
//+------------------------------------------------------------------+
inline bool CMTStr::CheckGroupTemplate(LPWSTR expr,LPCWSTR group)
  {
   wchar_t *mask=NULL,*mask_ast=NULL;
   bool     ast=false;
//--- check
   if(!expr || !group) return(false);
//--- skip multiple '!'
   for(mask=expr; *mask=='!'; mask++){}
//--- check for '*' at start
   for(; *mask && *mask=='*'; mask++)
     {
      ast     =true;
      mask_ast=mask;
     }
//--- group loop
   for(; *group && *mask; group++)
     {
      //--- check symbols
      if(*group!=*mask)
        {
         if(!ast) return(false);
         else     continue;
        }
      //--- check word
      for(; *mask && *mask!='*' && *group; mask++, group++)
         if(*group!=*mask)
           {
            if(!ast) return(false);
            else
              {
               mask=mask_ast;
               break;
              }
           }
      //--- check group
      if(!*mask && !*group) return(true);
      if(!*mask)
        {
         if(!ast) return(false);
         else     mask=mask_ast;
        }
      if(!*group)
        {
         if(*mask && *mask!='*') return(false);
         else
           {
            for(; *mask && *mask=='*'; mask++){}
            if(!*mask) return(true);
            return(false);
           }
        }
      else
        {
         for(; *mask && *mask=='*'; mask++)
            mask_ast=mask;
         if(!*mask) return(true);
         ast=true;
         group--;
        }
     }
//--- mask empty?
   if(*mask) return(false);
   return(true);
  }
//+------------------------------------------------------------------+
//| Windows error description                                        |
//+------------------------------------------------------------------+
inline LPCWSTR CMTStr::ErrorMsg(DWORD error)
  {
   CMTStrPath text;
//--- check
   if(!m_str) return(m_str);
//--- get description
   ::FormatMessageW(FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_SYSTEM,
                   NULL,error,
                   MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),
                   text.Buffer(),text.Max(),
                   NULL);
   text.Refresh();
//--- remove \r & \n in last symbol
   if(text.m_str_len && (text.m_str[text.m_str_len-1]==L'\r' || text.m_str[text.m_str_len-1]==L'\n'))
     {
      text.m_str[text.m_str_len-1]=L'\0';
      text.m_str_len--;
     }
//--- remove \r & \n in prelast symbol
   if(text.m_str_len && (text.m_str[text.m_str_len-1]==L'\r' || text.m_str[text.m_str_len-1]==L'\n'))
     {
      text.m_str[text.m_str_len-1]=L'\0';
      text.m_str_len--;
     }
//--- format both code and description
   Format(L"%s (%u)",text.Str(),error);
   return(m_str);
  }
//+------------------------------------------------------------------+
//| Error description macro                                          |
//+------------------------------------------------------------------+
#define MT_ERROR_MSG() CMTStr64().ErrorMsg(GetLastError())
//+------------------------------------------------------------------+
