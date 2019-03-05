require 'barcode'
require 'rmagick'

barcode = Barcode::Item.new("9782377643837")
barcode.encode(Barcode::BARCODE_EAN)
barcode.position(1024,512,0,0,0.0)

rd, wr = IO.pipe
barcode.print(wr,Barcode::BARCODE_OUT_EPS)
wr.close
image = Magick::Image.read(rd) { self.format = "eps" }
image[0].write("test.png")
