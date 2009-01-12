#include "ruby.h"
#include <hamlib/rig.h>

static VALUE rb_cRham;

static void rig_mark(RIG *my_rig){
}

static void rig_free(RIG *my_rig){
	rig_cleanup(my_rig);	
}

static VALUE rig_allocate(VALUE klass){
	RIG *my_rig;
	//rig_model_t my_model = RIG_MODEL_DUMMY; //RIG_MODEL_FT847;
	rig_model_t my_model = RIG_MODEL_FT847;	

	my_rig = rig_init(my_model);
	return Data_Wrap_Struct(klass, rig_mark, rig_free, my_rig);
}

static VALUE rb_rig_open(VALUE self){
	RIG *my_rig;
	char *serial = "/dev/ttyS0"

	Data_Get_Struct(self, RIG, my_rig);
	strncpy(my_rig->state.rigport.pathname, rig_file, 100);
	

	return INT2NUM(rig_open(my_rig));
}

static VALUE rb_rig_close(VALUE self){
	RIG *my_rig;

	Data_Get_Struct(self, RIG, my_rig);
	return INT2NUM(rig_close(my_rig));
}

static VALUE rb_rig_get_info(VALUE self){
	RIG *my_rig;

	Data_Get_Struct(self, RIG, my_rig);
	return rb_str_new2(rig_get_info(my_rig));
}

static VALUE rb_rig_get_freq(VALUE self){
	RIG *my_rig;
	freq_t *freq;

	Data_Get_Struct(self, RIG, my_rig);
	return INT2NUM(rig_get_freq(my_rig, VFO_CURR, freq));
}

/*
static VALUE rb_set_spike(VALUE self){
	struct spike *s;

	Data_Get_Struct(self, struct spike, s);
	return INT2NUM(setspike(s));
}

static VALUE rb_init_fuzzing(VALUE self){
	s_init_fuzzing();
	return Qnil;
}
*/

void Init_rham() {
	rb_cRham = rb_define_class("Rham", rb_cObject);
	rb_define_alloc_func(rb_cRham, rig_allocate);
	rb_define_method(rb_cRham, "rig_open", rb_rig_open, 0);
	rb_define_method(rb_cRham, "rig_close", rb_rig_close, 0);
	rb_define_method(rb_cRham, "rig_get_info", rb_rig_get_info, 0);
	rb_define_method(rb_cRham, "rig_get_freq", rb_rig_get_freq, 0);
	//rb_define_method(rb_cSpike, "set_spike", rb_set_spike, 0);
	//rb_define_method(rb_cSpike, "init_fuzz", rb_init_fuzzing, 0);
	//rb_define_method(rb_cSpike, "cstring", rb_cstring, 1);
	//rb_define_method(rb_cSpike, "unistring", rb_unistring, 1);
}
