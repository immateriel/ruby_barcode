ENV['PATH'] = [File.expand_path(
    File.join(File.dirname(__FILE__), "..", "ext")
), ENV['PATH']].compact.join(';') if RbConfig::CONFIG['host_os'] =~ /(mswin|mingw|mingw32)/i

require File.dirname(__FILE__) + '/../ext/barcode'

module Barcode
  BARCODE_DEFAULT_FLAGS = 0x00000000
  BARCODE_ENCODING_MASK = 0x000000ff # 256 possibilites...
  BARCODE_NO_ASCII = 0x00000100 # avoid text in output
  BARCODE_NO_CHECKSUM = 0x00000200 # avoid checksum in output
  BARCODE_OUTPUT_MASK = 0x000ff000 # 256 output types
  BARCODE_OUT_EPS = 0x00001000
  BARCODE_OUT_PS = 0x00002000
  BARCODE_OUT_PCL = 0x00004000 # by Andrea Scopece
  BARCODE_OUT_PCL_III = 0x0000C000
  BARCODE_OUT_SVG = 0x00010000
  BARCODE_OUT_NOHEADERS = 0x00100000 # no header nor footer */

  BARCODE_ANY = 0 # choose best-fit
  BARCODE_EAN = 1
  BARCODE_UPC = 2 # upc == 12-digit ean
  BARCODE_ISBN = 3 # isbn numbers (still EAN13)
  BARCODE_39 = 4 # code 39
  BARCODE_128 = 5 # code 128 (a,b,c: autoselection)
  BARCODE_128C = 6 # code 128 (compact form for digits)
  BARCODE_128B = 7 # code 128, full printable ascii
  BARCODE_I25 = 8 # interleaved 2 of 5 (only digits)
  BARCODE_128RAW = 9 # Raw code 128 (by Leonid A. Broukhis)
  BARCODE_CBR = 10 # Codabar (by Leonid A. Broukhis)
  BARCODE_MSI = 11 # MSI (by Leonid A. Broukhis)
  BARCODE_PLS = 12 # Plessey (by Leonid A. Broukhis)
  BARCODE_93 = 13 # code 93 (by Nathan D. Holmes)
  BARCODE_11 = 14 # code 11 (USD-8)
  BARCODE_39EXT = 15
end