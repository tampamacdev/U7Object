vala/
├── meson.build
├── mongoose.h          # Mongoose header (assumed downloaded or provided)
├── mongoose.c          # Mongoose implementation (assumed downloaded or provided)
├── mongoose_vala_bridge.h      # Bridge header defining the interface
├── mongoose_vala_bridge.c      # Bridge implementation
└── websocket_endpoint.vala     # Vala application code


For macOS:

    Install homebrew if not installed: 
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

    run setup script: 
        
        ./target_setup_files/macos_setup.sh

For Ubuntu:

    run setup script: 

        ./target_setup_files/linux_setup.sh

For Windows:

    Download and install Package Manager for Arch Linux (pacman)

        https://www.msys2.org/

