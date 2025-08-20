project('libpicotui', 'c',
  version: '0.1.0',
  default_options: ['c_std=gnu2x', 'warning_level=3'])

unibilium_dep = dependency('unibilium', required: true)

libpicotui = library(
  'picotui',
  ['src/picotui.c'],
  dependencies: [unibilium_dep],
  install: true,
  version: meson.project_version(),
  soversion: '0'
)

install_headers('src/picotui.h', subdir: 'picotui')

executable('picotui-demo',
  'src/demo.c',
  link_with: libpicotui,
  dependencies: [unibilium_dep],
  install: true)

pkgconfig = import('pkgconfig')
pkgconfig.generate(
  name: 'libpicotui',
  filebase: 'picotui',
  description: 'Minimal TUI helper (scroll-region pinned bottom UI) using unibilium',
  version: meson.project_version(),
  libraries: libpicotui,
  requires: 'unibilium'
)

