project('websocket_endpoint', 'vala', 'c', version: '1.0.0')

c_sources = [
    'u7_glib.c',
    'mongoose.c',
    'mongoose_extras.c',
    'u7_notification_center.c',
    'mongoose_vala_bridge.c',
    'u7_bridge.c'
]

vala_sources = [
    'websocket_endpoint.vala',
    'U7Object.vala',
    'U7String.vala',
    'U7WebSocketManager.vala',
    'U7Utility.vala',
    'U7Number.vala',
    'U7MainEventLoop.vala',
    'U7Array.vala',
    'U7ThreadLoop.vala',
    'U7Dictionary.vala',
    'U7Date.vala',
    'U7Data.vala',
    'U7PropertyList.vala',
    'U7Error.vala',
    'U7Bridge.vala'
]

dependencies = [
    dependency('glib-2.0'),
    dependency('gobject-2.0'),
    dependency('threads'),  # Adds pthread support
    dependency('json-glib-1.0'),  # Added for Json support
    dependency('gee-0.8'),        # Added for Gee collections
    meson.get_compiler('c').find_library('c', required: true),  # POSIX via libc
]

# Platform-specific adjustments
if host_machine.system() == 'windows'
    # Use linker argument instead of dependency() for ws2_32
    ws2_32_dep = meson.get_compiler('c').find_library('ws2_32', required: true)
    dependencies += [ws2_32_dep]
    exe_name = 'websocket_endpoint'
else
    exe_name = 'websocket_endpoint'
endif


vala_args = [
    '--pkg', 'U7NotificationCenter',
    '--pkg', 'posix',           # POSIX bindings
    '--pkg', 'U7Bridge',        # Explicitly include U7Bridge.vapi
    '--header=u7_api.h',        # Generate C header
    '--vapidir', meson.current_source_dir()              # Look for .vapi files in current dir
]

if get_option('track_object_alloc')
    vala_args += ['-D', 'USE_OBJECT_TRACKING']
endif
if get_option('include_c_bridge_code')
    vala_args += ['-D', 'INCLUDE_C_BRIDGE_CODE']
endif



executable(
    exe_name,
    c_sources + vala_sources,
    dependencies: dependencies,
    include_directories: include_directories('.'),  # Just the current source dir
    vala_args: vala_args,
    install: false,
    c_args: ['-w']
)