void main() {
    // Print socket option constants
    stdout.printf("Socket constants check\n");
    
    // Add the constants manually
    const int SOL_SOCKET = 1;
    const int SO_REUSEADDR = 2;
    
    stdout.printf("Defined manually:\n");
    stdout.printf("SOL_SOCKET: %d\n", SOL_SOCKET);
    stdout.printf("SO_REUSEADDR: %d\n", SO_REUSEADDR);
}
