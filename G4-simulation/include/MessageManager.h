#ifndef __MESSAGE_MANAGER_H__
#define __MESSAGE_MANAGER_H__

#define C_RED   "\033[1;31m"
#define C_GRN   "\033[1;32m"
#define C_YEL   "\033[1;33m"
#define C_BLU   "\033[1;34m"
#define C_MAZ   "\033[1;35m"
#define C_SKY   "\033[1;36m"
#define C_WHI   "\033[1;37m"
#define C_RET   "\033[0;39m"

/*
extern void message( int, const char *, ... );
extern void message( const char *, ... );
extern void warning( const char *, ... );
extern void error  ( const char *, ... );
*/

class MessageManager {
public:
    enum MSG_LEVEL{ QUIET = 0, ERROR = 1, WARNING = 2, NORMAL = 3, PARAM = 4, DEBUG = 5 };

private:
    int verbose;
    int indent;
    int tab_width;

public:
    static MessageManager *GetManager( void );

    int  GetVerbose( void ){ return verbose; }
    void SetVerbose( int verb ){ verbose = verb; }

    void Print  ( int verb, const char *msg );
    static void Message( int verb, const char *fmt, ... );
    static void Message( const char *fmt, ... );
    static void Warning( const char *fmt, ... );
    static void Error  ( const char *fmt, ... );

    void SetIndent( int i ){ if( i >= 0 ) indent = i; }
    int  GetIndent( void  ){ return indent; }

    void IndentIncrement( void ){ ++indent; }
    void IndentDecrement( void ){ if( indent > 0 ) --indent; }

    void operator++( int ){ IndentIncrement(); }
    void operator--( int ){ IndentDecrement(); }

private:
    MessageManager( void );
};

#define PMessage MessageManager::Message
#define PWarning MessageManager::Warning
#define PError   MessageManager::Error

#endif
