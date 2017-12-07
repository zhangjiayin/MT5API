//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Logins, orders and deals range                                   |
//+------------------------------------------------------------------+
class IMTConServerRange
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(IMTConServerRange* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- from
   virtual UINT64    From(void) const=0;
   virtual MTAPIRES  From(const UINT64 from)=0;
   //--- to
   virtual UINT64    To(void) const=0;
   virtual MTAPIRES  To(const UINT64 to)=0;
   //--- used range
   virtual UINT64    UsedFrom(void) const=0;
   virtual UINT64    UsedTo(void) const=0;
  };
//+------------------------------------------------------------------+
//| Trade and main platform server configuration                     |
//+------------------------------------------------------------------+
class IMTConServerTrade
  {
public:
   //--- demo account allocation mode
   enum EnDemoMode
     {
      DEMO_DISABLED         =0, // demo account allocation disabled 
      DEMO_PROLONG          =1, // prolong demo acounts after reconnect
      DEMO_FIXED            =2, // demo account with fixed period
      //--- enumeration borders
      DEMO_FIRST            =DEMO_DISABLED,
      DEMO_LAST             =DEMO_FIXED
     };
   //--- enumeration borders
   enum EnOvernightMode
     {
      OVERNIGHT_END_DAY     =0, // overnight performed at the end of the trading day
      OVERNIGHT_START_DAY   =1, // overnight performed at the begin of the trading day
      //--- enumeration borders
      OVERNIGHT_FIRST       =OVERNIGHT_END_DAY,
      OVERNIGHT_LAST        =OVERNIGHT_START_DAY
     };
   //--- overmonth mode 
   enum EnOvermonthMode
     {
      OVERMONTH_LAST_DAY    =0, // overmonth performed at the last month day
      OVERMONTH_FIRST_DAY   =1, // overmonth performed at the first month day
      //--- enumeration borders
      OVERMONTH_FIRST       =OVERMONTH_LAST_DAY,
      OVERMONTH_LAST        =OVERMONTH_FIRST_DAY
     };
   //--- overnigh days enumeration
   enum EnOvernightDays
     {
      OVERNIGHT_DAYS_SUN    =0x00000001,
      OVERNIGHT_DAYS_MON    =0x00000002,
      OVERNIGHT_DAYS_TUE    =0x00000004,
      OVERNIGHT_DAYS_WED    =0x00000008,
      OVERNIGHT_DAYS_THU    =0x00000010,
      OVERNIGHT_DAYS_FRI    =0x00000020,
      OVERNIGHT_DAYS_SAT    =0x00000040,
      //--- enumeration borders
      OVERNIGHT_DAYS_NONE   =0x00000000,
      OVERNIGHT_DAYS_DEFAULT=OVERNIGHT_DAYS_MON | OVERNIGHT_DAYS_TUE |OVERNIGHT_DAYS_WED  | OVERNIGHT_DAYS_THU | OVERNIGHT_DAYS_FRI,
      OVERNIGHT_DAYS_ALL    =OVERNIGHT_DAYS_SUN | OVERNIGHT_DAYS_MON | OVERNIGHT_DAYS_TUE |
      OVERNIGHT_DAYS_WED | OVERNIGHT_DAYS_THU | OVERNIGHT_DAYS_FRI | OVERNIGHT_DAYS_SAT
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(IMTConServerTrade* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- demo accounts mode EnDemoMode
   virtual UINT      DemoMode(void) const=0;
   virtual MTAPIRES  DemoMode(const UINT mode)=0;
   //--- demo accounts period
   virtual UINT      DemoPeriod(void) const=0;
   virtual MTAPIRES  DemoPeriod(const UINT period)=0;
   //--- overnight mode
   virtual UINT      OvernightMode(void) const=0;
   virtual MTAPIRES  OvernightMode(const UINT mode)=0;
   //--- overnight time (in minutes)
   virtual UINT      OvernightTime(void) const=0;
   virtual MTAPIRES  OvernightTime(const UINT time)=0;
   virtual INT64     OvernightTimeLast(void) const=0;
   virtual INT64     OvernightTimePrev(void) const=0;
   //--- overnight mode
   virtual UINT      OvermonthMode(void) const=0;
   virtual MTAPIRES  OvermonthMode(const UINT mode)=0;
   //--- overmonth time (in minutes)
   virtual INT64     OvermonthTimeLast(void) const=0;
   virtual INT64     OvermonthTimePrev(void) const=0;
   //--- client logins ranges for this trade server
   virtual MTAPIRES  LoginsRangeAdd(IMTConServerRange* range)=0;
   virtual MTAPIRES  LoginsRangeUpdate(const UINT pos,const IMTConServerRange* range)=0;
   virtual MTAPIRES  LoginsRangeDelete(const UINT pos)=0;
   virtual MTAPIRES  LoginsRangeClear(void)=0;
   virtual MTAPIRES  LoginsRangeShift(const UINT pos,const int shift)=0;
   virtual UINT      LoginsRangeTotal(void) const=0;
   virtual MTAPIRES  LoginsRangeNext(const UINT pos,IMTConServerRange* range) const=0;
   //--- orders tickets ranges for this trade server
   virtual MTAPIRES  OrdersRangeAdd(IMTConServerRange* range)=0;
   virtual MTAPIRES  OrdersRangeUpdate(const UINT pos,const IMTConServerRange* range)=0;
   virtual MTAPIRES  OrdersRangeDelete(const UINT pos)=0;
   virtual MTAPIRES  OrdersRangeClear(void)=0;
   virtual MTAPIRES  OrdersRangeShift(const UINT pos,const int shift)=0;
   virtual UINT      OrdersRangeTotal(void) const=0;
   virtual MTAPIRES  OrdersRangeNext(const UINT pos,IMTConServerRange* range) const=0;
   //--- deals tickets ranges for this trade server
   virtual MTAPIRES  DealsRangeAdd(IMTConServerRange* range)=0;
   virtual MTAPIRES  DealsRangeUpdate(const UINT pos,const IMTConServerRange* range)=0;
   virtual MTAPIRES  DealsRangeDelete(const UINT pos)=0;
   virtual MTAPIRES  DealsRangeClear(void)=0;
   virtual MTAPIRES  DealsRangeShift(const UINT pos,const int shift)=0;
   virtual UINT      DealsRangeTotal(void) const=0;
   virtual MTAPIRES  DealsRangeNext(const UINT pos,IMTConServerRange* range) const=0;
   //--- trade totals
   virtual UINT      TotalUsers(void) const=0;
   virtual UINT      TotalUsersReal(void) const=0;
   virtual UINT      TotalDeals(void) const=0;
   virtual UINT      TotalOrders(void) const=0;
   virtual UINT      TotalOrdersHistory(void) const=0;
   virtual UINT      TotalPositions(void) const=0;
   //--- overnight days EnOvernightDays
   virtual UINT      OvernightDays(void) const=0;
   virtual MTAPIRES  OvernightDays(const UINT days)=0;
  };
//+------------------------------------------------------------------+
//| History server configuration                                     |
//+------------------------------------------------------------------+
class IMTConServerHistory
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(IMTConServerHistory* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- datafeeds switch timeout
   virtual UINT      DatafeedsTimeout(void) const=0;
   virtual MTAPIRES  DatafeedsTimeout(const UINT timeout)=0;
   //--- max news buffer
   virtual UINT      NewsMax(void) const=0;
   virtual MTAPIRES  NewsMax(const UINT news_max)=0;
  };
//+------------------------------------------------------------------+
//| Backup server configuration                                      |
//+------------------------------------------------------------------+
class IMTConServerBackup
  {
public:
   //--- backup flags
   enum EnBackupFlags
     {
      FLAG_ENABLE_BACKUPS=0x00000001,
      FLAG_ENABLE_TICKS  =0x00000002,
     };
   //--- backup period
   enum EnBackupPeriod
     {
      BACKUP_DISABLED   =0,
      BACKUP_15MINUTES  =1,
      BACKUP_30MINUTES  =2,
      BACKUP_1HOUR      =3,
      BACKUP_4HOURS     =4,
      BACKUP_1DAY       =5,
      //--- enumeration borders
      BACKUP_FIRST      =BACKUP_DISABLED,
      BACKUP_LAST       =BACKUP_1DAY
     };
   //--- backup copy time to live
   enum EnBackupTTL
     {
      BACKUP_TTL_1DAY   =1,
      BACKUP_TTL_3DAYS  =2,
      BACKUP_TTL_1WEEK  =3,
      BACKUP_TTL_1MONTH =4,
      BACKUP_TTL_3MONTHS=5,
      BACKUP_TTL_6MONTHS=6,
      //--- enumeration borders
      BACKUP_TTL_FIRST  =BACKUP_TTL_1DAY,
      BACKUP_TTL_LAST   =BACKUP_TTL_6MONTHS
     };
   //--- SQL export modes
   enum EnSQLExportMode
     {
      SQL_MODE_NONE     =0,
      SQL_MODE_MSSQL    =1,
      SQL_MODE_FIREBIRD =2,
      SQL_MODE_MYSQL    =3,
      SQL_MODE_ORACLE   =4,
      //--- enumeration borders
      SQL_MODE_FIRST    =SQL_MODE_NONE,
      SQL_MODE_LAST     =SQL_MODE_ORACLE,
     };
   //--- SQL export flags
   enum EnSQLExportFlags
     {
      SQL_FLAG_NONE      =0x00000000,
      SQL_FLAG_PARTITIONS=0x00000001, // split by years
      SQL_FLAG_SKIP_DEMO =0x00000002, // skip demo accounts
      //--- enumeration borders
      SQL_FLAG_ALL       =SQL_FLAG_PARTITIONS|SQL_FLAG_SKIP_DEMO
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(IMTConServerBackup* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- master server
   virtual UINT64    MasterServer(void) const=0;
   virtual MTAPIRES  MasterServer(const UINT64 id)=0;
   //--- backup path
   virtual LPCWSTR   BackupPath(void) const=0;
   virtual MTAPIRES  BackupPath(LPCWSTR path)=0;
   //--- full backup time (minutes)
   virtual UINT      BackupFullTime(void) const=0;
   virtual MTAPIRES  BackupFullTime(const UINT time)=0;
   //--- backup period - EnBackupPeriod
   virtual UINT      BackupPeriod(void) const=0;
   virtual MTAPIRES  BackupPeriod(const UINT period)=0;
   //--- backup copy TTL - EnBackupTTL
   virtual UINT      BackupTTL(void) const=0;
   virtual MTAPIRES  BackupTTL(const UINT period)=0;
   //--- backup flags - EnBackupFlags
   virtual UINT64    BackupFlags(void) const=0;
   virtual MTAPIRES  BackupFlags(const UINT64 flags)=0;
   //--- sql export mode
   virtual UINT      SQLExportMode(void) const=0;
   virtual MTAPIRES  SQLExportMode(const UINT mode)=0;
   //--- sql export flags
   virtual UINT64    SQLExportFlags(void) const=0;
   virtual MTAPIRES  SQLExportFlags(const UINT64 flags)=0;
   //--- sql export open trades refresh period in minutes
   virtual UINT      SQLExportPeriod(void) const=0;
   virtual MTAPIRES  SQLExportPeriod(const UINT period)=0;
   //--- sql export server
   virtual LPCWSTR   SQLExportServer(void) const=0;
   virtual MTAPIRES  SQLExportServer(LPCWSTR server)=0;
   //--- sql export login
   virtual LPCWSTR   SQLExportLogin(void) const=0;
   virtual MTAPIRES  SQLExportLogin(LPCWSTR login)=0;
   //--- sql export password
   virtual LPCWSTR   SQLExportPassword(void) const=0;
   virtual MTAPIRES  SQLExportPassword(LPCWSTR password)=0;
   //--- sql export folder
   virtual LPCWSTR   SQLExportFolder(void) const=0;
   virtual MTAPIRES  SQLExportFolder(LPCWSTR folder)=0;
  };
//+------------------------------------------------------------------+
//| Access server configuration                                      |
//+------------------------------------------------------------------+
class IMTConServerAccess
  {
public:
   //--- access mask
   enum EnAccessMask
     {
      ACCESS_ALLOW_CLIENT     =1,
      ACCESS_ALLOW_MANAGER    =2,
      ACCESS_ALLOW_ADMIN      =4,
      ACCESS_ALLOW_CLIENT_API =8,
      ACCESS_ALLOW_MANAGER_API=16,
      //--- enumeration borders
      ACCESS_ALLOW_NONE       =0,
      ACCESS_ALLOW_ALL        =ACCESS_ALLOW_CLIENT|ACCESS_ALLOW_MANAGER|ACCESS_ALLOW_ADMIN|ACCESS_ALLOW_CLIENT_API|ACCESS_ALLOW_MANAGER_API
     };
   //--- EnServerPriority
   enum EnServerPriority
     {
      PRIORITY_HIGHEST        =0,
      PRIORITY_LOWEST         =15,
      PRIORITY_IDLE           =255,
      //---
      PRIORITY_FIRST          =PRIORITY_HIGHEST,
      PRIORITY_LAST           =PRIORITY_IDLE
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(IMTConServerAccess* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- priority
   virtual UINT      Priority(void) const=0;
   virtual MTAPIRES  Priority(const UINT priority)=0;
   virtual UINT      PriorityCurrent(void) const=0;
   //--- access flags EnAccessMask
   virtual UINT      AccessFlags(void) const=0;
   virtual MTAPIRES  AccessFlags(const UINT flags)=0;
   //--- max news buffer
   virtual UINT      NewsMax(void) const=0;
   virtual MTAPIRES  NewsMax(const UINT news_max)=0;
   //--- antiflood
   virtual UINT      AntifloodEnabled(void) const=0;
   virtual MTAPIRES  AntifloodEnabled(const UINT enabled)=0;
   //--- antiflood connects criterion
   virtual UINT      AntifloodConnects(void) const=0;
   virtual MTAPIRES  AntifloodConnects(const UINT connects)=0;
   //--- antiflood connects criterion
   virtual UINT      AntifloodErrors(void) const=0;
   virtual MTAPIRES  AntifloodErrors(const UINT errors)=0;
   //--- list of public addresses (address:port) available for terminals
   virtual MTAPIRES  PointsAdd(LPCWSTR path)=0;
   virtual MTAPIRES  PointsUpdate(const UINT pos,LPCWSTR address)=0;
   virtual MTAPIRES  PointsDelete(const UINT pos)=0;
   virtual MTAPIRES  PointsClear(void)=0;
   virtual MTAPIRES  PointsShift(const UINT pos,const int shift)=0;
   virtual UINT      PointsTotal(void) const=0;
   virtual LPCWSTR   PointsNext(const UINT pos) const=0;
   //--- list of internal addresses (address:port) for server listening
   virtual MTAPIRES  BindingsAdd(LPCWSTR path)=0;
   virtual MTAPIRES  BindingsUpdate(const UINT pos,LPCWSTR address)=0;
   virtual MTAPIRES  BindingsDelete(const UINT pos)=0;
   virtual MTAPIRES  BindingsClear(void)=0;
   virtual MTAPIRES  BindingsShift(const UINT pos,const int shift)=0;
   virtual UINT      BindingsTotal(void) const=0;
   virtual LPCWSTR   BindingsNext(const UINT pos) const=0;
   //--- list of trade attended trade servers
   virtual MTAPIRES  ServersAdd(const UINT64 server_id)=0;
   virtual MTAPIRES  ServersUpdate(const UINT pos,UINT64 server_id)=0;
   virtual MTAPIRES  ServersDelete(const UINT pos)=0;
   virtual MTAPIRES  ServersClear(void)=0;
   virtual MTAPIRES  ServersShift(const UINT pos,const int shift)=0;
   virtual UINT      ServersTotal(void) const=0;
   virtual UINT64    ServersNext(const UINT pos) const=0;
  };
//+------------------------------------------------------------------+
//| Web server configuration                                         |
//+------------------------------------------------------------------+
class IMTConServerWeb
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(IMTConServerWeb* param)=0;
   virtual MTAPIRES  Clear(void)=0;
  };
//+------------------------------------------------------------------+
//| Common platform server configuration                             |
//+------------------------------------------------------------------+
class IMTConServer
  {
public:
   //--- server types
   enum EnServerTypes
     {
      NET_MAIN_TRADE_SERVER   =0,
      NET_TRADE_SERVER        =1,
      NET_HISTORY_SERVER      =2,
      NET_ACCESS_SERVER       =3,
      NET_BACKUP_SERVER       =4,
      NET_WEB_SERVER          =6,
      //--- enumeration borders
      NET_SERVER_FIRST        =NET_MAIN_TRADE_SERVER,
      NET_SERVER_LAST         =NET_WEB_SERVER
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(IMTConServer* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- server type
   virtual UINT      Type(void) const=0;
   virtual MTAPIRES  Type(const UINT type)=0;
   //--- server name
   virtual LPCWSTR   Name(void) const=0;
   virtual MTAPIRES  Name(LPCWSTR name)=0;
   //--- address 
   virtual LPCWSTR   Address(void) const=0;
   virtual MTAPIRES  Address(LPCWSTR name)=0;
   //--- server id
   virtual UINT64    Id(void) const=0;
   virtual MTAPIRES  Id(const UINT64 id)=0;
   //--- password
   virtual MTAPIRES  Password(LPCWSTR password)=0;
   virtual MTAPIRES  PasswordCheck(LPCWSTR password) const=0;
   //--- service time in minutes
   virtual UINT      ServiceTime(void) const=0;
   virtual MTAPIRES  ServiceTime(const UINT stime)=0;
   //--- list of network adapters
   virtual LPCWSTR   AdaptersCurrent(void) const=0;
   virtual MTAPIRES  AdaptersCurrent(LPCWSTR current)=0;
   virtual UINT      AdaptersTotal(void) const=0;
   virtual LPCWSTR   AdaptersNext(const UINT pos) const=0;
   //--- list of available ips
   virtual UINT      AddressTotal(void) const=0;
   virtual UINT      AddressNext(const UINT pos) const=0;
   //--- server info
   virtual UINT      Version(void) const=0;
   virtual UINT      Build(void) const=0;
   virtual LPCWSTR   BuildDate(void) const=0;
   virtual INT64     LastBootTime(void) const=0;
   virtual bool      Connected(void) const=0;
   virtual LPCWSTR   OS(void) const=0;
   //--- cpu info
   virtual LPCWSTR   CPU(void) const=0;
   virtual UINT      CPUTotal(void) const=0;
   virtual UINT      CPUUsageMax(void) const=0;
   virtual UINT      CPUUsageCritical(void) const=0;
   //--- memory info (in MB)
   virtual UINT      MemoryTotal(void) const=0;
   virtual UINT      MemoryFree(void) const=0;
   virtual UINT      MemoryFreeMin(void) const=0;
   virtual UINT      MemoryFreeCritical(void) const=0;
   //--- hdd info (in MB)
   virtual UINT      HDDTotal(void) const=0;
   virtual UINT      HDDFree(void) const=0;
   virtual UINT      HDDFreeCritical(void) const=0;
   virtual UINT      HDDFragments(void) const=0;
   virtual UINT      HDDFragmentsCritical(void) const=0;
   virtual UINT      HDDSpeedRead(void) const=0;
   virtual UINT      HDDSpeedReadCritical(void) const=0;
   virtual UINT      HDDSpeedWrite(void) const=0;
   virtual UINT      HDDSpeedWriteCritical(void) const=0;
   //--- connections info
   virtual UINT      ConnectsMax(void) const=0;
   virtual UINT      ConnectsCritical(void) const=0;
   //--- network info (Kbyte/s)
   virtual UINT      NetworkMax(void) const=0;
   virtual UINT      NetworkCritical(void) const=0;
   //--- specific server interfaces
   virtual IMTConServerTrade* TradeServer(void)=0;
   virtual IMTConServerHistory* HistoryServer(void)=0;
   virtual IMTConServerAccess* AccessServer(void)=0;
   virtual IMTConServerBackup* BackupServer(void)=0;
   virtual IMTConServerWeb* WebServer(void)=0;
   virtual void*     ReservedServer1(void)=0;
   virtual void*     ReservedServer2(void)=0;
   virtual void*     ReservedServer3(void)=0;
   virtual void*     ReservedServer4(void)=0;
   //--- list of external addresses (address:port) for connections to server
   virtual MTAPIRES  PointsAdd(LPCWSTR path)=0;
   virtual MTAPIRES  PointsUpdate(const UINT pos,LPCWSTR address)=0;
   virtual MTAPIRES  PointsDelete(const UINT pos)=0;
   virtual MTAPIRES  PointsClear(void)=0;
   virtual MTAPIRES  PointsShift(const UINT pos,const int shift)=0;
   virtual UINT      PointsTotal(void) const=0;
   virtual LPCWSTR   PointsNext(const UINT pos) const=0;
   //--- list of internal addresses (address:port) for server listening
   virtual MTAPIRES  BindingsAdd(LPCWSTR path)=0;
   virtual MTAPIRES  BindingsUpdate(const UINT pos,LPCWSTR address)=0;
   virtual MTAPIRES  BindingsDelete(const UINT pos)=0;
   virtual MTAPIRES  BindingsClear(void)=0;
   virtual MTAPIRES  BindingsShift(const UINT pos,const int shift)=0;
   virtual UINT      BindingsTotal(void) const=0;
   virtual LPCWSTR   BindingsNext(const UINT pos) const=0;
  };
//+------------------------------------------------------------------+
//| Time config events notification interface                        |
//+------------------------------------------------------------------+
class IMTConServerSink
  {
public:
   virtual void      OnConServerAdd(const IMTConServer*    /*server*/) {  }
   virtual void      OnConServerUpdate(const IMTConServer* /*server*/) {  }
   virtual void      OnConServerDelete(const IMTConServer* /*server*/) {  }
   virtual void      OnConServerSync(void)                             {  }
  };
//+------------------------------------------------------------------+
