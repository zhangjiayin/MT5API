//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include "MT5APIStr.h"
//+------------------------------------------------------------------+
//| File operations wrapper class                                    |
//+------------------------------------------------------------------+
class CMTFile
  {
public:
   static const UINT64 INVALID_POSITION;
private:
   HANDLE            m_file;

public:
                     CMTFile():m_file(INVALID_HANDLE_VALUE) {}
   virtual          ~CMTFile()                              { Close(); }
   //--- file open
   bool              Open(LPCWSTR lpFileName,const DWORD dwAccess,const DWORD dwShare,const DWORD dwCreationFlags,const DWORD dwAttributes=FILE_ATTRIBUTE_NORMAL);
   bool              OpenRead(LPCWSTR lpFileName);
   bool              OpenWrite(LPCWSTR lpFileName);
   //--- file close
   void              Close(void);
   //--- file properties
   HANDLE            Handle(void);
   bool              IsOpen() const;
   UINT64            Size(void) const;
   static UINT64     Size(LPCWSTR path);
   FILETIME          TimeCreate(void) const;
   FILETIME          TimeLastAccess(void) const;
   FILETIME          TimeLastModify(void) const;
   UINT64            CurrPos(void);
   //--- file operations
   DWORD             Read(void  *buffer,const DWORD length);
   DWORD             Write(const void *buffer,const DWORD length);
   UINT64            Seek(const INT64 distance,const DWORD method);
   bool              ChangeSize(const UINT64 size);
   bool              Flush();
   //--- files group operations
   static int        FilesCopy(const CMTStr& path,const CMTStr& newpath,const CMTStr& mask,const bool subdir);
   //--- direcory operations
   static bool       DirectoryCreate(const CMTStr& path);
   static bool       DirectoryRemove(const CMTStr& path);
   static bool       DirectoryClean(const CMTStr& path,const CMTStr& mask);
  };
//+------------------------------------------------------------------+
//| Constant declaration                                             |
//+------------------------------------------------------------------+
const __declspec(selectany) UINT64 CMTFile::INVALID_POSITION=_UI64_MAX;
//+------------------------------------------------------------------+
//| File open                                                        |
//+------------------------------------------------------------------+
inline bool CMTFile::Open(LPCWSTR lpFileName,const DWORD dwAccess,const DWORD dwShare,const DWORD dwCreationFlags,const DWORD dwAttributes)
  {
//--- close previous
   Close();
//--- check name and open
   if(lpFileName)
      m_file=CreateFileW(lpFileName,dwAccess,dwShare,NULL,dwCreationFlags,dwAttributes,NULL);
//--- return
   return(m_file!=INVALID_HANDLE_VALUE);
  }
//+------------------------------------------------------------------+
//| File open for read                                               |
//+------------------------------------------------------------------+
inline bool CMTFile::OpenRead(LPCWSTR lpFileName)  
  { 
   return Open(lpFileName,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,OPEN_EXISTING);
  }
//+------------------------------------------------------------------+
//| File open for write                                              |
//+------------------------------------------------------------------+
inline bool CMTFile::OpenWrite(LPCWSTR lpFileName)
 { 
  return Open(lpFileName,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,CREATE_ALWAYS); 
 }
//+------------------------------------------------------------------+
//| File close                                                       |
//+------------------------------------------------------------------+
inline void CMTFile::Close(void)
  {
   if(m_file!=INVALID_HANDLE_VALUE)
     {
      CloseHandle(m_file);
      m_file=INVALID_HANDLE_VALUE;
     }
  }
//+------------------------------------------------------------------+
//| File handle                                                      |
//+------------------------------------------------------------------+
inline HANDLE CMTFile::Handle(void)
  {
   return(m_file);
  }
//+------------------------------------------------------------------+
//| Check file state                                                 |
//+------------------------------------------------------------------+
inline bool CMTFile::IsOpen(void) const
  { 
   return(m_file!=INVALID_HANDLE_VALUE); 
  }
//+------------------------------------------------------------------+
//| File size                                                        |
//+------------------------------------------------------------------+
inline UINT64 CMTFile::Size() const
  {
   LARGE_INTEGER li={0};
//--- check and receive
   if(m_file==INVALID_HANDLE_VALUE || !::GetFileSizeEx(m_file,&li)) return(0);
//--- return result
   return((UINT64)li.QuadPart);
  }
//+------------------------------------------------------------------+
//| File size                                                        |
//+------------------------------------------------------------------+
inline UINT64 CMTFile::Size(LPCWSTR path)
  {
   LARGE_INTEGER             li={0};
   WIN32_FILE_ATTRIBUTE_DATA fad;
//--- receive file 
   if(GetFileAttributesExW(path,GetFileExInfoStandard,&fad))
     {
      li.LowPart =fad.nFileSizeLow;
      li.HighPart=(LONG)fad.nFileSizeHigh;
     }
//--- return result
   return((UINT64)li.QuadPart);
  }
//+------------------------------------------------------------------+
//| File creation time                                               |
//+------------------------------------------------------------------+
inline FILETIME CMTFile::TimeCreate() const
  {
   FILETIME ft={0};
//--- check and receive
   if(m_file!=INVALID_HANDLE_VALUE) GetFileTime(m_file,&ft,NULL,NULL);
//--- return result
   return(ft);
  }
//+------------------------------------------------------------------+
//| File last access time                                            |
//+------------------------------------------------------------------+
inline FILETIME CMTFile::TimeLastAccess() const
  {
   FILETIME ft={0};
//--- check and receive
   if(m_file!=INVALID_HANDLE_VALUE) GetFileTime(m_file,NULL,&ft,NULL);
//--- return result
   return(ft);
  }
//+------------------------------------------------------------------+
//| File last modify time                                            |
//+------------------------------------------------------------------+
inline FILETIME CMTFile::TimeLastModify() const
  {
   FILETIME ft={0};
//--- check and receive
   if(m_file!=INVALID_HANDLE_VALUE) GetFileTime(m_file,NULL,NULL,&ft);
//--- return result
   return(ft);
  }
//+------------------------------------------------------------------+
//| File pointer position                                            |
//+------------------------------------------------------------------+
inline UINT64 CMTFile::CurrPos()
  {
   return(CMTFile::Seek(INT64(0),FILE_CURRENT));
  }
//+------------------------------------------------------------------+
//| File read                                                        |
//+------------------------------------------------------------------+
inline DWORD CMTFile::Read(void *buffer,const DWORD length)
  {
   DWORD readed=0;
//--- check
   if(m_file==INVALID_HANDLE_VALUE || buffer==NULL || length<1) return(0);
//--- read
   if(ReadFile(m_file,buffer,length,&readed,NULL)==0) readed=0;
//--- return
   return(readed);
  }
//+------------------------------------------------------------------+
//| Write to file                                                    |
//+------------------------------------------------------------------+
inline DWORD CMTFile::Write(const void *buffer,const DWORD length)
  {
   DWORD written=0;
//--- check
   if(m_file==INVALID_HANDLE_VALUE || buffer==NULL || length<1) return(0);
//--- write
   if(WriteFile(m_file,buffer,length,&written,NULL)==0) written=0;
//--- return
   return(written);
  }
//+------------------------------------------------------------------+
//| Seek file pointer                                                |
//+------------------------------------------------------------------+
inline UINT64 CMTFile::Seek(const INT64 distance,const DWORD method)
  {
   LARGE_INTEGER li={0};
//--- check
   if(m_file==INVALID_HANDLE_VALUE) return(INVALID_POSITION);
//--- fill and seek
   li.QuadPart=distance;
   li.LowPart=SetFilePointer(m_file,(LONG)li.LowPart,&li.HighPart,method);
//--- check result
   if(li.LowPart==INVALID_SET_FILE_POINTER && GetLastError()!=NO_ERROR) return(INVALID_POSITION);
//--- return new file pointer position
   return((UINT64)li.QuadPart);
  }
//+------------------------------------------------------------------+
//| Change file size                                                 |
//+------------------------------------------------------------------+
inline bool CMTFile::ChangeSize(const UINT64 size)
  {
   return(CMTFile::Seek((INT64)size,FILE_BEGIN)==size && SetEndOfFile(m_file));
  }
//+------------------------------------------------------------------+
//| Flush file buffer                                                |
//+------------------------------------------------------------------+
inline bool CMTFile::Flush()
  {
   if(m_file!=INVALID_HANDLE_VALUE) return(::FlushFileBuffers(m_file)!=0);
   return(false);
  }
//+------------------------------------------------------------------+
//| Copy files by mask                                               |
//+------------------------------------------------------------------+
inline int CMTFile::FilesCopy(const CMTStr& path,const CMTStr& newpath,const CMTStr& mask,const bool subdir)
  {
   CMTStr512        src,dst,name;
   HANDLE           hSearch;
   WIN32_FIND_DATAW fnd;
   int              count=0;
//--- find files
   src.Format(L"%s\\%s",path.Str(),mask.Str());
   if((hSearch=FindFirstFileW(src.Str(), &fnd))!=INVALID_HANDLE_VALUE)
     {
      do
        {
         //--- skip root directories
         if(CMTStr::Compare(fnd.cFileName,L".")==0 || CMTStr::Compare(fnd.cFileName,L"..")==0) continue;
         //--- directory?
         if(!(fnd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
           {
            //--- create source path
            src.Format(L"%s\\%s",path.Str(),fnd.cFileName);
            //--- create dst path
            dst.Format(L"%s\\%s",newpath.Str(),fnd.cFileName);
            //--- copy file
            if(::CopyFileW(src.Str(),dst.Str(),FALSE)!=FALSE) count++;
           }
         else
            if(subdir)
              {
               //--- create path
               src.Format(L"%s\\%s",path.Str(),fnd.cFileName);
               dst.Format(L"%s\\%s",newpath.Str(),fnd.cFileName);
               //--- create dst path
               DirectoryCreate(dst);
               //--- copy files
               count+=FilesCopy(src,dst,mask,subdir);
              }
        } while(FindNextFileW(hSearch,&fnd)!=0);
      //--- close handle
      FindClose(hSearch);
     }
//--- return copied count
   return(count);
  }
//+------------------------------------------------------------------+
//| Create directory with subdirectories                             |
//+------------------------------------------------------------------+
inline bool CMTFile::DirectoryCreate(const CMTStr& path)
  {
   wchar_t *cp,temp[MAX_PATH];
//--- check directory
   if(GetFileAttributesW(path.Str())!=INVALID_FILE_ATTRIBUTES) 
      return(true);
//--- copy
   CMTStr::Copy(temp,path.Str());
//--- parse path and create directories
   for(cp=temp;*cp!=L'\0';cp++)
      if(*cp==L'\\')
        {
         *cp=L'\0';
         if(GetFileAttributesW(temp)==INVALID_FILE_ATTRIBUTES)
            if(!::CreateDirectoryW(temp,NULL)) 
               return(false);
         *cp=L'\\';
        }
//--- copy remainder
   if(GetFileAttributesW(temp)==INVALID_FILE_ATTRIBUTES)
      if(!::CreateDirectoryW(temp,NULL))
         return(false);
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Directory clean by mask                                          |
//+------------------------------------------------------------------+
inline bool CMTFile::DirectoryClean(const CMTStr& path,const CMTStr& mask)
  {
   HANDLE           hSearch;
   WIN32_FIND_DATAW fnd;
   CMTStrPath       tmp;
   bool             res=true;
//--- check
   if(path.Empty() || path.Len()<=3) 
      return(false);
//--- create path
   tmp.Format(L"%s\\%s",path.Str(),mask.Str());
//--- search
   if((hSearch=FindFirstFileW(tmp.Str(),&fnd))!=INVALID_HANDLE_VALUE)
     {
      do
        {
         //--- directory?
         if(fnd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
           {
            //--- skip root directories
            if(CMTStr::Compare(fnd.cFileName,L".")==0 || CMTStr::Compare(fnd.cFileName,L"..")==0)
               continue;
            //--- create directory path
            tmp.Format(L"%s\\%s",path.Str(),fnd.cFileName);
            //--- clean directory
            DirectoryClean(tmp,mask);
            //--- delete directory
            res=::RemoveDirectoryW(tmp.Str()) && res;
           }
         else
           {
            //--- create file path
            tmp.Format(L"%s\\%s",path.Str(),fnd.cFileName);
            //--- delete file
            res=::DeleteFileW(tmp.Str()) && res;
           }
        }
      while(FindNextFileW(hSearch,&fnd));
      //--- close handle
      FindClose(hSearch);
     }
//--- result
   return(res);
  }
//+------------------------------------------------------------------+
//| Full directory remove                                            |
//+------------------------------------------------------------------+
inline bool CMTFile::DirectoryRemove(const CMTStr& path)
  {
   return(DirectoryClean(path,CMTStr16(L"*")) && ::RemoveDirectoryW(path.Str()));
  }
//+------------------------------------------------------------------+
