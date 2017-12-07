//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include "MT5APITypes.h"
//+------------------------------------------------------------------+
//| MetaTrader 5 API return codes                                    |
//+------------------------------------------------------------------+
enum EnMTAPIRetcode
  {
//--- successfully codes
   MT_RET_OK                    =0,       // ok
   MT_RET_OK_NONE               =1,       // ok, no data
//--- common errors
   MT_RET_ERROR                 =2,       // Common error
   MT_RET_ERR_PARAMS            =3,       // Invalid parameters
   MT_RET_ERR_DATA              =4,       // Invalid data
   MT_RET_ERR_DISK              =5,       // Disk error
   MT_RET_ERR_MEM               =6,       // Memory error
   MT_RET_ERR_NETWORK           =7,       // Network error
   MT_RET_ERR_PERMISSIONS       =8,       // Not enough permissions
   MT_RET_ERR_TIMEOUT           =9,       // Operation timeout
   MT_RET_ERR_CONNECTION        =10,      // No connection
   MT_RET_ERR_NOSERVICE         =11,      // Service is not available
   MT_RET_ERR_FREQUENT          =12,      // Too frequent requests
   MT_RET_ERR_NOTFOUND          =13,      // Not found
   MT_RET_ERR_PARTIAL           =14,      // Partial error
   MT_RET_ERR_SHUTDOWN          =15,      // Server shutdown in progress
   MT_RET_ERR_CANCEL            =16,      // Operation has been canceled
   MT_RET_ERR_DUPLICATE         =17,      // Duplicate data
//--- authentication retcodes
   MT_RET_AUTH_CLIENT_INVALID   =1000,    // Invalid terminal type
   MT_RET_AUTH_ACCOUNT_INVALID  =1001,    // Invalid account
   MT_RET_AUTH_ACCOUNT_DISABLED =1002,    // Account disabled
   MT_RET_AUTH_ADVANCED         =1003,    // Advanced authorization necessary
   MT_RET_AUTH_CERTIFICATE      =1004,    // Certificate required
   MT_RET_AUTH_CERTIFICATE_BAD  =1005,    // Invalid certificate
   MT_RET_AUTH_NOTCONFIRMED     =1006,    // Certificate is not confirmed
   MT_RET_AUTH_SERVER_INTERNAL  =1007,    // Attempt to connect to non-access server
   MT_RET_AUTH_SERVER_BAD       =1008,    // Server isn't authenticated 
   MT_RET_AUTH_UPDATE_ONLY      =1009,    // Only updates available
   MT_RET_AUTH_CLIENT_OLD       =1010,    // Client has old version
   MT_RET_AUTH_MANAGER_NOCONFIG =1011,    // Manager account doesn't have manager config
   MT_RET_AUTH_MANAGER_IPBLOCK  =1012,    // IP address unallowed for manager
   MT_RET_AUTH_GROUP_INVALID    =1013,    // Group is not initialized (server restart neccesary)
   MT_RET_AUTH_CA_DISABLED      =1014,    // Certificate generation disabled
   MT_RET_AUTH_INVALID_ID       =1015,    // Invalid or disabled server id [check server's id]
   MT_RET_AUTH_INVALID_IP       =1016,    // Unallowed address [check server's ip address]
   MT_RET_AUTH_INVALID_TYPE     =1017,    // Invalid server type [check server's id and type]
   MT_RET_AUTH_SERVER_BUSY      =1018,    // Server is busy
   MT_RET_AUTH_SERVER_CERT      =1019,    // Invalid server certificate
   MT_RET_AUTH_ACCOUNT_UNKNOWN  =1020,    // Unknown account
   MT_RET_AUTH_SERVER_OLD       =1021,    // Old server version
   MT_RET_AUTH_SERVER_LIMIT     =1022,    // Server cannot be connected due to license limitation
   MT_RET_AUTH_MOBILE_DISABLED  =1023,    // Mobile connection aren't allowed in server license
   MT_RET_AUTH_MANAGER_TYPE     =1024,    // Connection type is not permitted for manager
   MT_RET_AUTH_DEMO_DISABLED    =1025,    // Demo allocation disabled
   MT_RET_AUTH_RESET_PASSWORD   =1026,    // Master password must be changed
//--- config management retcodes
   MT_RET_CFG_LAST_ADMIN        =2000,    // Last admin config deleting
   MT_RET_CFG_LAST_ADMIN_GROUP  =2001,    // Last admin group cannot be deleted
   MT_RET_CFG_NOT_EMPTY         =2003,    // Accounts or trades in group/symbol
   MT_RET_CFG_INVALID_RANGE     =2004,    // Invalid accounts or trades ranges
   MT_RET_CFG_NOT_MANAGER_LOGIN =2005,    // Manager account is not from manager group
   MT_RET_CFG_BUILTIN           =2006,    // Built-in protected config
   MT_RET_CFG_DUPLICATE         =2007,    // Configuration duplicate
   MT_RET_CFG_LIMIT_REACHED     =2008,    // Configuration limit reached
   MT_RET_CFG_NO_ACCESS_TO_MAIN =2009,    // Invalid network configuration
   MT_RET_CFG_DEALER_ID_EXIST   =2010,    // Dealer with same ID exists
   MT_RET_CFG_BIND_ADDR_EXIST   =2011,    // Bind address already exists
   MT_RET_CFG_WORKING_TRADE     =2012,    // Attempt to delete working trade server
   MT_RET_CFG_GATEWAY_NAME_EXIST=2013,    // Gateway with same name exists
   MT_RET_CFG_SWITCH_TO_BACKUP  =2014,    // Server must be switched to backup mode
   MT_RET_CFG_NO_BACKUP_MODULE  =2015,    // Backup server module is absent
   MT_RET_CFG_NO_TRADE_MODULE   =2016,    // Trade server module is absent
   MT_RET_CFG_NO_HISTORY_MODULE =2017,    // History server module is absent
   MT_RET_CFG_ANOTHER_SWITCH    =2018,    // Another switching process in progress
   MT_RET_CFG_NO_LICENSE_FILE   =2019,    // License file is absent
//--- client management retcodes
   MT_RET_USR_LAST_ADMIN        =3001,    // Last admin account deleting
   MT_RET_USR_LOGIN_EXHAUSTED   =3002,    // Logins range exhausted
   MT_RET_USR_LOGIN_PROHIBITED  =3003,    // Login reserved at another server
   MT_RET_USR_LOGIN_EXIST       =3004,    // Account already exists
   MT_RET_USR_SUICIDE           =3005,    // Attempt of self-deletion
   MT_RET_USR_INVALID_PASSWORD  =3006,    // Invalid account password
   MT_RET_USR_LIMIT_REACHED     =3007,    // Users limit reached
   MT_RET_USR_HAS_TRADES        =3008,    // Account has open trades
   MT_RET_USR_DIFFERENT_SERVERS =3009,    // Attempt to move account to different server
   MT_RET_USR_DIFFERENT_CURRENCY=3010,    // Attempt to move account to different currency group
   MT_RET_USR_IMPORT_BALANCE    =3011,    // Account balance import error
   MT_RET_USR_IMPORT_GROUP      =3012,    // Account import with invalid group
   MT_RET_USR_ACCOUNT_EXIST     =3013,    // Account already exist
//--- trades management retcodes
   MT_RET_TRADE_LIMIT_REACHED   =4001,    // Orders or deals limit reached
   MT_RET_TRADE_ORDER_EXIST     =4002,    // Order already exists
   MT_RET_TRADE_ORDER_EXHAUSTED =4003,    // Orders range exhausted
   MT_RET_TRADE_DEAL_EXHAUSTED  =4004,    // Deals range exhausted
   MT_RET_TRADE_MAX_MONEY       =4005,    // Money limit reached
//--- report generation retcodes
   MT_RET_REPORT_SNAPSHOT       =5001,    // Base snapshot error
   MT_RET_REPORT_NOTSUPPORTED   =5002,    // Method doesn't support for this report
   MT_RET_REPORT_NODATA         =5003,    // No report data
   MT_RET_REPORT_TEMPLATE_BAD   =5004,    // Bad template
   MT_RET_REPORT_TEMPLATE_END   =5005,    // End of template (template success processed)
   MT_RET_REPORT_INVALID_ROW    =5006,    // Invalid row size
   MT_RET_REPORT_LIMIT_REPEAT   =5007,    // Tag repeat limit reached
   MT_RET_REPORT_LIMIT_REPORT   =5008,    // Report size limit reached
//--- price history reports retcodes
   MT_RET_HST_SYMBOL_NOTFOUND   =6001,    // Symbol not found, try to restart history server
//--- trade request retcodes
   MT_RET_REQUEST_INWAY         =10001,   // Request on the way
   MT_RET_REQUEST_ACCEPTED      =10002,   // Request accepted
   MT_RET_REQUEST_PROCESS       =10003,   // Request processed
   MT_RET_REQUEST_REQUOTE       =10004,   // Request Requoted
   MT_RET_REQUEST_PRICES        =10005,   // Request Prices
   MT_RET_REQUEST_REJECT        =10006,   // Request rejected
   MT_RET_REQUEST_CANCEL        =10007,   // Request canceled
   MT_RET_REQUEST_PLACED        =10008,   // Order from requestplaced
   MT_RET_REQUEST_DONE          =10009,   // Request executed
   MT_RET_REQUEST_DONE_PARTIAL  =10010,   // Request executed partially
   MT_RET_REQUEST_ERROR         =10011,   // Request common error
   MT_RET_REQUEST_TIMEOUT       =10012,   // Request timeout
   MT_RET_REQUEST_INVALID       =10013,   // Invalid request
   MT_RET_REQUEST_INVALID_VOLUME=10014,   // Invalid volume
   MT_RET_REQUEST_INVALID_PRICE =10015,   // Invalid price
   MT_RET_REQUEST_INVALID_STOPS =10016,   // Invalid stops or price
   MT_RET_REQUEST_TRADE_DISABLED=10017,   // Trade disabled
   MT_RET_REQUEST_MARKET_CLOSED =10018,   // Market closed
   MT_RET_REQUEST_NO_MONEY      =10019,   // Not enough money
   MT_RET_REQUEST_PRICE_CHANGED =10020,   // Price changed
   MT_RET_REQUEST_PRICE_OFF     =10021,   // No prices
   MT_RET_REQUEST_INVALID_EXP   =10022,   // Invalid order expiration
   MT_RET_REQUEST_ORDER_CHANGED =10023,   // Order has been changed already
   MT_RET_REQUEST_TOO_MANY      =10024,   // Too many trade requests
   MT_RET_REQUEST_NO_CHANGES    =10025,   // Request doesn't contain changes
   MT_RET_REQUEST_AT_DISABLED_SERVER=10026, // AutoTrading disabled by server
   MT_RET_REQUEST_AT_DISABLED_CLIENT=10027, // AutoTrading disabled by client
   MT_RET_REQUEST_LOCKED        =10028,     // Request locked by dealer
   MT_RET_REQUEST_FROZEN        =10029,     // Order or position frozen
   MT_RET_REQUEST_INVALID_FILL  =10030,     // Unsupported filling mode
   MT_RET_REQUEST_CONNECTION    =10031,     // No connection
   MT_RET_REQUEST_ONLY_REAL     =10032,     // Allowed for real accounts only
   MT_RET_REQUEST_LIMIT_ORDERS  =10033,     // Orders limit reached
   MT_RET_REQUEST_LIMIT_VOLUME  =10034,     // Volume limit reached
   MT_RET_REQUEST_INVALID_ORDER =10035,     // Invalid or prohibited order type
   MT_RET_REQUEST_POSITION_CLOSED=10036,    // Position doesn't exist
   MT_RET_REQUEST_EXECUTION_SKIPPED   =10037,  // Execution doesn't belong to this server
   MT_RET_REQUEST_INVALID_CLOSE_VOLUME=10038,  // Volume to be closed exceeds the position volume
   MT_RET_REQUEST_CLOSE_ORDER_EXIST   =10039,  // Order to close this position already exists
   MT_RET_REQUEST_LIMIT_POSITIONS=10040,    // Positions limit reached
   MT_RET_REQUEST_REJECT_CANCEL  =10041,    // Request rejected, order will be canceled
   MT_RET_REQUEST_LONG_ONLY      =10042,    // Only long positions are allowed
   MT_RET_REQUEST_SHORT_ONLY     =10043,    // Only short positions are allowed
   MT_RET_REQUEST_CLOSE_ONLY     =10044,    // Only position closing is allowed
//--- dealer retcodes
   MT_RET_REQUEST_RETURN        =11000,     // Request returned in queue
   MT_RET_REQUEST_DONE_CANCEL   =11001,     // Request partially filled, remainder has been canceled
   MT_RET_REQUEST_REQUOTE_RETURN=11002,     // Request requoted and returned in queue with new prices
//--- API retcodes
   MT_RET_ERR_NOTIMPLEMENT      =12000,     // Not implement yet
   MT_RET_ERR_NOTMAIN           =12001,     // Operation must be performed on main server
   MT_RET_ERR_NOTSUPPORTED      =12002,     // Command doesn't supported
   MT_RET_ERR_DEADLOCK          =12003,     // Operation canceled due possible deadlock
   MT_RET_ERR_LOCKED            =12004      // Operation on locked entity
  };
//+------------------------------------------------------------------+
