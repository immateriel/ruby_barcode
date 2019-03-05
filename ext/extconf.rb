require 'mkmf'

$LDFLAGS += " -lbarcode"

extension_name = 'barcode'
dir_config(extension_name)
create_makefile(extension_name)
