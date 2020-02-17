#define CLIENTICON 1

extern   void ClientPaint( HWND hWnd, USHORT msg,
                           MPARAM mp1, MPARAM mp2 );

MRESULT EXPENTRY ClientWndProc( HWND, USHORT, MPARAM, MPARAM );

int main( void );

char                szMessage[] = " Client App ";
char                szPClass[] = "PClass";
HAB                 hAB;
HMQ                 hmqClient;
HWND                hPanelWnd;
HWND                hPanelFrm;
char                szTraceBuf[81];
