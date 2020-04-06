#include "MessageManager.h"

#include "globals.hh"

#include <stdarg.h>

MessageManager::MessageManager( void )
    : verbose( NORMAL ), indent( 0 ), tab_width( 2 )
{
}

MessageManager *MessageManager::GetManager( void )
{
    static MessageManager msg_manager;
    return &msg_manager;
}

void MessageManager::Print( int verb, const char *msg )
{
    if( verbose >= verb )
    {
        for( int i = 0; i < tab_width*indent; i++ )
            G4cout << ' ';
        G4cout << msg << std::flush;
    }
}

void MessageManager::Message( int verb, const char *fmt, ... )
{
    static const int mb_size = 1024;
    static char msgbuf[mb_size];

    va_list ap;
    va_start( ap, fmt );
    vsnprintf( msgbuf, mb_size-1, fmt, ap );
    va_end( ap );

    MessageManager *mgr = MessageManager::GetManager();
    mgr->Print( verb, msgbuf );
}

void MessageManager::Message( const char *fmt, ... )
{
    static const int mb_size = 1024;
    static char msgbuf[mb_size];

    va_list ap;
    va_start( ap, fmt );
    vsnprintf( msgbuf, mb_size-1, fmt, ap );
    va_end( ap );

    MessageManager *mgr = MessageManager::GetManager();
    mgr->Print( NORMAL, msgbuf );
}

void MessageManager::Warning( const char *fmt, ... )
{
    static const int mb_size = 1024;
    static char msgbuf[mb_size];

    va_list ap;
    va_start( ap, fmt );
    vsnprintf( msgbuf, mb_size-1, fmt, ap );
    va_end( ap );

    G4String warn = "Warning: ";
    warn += msgbuf;
    warn = C_YEL + warn + C_RET;

    MessageManager *mgr = MessageManager::GetManager();
    mgr->Print( WARNING, warn.c_str() );
}

void MessageManager::Error( const char *fmt, ... )
{
    static const int mb_size = 1024;
    static char msgbuf[mb_size];

    va_list ap;
    va_start( ap, fmt );
    vsnprintf( msgbuf, mb_size-1, fmt, ap );
    va_end( ap );

    G4String err = "Error: ";
    err += msgbuf;
    err = C_RED + err + C_RET;

    MessageManager *mgr = MessageManager::GetManager();
    mgr->Print( ERROR, err.c_str() );
}


