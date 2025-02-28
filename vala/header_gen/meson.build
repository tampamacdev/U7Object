project('header_gen', 'vala')

vala_sources = [
    '../websocket_endpoint.vala',
    '../U7Object.vala',
    '../U7String.vala',
    '../U7Number.vala',
    '../U7Array.vala',
    '../U7Dictionary.vala',
    '../U7Date.vala',
    '../U7Utility.vala',
    '../U7Data.vala',
    '../U7PropertyList.vala',
    '../U7Error.vala'
]

vala_compiler = find_program('valac')
vala_args = [
    '-C',  # Output C code only, no compilation or linking
    '--pkg', 'posix',
    '--pkg', 'gee-0.8',
    '--pkg', 'json-glib-1.0',
    '--vapidir', meson.current_source_dir() / '..',
    '--Xcc=-I' + (meson.current_source_dir() / '..')  # For u7_bridge.h if included
]

custom_target(
    'u7_api_header',
    input: vala_sources,
    output: 'u7_api.h',
    command: [vala_compiler, '--header', '@OUTPUT@', '@INPUT@'] + vala_args,
    depend_files: vala_sources,
    build_by_default: true
)