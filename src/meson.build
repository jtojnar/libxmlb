# this seems redundant, but it allows us to use libxmlb as a subproject
if meson.project_name() != 'libxmlb'

libxmlbstatic = static_library(
  'xmlbstatic',
  sources : [
    'xb-builder.c',
    'xb-builder-node.c',
    'xb-builder-source.c',
    'xb-machine.c',
    'xb-node.c',
    'xb-opcode.c',
    'xb-silo.c',
    'xb-silo-export.c',
    'xb-silo-query.c',
    'xb-string.c',
  ],
  include_directories : [
    configinc,
  ],
  dependencies : [
    gio,
    uuid,
  ],
)

else

libxmlb_version_h = configure_file(
  input : 'xb-version.h.in',
  output : 'xb-version.h',
  configuration : conf
)

install_headers(
  'xmlb.h',
  subdir : 'libxmlb-1',
)

install_headers([
    'xb-builder.h',
    'xb-builder-node.h',
    'xb-builder-source.h',
    'xb-machine.h',
    'xb-node.h',
    'xb-opcode.h',
    'xb-silo-export.h',
    'xb-silo.h',
    'xb-silo-query.h',
    'xb-string.h',
    libxmlb_version_h,
  ],
  subdir : 'libxmlb-1/libxmlb',
)

mapfile = 'libxmlb.map'
vflag = '-Wl,--version-script,@0@/@1@'.format(meson.current_source_dir(), mapfile)
libxmlb = shared_library(
  'xmlb',
  sources : [
    'xb-builder.c',
    'xb-builder-node.c',
    'xb-builder-source.c',
    'xb-machine.c',
    'xb-opcode.c',
    'xb-node.c',
    'xb-silo.c',
    'xb-silo-export.c',
    'xb-silo-query.c',
    'xb-string.c',
  ],
  soversion : lt_current,
  version : lt_version,
  include_directories : [
    configinc,
  ],
  dependencies : [
    gio,
    uuid,
  ],
  link_args : vflag,
  link_depends : mapfile,
  install : true
)

xb_tool = executable(
  'xb-tool',
  sources : [
    'xb-tool.c',
  ],
  include_directories : [
    configinc,
  ],
  dependencies : [
    gio,
  ],
  link_with : [
    libxmlb,
  ],
  install : true,
  install_dir : libexecdir
)

pkgg = import('pkgconfig')
pkgg.generate(
  libraries : libxmlb,
  requires : [ 'gio-2.0' ],
  subdirs : 'libxmlb-1',
  version : meson.project_version(),
  name : 'libxmlb',
  filebase : 'xmlb',
  description : 'libxmlb is a library to create or query compressed XML files',
)

if get_option('introspection')
  gir = gnome.generate_gir(libxmlb,
    sources : [
      'xb-builder.c',
      'xb-builder.h',
      'xb-builder-node.c',
      'xb-builder-node.h',
      'xb-builder-source.c',
      'xb-builder-source.h',
      'xb-machine.c',
      'xb-machine.h',
      'xb-node.c',
      'xb-node.h',
      'xb-opcode.c',
      'xb-opcode.h',
      'xb-silo.c',
      'xb-silo.h',
      'xb-silo-export.c',
      'xb-silo-export.h',
      'xb-silo-query.c',
      'xb-silo-query.h',
      'xb-string.c',
      'xb-string.h',
    ],
    nsversion : '1.0',
    namespace : 'Xmlb',
    symbol_prefix : 'xb',
    identifier_prefix : 'Xb',
    export_packages : 'libxmlb',
    header : 'xmlb.h',
    dependencies : [
      gio,
    ],
    includes : [
      'Gio-2.0',
      'GObject-2.0',
    ],
    link_with : [
      libxmlb,
    ],
    install : true
  )

  # Verify the map file is correct -- note we can't actually use the generated
  # file for two reasons:
  #
  #  1. We don't hard depend on GObject Introspection
  #  2. The map file is required to build the lib that the GIR is built from
  #
  # To avoid the circular dep, and to ensure we don't change exported API
  # accidentaly actually check in a version of the version script to git.
  mapfile_target = custom_target('mapfile',
    input: gir[0],
    output: 'libxmlb.map',
    command: [
      join_paths(meson.current_source_dir(), 'generate-version-script.py'),
      'LIBXMLB',
      '@INPUT@',
      '@OUTPUT@',
    ],
  )
  diffcmd = find_program('diff')
  test('libxmlb-exported-api', diffcmd,
       args : [
        '-urNp',
        join_paths(meson.current_source_dir(), 'libxmlb.map'),
        mapfile_target,
        ],
      )
endif

if get_option('tests')
  testdatadir = join_paths(meson.source_root(), 'data')
  e = executable(
    'xb-self-test',
    sources : [
      'xb-builder.c',
      'xb-builder-node.c',
      'xb-builder-source.c',
      'xb-machine.c',
      'xb-node.c',
      'xb-opcode.c',
      'xb-self-test.c',
      'xb-silo.c',
      'xb-silo-export.c',
      'xb-silo-query.c',
      'xb-string.c',
    ],
    include_directories : [
      configinc,
    ],
    dependencies : [
      gio,
      uuid,
    ],
  )
  test('xb-self-test', e)
endif

endif # meson.project_name() == 'libxmlb'
