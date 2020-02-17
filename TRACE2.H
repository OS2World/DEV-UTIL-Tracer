/************************************************************************

  TRACER.H


    To use TRACER, follow these 5 steps.


    1. Include this header in your program.
       Includes necessary macros. 

    2. Add macro TRACERVARIABLES above main().
       Defines necessary variables / defines.-

    3. Add macro TRACERHELLO in your WM_CREATE
       Put between WM_CREATE and break;
       Initiates handshaking with debugger.

    4. Add macro TRACERATTACH in your WndProc.
       Put as a seperate case in your WndProc.
       Completes handshaking with debugger.

    !!! When placing the TRACERATTACH in your
        window procedure, don't forget the
        break; statement after it. !!!

    5. Use macro TRACER("string") freely.
       This is the debug statement.



    Note:
    Tracer macros are included in your program
    only if the constant TDEBUG is defined prior
    to the inclusion of tracer.h.  If TDEBUG is
    not defined, the Tracer macros translate into
    nothing.


    Note:
    You may need to include EXTERNTRACERVARS
    in secondary modules if you want to call
    TRACER from those modules.


    Note:

    In the TRACERHELLO macro, there is a param
    called hWnd.  You need to pass your window
    handle to me so that I can send mine back
    to you.  You may need to change "hWnd" to
    whatever your wndproc parameter name is
    for window handle ( e.g. MyhWnd ).

************************************************************************/



#define TRACER_MEM     "\\SHAREMEM\\TRACER.DAT"
#define TRACER_SEMAPHORE   "\\SEM32\\TRACER.SEM"


// Step 1 - INCLUDE THIS FILE IN YOUR APP CODE AS FOLLOWS

//#include <tracer.h>


#define TRACER_REQUEST_HANDLE   WM_USER + 501
#define TRACER_RECEIVE_HANDLE   WM_USER + 502
#define TRACER_REQUEST_ACTION   WM_USER + 503
#define TRACER_GOODBYE          WM_USER + 504
#define TRACER_MYCLOSE          WM_USER + 505


// Step 2 - INCLUDE THE TRACERVARIABLES STATEMENT IN YOUR
//                       DECLARATION SECTION

#ifdef TDEBUG
#define TRACERVARIABLES                    \
         PVOID      pTracerBaseAddr;       \
         HMTX       hTracerSysSem;         \
         BOOL       bTracerConnected;      \
         HWND       hTracerWnd;            \
         PSZ        pTracerString;
#else
#define TRACERVARIABLES
#endif




// Step 3 - INCLUDE THE TRACERHELLO STATEMENT IN YOUR
//                      WM_CREATE MESSAGE


#ifdef TDEBUG

#define TRACERHELLO                                        \
WinBroadcastMsg( hWnd, TRACER_REQUEST_HANDLE,              \
                    MPFROMHWND( hWnd ), 0L,                \
                        BMSG_FRAMEONLY | BMSG_POSTQUEUE );
#else
#define TRACERHELLO

#endif


// Step 4 - INCLUDE THE TRACERATTACH STATEMENT IN YOUR
//                        MESSAGE WNDPROC


#ifdef TDEBUG

#define TRACERATTACH                                                    \
case TRACER_RECEIVE_HANDLE:                                             \
if ( bTracerConnected )                                                 \
    break;                                                              \
hTracerWnd = HWNDFROMMP( mp1 );                                         \
bTracerConnected = 1;                                                   \
if ( DosGetNamedSharedMem( &pTracerBaseAddr,TRACER_MEM,fPERM ) )        \
    bTracerConnected = 0;                                               \
if ( DosOpenMutexSem(TRACER_SEMAPHORE, &hTracerSysSem ) )               \
    bTracerConnected = 0;                                               \

#else
#define TRACERATTACH
#endif



// Step 5 - THEN USE THE TRACER("HELLO, WORLD") MACRO FREELY

#ifdef TDEBUG

#define TRACER(s)                                                  \
 if ( bTracerConnected )                                           \
 {                                                                 \
 pTracerString = (PSZ) pTracerBaseAddr;    	                   \
 DosRequestMutexSem( hTracerSysSem, -1L );                         \
 strncpy( pTracerString, s, 80 );                                  \
 pTracerString[80] = '\0';                                         \
 WinSendMsg( hTracerWnd, TRACER_REQUEST_ACTION, 0L, 0L );          \
 DosReleaseMutexSem( hTracerSysSem );                              \
 }
#else

#define TRACER(s) {}

#endif


#define EXTERNTRACERVARS                                           \
extern unsigned short      sTracerSelector;                        \
extern          HSYSSEM    hTracerSysSem;                          \
extern          BOOL       bTracerConnected;                       \
extern          char far * szSelector_string;                      \
extern          HWND       hTracerWnd;

extern   PVOID      pTracerBaseAddr;                               \
extern   HMTX       hTracerSysSem;                                 \
extern   BOOL       bTracerConnected;                              \
extern   HWND       hTracerWnd;
extern   PSZ        pTracerString;

