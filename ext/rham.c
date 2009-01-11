#include "ruby.h"
#include <hamlib/rig.h>
/*
#include "misc.h"
#include "iofunc.h"
#include "serial.h"
#include "sprintflst.h"
*/

static VALUE rb_cRham;

/*
  int (*rig_init) (RIG * rig);
  int (*rig_cleanup) (RIG * rig);
  int (*rig_open) (RIG * rig);
  int (*rig_close) (RIG * rig);
*/

static void rig_mark(RIG *my_rig){
}

static void rig_free(RIG *my_rig){
	//spike_free(s);
}

static VALUE rig_allocate(VALUE klass){
	RIG *my_rig;
	rig_model_t my_model = RIG_MODEL_DUMMY;
	
	my_rig = rig_init(my_model);
	return Data_Wrap_Struct(klass, rig_mark, rig_free, my_rig);
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
	//rb_define_method(rb_cSpike, "set_spike", rb_set_spike, 0);
	//rb_define_method(rb_cSpike, "init_fuzz", rb_init_fuzzing, 0);
	//rb_define_method(rb_cSpike, "cstring", rb_cstring, 1);
	//rb_define_method(rb_cSpike, "unistring", rb_unistring, 1);
}
