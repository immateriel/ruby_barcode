#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <barcode.h>

#include <ruby.h>
#include <ruby/io.h>

/* ruby binding */

typedef struct _c_barcode {
    struct Barcode_Item * item;
} c_barcode;


void rb_barcode_free(void* data)
{
    c_barcode *barcode = (c_barcode *)data;
    if (barcode->item)
        Barcode_Delete(barcode->item);
    free(barcode);
}

static const rb_data_type_t rb_barcode_type = {
    .wrap_struct_name = "barcode",
    .function = {
        .dfree = rb_barcode_free,
        /* probably should set .dsize but I don't know how to write it for mpz_t... */
    },
    .flags = RUBY_TYPED_FREE_IMMEDIATELY,
};


/* GMP::Integer.allocate */
VALUE rb_barcode_c_alloc(VALUE self)
{
    c_barcode * data = malloc(sizeof(c_barcode));
    data->item = NULL;

    return TypedData_Wrap_Struct(self, &rb_barcode_type, data);
}

VALUE rb_barcode_m_initialize(VALUE self, VALUE rb_str)
{
    c_barcode *data;
    char* cstr;
    TypedData_Get_Struct(self, c_barcode, &rb_barcode_type, data);

    Check_Type(rb_str, T_STRING);

    cstr = StringValueCStr(rb_str);
    data->item = Barcode_Create(cstr);
    return self;
}

VALUE rb_barcode_m_encode(VALUE self, VALUE rb_flags)
{
    c_barcode *data;
    int flags, res;
    TypedData_Get_Struct(self, c_barcode, &rb_barcode_type, data);

    Check_Type(rb_flags, T_FIXNUM);

    flags = FIX2INT(rb_flags);
    res = Barcode_Encode(data->item, flags);
    return INT2FIX(res);
}

VALUE rb_barcode_m_print(VALUE self, VALUE rb_io, VALUE rb_flags) {
    c_barcode *data;
    rb_io_t *fptr;
    int flags, res;
    FILE *file;

    TypedData_Get_Struct(self, c_barcode, &rb_barcode_type, data);

    Check_Type(rb_flags, T_FIXNUM);

    if (rb_obj_is_kind_of(rb_io, rb_cIO) == Qfalse)
        rb_raise(rb_eTypeError, "need an IO object");

    GetOpenFile(rb_io, fptr);
    rb_io_check_writable(fptr);
    file = rb_io_stdio_file(fptr);
    flags = FIX2INT(rb_flags);
    res = Barcode_Print(data->item, file, flags);
    return INT2FIX(res);
}

VALUE rb_barcode_m_position(VALUE self, VALUE rb_w, VALUE rb_h, VALUE rb_x, VALUE rb_y, VALUE rb_scale) {
    c_barcode *data;
    int res, w, h, x, y;
    TypedData_Get_Struct(self, c_barcode, &rb_barcode_type, data);

    Check_Type(rb_w, T_FIXNUM);
    Check_Type(rb_h, T_FIXNUM);
    Check_Type(rb_x, T_FIXNUM);
    Check_Type(rb_y, T_FIXNUM);
    Check_Type(rb_scale, T_FLOAT);

    w = FIX2INT(rb_w);
    h = FIX2INT(rb_h);
    x = FIX2INT(rb_x);
    y = FIX2INT(rb_y);

    res = Barcode_Position(data->item,w,h,x,y,RFLOAT_VALUE(rb_scale));
    return INT2FIX(res);
}

VALUE cBarcode;
VALUE cItem;

/* entry point */
void Init_barcode()
{
    cBarcode = rb_define_module("Barcode");
    cItem = rb_define_class_under(cBarcode, "Item", rb_cData);
    rb_define_alloc_func(cItem, rb_barcode_c_alloc);
    rb_define_method(cItem, "initialize", rb_barcode_m_initialize, 1);
    rb_define_method(cItem, "encode", rb_barcode_m_encode, 1);
    rb_define_method(cItem, "position", rb_barcode_m_position, 5);
    rb_define_method(cItem, "print", rb_barcode_m_print, 2);
}
