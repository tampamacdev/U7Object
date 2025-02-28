# VALA Code Assistant Guide

## Build Commands
- Build: `./buildrun.sh`
- Clean build: `rm -rf build && ./buildrun.sh`
- Run executable: `./build/websocket_endpoint`
- Debug: Run with `G_MESSAGES_DEBUG=all`

## Code Style Guidelines
- **Naming**: Classes use PascalCase with U7 prefix (U7Array, U7Object)
- **Methods**: Use snake_case (deep_copy, get_value, to_string)
- **Types**: Strong typing with generics (Gee.ArrayList<T>)
- **Inheritance**: U7PropertyList serves as base class for many objects
- **Constructors**: Use Object(...) pattern for property initialization
- **Error handling**: Free resources in catch blocks and return error
- **Memory**: Use reference counting with proper unref() calls
- **Threading**: Always protect shared resources with mutex locks
- **Documentation**: Add comments for public methods and complex logic
- **Bridge code**: Keep C bridge interfaces consistent for API stability

## Project Architecture
- Vala with GObject/GLib backend
- JSON-GLib for JSON handling
- Gee for collections
- Mongoose for WebSocket implementation
- Cross-platform support (Linux, macOS, Windows)